/*****************************************************************
*�ļ�����			RadarBaseDlg.h
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
	�����״�--�Ի������
******************************************************************/
#if !defined(AFX_RADARBASEDLG_H__785D9C33_89AA_402E_B19E_D7E61C300DE1__INCLUDED_)
#define AFX_RADARBASEDLG_H__785D9C33_89AA_402E_B19E_D7E61C300DE1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RadarBaseDlg.h : header file
//
#include "radarapp.h"

/////////////////////////////////////////////////////////////////////////////
// CRadarBaseDlg dialog

class CRadarBaseDlg : public CDialog
{
	// Construction
public:
	CRadarBaseDlg(CWnd* pParent = NULL);   // standard constructor

	CRadarBaseDlg(UINT nIDTemplate,
		CWnd* pParentWnd = NULL )
		:CDialog(nIDTemplate, pParentWnd)
	{
		CDialog(nIDTemplate, pParentWnd);	
	};

	void ShowBmpPicByHBITMAP(HDC dc,HBITMAP hBitmap,int x,int y);

	// Dialog Data
	//{{AFX_DATA(CRadarBaseDlg)
	enum { IDD = IDD_DIALOG_BASEDLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRadarBaseDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CRadarApp * app;

	// Generated message map functions
	//{{AFX_MSG(CRadarBaseDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RADARBASEDLG_H__785D9C33_89AA_402E_B19E_D7E61C300DE1__INCLUDED_)
