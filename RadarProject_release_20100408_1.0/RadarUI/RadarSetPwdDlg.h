/*****************************************************************
*�ļ�����			RadarSetPwdDlg.h
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
	�����״�������ý��档
******************************************************************/
#if !defined(AFX_RADARSETPWDDLG_H__BB36588A_DDA0_435C_AFD3_23C1FC3E70F2__INCLUDED_)
#define AFX_RADARSETPWDDLG_H__BB36588A_DDA0_435C_AFD3_23C1FC3E70F2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RadarSetPwdDlg.h : header file
//
#include "RadarBaseDlg.h"
#include "RadarButton.h"
/////////////////////////////////////////////////////////////////////////////
// CRadarSetPwdDlg dialog

class CRadarSetPwdDlg : public CRadarBaseDlg
{
// Construction
public:
	CRadarSetPwdDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CRadarSetPwdDlg();
// Dialog Data
	//{{AFX_DATA(CRadarSetPwdDlg)
	enum { IDD = IDD_DIALOG_PWDSET };
	CRadarButton	m_returnBtn;
	CRadarButton	m_okBtn;
	CEdit	m_oldPwd;
	CEdit	m_newPwd1;
	CEdit	m_newPwd;
	//}}AFX_DATA

	CBitmap		m_bmpBg;
	HBITMAP		m_hbmpBg;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRadarSetPwdDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRadarSetPwdDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonOk();
	afx_msg void OnButtonReturn();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RADARSETPWDDLG_H__BB36588A_DDA0_435C_AFD3_23C1FC3E70F2__INCLUDED_)
