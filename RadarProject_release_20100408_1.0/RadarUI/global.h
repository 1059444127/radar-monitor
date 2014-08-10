/*****************************************************************
*�ļ�����			global.h
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
	ȫ��ͷ�ļ���ȫ�ֵĺ궨��������
******************************************************************/
#ifndef _RDGlobal_H_
#define _RDGlobal_H_

#define WM_SYSPARAM_CHANGE	WM_USER+201		//ϵͳ�����ı���Ϣ


//�״�ؼ����ͼƬ�궨��
#define MAP_BG				"bmp\\map\\bg.bmp"
#define MAP_STATEING		"bmp\\map\\stateing.bmp"		//ѧϰ��
#define MAP_STATED			"bmp\\map\\stated.bmp"		//ѧϰ��ɣ�ɨ����
#define MAP_STATESTART		"bmp\\map\\statestart.bmp"	//�ȴ�����
#define MAP_STATE_PLAYBACK	"bmp\\map\\playback.bmp"		//���ݻط�

#define MAP_ZOOMIN			"bmp\\map\\zoomin.bmp"
#define MAP_ZOOMIND			"bmp\\map\\zoomind.bmp"
#define MAP_ZOOMOUT			"bmp\\map\\zoomout.bmp"
#define MAP_ZOOMOUTD		"bmp\\map\\zoomoutd.bmp"


//��������
#define ALARM_SOUND			"wav\\alarm.wav"

//��ʷ����Ŀ¼
#define DIR_HISTORY			"history"



//////////////////////////////////////UI����BMP////////////////////////////////////
#define UI_MAINBG								"bmp\\mainbg.bmp"
//�رհ�ť
#define UI_MAIN_CLOSEBTN_NORMAL					"bmp\\mainCloseBtnN.bmp"
#define UI_MAIN_CLOSEBTN_HOVER					"bmp\\mainCloseBtnH.bmp"

//�����״ﰴť
#define UI_MAIN_OPENRADARBTN_NORMAL				"bmp\\mainStartBtnN.bmp"
#define UI_MAIN_OPENRADARBTN_HOVER				"bmp\\mainStartBtnH.bmp"
#define UI_MAIN_OPENRADARBTN_DISABLE			"bmp\\mainStartBtnD.bmp"

//ֹͣ�״ﰴť
#define UI_MAIN_STOPRADARBTN_NORMAL				"bmp\\mainStopBtnN.bmp"
#define UI_MAIN_STOPRADARBTN_HOVER				"bmp\\mainStopBtnH.bmp"
#define UI_MAIN_STOPRADARBTN_DISABLE			"bmp\\mainStopBtnD.bmp"

//��ʷ���ݰ�ť
#define UI_MAIN_HISTORYBTN_NORMAL				"bmp\\mainHistoryBtnN.bmp"
#define UI_MAIN_HISTORYBTN_HOVER				"bmp\\mainHistoryBtnH.bmp"
#define UI_MAIN_HISTORYBTN_DISABLE				"bmp\\mainHistoryBtnD.bmp"

//�������ð�ť
#define UI_MAIN_PARAMBTN_NORMAL					"bmp\\mainParamBtnN.bmp"
#define UI_MAIN_PARAMBTN_HOVER					"bmp\\mainParamBtnH.bmp"
#define UI_MAIN_PARAMBTN_DISABLE				"bmp\\mainParamBtnD.bmp"

//��Ӧ/ȡ��������ť
#define UI_MAIN_ALARMBTN_ON						"bmp\\mainAlarmBtnAnwser.bmp"
#define UI_MAIN_ALARMBTN_OFF					"bmp\\mainAlarmBtnCancel.bmp"
#define UI_MAIN_ALARMBTN_DISABLE				"bmp\\mainAlarmBtnCancel.bmp"

//����/�ر�������ť
#define UI_MAIN_SOUNDBTN_ON						"bmp\\mainOpenSoundBtn.bmp"
#define UI_MAIN_SOUNDBTN_OFF					"bmp\\mainCloseSoundBtn.bmp"
#define UI_MAIN_SOUNDBTN_DISABLE				"bmp\\mainOpenSoundBtn.bmp"

//��½
#define UI_LOGINBG								"bmp\\loginbg.bmp"
#define UI_LOGINBTN_NORMAL						"bmp\\loginnormal.bmp"
#define UI_LOGINBTN_HOVER						"bmp\\loginhover.bmp"

//�ر�
#define UI_LOGINCLOSEBTN_NORMAL					"bmp\\logincloseN.bmp"
#define UI_LOGINCLOSEBTN_HOVER					"bmp\\logincloseH.bmp"

///////////////////////////��ʷ����
#define UI_HISTORY_BG							"bmp\\history\\historybg.bmp"
#define UI_HISTORY_RETURNN						"bmp\\history\\returnn.bmp"
#define UI_HISTORY_RETURNH						"bmp\\history\\returnh.bmp"
#define UI_HISTORY_RETURND						"bmp\\history\\returnd.bmp"

#define UI_HISTORY_REFRESHN						"bmp\\history\\refreshn.bmp"
#define UI_HISTORY_REFRESHH						"bmp\\history\\refreshh.bmp"
#define UI_HISTORY_REFRESHD						"bmp\\history\\refreshd.bmp"

///////////////////////////��������
#define UI_PARAM_BG								"bmp\\paramset\\paramsetbg.bmp"

#define UI_PARAM_ALGSETN						"bmp\\paramset\\algsetn.bmp"
#define UI_PARAM_ALGSETH						"bmp\\paramset\\algseth.bmp"
#define UI_PARAM_ALGSETD						"bmp\\paramset\\algsetd.bmp"

#define UI_PARAM_PWDSETN						"bmp\\paramset\\pwdsetn.bmp"
#define UI_PARAM_PWDSETH						"bmp\\paramset\\pwdseth.bmp"
#define UI_PARAM_PWDSETD						"bmp\\paramset\\pwdsetd.bmp"

#define UI_PARAM_RADARSETN						"bmp\\paramset\\radarsetn.bmp"
#define UI_PARAM_RADARSETH						"bmp\\paramset\\radarseth.bmp"
#define UI_PARAM_RADARSETD						"bmp\\paramset\\radarsetd.bmp"

#define UI_PARAM_SYSSETN						"bmp\\paramset\\syssetn.bmp"
#define UI_PARAM_SYSSETH						"bmp\\paramset\\sysseth.bmp"
#define UI_PARAM_SYSSETD						"bmp\\paramset\\syssetd.bmp"


////////////////////////COMMON
#define UI_COMMON_CONFIRMN						"bmp\\common\\confirmn.bmp"
#define UI_COMMON_CONFIRMH						"bmp\\common\\confirmh.bmp"
#define UI_COMMON_CONFIRMD						"bmp\\common\\confirmd.bmp"

#define UI_COMMON_RETURNN						"bmp\\common\\returnn.bmp"
#define UI_COMMON_RETURNH						"bmp\\common\\returnh.bmp"
#define UI_COMMON_RETURND						"bmp\\common\\returnd.bmp"

#define UI_COMMON_RADIO_UNCHECKED				"bmp\\common\\radioUnchecked.bmp"
#define UI_COMMON_RADIO_CHECKED					"bmp\\common\\radiochecked.bmp"

///////////////////////PWD SET
#define UI_PWD_BG								"bmp\\pwd\\pwdBg.bmp"

///////////////////////SYS SET
#define UI_SYSTEM_BG							"bmp\\system\\sysBg.bmp"

///////////////////////RADAR SET
#define UI_RADAR_BG								"bmp\\radar\\radarBg.bmp"

///////////////////////ALG SET
#define UI_ALG_BG								"bmp\\alg\\algbg.bmp"

#endif 