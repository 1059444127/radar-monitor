/*****************************************************************
*�ļ�����			SCIPRadarComm.h
*����������	        -
*����������	        -
*��˾����			�п�Ժ������������ҵ�о�Ժ
*��ǰ�汾�ţ�	    v1.0
*
*Copyright? 2009, �п�Ժ������������ҵ�о�Ժ All rights reserved.
*
*����			ʱ��					��ע
*zhangyong		2009-12-28			
*
*˵��
	�����״�--ͨ�Ž�����--ͨ��ģ���ձ�SCIP�����Ʒͨ���ࡣ���ڡ���ظ�ʽ����ο���ƷSPEC
******************************************************************/

// SCIPRadarComm.h: interface for the CSCIPRadarComm class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCIPRADARCOMM_H__43B215BF_B7FA_4643_A04D_CBC5293FA058__INCLUDED_)
#define AFX_SCIPRADARCOMM_H__43B215BF_B7FA_4643_A04D_CBC5293FA058__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef __cplusplus		//ʹ�����ַ�ʽ����������C���Կ�
extern "C" {
#endif

#include "urg_ctrl.h"

#ifdef __cplusplus
	}
#endif

#include "RadarCommunicationBase.h"

class CSCIPRadarComm : public CRadarCommunicationBase  
{
public:
	CSCIPRadarComm();
	virtual ~CSCIPRadarComm();

	virtual int  StartRadar(void);
	virtual int	 CloseRadar(void);
	virtual bool GetRawData(DataFrame * pData);
private:
	urg_t urg;
	double m_degreePerIndex;		//��λ��������Ķ���
	double m_maxDegree;			//ɨ���ʵ��������
protected:
	bool ResolveData(long data[],int dataLength,DataFrame * pData);
};

#endif // !defined(AFX_SCIPRADARCOMM_H__43B215BF_B7FA_4643_A04D_CBC5293FA058__INCLUDED_)
