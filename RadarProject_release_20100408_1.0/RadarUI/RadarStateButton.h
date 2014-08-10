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
	�����״�--UI�����л�״̬��ť��
******************************************************************/
#if !defined(AFX_RADARSTATEBUTTON_H__2A9885DB_9CCC_453A_A085_5FDE6A38FBC8__INCLUDED_)
#define AFX_RADARSTATEBUTTON_H__2A9885DB_9CCC_453A_A085_5FDE6A38FBC8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RadarStateButton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRadarStateButton window

class CRadarStateButton : public CButton
{
// Construction
public:
	CRadarStateButton();

// Attributes
public:
	bool		m_bOn;		//�Ƿ�On״̬
protected:
	CBitmap		m_bmpOn;
	HBITMAP		m_hbmpOn;

	CBitmap		m_bmpOff;
	HBITMAP		m_hbmpOff;

	CBitmap		m_bmpDisable;
	HBITMAP		m_hbmpDisable;
// Operations
public:
	void LoadBmp(CString bmpOn,CString bmpOff,CString bmpDisable);
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
	virtual ~CRadarStateButton();
	void SetState(bool state);
	// Generated message map functions
protected:
	//{{AFX_MSG(CRadarButton)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RADARSTATEBUTTON_H__2A9885DB_9CCC_453A_A085_5FDE6A38FBC8__INCLUDED_)
