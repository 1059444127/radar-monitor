// LeuzeSocketComm.cpp: implementation of the CLeuzeSocketComm class.
//
//////////////////////////////////////////////////////////////////////

#include "LeuzeSocketComm.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLeuzeSocketComm::CLeuzeSocketComm()
{
	findStartTag=false;
	findStopTag=false;
	ReSetTagBuffer();
	m_pFile=NULL;
}

CLeuzeSocketComm::~CLeuzeSocketComm()
{
	closesocket(m_socket);
	WSACleanup();

}
void CLeuzeSocketComm::SetTagBuffer(unsigned char tag)
{
	if(tagBufferNumber==3)
	{
		tagBuffer[0]=tagBuffer[1];
		tagBuffer[1]=tagBuffer[2];
		tagBufferNumber=2;
	}
	tagBuffer[tagBufferNumber]=tag;
	tagBufferNumber++;
}
void CLeuzeSocketComm::ReSetTagBuffer()
{
	tagBuffer[0]=0xff;
	tagBuffer[1]=0xff;
	tagBuffer[2]=0xff;

	tagBufferNumber=0;
}

int  CLeuzeSocketComm::StartRadar(void)
{
	if(m_saveRawData)
	{
		m_pFile=fopen(m_rawDataFile,"w");
		if(!m_pFile)
			return false;
	}

	//���SOCKET�汾
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	
	wVersionRequested = MAKEWORD( 1, 1 );
	
	err = WSAStartup( wVersionRequested, &wsaData );
	if ( err != 0 ) 
	{
		return -1;
	}
	
	if ( LOBYTE( wsaData.wVersion ) != 1 ||
        HIBYTE( wsaData.wVersion ) != 1 ) 
	{
		WSACleanup( );
		return -1; 
	}
	
	//����
	m_socket=socket(AF_INET,SOCK_STREAM,0);
	
	
	int TimeOut=1000;//���ý��ճ�ʱ 
	
	if(::setsockopt(m_socket,SOL_SOCKET,SO_RCVTIMEO,(char *)&TimeOut,sizeof(int))==SOCKET_ERROR){
		
		return -1;
		
	}
	
	SOCKADDR_IN addrSrv;
	//addrSrv.sin_addr.S_un.S_addr=inet_addr("127.0.0.1");
	//addrSrv.sin_addr.S_un.S_addr=inet_addr("10.13.15.60");
	addrSrv.sin_addr.S_un.S_addr=inet_addr(m_ip);
	
	
	addrSrv.sin_family=AF_INET;
	addrSrv.sin_port=htons(m_port);
	int ret=connect(m_socket,(SOCKADDR*)&addrSrv,sizeof(SOCKADDR));
	if(ret == SOCKET_ERROR )
		return -1;
	
	//�������ײ��״��ʼ��������
	char buf[5];
	buf[0]=0x02;
	buf[1]='S';
	buf[2]='B';
	buf[3]='+';
	buf[4]=0x03;
	int recvCnt=send(m_socket,buf,5,0);

	return 1;
	
}
int	 CLeuzeSocketComm::CloseRadar(void)
{
	//�������ײ��״������������
	char buf[5];
	buf[0]=0x02;
	buf[1]='S';
	buf[2]='B';
	buf[3]='-';		//�ؼ������
	buf[4]=0x03;
	int recvCnt=send(m_socket,buf,5,0);

	if(m_saveRawData)
	{
		if(m_pFile!=NULL)
		{
			//�ر��ļ�
			fclose(m_pFile);
			m_pFile=NULL;
		}
	}
	
	closesocket(m_socket);
	WSACleanup();
	ClearRawData();
	return 1;
}

bool CLeuzeSocketComm::GetRawData(DataFrame * pData)
{
	//����Ļ����С�������ӳ������й�ϵ��
	//ͬʱҲ���״�Ʒ���ͺŵĲ�ͬ����ͬ���������ó�250�ͻ��ǻ����ӳ٣�Ŀǰ���ó�500
	char recvBuf[500];
	int recvCnt=recv(m_socket,recvBuf,500,0);

	if(recvCnt<=0)
		return false;
	return ProcessData(recvBuf,recvCnt, pData);
	
}
bool CLeuzeSocketComm::CheckStartTag()
{
	if(tagBufferNumber!=3)
		return false;

	if(tagBuffer[0]==0x00
		&& tagBuffer[1]==0x00
		&& tagBuffer[2]!=0xff
		&& tagBuffer[2]!=0x00)
	{
		return true;
	}
	else
		return false;
	
	
}
bool CLeuzeSocketComm::CheckStopTag()
{
	if(tagBufferNumber!=3)
		return false;

	if(tagBuffer[0]==0x00
		&& tagBuffer[1]==0x00
		&& tagBuffer[2]==0x00)
	{
		return true;
	}
	else
		return false;
}
bool CLeuzeSocketComm::ProcessData(char * recvBuf,int size,DataFrame * pData)
{
	char * ptr=recvBuf;
	bool rettag=false;
	char * p;
	unsigned char byte;
	
	for(int i=0;i<size;i+=1,ptr+=1)
	{
		p=ptr;
		byte=*p;
		SetTagBuffer(byte);
		if(CheckStartTag())
		{
			findStartTag=true;
			m_rawDataBuff.push_back(byte);//ע�⣬���ﱣ��������rawdatabuffʼ��û����ʼ��־�������ֽڣ�0x00,0x00��
			ReSetTagBuffer();
			continue;
		}
		if(findStartTag)
		{
			m_rawDataBuff.push_back(byte);
			if(CheckStopTag())
			{
				findStopTag=true;					
				rettag=LoadData(pData);				//�������ݣ����ԭʼ����
				//�����ļ�,������־
				if(m_saveRawData)
				{
					fprintf(m_pFile,"-1\n");
				}

				findStartTag=false;					//�ҵ�������־������Ҫ����ʼ��־��
				ReSetTagBuffer();
				continue;
			}
			
		}
	}
	return rettag;
}
bool CLeuzeSocketComm::LoadData(DataFrame *pData)
{
	if(m_rawDataBuff.size()==0)
	{
		ClearRawData();//װ��һ�Σ��ͱ������ԭʼ���ݻ���
		return false;
	}


	//���У���
	if(!CheckSum())
	{
		ClearRawData();//װ��һ�Σ��ͱ������ԭʼ���ݻ���
		return false;
	}
	//���operation�ֽ�
	if(!CheckOperation())
	{
		ClearRawData();//װ��һ�Σ��ͱ������ԭʼ���ݻ���
		return false;		
	}


	int distance;
	int index=GetDataOffset();//��ȡ����������buffer�е�ƫ����
	int i=0;
	int dataCnt=0;

	int data[600],okData[600];//�������ײ�ĽǶ���˳ʱ����ת�ģ������Ƕ�����෴��������Ҫ������

	while(i<m_rawDataBuff.size()-4)//Ҫȥ�����һ���ֽ�checksum�������ֽڽ�����־
	{
		if(i<index)
		{
			i++;
			continue;		//ֱ���ƶ������ݶ�ȡ����
		}
		distance=GetDistance(m_rawDataBuff[i],m_rawDataBuff[i+1]);
		
		if(m_rawDataBuff[i]==0x00
			&& m_rawDataBuff[i+1]==0x00)
		{
			i+=3;		//ȥ����ӽ�����0XFF
		}
		else
		{
			i+=2;
		}
		if(dataCnt>=600)//�������ײ��Э�飬�����ܴ���600���������ݡ�
		{
			ClearRawData();//װ��һ�Σ��ͱ������ԭʼ���ݻ���
			return false;
		}
		data[dataCnt]=distance;
		dataCnt++;
	}

	for(i=0;i<dataCnt;i++)
	{
		okData[i]=data[dataCnt-1-i];
	}


	pData->dataLength=dataCnt;
	
	//����-5.04��185.04��,��(-25,925),0.2��ʾ
	if(m_startAngle<-25)
		m_startAngle=-25;
	if(m_stopAngle>925)
		m_stopAngle=925;
	if(m_stopAngle<=m_startAngle)
	{
		m_startAngle=-25;
		m_stopAngle=925;
	}	
	
	double angleResolution=GetAngularResolution()*0.36;//�����ȵ�λ�Ƕȣ�0.36�����ײ�ĵ�λ�����ȣ������ȶ������ı���

	int startDataNumber=(1+m_startAngle-(-25))*0.2/angleResolution;//��ȡ��ʼ����data�����еľ���ֵ���,��1��ԭ���ǣ����ײ��-25����-5.04����1��������0
	int stopDataNumber=(m_stopAngle-(-25))*0.2/angleResolution;//��ȡ��������data�����еľ���ֵ���


	pData->dataLength=stopDataNumber-startDataNumber+1;
	pData->startAngle=m_startAngle;
	pData->stopAngle=m_stopAngle;
	SYSTEMTIME time;
	GetLocalTime(&time);

	pData->time=time;

	int k=0;
	for(i=0;i<dataCnt;i++)
	{
		if(i<startDataNumber)
			continue;
		if(i>=stopDataNumber)
			break;

		pData->data[k]=okData[i];

		//�����ļ�
		if(m_saveRawData)
		{
			fprintf(m_pFile,"%d\n",okData[i]);
		}
		
		k++;
	}
	ClearRawData();//װ��һ�Σ��ͱ������ԭʼ���ݻ���
	return true;
}
bool CLeuzeSocketComm::CheckOperation()
{
	return m_rawDataBuff[0]==0x23;
}
//���У��ͣ���operation�ֽڵ�checksum��ǰһ���ֽڣ�����������
bool CLeuzeSocketComm::CheckSum()
{
	unsigned char tag=m_rawDataBuff[0];
	int sizes=m_rawDataBuff.size();
	for(int i=1;i<(sizes-4);i++)
	{
		tag^=m_rawDataBuff[i];
	}
	if(tag==0x00)tag=0xff;
	unsigned char checkSum=m_rawDataBuff[sizes-4];
	return tag==checkSum;
}
//��ȡangular resolution
int CLeuzeSocketComm::GetAngularResolution()
{
	int optionBytes=GetOptionByteNum();
	return m_rawDataBuff[1+optionBytes+8];
}
//����һ��Э������ݵ�ʱ�򣬻�ȡЭ���о������ݴ�start�ֽڵ��������ݵ�ƫ����
int CLeuzeSocketComm::GetDataOffset()
{
	//m_rawDataBuff��û�д���ʼ�����ֽڱ�־
	int offset=0;
	if(m_rawDataBuff.size()<19)//��������ǰ����ֽ��������19��
		return offset;
	
	int startAngleIndex,stopAngleIndex;
	int optionByteNum=GetOptionByteNum();//option�ֽ���
	
	startAngleIndex=1+optionByteNum+8+1;
	offset=startAngleIndex;
	if(m_rawDataBuff[startAngleIndex]==0x00		//15����ʼ�Ǹ�λ�ֽڵ�ƫ��λ��
	&& m_rawDataBuff[startAngleIndex+1]==0x00)		
	{
		offset+=3;
		stopAngleIndex=startAngleIndex+3;
	}
	else
	{
		offset+=2;
		stopAngleIndex=startAngleIndex=2;
	}
	if(m_rawDataBuff[stopAngleIndex]==0x00		//17�ǽ����Ǹ�λ�ֽڵ�ƫ��λ��
	&& m_rawDataBuff[stopAngleIndex=1]==0x00)		
	{
		offset+=3;
	}
	else
	{
		offset+=2;
	}
	return offset;

}
//����option�ֽ���������option1��2��3
int CLeuzeSocketComm::GetOptionByteNum()
{
	//option 1+2+3
	if((m_rawDataBuff[1] & 3) > 0)
	{
		return 3;
	}
	//option 1+2
	else if((m_rawDataBuff[1] & 2) > 0)
	{
		return 2;
	}
	//option 1
	else if((m_rawDataBuff[1] & 1) > 0)
	{
		return 1;
	}
	return 3;
}
int CLeuzeSocketComm::GetDistance(unsigned char highByte,unsigned char lowByte)
{
	int distance=0;
	distance=(highByte<<8) | (lowByte & 0xFE);//���ε����ֽڵ�bit0λ��
	return distance;
}

void CLeuzeSocketComm::ClearRawData()
{
	std::vector<unsigned char>::iterator theIt;
	for(theIt = m_rawDataBuff.begin(); theIt != m_rawDataBuff.end(); ++theIt)
	{
		m_rawDataBuff.erase(theIt);
		theIt--; 
	}
	
}
