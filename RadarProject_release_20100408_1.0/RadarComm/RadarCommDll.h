/*****************************************************************
*�ļ�����			RadarCommDll.h
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
	�����״�ͨ��ģ�����ӿ��ࡣ������ά���ײ�ͨ��ģ�������ͨ�ţ�
	��ƷЭ��ĸ�����
******************************************************************/

// RadarCommDll.h: interface for the CRadarCommDll class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RADARCOMMDLL_H__644DF948_F73C_4AB8_A2FB_77C4A9999E6B__INCLUDED_)
#define AFX_RADARCOMMDLL_H__644DF948_F73C_4AB8_A2FB_77C4A9999E6B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Jthread.h"
#include "jmutex.h"
#include "fifo.h"

#include "struct.h"
#include "RadarCommunicationBase.h"


#ifdef RADARCOMM_EXPORTS
class _declspec(dllexport) CRadarCommDll : public JThread    //������circle
#else
class _declspec(dllimport) CRadarCommDll : public JThread    //������circle
#endif
{
public:
	CRadarCommDll();
	virtual ~CRadarCommDll();

	/**	����:����ӿڣ���FIFO��ȡԭʼ���ݣ�����false��ʾû��ԭʼ����
	 *	����:
	 *		
	 *	����ֵ:
	 *	*/
	bool Comm_GetRawDataFromFIFO(DataFrame * pData);			
	
	
	/**	����:�����״�
	 *	����:
	 *		
	 *	����ֵ:
	 *	*/
	bool Comm_StartRadar();

	/**	����:ֹͣ�״�
	 *	����:
	 *		
	 *	����ֵ:
	 *	*/
	bool Comm_StopRadar();

	/**	����:��ʼ���״�
	 *	����:
	 *		
	 *	����ֵ:
	 *	*/
	bool Comm_SetRadarConfig(HardConfigInfo &cfgInfo);
	
	

private:
	JMutex				m_mutex;										//������
	FIFO_LIST*			comm_rawdata_fifo;								//ԭʼ���ݻ������
	void*				Thread(); 
	bool				SetRawDataToFIFO(DataFrame * pData);			//��ԭʼ���ݴ���FIFO
	bool				GetRawData(DataFrame * pData);					//�Ӽ����״��ȡԭʼ����
	
	CRadarCommunicationBase	*	m_radarComm;		//�״�ͨ��ʵ��ָ�룬���ݲ�Ʒ��ȡ��ͬ��Ʒ��Ӧ��ͨ����
};

#endif // !defined(AFX_RADARCOMMDLL_H__644DF948_F73C_4AB8_A2FB_77C4A9999E6B__INCLUDED_)
