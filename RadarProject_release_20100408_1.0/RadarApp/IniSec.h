/*****************************************************************
*�ļ�����			inisec.h
*����������	        -
*����������	        -
*��˾����			�п�Ժ������������ҵ�о�Ժ
*��ǰ�汾�ţ�	    v1.0
*
*Copyright? 2009, �п�Ժ������������ҵ�о�Ժ All rights reserved.
*
*����			ʱ��					��ע
*zhangyong		2010-1-19			
*
*˵��
	INI�ļ��и��ֶΣ�����������
******************************************************************/

#ifndef _RADARAPPINISEC_H_
#define _RADARAPPINISEC_H_

/*****************INI��������*************************/

#define INI_SEC_SYS						"system"							//ϵͳ��
#define INI_SEC_RADAR					"radar"								//�״����ö�
#define INI_SEC_ALG						"algorithm"							//�㷨���ö�


/*****************INI����������*************************/

//ϵͳ����
#define INI_P_SYS_PWD							"pwd"						//����
#define INI_P_SYS_ANSWERALARM					"answerAlarm"				//�Ƿ���Ӧ����
#define INI_P_SYS_SOUNDALARM					"soundAlarm"				//�Ƿ�����������
#define INI_P_SYS_ALARMSHOWCNT					"alarmshowcnt"				//������¼��ʾ����


//�״ﲿ��
#define INI_P_RADAR_PRODUCT						"product"					//�״��Ʒ
#define INI_P_RADAR_BITRATE						"bitrate"					//������
#define INI_P_RADAR_COMPORT						"comport"					//com��
#define INI_P_RADAR_STARTANGLE					"startangle"				//��ʼ�ǣ�0.2��λ��
#define INI_P_RADAR_STOPANGLE					"stopangle"					//������
#define INI_P_RADAR_IPADDR						"ipaddr"					//ip��ַ
#define INI_P_RADAR_IPPORT						"ipport"					//ip�˿�
#define INI_P_RADAR_MOTORRATE					"motorRate"					//���ת��
#define INI_P_RADAR_SAVERAWDATA					"saveRawData"				//�Ƿ񱣴�ԭʼ����
#define INI_P_RADAR_RAWDATAFILE					"rawDataFile"				//ԭʼ���ݴ��·��
#define INI_P_RADAR_VALIDDISTANCE				"validDistance"				//��Ч����

//�㷨����
#define INI_P_ALG_BKGRDOFFSET					"bkgrdOffset"				//�㷨����--����ƫ��������λ�����ף�
#define INI_P_ALG_BLDMAPPERIOD					"bldmapPeriod"				//�㷨����--������ͼ�Ľ�������
#define INI_P_ALG_CHKWIDTHTHRESHOLD				"chkWidthThreshold"			//�㷨����--Ŀ����˿����ֵ����λ�����ף�
#define INI_P_ALG_FUSHIONSTEPNUM				"fushionStepNum"			//�㷨����--�ںϲ���
#define INI_P_ALG_SAMEOBLENGTH					"sameobLength"				//�㷨����--�ж�ΪͬһĿ��ĳ�����ֵ����λ�����ף�
#define INI_P_ALG_FUSHIONTIME					"fushionTime"				//�㷨����--�ں�ʱ��������λ�����룩
#define INI_P_ALG_RADARTYPE						"radarType"					//�㷨����--�״�����



#endif