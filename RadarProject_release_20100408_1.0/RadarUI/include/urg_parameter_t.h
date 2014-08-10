#ifndef URG_PARAMETER_T_H
#define URG_PARAMETER_T_H

/*!
  \file
  \brief URG �̃p�����[�^���

  \author Satofumi KAMIMURA

  $Id: urg_parameter_t.h 411 2008-12-22 05:48:43Z satofumi $
*/


enum {
  UrgParameterLines = 8 + 1 + 1,
};


/*!
  \brief URG �̃p�����[�^���
*/
typedef struct {
  long distance_min_;		/*!< DMIN ��� */
  long distance_max_;		/*!< DMAX ��� */
  int area_total_;		/*!< ARES ��� */
  int area_min_;		/*!< AMIN ��� */
  int area_max_;		/*!< AMAX ��� */
  int area_front_;		/*!< AFRT ��� */
  int scan_rpm_;		/*!< SCAN ��� */
} urg_parameter_t;

#endif /* !URG_PARAMETER_T_H */
