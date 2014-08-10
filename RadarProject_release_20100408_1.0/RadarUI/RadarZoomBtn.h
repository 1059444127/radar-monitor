/*****************************************************************
*�ļ�����			RadarRoomBtn.h
*����������	        -
*����������	        -
*��˾����			�п�Ժ������������ҵ�о�Ժ
*��ǰ�汾�ţ�	    v1.0
*
*Copyright? 2009, �п�Ժ������������ҵ�о�Ժ All rights reserved.
*
*����			ʱ��					��ע
*zhangyong		2009-12-29			
*
*˵��
	�����״�UIģ���ͼ��ʾ�ؼ������Ű�ť�ࡣ
******************************************************************/

// RadarRoomBtn.h: interface for the CRadarZoomBtn class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RADARROOMBTN_H__6845208E_7CB8_4CCC_89A1_2CB2486D6486__INCLUDED_)
#define AFX_RADARROOMBTN_H__6845208E_7CB8_4CCC_89A1_2CB2486D6486__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "UIBtn.h"

//�Զ�����Ϣ
#define WM_ZOOMLICK		WM_USER+110			//���Ű�ť��Ϣ



class CRadarZoomBtn : public CUIBtn  
{
public:
	
	CRadarZoomBtn(CWnd* pWnd,int zoom);

	virtual						~CRadarZoomBtn();
	virtual void				Draw(CDC *pDC);
	virtual void				Click();
	void						LoadBkBitmap(CString bitmapbgEnable,CString bitmapbgDisable);

	void						SetZoomTag( int zoom) 	   {  m_zoomTag=zoom;					}
	bool						m_enable;

protected:
	int						m_zoomTag;	//1,zoomIn,2,zoomOut
	
	CWnd*					m_pWnd;
	CBitmap					m_bitmapBgEnable;
	CBitmap					m_bitmapBgDisable;
	HBITMAP					m_hbmpbgEnable;
	HBITMAP					m_hbmpbgDisable;
};

#endif // !defined(AFX_RADARROOMBTN_H__6845208E_7CB8_4CCC_89A1_2CB2486D6486__INCLUDED_)
