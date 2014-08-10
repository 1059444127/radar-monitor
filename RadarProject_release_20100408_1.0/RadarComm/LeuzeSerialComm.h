/*****************************************************************
*�ļ�����			LeuzeSerialComm.h
*����������	        -
*����������	        -
*��˾����			�п�Ժ������������ҵ�о�Ժ
*��ǰ�汾�ţ�	    v1.0
*
*Copyright? 2009, �п�Ժ������������ҵ�о�Ժ All rights reserved.
*
*����			ʱ��					��ע
*zhangyong		2010-2-1			
*
*˵��
	�����״�--ͨ�Ž�����--���ײ��״����ݽ����࣬����ͨ�š����Э���ʽ��ο�SPEC
******************************************************************/
// LeuzeSerialComm.h: interface for the CLeuzeSerialComm class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LEUZESERIALCOMM_H__3040CF98_F864_41CC_988F_5537D342F40C__INCLUDED_)
#define AFX_LEUZESERIALCOMM_H__3040CF98_F864_41CC_988F_5537D342F40C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "RadarCommunicationBase.h"
#include <vector>
using std::vector;

class CLeuzeSerialComm : public CRadarCommunicationBase  
{
public:
	CLeuzeSerialComm();
	virtual ~CLeuzeSerialComm();
	virtual int  StartRadar(void);
	virtual int	 CloseRadar(void);
	virtual bool GetRawData(DataFrame * pData);
private:
	HANDLE hCom;  //ȫ�ֱ��������ھ��
	FILE * m_pFile;//�ļ�ָ��
	vector<unsigned char> m_rawDataBuff;
	
	int angluarResolution;

	bool findStartTag;	//�Ƿ��ҵ���ʼ��־
	bool findStopTag;	//�Ƿ��ҵ�������־
	
	unsigned char tagBuffer[3];
	int tagBufferNumber;

protected:
	void ClearRawData();
	bool ProcessData(char * recvBuf,int size,DataFrame * pData);
	void ReSetTagBuffer();
	void SetTagBuffer(unsigned char tag);
	bool CheckStartTag();
	bool CheckStopTag();
	bool LoadData(DataFrame *pData);
	int  GetDistance(unsigned char highByte,unsigned char lowByte);

	int GetDataOffset();

	bool CheckSum();
	bool CheckOperation();
	int GetOptionByteNum();
	int GetAngularResolution();

};

#endif // !defined(AFX_LEUZESERIALCOMM_H__3040CF98_F864_41CC_988F_5537D342F40C__INCLUDED_)
