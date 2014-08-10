/*****************************************************************
*�ļ�����			IniHelper.h
*����������	        -
*����������	        -
*��˾����			�п�Ժ������������ҵ�о�Ժ
*��ǰ�汾�ţ�	    v1.0
*
*Copyright? 2009, �п�Ժ������������ҵ�о�Ժ All rights reserved.
*
*����			ʱ��					��ע
*zhangyong		2010-1-06			
*
*˵��
	�����״�--Ӧ�ó����--INI�ļ���ȡ�ࡣ
******************************************************************/

// IniHelper.h: interface for the CIniHelper class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INIHELPER_H__4D449A73_148C_464E_A056_1CE93BFE90C3__INCLUDED_)
#define AFX_INIHELPER_H__4D449A73_148C_464E_A056_1CE93BFE90C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <windows.h>
class CIniHelper  
{
public:
	CIniHelper::CIniHelper(LPCSTR directory,   /*��ǰ�������Ŀ¼������ļ��ڸ�Ŀ¼������NULL*/
					   LPCSTR file				/*ini�ļ�����ڵ�ǰ�����·��*/
					   );
	virtual ~CIniHelper();

	/**	����:��ȡINI�ļ���ֵ
	 *	����:
	 *		
	 *	����ֵ:
	 *	*/
	BOOL ReadIniFile(
		LPCSTR lpAppName,				/*�ڵ�����*/
		LPCSTR lpKeyName,				/*��*/
		LPCSTR lpDefault,				/*Ĭ��ֵ��=NULL*/
		LPSTR lpReturnedString,		/*���ؼ�ֵ*/
		DWORD nSize					/*���ؼ�ֵ�ߴ�*/
    );

	/**	����:д��INI�ļ���ֵ
	 *	����:
	 *		
	 *	����ֵ:
	 *	*/
	BOOL WriteIniFile(
		LPCSTR lpAppName,				/*�ڵ�����*/
		LPCSTR lpKeyName,				/*��*/
		LPCSTR lpString				/*��ֵ*/
    );
protected:
	char m_iniFile[250];		//ini�ļ�·��
};

#endif // !defined(AFX_INIHELPER_H__4D449A73_148C_464E_A056_1CE93BFE90C3__INCLUDED_)
