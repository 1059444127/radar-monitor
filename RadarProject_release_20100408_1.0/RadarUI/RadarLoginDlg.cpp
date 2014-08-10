// RadarLoginDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RadarUI.h"
#include "RadarLoginDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRadarLoginDlg dialog


CRadarLoginDlg::CRadarLoginDlg(CWnd* pParent /*=NULL*/)
	: CRadarBaseDlg(CRadarLoginDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRadarLoginDlg)
	//}}AFX_DATA_INIT
	//����ͼƬ��Դ
	m_hbmpBg = (HBITMAP)::LoadImage(0, UI_LOGINBG, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	
	if(m_hbmpBg!=NULL)
	{
		m_bmpBg.Attach(m_hbmpBg);
	}
	m_Font.CreateFont(
		14,                        // nHeight,INIT
		0,                        // nWidth
		0,                        // nEscapement
		0,                        // nOrientation
		FW_NORMAL,                // nWeight
		FALSE,                    // bItalic
		FALSE,                    // bUnderline
		0,                        // cStrikeOut
		ANSI_CHARSET,              // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,      // nClipPrecision
		DEFAULT_QUALITY,          // nQuality
		DEFAULT_PITCH | FF_SWISS,
		_T("Arial")                    // nPitchAndFamily
		); 
}
CRadarLoginDlg::~CRadarLoginDlg()
{
	if(app!=NULL)
	{
		delete app;
	}
	if(m_hbmpBg!=NULL)
		DeleteObject(m_hbmpBg);
}

void CRadarLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CRadarBaseDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRadarLoginDlg)
	DDX_Control(pDX, IDC_BTN_CLOSE, m_closeBtn);
	DDX_Control(pDX, ID_LOGIN, m_loginBtn);
	DDX_Control(pDX, IDC_EDIT_PWD, m_pwd);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRadarLoginDlg, CRadarBaseDlg)
	//{{AFX_MSG_MAP(CRadarLoginDlg)
	ON_BN_CLICKED(ID_LOGIN, OnLogin)
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_BTN_CLOSE, OnBtnClose)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRadarLoginDlg message handlers
BOOL CRadarLoginDlg::OnInitDialog()
{
	CRadarBaseDlg::OnInitDialog();

	try
	{
		app=CRADAR_APP;
	}
	catch(...)
	{
		MessageBox("��ʼ��APP������ȷ��dataĿ¼��data.mdb�Ƿ�����");
		exit(0);
	}
	if(app==NULL)
	{
		MessageBox("����APPʵ������");
		exit(0);
		//return TRUE;
	}
	SetWindowText("�����״��ںϱ������");

	m_pwd.MoveWindow(59,106,172,28);
	m_loginBtn.MoveWindow(241,106,94,28);
	m_loginBtn.LoadBmp(UI_LOGINBTN_NORMAL,UI_LOGINBTN_HOVER,UI_LOGINBTN_NORMAL);
	
	m_closeBtn.MoveWindow(334,10,28,28);
	m_closeBtn.LoadBmp(UI_LOGINCLOSEBTN_NORMAL,UI_LOGINCLOSEBTN_HOVER,UI_LOGINCLOSEBTN_NORMAL);


	return TRUE;
}


void CRadarLoginDlg::OnLogin() 
{
	// TODO: Add your control notification handler code here
	
	char pwd[50];
	CString s;
	m_pwd.GetWindowText(s);
	memcpy(pwd,s,50);
	int ret =app->CheckPwd(pwd,50);
	if(ret==META_ERR_PWD)
	{
		MessageBox("�������");
	}
	else
	{
		CRadarBaseDlg::OnOK();
	}
}

BOOL CRadarLoginDlg::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	ShowBmpPicByHBITMAP(pDC->m_hDC,m_hbmpBg,0,0);
	
	return TRUE;
	//return CRadarBaseDlg::OnEraseBkgnd(pDC);
}

void CRadarLoginDlg::OnBtnClose() 
{
	// TODO: Add your control notification handler code here
	exit(0);
}

void CRadarLoginDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here

	//�汾��Ϣ
	CFont* pOldFont=dc.SelectObject(&m_Font);  
	dc.SetTextColor(RGB(0,0,0));
	CString str;	
    
	if(!GetMyProcessVer(str))
		str="";
	
	CRect rfont;
	CRect rect;
	GetClientRect(&rect);
	rfont.left=5;
	rfont.top=rect.Height()-21;
	rfont.bottom=rect.Height()-6;
	rfont.right=130;

	/*�Ŷ���
	rfont.left=5;
	rfont.top=2;
	rfont.bottom=17;
	rfont.right=130;
*/
	dc.SetBkMode(TRANSPARENT);
	dc.DrawText(str,&rfont,DT_LEFT);
	// Do not call CRadarBaseDlg::OnPaint() for painting messages
}

   
BOOL CRadarLoginDlg::GetMyProcessVer(CString& strver)   //����ȡ���Լ��İ汾��    
{    
    TCHAR strfile[MAX_PATH];    
    GetModuleFileName(NULL, strfile, sizeof(strfile));  //����ȡ���Լ����ļ���    
   
    DWORD dwVersize = 0;    
    DWORD dwHandle = 0;    
   
    dwVersize = GetFileVersionInfoSize(strfile, &dwHandle);    
    if (dwVersize == 0)    
    {    
        return FALSE;    
    }    
   
    TCHAR szVerBuf[8192] = _T("");    
    if (GetFileVersionInfo(strfile, 0, dwVersize, szVerBuf))    
    {    
        VS_FIXEDFILEINFO* pInfo;    
        UINT nInfoLen;    
		CString ver;
		//��ȡ�汾�� ������1.0.0.1
        if (VerQueryValue(szVerBuf, _T("\\"), (LPVOID*)&pInfo, &nInfoLen))   
        {   
            ver.Format(_T("%d.%d.%d.%d"), HIWORD(pInfo->dwFileVersionMS),     
                LOWORD(pInfo->dwFileVersionMS), HIWORD(pInfo->dwFileVersionLS),    
                LOWORD(pInfo->dwFileVersionLS));    
   
            
        }   
		//��ȡprivateBuild 
		LPCTSTR pVal;
		UINT iLenVal;
		CString build;
		if (VerQueryValue(szVerBuf, _T("\\StringFileInfo\\080404b0\\PrivateBuild"),
				(LPVOID*)&pVal, &iLenVal)) {
			build=pVal;
			
		}
		strver.Format("v%s %s",ver, build);
		return TRUE;
    }    
    return FALSE;    
}   