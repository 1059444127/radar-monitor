#ifndef C_SERIAL_T_LIN_H
#define C_SERIAL_T_LIN_H

/*!
  \file
  \brief �V���A������̍\���� (Linux, Mac ����)

  \author Satofumi KAMIMURA

  $Id: serial_t_lin.h 136 2008-07-29 10:27:20Z satofumi $
*/

#include <termios.h>


enum {
  SerialErrorStringSize = 256,
};


/*!
  \brief �V���A������̍\����
*/
typedef struct {

  int errno_;                                //!< �G���[�ԍ�
  char error_string_[SerialErrorStringSize]; //!< �G���[������
  int fd_;                                   //!< �ڑ����\�[�X
  struct termios sio_;                       //!< �^�[�~�i������
  char last_ch_;                             //!< �����߂����P����

} serial_t;

#endif /*! C_SERIAL_T_LIN_H */
