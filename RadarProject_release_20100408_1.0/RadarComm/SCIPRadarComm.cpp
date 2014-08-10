// SCIPRadarComm.cpp: implementation of the CSCIPRadarComm class.
//
//////////////////////////////////////////////////////////////////////

#include "SCIPRadarComm.h"
#include <ctime>  //���������

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSCIPRadarComm::CSCIPRadarComm()
{
	m_degreePerIndex=0.25;
	m_maxDegree=270.25;
	
}

CSCIPRadarComm::~CSCIPRadarComm()
{
	
}

int  CSCIPRadarComm::StartRadar(void)
{	
	int ret;	
	ret = urg_connect(&urg, m_comDevice, m_bitRate);	
	if (ret < 0) 
	{		
		return -1;
	}
		
	return 1;
	
}
int	 CSCIPRadarComm::CloseRadar(void)
{
	if(urg.is_laser_on_==UrgLaserOn)
	{
		//���巢������ȥ�����״�ֹͣ
		urg_disconnect(&urg);
	}
	return 1;
}

//��ȡԭʼ���ݣ�����ȥ����SCIP lib�Ŀ⺯�������DataFrameʵ��
bool CSCIPRadarComm::GetRawData(DataFrame * pData)
{
	int data_max;
	long *data;
	int ret;
	int n;
	
	data_max = urg_dataMax(&urg);
	data = new long[data_max];
	if (data == NULL) {
		//perror("malloc");
		return false;
	}
	memset(data,0,sizeof(long)*data_max);	
	
	ret = urg_requestData(&urg, URG_GD, URG_FIRST, URG_LAST);	
	if (ret < 0) {
		delete data;
		return false;
	}
	
	n = urg_receiveData(&urg, data, data_max);//n ��ʾ���صľ�����������1081
	if (n < 0) {
		delete data;
		return false;
	}
				
	if( ResolveData(data,n,pData))	//����ԭʼ���ݣ������Լ������ԭʼ����
	{
		delete data;
		return true;
	}
	else
	{
		delete data;
		return false;
	}
	
}
bool CSCIPRadarComm::ResolveData(long data[],int dataLength,DataFrame * pData)
{
	if(m_startAngle<-225)
		m_startAngle=-225;
	if(m_stopAngle>1125)
		m_stopAngle=1125;
	if(m_stopAngle<=m_startAngle)
	{
		m_startAngle=-225;
		m_stopAngle=1125;
	}

	int startDataNumber=(int)((m_startAngle-(-225))*0.2/0.25);//��ȡ��ʼ����data�����еľ���ֵ���
	int stopDataNumber=(int)((m_stopAngle-(-225))*0.2/0.25);//��ȡ��������data�����еľ���ֵ���

	pData->dataLength=stopDataNumber-startDataNumber+1;//��Ҫ��ʵ�ʳ������ټ�1
	pData->startAngle=m_startAngle;											//��ʼ�Ƕ�
	pData->stopAngle=m_stopAngle;											//�����Ƕ�
	
	SYSTEMTIME stime;
	GetLocalTime(&stime);
	pData->time=stime;
	
	
	int index=0;
	for(int i=0;i<dataLength;i++)
	{
		if(i<startDataNumber)
			continue;
		if(i>=stopDataNumber)
			break;

		if(data[i]==1 || data[i]>m_validDistance)
			pData->data[index]=m_validDistance;//���ԭʼ��������Ϊ1����ʾ�ǹ���δ���أ���Ҫ���ó���Ч����
		else	
			pData->data[index]=data[i];
		
		index++;
	}
	return true;
}