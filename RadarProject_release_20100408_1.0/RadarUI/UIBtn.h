/*****************************************************************
*�ļ�����			UIBtn.h
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
	�����״�UIģ���ͼ��ʾ�ؼ������Ű�ť��ĳ���ť�ࡣ�����Զ���ؼ���ť����
	����������

******************************************************************/

// UIBtn.h: interface for the CUIBtn class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UIBTN_H__232728E1_B55E_4E42_919C_366068514C85__INCLUDED_)
#define AFX_UIBTN_H__232728E1_B55E_4E42_919C_366068514C85__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CUIBtn  
{
public:
	CUIBtn();
	virtual				~CUIBtn();

	void				SetSize(const CRect& rect)				{ m_rSize = rect;						}	
	BOOL				TestInArea(const CPoint& point) const	{ return m_rSize.PtInRect(point);		}

	virtual void		Draw(CDC *pDC)  = 0;
	virtual void		Click() = 0;

protected:
	CRect				m_rSize;

};

#endif // !defined(AFX_UIBTN_H__232728E1_B55E_4E42_919C_366068514C85__INCLUDED_)
