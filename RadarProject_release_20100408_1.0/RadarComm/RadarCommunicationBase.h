/*****************************************************************
*�ļ�����			RadarCommunicationBase.h
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
	�����״�ͨ��ģ��ͨ�Ų�Ʒ���ࡣ�����ࡣ��������ͨ�ŵĳ���ӿڣ�
	����Ĳ�Ʒ��ͨ�������Ӹ���̳С�
******************************************************************/

// RadarCommunicationBase.h: interface for the CRadarCommunicationBase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RADARCOMMUNICATIONBASE_H__04E7987A_6DB4_4E78_8BD6_C4EE3E525421__INCLUDED_)
#define AFX_RADARCOMMUNICATIONBASE_H__04E7987A_6DB4_4E78_8BD6_C4EE3E525421__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "struct.h"

class CRadarCommunicationBase  
{
public:
	CRadarCommunicationBase();
	virtual ~CRadarCommunicationBase();
	int		m_startAngle;		//��ʼ�Ƕȣ�����1��ʾ0.2�ȵĸ�ʽ�洢
	int		m_stopAngle;		//�����Ƕȣ�ͬ��
	int		m_bitRate;			
	char	m_comDevice[50];	//com��
	char	m_ip[50];			//IP��ַ
	int		m_port;				//�˿ں�
	EnumRadar m_radar;			//�״��Ʒ
	int		m_motorRate;		//���ת��
	bool	m_saveRawData;		//����ԭʼ����
	char	m_rawDataFile[500];	//ԭʼ�����ļ����·��
	int		m_validDistance;	//��Ч����

	virtual int  StartRadar(void)				=	0;
	virtual int	 CloseRadar(void)				=	0;
	virtual bool GetRawData(DataFrame * pData)	=	0;
};

#endif // !defined(AFX_RADARCOMMUNICATIONBASE_H__04E7987A_6DB4_4E78_8BD6_C4EE3E525421__INCLUDED_)
