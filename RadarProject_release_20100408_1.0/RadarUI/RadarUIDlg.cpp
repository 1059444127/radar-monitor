// RadarUIDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RadarUI.h"
#include "RadarUIDlg.h"
#include "IniHelper.h"
#include "radarparamsetdlg.h"
#include "RadarEnumMap.h"
#include "RadarHistoryDlg.h"
#include "mmsystem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



#ifdef __cplusplus
extern "C" {
#endif

#include "urg_ctrl.h"

#ifdef __cplusplus
	}
#endif

#import "msxml3.dll"
using namespace MSXML2;

/////////////////////////////////////////////////////////////////////////////
// CRadarUIDlg dialog

CRadarUIDlg::CRadarUIDlg(CWnd* pParent /*=NULL*/)
	: CRadarBaseDlg(CRadarUIDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRadarUIDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	::CoInitialize(NULL); //��ʼ��COM
	m_xmlFileName="";
	ismove=false;

	//����ͼƬ��Դ
	m_hbmpBg = (HBITMAP)::LoadImage(0, UI_MAINBG, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	
	if(m_hbmpBg!=NULL)
	{
		m_bmpBg.Attach(m_hbmpBg);
	}

}
CRadarUIDlg::~CRadarUIDlg()
{
	CoUninitialize();
	if(m_hbmpBg!=NULL)
		DeleteObject(m_hbmpBg);

}
void CRadarUIDlg::DoDataExchange(CDataExchange* pDX)
{
	CRadarBaseDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRadarUIDlg)
	DDX_Control(pDX, IDOK, m_closeBtn);
	DDX_Control(pDX, IDC_BUTTON_SET, m_paramBtn);
	DDX_Control(pDX, IDC_BUTTON_HISTORY, m_historyBtn);
	DDX_Control(pDX, IDC_BUTTON_CLOSESOUND, m_soundBtn);
	DDX_Control(pDX, IDC_BUTTON_ALARM, m_alarmBtn);
	DDX_Control(pDX, IDC_LIST_ALARMRECORD, m_alarmRecordList);
	DDX_Control(pDX, IDC_BUTTON_STOPRADAR, m_stopBtn);
	DDX_Control(pDX, IDC_BUTTON_STARTRADAR, m_startBtn);
	DDX_Control(pDX, IDC_STATIC_MAP, m_mapCtrl);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CRadarUIDlg, CRadarBaseDlg)
	//{{AFX_MSG_MAP(CRadarUIDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_STARTRADAR, OnButtonStartRadar)
	ON_BN_CLICKED(IDC_BUTTON_STOPRADAR, OnButtonStopRadar)
	ON_BN_CLICKED(IDC_BUTTON_SET, OnButtonSet)
	ON_BN_CLICKED(IDC_BUTTON_ALARM, OnButtonAlarm)
	ON_BN_CLICKED(IDC_BUTTON_CLOSESOUND, OnButtonClosesound)
	ON_BN_CLICKED(IDC_BUTTON_HISTORY, OnButtonHistory)
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_GETDATA, OnGetData)
	ON_MESSAGE(WM_GETMAP, OnGetMap)	
	ON_MESSAGE(WM_GETDATATIMEOUT, OnDataTimeOut)
	ON_MESSAGE(WM_SYSPARAM_CHANGE,OnSysParamChange)
	ON_MESSAGE(WM_MOUSELEAVE,OnMouseOut)
END_MESSAGE_MAP()



/////////////////////////////////////////////////////////////////////////////
// CRadarUIDlg message handlers

BOOL CRadarUIDlg::OnInitDialog()
{
	CRadarBaseDlg::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	app=CRADAR_APP;
	if(app==NULL)
	{
		MessageBox("appδ��ʼ����");
		exit(0);
	}
	int ret=app->Init(this->GetSafeHwnd());
	if(ret!=META_ERR_SUCCESS)
	{
		CString str;
		str.Format("��ʼ��APP���󣡴�����Ϣ:%s",CRadarEnumMap::m_appErrorArray[-ret]);
		MessageBox(str);
		exit(0);
	
	}
	SetWindowText("�����״��ںϱ������");
	//��ʼ����ͼ�ؼ�
	InitMapCtrl();

	m_startBtn.EnableWindow(TRUE);
	m_stopBtn.EnableWindow(FALSE);

	//������¼
	m_alarmRecordList.InsertColumn(0,"ʱ��",LVCFMT_CENTER,100);
    m_alarmRecordList.InsertColumn(1,"Ŀ��",LVCFMT_CENTER,60);
	m_alarmRecordList.InsertColumn(2,"�Ƕ�(��)",LVCFMT_CENTER,60);
	m_alarmRecordList.InsertColumn(3,"����(m)",LVCFMT_CENTER,60);
	m_alarmRecordList.InsertColumn(4,"���(m)",LVCFMT_CENTER,60);
	
	//��ʼ����ť
	m_closeBtn.MoveWindow(279,25,91,27);
	m_closeBtn.LoadBmp(UI_MAIN_CLOSEBTN_NORMAL,UI_MAIN_CLOSEBTN_HOVER,UI_MAIN_CLOSEBTN_NORMAL);

	m_startBtn.MoveWindow(24,99,98,32);
	m_startBtn.LoadBmp(UI_MAIN_OPENRADARBTN_NORMAL,UI_MAIN_OPENRADARBTN_HOVER,UI_MAIN_OPENRADARBTN_DISABLE);


	m_stopBtn.MoveWindow(152,99,98,32);
	m_stopBtn.LoadBmp(UI_MAIN_STOPRADARBTN_NORMAL,UI_MAIN_STOPRADARBTN_HOVER,UI_MAIN_STOPRADARBTN_DISABLE);

	m_historyBtn.MoveWindow(279,99,98,32);
	m_historyBtn.LoadBmp(UI_MAIN_HISTORYBTN_NORMAL,UI_MAIN_HISTORYBTN_HOVER,UI_MAIN_HISTORYBTN_DISABLE);

	///////
	m_paramBtn.MoveWindow(24,142,98,32);
	m_paramBtn.LoadBmp(UI_MAIN_PARAMBTN_NORMAL,UI_MAIN_PARAMBTN_HOVER,UI_MAIN_PARAMBTN_DISABLE);
	
	m_alarmBtn.MoveWindow(152,142,98,32);
	m_alarmBtn.LoadBmp(UI_MAIN_ALARMBTN_ON,UI_MAIN_ALARMBTN_OFF,UI_MAIN_ALARMBTN_DISABLE);
	
	m_soundBtn.MoveWindow(279,142,98,32);
	m_soundBtn.LoadBmp(UI_MAIN_SOUNDBTN_ON,UI_MAIN_SOUNDBTN_OFF,UI_MAIN_SOUNDBTN_DISABLE);
	

	//��ȡϵͳ����
	LoadSysParam();

	return TRUE;  // return TRUE  unless you set the focus to a control
}
void CRadarUIDlg::LoadSysParam()
{
	m_enableAlarm=app->GetAnswerAlarm();
	m_enableSound=app->GetSoundAlarm();

	CString str;
	str=m_enableAlarm?"ȡ������":"��Ӧ����";
	m_alarmBtn.SetWindowText(str);
	m_alarmBtn.SetState(!m_enableAlarm);


	str=m_enableSound?"�ر�����":"��������";
	m_soundBtn.SetWindowText(str);	
	m_soundBtn.SetState(!m_enableSound);

	m_alarmListShowMaxCnt=app->GetAlarmShwoCnt();	//������¼��ʾ������

}
void CRadarUIDlg::InitMapCtrl()
{
	m_mapCtrl.InitData(MAP_ZOOMIN
		,MAP_ZOOMIND
		,MAP_ZOOMOUT
		,MAP_ZOOMOUTD
		,MAP_BG
		,MAP_STATEING
		,MAP_STATED
		,MAP_STATESTART
		,MAP_STATE_PLAYBACK);

	CRect rzoomin;
	int height;
	height=590;
	rzoomin.left=height-48-10;
	rzoomin.right=rzoomin.left+24;
	rzoomin.top=10;
	rzoomin.bottom=34;

	CRect rzoomout(rzoomin);
	rzoomout.left+=24;
	rzoomout.right+=24;

	CRect rstate;
	rstate.left=10;
	rstate.right=rstate.left+96;
	rstate.top=height-24-10;
	rstate.bottom=rstate.top+24;
	m_mapCtrl.MoveWindow(420,30,10,10);

	m_mapCtrl.InitSizes(height,height,rzoomin,rzoomout,rstate);
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CRadarUIDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CRadarBaseDlg::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CRadarUIDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CRadarUIDlg::CheckAlarmList()
{
	int cnt=m_alarmRecordList.GetItemCount();
	
	//ʼ�ձ����б�ֻ�����޸���
	while(cnt>m_alarmListShowMaxCnt)
	{
		m_alarmRecordList.DeleteItem(0);//ɾ����һ�м�¼
		cnt=m_alarmRecordList.GetItemCount();
	}

}

//�����ͼ
void CRadarUIDlg::SaveMap(BkgrdMap * map)
{
	//���жϵ����Ӧ���ļ����Ƿ��Ѿ�����
	SYSTEMTIME stime;
	GetLocalTime(&stime);

	CString timeFolder;
	timeFolder.Format("%s\\%.4d-%.2d-%.2d"
				,DIR_HISTORY
				,stime.wYear
				,stime.wMonth
				,stime.wDay);
	if(!m_fileOp.FolderExist(DIR_HISTORY))
	{
		BOOL tag=m_fileOp.CreateFolder(DIR_HISTORY);
		if(!tag)
			return;		
	}
	if(!m_fileOp.FolderExist(timeFolder))
	{
		BOOL tag=m_fileOp.CreateFolder(timeFolder);
		if(!tag)
			return;
	}
	CString timeFile;
	timeFile.Format("%s\\%.2d-%.2d-%.2d.xml"
					,timeFolder
					,stime.wHour
					,stime.wMinute
					,stime.wSecond);
	m_xmlFileName=timeFile;

	//���浽XML�ļ�
	MSXML2::IXMLDOMDocumentPtr pDoc;
	MSXML2::IXMLDOMElementPtr xmlRoot;
	HRESULT hr = pDoc.CreateInstance(__uuidof(MSXML2::DOMDocument30));
	if(!SUCCEEDED(hr))
	{
		MessageBox("����XML�ļ�--��ʼ������");
		return;
	}
	pDoc->raw_createElement((_bstr_t)(char*)"xml", &xmlRoot);
	pDoc->raw_appendChild(xmlRoot, NULL);
	
	MSXML2::IXMLDOMElementPtr childNode;
	pDoc->raw_createElement((_bstr_t)(char*)"map", &childNode);

	CString str;

	childNode->setAttribute("bReady", "TRUE");

	str.Format("%.4d-%.2d-%.2d %.2d:%.2d:%.2d"
				,map->time.wYear
				,map->time.wMonth
				,map->time.wDay
				,map->time.wHour
				,map->time.wMinute
				,map->time.wSecond);
	char *pChar=str.GetBuffer(str.GetLength());
	childNode->setAttribute("time", pChar);
	
	str.Format("%d",map->mapDataLength);
	pChar=str.GetBuffer(str.GetLength());
	childNode->setAttribute("dataLength", pChar);

	str.Format("%d",map->startAngle);
	pChar=str.GetBuffer(str.GetLength());
	childNode->setAttribute("startAngle", pChar);

	str.Format("%d",map->stopAngle);
	pChar=str.GetBuffer(str.GetLength());
	childNode->setAttribute("stopAngle", pChar);

	xmlRoot->appendChild(childNode);
	
	for(int i=0;i<map->mapDataLength;i++)
	{
		MSXML2::IXMLDOMElementPtr data;
		pDoc->raw_createElement((_bstr_t)(char*)"data", &data);

		str.Format("%d",map->data[i]);
		pChar=str.GetBuffer(str.GetLength());

		data->Puttext(pChar);
		childNode->appendChild(data);
	}
	
	//����warningData�ڵ㣬���ڴ�ű����ڵ�����
	pDoc->raw_createElement((_bstr_t)(char*)"warningData", &childNode);
	xmlRoot->appendChild(childNode);
	
	pChar=m_xmlFileName.GetBuffer(m_xmlFileName.GetLength());

	pDoc->save(pChar);

}
//���汨������
void CRadarUIDlg::SaveWarnigData(WarningResult * warningData)
{
	if(m_xmlFileName=="")
		return;
	MSXML2::IXMLDOMDocumentPtr pDoc;
	HRESULT hr = pDoc.CreateInstance(__uuidof(MSXML2::DOMDocument30));
	if(!SUCCEEDED(hr))
	{
		MessageBox("���汨������--��ʼ������!");
		return;
	}
	char * pChar=m_xmlFileName.GetBuffer(m_xmlFileName.GetLength());
	pDoc->load(pChar);
	
	MSXML2::IXMLDOMElementPtr node;
	node = (MSXML2::IXMLDOMElementPtr)(pDoc->selectSingleNode("//warningData"));
	if(node==NULL)
		return;
	MSXML2::IXMLDOMElementPtr childNode;
	pDoc->raw_createElement((_bstr_t)(char*)"warningResult", &childNode);

	CString str;
	str.Format("%.4d-%.2d-%.2d %.2d:%.2d:%.2d"
				,warningData->time.wYear
				,warningData->time.wMonth
				,warningData->time.wDay
				,warningData->time.wHour
				,warningData->time.wMinute
				,warningData->time.wSecond);
	pChar=str.GetBuffer(str.GetLength());
	childNode->setAttribute("time", pChar);

	str.Format("%d",warningData->objNum);
	pChar=str.GetBuffer(str.GetLength());
	childNode->setAttribute("objNum", pChar);

	node->appendChild(childNode);
	
	for(int i=0;i<warningData->objNum;i++)
	{
		MSXML2::IXMLDOMElementPtr data;
		pDoc->raw_createElement((_bstr_t)(char*)"warningObject", &data);
		
		str.Format("%d",warningData->obj[i].angle);
		pChar=str.GetBuffer(str.GetLength());
		data->setAttribute("angle", pChar);


		str.Format("%d",warningData->obj[i].distance);
		pChar=str.GetBuffer(str.GetLength());
		data->setAttribute("distance", pChar);

		str.Format("%d",warningData->obj[i].objWidth);
		pChar=str.GetBuffer(str.GetLength());
		data->setAttribute("objWidth", pChar);

		childNode->appendChild(data);		
	}
	pChar=m_xmlFileName.GetBuffer(m_xmlFileName.GetLength());
	pDoc->save(pChar);	
	
}

//��������¼�����
LRESULT CRadarUIDlg::OnGetData(WPARAM wParam, LPARAM lParam)
{
	DataFrame * pData;
	pData=(DataFrame *)wParam;

	WarningResult * result=(WarningResult *)lParam;//��ȡ���ս������

	if(result->objNum>0)
	{
		//���汨�����
		SaveWarnigData(result);
	}
	//ֻ�е��б������������������λ��������Ӧ�������ſ��Ա���
	if(result->objNum>0 
		&& m_enableAlarm)
	{
		if(m_enableSound)
		{			
			PlaySound(ALARM_SOUND,NULL, SND_ASYNC|SND_NODEFAULT );
		}
		
		CString str;
		
		//���õ�ͼ��ʾ�ؼ������������֪ͨ
		m_mapCtrl.m_map_warningResult=*result;
		m_mapCtrl.Invalidate(TRUE);


		//��ʾ��������
		for(int i=0;i<result->objNum;i++)
		{
			str.Format("%d:%d:%d"
				,result->time.wHour
				,result->time.wMinute
				,result->time.wSecond);
			
			int itemCnt=m_alarmRecordList.GetItemCount();
			
			int nRow = m_alarmRecordList.InsertItem(itemCnt, str);//������
			str.Format("Ŀ��%d",i);
			m_alarmRecordList.SetItemText(nRow, 1, str);//���õ�1�����ݣ���һ���������У��ڶ����������У�������������ֵ
			
			str.Format("%0.2f",result->obj[i].angle*0.2);
			m_alarmRecordList.SetItemText(nRow, 2, str);
			
			double v=0;
			v=(double)result->obj[i].distance/1000;
			
			str.Format("%0.2f",v);
			m_alarmRecordList.SetItemText(nRow, 3, str);
			
			v=(double)result->obj[i].objWidth/1000;
			str.Format("%0.2f",v);
			m_alarmRecordList.SetItemText(nRow, 4, str);
			
			m_alarmRecordList.EnsureVisible(nRow, FALSE);
		}
		int itemC=m_alarmRecordList.GetItemCount();		
		int nR = m_alarmRecordList.InsertItem(itemC, "-");//������
		m_alarmRecordList.SetItemText(nR, 1, "-");
		m_alarmRecordList.SetItemText(nR, 2, "-");
		m_alarmRecordList.SetItemText(nR, 3, "-");
		m_alarmRecordList.SetItemText(nR, 4, "-");
		
		CheckAlarmList();//��鱨����¼�б����̫������Ҫȥ�������������ݣ����ⱬ��
	}
	return 0;
}

//��ȡ��ͼ������Ӧ����
LRESULT CRadarUIDlg::OnGetMap(WPARAM wParam, LPARAM lParam)
{
	BkgrdMap * map=(BkgrdMap *)wParam;
	m_mapCtrl.m_map_bkgrdMap=*map;
	m_mapCtrl.m_state=RDScanning;//ѧϰ���,ɨ����
	
	m_mapCtrl.Invalidate(TRUE);
	
	//�����ͼ����
	SaveMap(map);
	return 0;
}
//��ȡ���ݳ�ʱ��Ϣ����
LRESULT CRadarUIDlg::OnDataTimeOut(WPARAM wParam, LPARAM lParam)
{
	OnButtonStopRadar();
	MessageBox("��ȡ���ݳ�ʱ���޷���ȡԭʼ���ݣ�");	
	return 0;
}
LRESULT CRadarUIDlg::OnSysParamChange(WPARAM wParam, LPARAM lParam)
{
	LoadSysParam();
	return 0;
}



//�����״�
void CRadarUIDlg::OnButtonStartRadar() 
{	
	// TODO: Add your control notification handler code here	
	m_mapCtrl.m_map_warningResult.objNum=0;//��ձ����ڵ�
	m_mapCtrl.m_map_bkgrdMap.bReady=FALSE;

	m_mapCtrl.m_state=RDStudying;	//ѧϰ��
	m_mapCtrl.Invalidate(TRUE);
	m_mapCtrl.RedrawWindow();

	
	app->UpdateRadarConfig();//ÿ�ζ�Ҫ����INI�ļ��Ĳ���������ʹ���ĸ��״�	

	app->UpdateAlgConfig();//ÿ�ζ�Ҫ����һ���㷨�Ĳ�������Ϊֹͣ������֮�䣬�û�����ȥ�������㷨������

	int ret=app->StartRadar();
	if(ret<0)
	{
		CString str;
		str.Format("�����״����������Ϣ��%s",CRadarEnumMap::m_appErrorArray[-ret]);
		MessageBox(str);
		m_mapCtrl.m_state=RDReadyScan;//��ɨ��
		m_mapCtrl.Invalidate(TRUE);
		return ;
	}
	m_startBtn.EnableWindow(FALSE);
	m_stopBtn.EnableWindow(TRUE);
	
	m_alarmRecordList.DeleteAllItems();

}

//ֹͣ�״�
void CRadarUIDlg::OnButtonStopRadar() 
{
	// TODO: Add your control notification handler code here
	app->StopRadar();
	m_mapCtrl.m_state=RDReadyScan;
	m_mapCtrl.Invalidate();
	m_startBtn.EnableWindow(TRUE);
	m_stopBtn.EnableWindow(FALSE);
	m_xmlFileName="";//���֮ǰ������ļ���Ϣ�������´��ٴδ�ȡ��ͬһ���ļ�
}

void CRadarUIDlg::OnButtonSet() 
{
	// TODO: Add your control notification handler code here	
	
	CRadarParamSetDlg dlg;
	dlg.DoModal();
}

void CRadarUIDlg::OnButtonAlarm() 
{
	// TODO: Add your control notification handler code here
	m_enableAlarm=!m_enableAlarm;
	
	app->SetAnswerAlarm(m_enableAlarm);

	CString str;
	str=m_enableAlarm?"ȡ������":"��Ӧ����";
	m_alarmBtn.SetWindowText(str);
	m_alarmBtn.SetState(!m_enableAlarm);

}

void CRadarUIDlg::OnButtonClosesound() 
{
	// TODO: Add your control notification handler code here
	m_enableSound=!m_enableSound;
	
	app->SetSoundAlarm(m_enableSound);

	CString str;
	str=m_enableSound?"�ر�����":"��������";
	m_soundBtn.SetWindowText(str);
	m_soundBtn.SetState(!m_enableSound);

}

void CRadarUIDlg::OnButtonHistory() 
{
	// TODO: Add your control notification handler code here
	CRadarHistoryDlg dlg;
	dlg.DoModal();
}

BOOL CRadarUIDlg::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	ShowBmpPicByHBITMAP(pDC->m_hDC,m_hbmpBg,0,0);
	
	return TRUE;
	//return CRadarBaseDlg::OnEraseBkgnd(pDC);
}

void CRadarUIDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_pos=point;
	ismove=true;

	CRadarBaseDlg::OnLButtonDown(nFlags, point);
}

void CRadarUIDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	ismove=false;

	CRadarBaseDlg::OnLButtonUp(nFlags, point);
}

void CRadarUIDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CPoint x_pos;
	CRect x_rect;
	int x_x;
	int x_y;
	
	//ȡ�ô���λ�ô�С�ṹ
	GetWindowRect(&x_rect);
	//�������Ͻ�����
	x_pos=x_rect.TopLeft();
		
	if (ismove)
	{
		x_x=point.x-m_pos.x;
		x_y=point.y-m_pos.y;
		x_pos.Offset(x_x,x_y);
		SetWindowPos(&wndTopMost,x_pos.x,x_pos.y,0,0,SWP_NOSIZE|SWP_NOZORDER);
	}
	else
	{
		
		//�������
		//������뿪��ť������յ�WM_MOUSELEAVE,����Ϣֱ�ӵ���OnMouseOut()
		TRACKMOUSEEVENT	tme;
		tme.cbSize =sizeof(TRACKMOUSEEVENT);
		tme.dwFlags =TME_LEAVE;
		tme.dwHoverTime=0;
		tme.hwndTrack =m_hWnd;
		::TrackMouseEvent(&tme);

	}

	CRadarBaseDlg::OnMouseMove(nFlags, point);
}
void CRadarUIDlg::OnMouseOut (WPARAM   wParam,   LPARAM   lParam)
{
    ismove =false;		
}
