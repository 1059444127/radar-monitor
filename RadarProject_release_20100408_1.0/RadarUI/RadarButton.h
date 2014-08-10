/*****************************************************************
*�ļ�����			RadarButton.h
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
	�����״�--UI������ť��
******************************************************************/
#if !defined(AFX_RADARBUTTON_H__F4FD1359_4497_4EAA_BC15_029B3B0A3E25__INCLUDED_)
#define AFX_RADARBUTTON_H__F4FD1359_4497_4EAA_BC15_029B3B0A3E25__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RadarButton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRadarButton window
extern "C" WINUSERAPI BOOL WINAPI TrackMouseEvent(LPTRACKMOUSEEVENT lpEventTrack);

class CRadarButton : public CButton
{
// Construction
public:
	CRadarButton();

// Attributes
public:
	bool		m_bHover;		//�Ƿ�����ڰ�ť��
protected:
	CBitmap		m_bmpNormal;
	HBITMAP		m_hbmpNormal;

	CBitmap		m_bmpHover;
	HBITMAP		m_hbmpHover;

	CBitmap		m_bmpDisable;
	HBITMAP		m_hbmpDisable;

// Operations
public:
	void LoadBmp(CString bmpNormal,CString bmpHover,CString bmpDisable);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRadarButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CRadarButton();

	// Generated message map functions
protected:
	//{{AFX_MSG(CRadarButton)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseOut(WPARAM   wParam,   LPARAM   lParam);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	BOOL MouseOver();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RADARBUTTON_H__F4FD1359_4497_4EAA_BC15_029B3B0A3E25__INCLUDED_)
