#ifndef QRK_C_URG_T_H
#define QRK_C_URG_T_H

/*!
  \file
  \brief URG ����p�̍\����

  \author Satofumi KAMIMURA

  $Id: urg_t.h 979 2009-06-08 16:54:46Z satofumi $
*/

#include "urg_parameter_t.h"
#include "serial_t.h"


/*!
  \brief URG ����p�̒萔
*/
typedef enum {
  UrgLaserOff = 0,
  UrgLaserOn,
  UrgLaserUnknown,
} urg_laser_state_t;


/*!
  \brief URG ����p�̍\����
*/
typedef struct {

  serial_t serial_;              /*!< �V���A������̍\���� */
  int errno_;                    /*!< �G���[�ԍ��̊i�[ */
  urg_parameter_t parameters_;   /*!< �Z���T�p�����[�^ */

  int skip_lines_;               /*!< ���C���Ԉ����� */
  int skip_frames_;              /*!< �X�L�����Ԉ�����(MD/MS �̂�) */
  int capture_times_;            /*!< �f�[�^�擾��(MD/MS �̂�) */

  urg_laser_state_t is_laser_on_; /*!< ���[�U�������̂Ƃ��� 0 */

  long last_timestamp_;          /*!< �ŏI�̃^�C���X�^���v */
  int remain_times_;             /*!< �f�[�^�擾�̎c��� */

  char remain_data_[3];
  int remain_byte_;

} urg_t;

#endif /* !QRK_C_URG_T_H */
