#ifndef QRK_C_SERIAL_T_WIN_H
#define QRK_C_SERIAL_T_WIN_H

/*!
  \file
  \brief �V���A������̍\���� (Windows ����)

  \author Satofumi KAMIMURA

  $Id: serial_t_win.h 1286 2009-09-10 02:19:02Z satofumi $
*/

#include <windows.h>


enum {
  SerialErrorStringSize = 256,
};


/*!
  \brief �V���A������̍\����
*/
typedef struct {
  HANDLE hCom_;                 /*!< �ڑ����\�[�X */
  char has_last_ch_;            /*!< �����߂������������邩�̃t���O */
  char last_ch_;                /*!< �����߂����P���� */
  int current_timeout_;         /*!< �^�C���A�E�g�̐ݒ莞�� [msec] */
} serial_t;

#endif /* !QRK_C_SERIAL_T_LIN_H */
