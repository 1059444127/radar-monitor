/*****************************************************************
*�ļ�����			RadarFileOp.h
*����������	        -
*����������	        -
*��˾����			�п�Ժ������������ҵ�о�Ժ
*��ǰ�汾�ţ�	    v1.0
*
*Copyright? 2009, �п�Ժ������������ҵ�о�Ժ All rights reserved.
*
*����			ʱ��					��ע
*zhangyong		2010-1-27			
*
*˵��
	�ļ�Ŀ¼����������
******************************************************************/
// RadarFileOp.h: interface for the CRadarFileOp class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RADARFILEOP_H__6C633A0F_006C_43FA_A288_C1CCDC252009__INCLUDED_)
#define AFX_RADARFILEOP_H__6C633A0F_006C_43FA_A288_C1CCDC252009__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CRadarFileOp  
{
public:
	CRadarFileOp();
	virtual ~CRadarFileOp();
	BOOL   FolderExist(CString strPath);

	BOOL   FileExist(CString strFileName);
	BOOL CreateFolder(CString strPath);

};

#endif // !defined(AFX_RADARFILEOP_H__6C633A0F_006C_43FA_A288_C1CCDC252009__INCLUDED_)
