//################################################
// DC���[�^
//  Motor	 : Faulhaber 1717T06SR
//  Driver	 : TB6612FNG
//  Encoder	 : IE2-256
//                             			 K.Richardo
//################################################
#ifndef MIDDLEWARES_MOTOR_H_
#define MIDDLEWARES_MOTOR_H_

//************************************************
// Include�錾
//************************************************
#include "main.h"

//************************************************
// Define�錾
//************************************************
#define MOT_T 			0.001f							// ������� : 1 ms
#define RAD_TO_DEG		57.29578f						// ���W�A������degree�ɕϊ�
#define DEG_TO_RAD		1/RAD_TO_DEG					// degree���烉�W�A���ɕϊ�
// ���{�b�g�d�l�p�����[�^
#define ROBOT_MASS 		99 								// �d��[g]
#define GEAR_PINION 	9.0f							// �s�j�I���̎���
#define GEAR_WHEEL		42.0f							// �z�C�[���̎���
#define GEAR_RATIO		( GEAR_PINION / GEAR_WHEEL )	// �s�j�I���ƃz�C�[���̃M�A��
#define WHEEL_D			(24.95/1000.0)				// �z�C�[���̒��a[mm]
#define WHEEL_R			( WHEEL_D/2.0 )					// �z�C�[���̔��a[mm]
#define ROBOT_THREAD 	64.0f 							// �X���b�h��[mm]
#define PULSE_TO_RPM 	( 60.0 * 1000.0 / 1024.0 )		// �p���X���烂�[�^�̉�]���̕ϐ��W��[rpm]
#define PULSE_TO_MMPS 	( M_PI * WHEEL_D * 1000.0 / 1024.0 * GEAR_PINION / GEAR_WHEEL * 1000.0 )	//�p���X����}�E�X���x�̕ϊ��W��[mm/s]

#define MOT_ENABLE 		1		// ���[�^�̃C�l�[�u��:�@high�o��
#define MOT_DISABLE 	0		// ���[�^�̃f�B�X�G�[�u��: low�o��

// �ړ������̓���
#define FORWARD 		0		// �O�i
#define BACKWARD		1		// ��i
#define BRAKE			2		// �u���[�L
#define FREE			3		//�@�t���[

// �z��̊i�[��
#define MOT_L			0		// �����[�^���x
#define MOT_R			1		// �E���[�^���x

// GPIO�֐��ȗ��p��`
#define	MOT_LIN1(x)		HAL_GPIO_WritePin(MOT_AIN1_GPIO_Port, MOT_AIN1_Pin, x);
#define MOT_LIN2(x)		HAL_GPIO_WritePin(MOT_AIN2_GPIO_Port, MOT_AIN2_Pin, x);
#define MOT_STBY(x)		HAL_GPIO_WritePin(MOT_STBY_GPIO_Port, MOT_STBY_Pin, x);
#define MOT_RIN1(x)		HAL_GPIO_WritePin(MOT_BIN1_GPIO_Port, MOT_BIN1_Pin, x);
#define MOT_RIN2(x)		HAL_GPIO_WritePin(MOT_BIN2_GPIO_Port, MOT_BIN2_Pin, x);

//************************************************
// �O���[�o���ϐ��錾
//************************************************
extern ENC_T Enc;

//************************************************
// �֐��v���g�^�C�v�錾
//************************************************
void MOT_Init( void );
void MOT_Set_Enable( uint8_t x );
void MOT_Set_Dir( uint8_t ldir, uint8_t rdir );
void MOT_Set_Duty( int16_t lduty, int16_t rduty );
void ENC_Read( void );

#endif /* MIDDLEWARES_MOTOR_H_ */
