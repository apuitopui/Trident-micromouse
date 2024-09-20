//################################################
// ���[�U�C���^�t�F�[�X
//                             			K.Richardo
//################################################
#include "ui.h"

//************************************************
// �ϐ��錾
//************************************************
bool buzzer_flg = BUZZER_ON;		// �u�U�[�~���[�g�t���O

//===============================================
// LED : �SLED�_��
//===============================================
void LED_Set_All_On( void )
{
    HAL_GPIO_WritePin( LED1_GPIO_Port, LED1_Pin, LED_ON );	// LED1�_��
	HAL_GPIO_WritePin( LED2_GPIO_Port, LED2_Pin, LED_ON );	// LED2�_��
	HAL_GPIO_WritePin( LED3_GPIO_Port, LED3_Pin, LED_ON );	// LED3�_��
	HAL_GPIO_WritePin( LED4_GPIO_Port, LED4_Pin, LED_ON );	// LED4�_��
}

//===============================================
// LED : �SLED����
//===============================================
void LED_Set_All_Off( void )
{
	HAL_GPIO_WritePin( LED1_GPIO_Port, LED1_Pin, LED_OFF );	// LED1����
	HAL_GPIO_WritePin( LED2_GPIO_Port, LED2_Pin, LED_OFF );	// LED2����
	HAL_GPIO_WritePin( LED3_GPIO_Port, LED3_Pin, LED_OFF );	// LED3����
	HAL_GPIO_WritePin( LED4_GPIO_Port, LED4_Pin, LED_OFF );	// LED4����
}

//===============================================
// LED : �N�����̉��o
//===============================================
void LED_Set_PowerOn( void )
{
	LED_Set_All_Off();
	HAL_GPIO_WritePin( LED1_GPIO_Port, LED1_Pin, LED_ON );	// LED1�_��
	HAL_Delay( 50 );										// 100 ms�҂�

	HAL_GPIO_WritePin( LED1_GPIO_Port, LED1_Pin, LED_OFF );	// LED1����
	HAL_GPIO_WritePin( LED2_GPIO_Port, LED2_Pin, LED_ON );	// LED2�_��
	HAL_Delay( 50 );										// 100 ms�҂�

	HAL_GPIO_WritePin( LED2_GPIO_Port, LED2_Pin, LED_OFF );	// LED2����
	HAL_GPIO_WritePin( LED3_GPIO_Port, LED3_Pin, LED_ON );	// LED3�_��
	HAL_Delay( 50 );										// 100 ms�҂�

	HAL_GPIO_WritePin( LED3_GPIO_Port, LED3_Pin, LED_OFF );	// LED3����
	HAL_GPIO_WritePin( LED4_GPIO_Port, LED4_Pin, LED_ON );	// LED4�_��
	HAL_Delay( 50 );										// 100 ms�҂�

	HAL_GPIO_WritePin( LED4_GPIO_Port, LED4_Pin, LED_OFF );	// LED4����
	HAL_GPIO_WritePin( LED3_GPIO_Port, LED3_Pin, LED_ON );	// LED3�_��
	HAL_Delay( 50 );										// 100 ms�҂�

	HAL_GPIO_WritePin( LED3_GPIO_Port, LED3_Pin, LED_OFF );	// LED3����
	HAL_GPIO_WritePin( LED2_GPIO_Port, LED2_Pin, LED_ON );	// LED2�_��
	HAL_Delay( 50 );										// 100 ms�҂�

	HAL_GPIO_WritePin( LED2_GPIO_Port, LED2_Pin, LED_OFF );	// LED2����
	HAL_GPIO_WritePin( LED1_GPIO_Port, LED1_Pin, LED_ON );	// LED1�_��
	HAL_Delay( 50 );										// 100 ms�҂�

	HAL_GPIO_WritePin( LED1_GPIO_Port, LED1_Pin, LED_OFF );	// LED1����
}

//===============================================
// LED : ���莞�̉��o
//===============================================
void LED_Set_Confirm( void )
{
	HAL_GPIO_WritePin( LED4_GPIO_Port, LED4_Pin, LED_OFF );	// LED4����
	HAL_GPIO_WritePin( LED3_GPIO_Port, LED3_Pin, LED_ON );	// LED3�_��
	HAL_Delay( 100 );										// 100 ms�҂�

	HAL_GPIO_WritePin( LED3_GPIO_Port, LED3_Pin, LED_OFF );	// LED3����
	HAL_GPIO_WritePin( LED2_GPIO_Port, LED2_Pin, LED_ON );	// LED2�_��
	HAL_Delay( 100 );										// 100 ms�҂�

	HAL_GPIO_WritePin( LED2_GPIO_Port, LED2_Pin, LED_OFF );	// LED2����
	HAL_GPIO_WritePin( LED1_GPIO_Port, LED1_Pin, LED_ON );	// LED1�_��
	HAL_Delay( 100 );										// 100 ms�҂�

	HAL_GPIO_WritePin( LED1_GPIO_Port, LED1_Pin, LED_OFF );	// LED1����
	HAL_Delay( 100 );

//	LED_Set_All_On();	// �SLED�_��
//	HAL_Delay( 150 );	// 150 ms�҂�
//
//	LED_Set_All_Off();	// �SLED����
//	HAL_Delay( 100 );	// 100 ms�҂�

}
//===============================================
// LED : 2�i���\��(����10�i��)
//===============================================
void LED_Disp_Binary( char dec )
{
	LED_Set_All_Off();
	if( (dec & 0x01) == 0x01 ) HAL_GPIO_WritePin( LED1_GPIO_Port, LED1_Pin, LED_ON );	// 2�i����1����0�̎�LED�_��
	if( (dec & 0x02) == 0x02 ) HAL_GPIO_WritePin( LED2_GPIO_Port, LED2_Pin, LED_ON );	// 2�i����1����0�̎�LED�_��
	if( (dec & 0x04) == 0x04 ) HAL_GPIO_WritePin( LED3_GPIO_Port, LED3_Pin, LED_ON );	// 2�i����1����0�̎�LED�_��
	if( (dec & 0x08) == 0x08 ) HAL_GPIO_WritePin( LED4_GPIO_Port, LED4_Pin, LED_ON );	// 2�i����1����0�̎�LED�_��
}

//===============================================
// LED : 2S�o�b�e���d���\��
//===============================================
void LED_Disp_Batt_V( float v )
{
	LED_Set_All_Off();
	if( v > 8.0 ){
		HAL_GPIO_WritePin( LED1_GPIO_Port, LED1_Pin, LED_ON );	// LED1�_��
		HAL_Delay( 50 );
		HAL_GPIO_WritePin( LED2_GPIO_Port, LED2_Pin, LED_ON );	// LED2�_��
		HAL_Delay( 50 );
		HAL_GPIO_WritePin( LED3_GPIO_Port, LED3_Pin, LED_ON );	// LED3�_��
		HAL_Delay( 50 );
		HAL_GPIO_WritePin( LED4_GPIO_Port, LED4_Pin, LED_ON );	// LED4�_��
	}else if( v >= 7.5 ){
		HAL_GPIO_WritePin( LED1_GPIO_Port, LED1_Pin, LED_ON );	// LED1�_��
		HAL_Delay( 50 );
		HAL_GPIO_WritePin( LED2_GPIO_Port, LED2_Pin, LED_ON );	// LED2�_��
		HAL_Delay( 50 );
		HAL_GPIO_WritePin( LED3_GPIO_Port, LED3_Pin, LED_ON );	// LED3�_��
	}else if( v >= 7.2 ){
		HAL_GPIO_WritePin( LED1_GPIO_Port, LED1_Pin, LED_ON );	// LED1�_��
		HAL_Delay( 50 );
		HAL_GPIO_WritePin( LED2_GPIO_Port, LED2_Pin, LED_ON );	// LED2�_��
	}else{
		HAL_GPIO_WritePin( LED1_GPIO_Port, LED1_Pin, LED_ON );	// LED1�_��
		HAL_Delay( 50 );
		HAL_GPIO_WritePin( LED1_GPIO_Port, LED1_Pin, LED_OFF );	// LED1����
		HAL_Delay( 50 );
		HAL_GPIO_WritePin( LED1_GPIO_Port, LED1_Pin, LED_ON );	// LED1�_��
		HAL_Delay( 50 );
		HAL_GPIO_WritePin( LED1_GPIO_Port, LED1_Pin, LED_OFF );	// LED1����
		HAL_Delay( 50 );
		HAL_GPIO_WritePin( LED1_GPIO_Port, LED1_Pin, LED_ON );	// LED1�_��
		HAL_Delay( 50 );
		HAL_GPIO_WritePin( LED1_GPIO_Port, LED1_Pin, LED_OFF );	// LED1����
		HAL_Delay( 50 );
		HAL_GPIO_WritePin( LED1_GPIO_Port, LED1_Pin, LED_ON );	// LED1�_��
	}

	HAL_Delay( 1000 );
	LED_Set_All_Off();
}

//===============================================
// LED : �X�^�[�g�̐M���܂ő҂�
//===============================================
void LED_Start_Wait( void )
{
	uint16_t x = 0;								// �^�C�}�[�̕ϐ��̒�`
	while( 1 ){
		x++;									// �^�C�}�[�̃C���N�������g
		// �SLED��L�`�J
		if( x < 10000 ) LED_Set_All_On();		// LED��ON��
		else if( x < 20000 ) LED_Set_All_Off();	// LED��OFF��
		else if( x > 30000 ) x = 0;		// �^�C�}�[�̃��Z�b�g
		// �X�^�[�g�M���̔��f
		if( SW_Read_R() == SW_ON || (( WallSen.Value[FR] > 1000 ) && ( WallSen.Value[FL] > 1000 )) ){
			HAL_Delay( SW_WAIT );						// �`���^�����O�h�~
			//LED_Set_Confirm();						// ���莞LED�̉��o
			LED_Set_All_Off();
			Buzzer_Set_Confirm();
			break;
		}
	}
}

//===============================================
// LED :
//===============================================
void LED_Switch_Wait( void )
{
	uint16_t x = 0;								// �^�C�}�[�̕ϐ��̒�`
	while( 1 ){
		x++;									// �^�C�}�[�̃C���N�������g
		// �SLED��L�`�J
		if( x < 10000 ) LED_Set_All_On();		// LED��ON��
		else if( x < 20000 ) LED_Set_All_Off();	// LED��OFF��
		else if( x > 30000 ) x = 0;		// �^�C�}�[�̃��Z�b�g
		// �X�^�[�g�M���̔��f
		if( SW_Read_R() == SW_ON || SW_Read_L() == SW_ON ){
			HAL_Delay( SW_WAIT );						// �`���^�����O�h�~
			//LED_Set_Confirm();						// ���莞LED�̉��o
			LED_Set_All_Off();
			Buzzer_Set_Confirm();
			break;
		}
	}
}

//===============================================
// LED :
//===============================================
void LED_Cleaning_Wait( void )
{
	uint16_t x = 0;								// �^�C�}�[�̕ϐ��̒�`
	while( 1 ){
		x++;									// �^�C�}�[�̃C���N�������g
		// �SLED��L�`�J
		if( x < 40000 ) LED_Set_All_On();		// LED��ON��
		else if( x < 80000 ) LED_Set_All_Off();	// LED��OFF��
		else if( x > 120000 ) x = 0;		// �^�C�}�[�̃��Z�b�g
		// �X�^�[�g�M���̔��f
		if( SW_Read_R() == SW_ON || SW_Read_L() == SW_ON ){
			HAL_Delay( SW_WAIT );						// �`���^�����O�h�~
			LED_Set_Confirm();						// ���莞LED�̉��o
			LED_Set_All_Off();
			Buzzer_Set_Confirm();
			break;
		}
	}
}
//===============================================
// �X�C�b�` : L�X�C�b�`�Ǎ���
//  return  0: SW_ON, 1: SW_OFF
//===============================================
bool SW_Read_L( void )
{
	return HAL_GPIO_ReadPin( SW_L_GPIO_Port, SW_L_Pin );	// SW_L�̓��͔��f
}

//===============================================
// �X�C�b�` : R�X�C�b�`�Ǎ���
//  return  0: SW_ON, 1: SW_OFF
//===============================================
bool SW_Read_R( void )
{
	return HAL_GPIO_ReadPin( SW_R_GPIO_Port, SW_R_Pin );	// SW_R�̓��͔��f
}

//===============================================
// �u�U�[ : �L����
//===============================================
void Buzzer_Set_Enable( uint8_t x )
{
	buzzer_flg = x;		// �t���O�ɑ��
}

//===============================================
// �u�U�[ : Prescaler�̐ݒ�
//===============================================
void Buzzer_Set_Prescaler( uint16_t prescaler, uint16_t duty )
{
	__HAL_TIM_SET_PRESCALER( &htim11, prescaler );			// Prescaler��TIM�ɑ��
	__HAL_TIM_SET_COMPARE( &htim11, TIM_CHANNEL_1, duty );	// Duty��TIM�ɑ��

	HAL_TIM_PWM_Start( &htim11, TIM_CHANNEL_1 );			// PWM�o�͊J�n
}
//===============================================
// �u�U�[ : ����炷
//     freq  = ��{���g���i�h���~�j:�s�b�`4�̎��g��[Hz]
//     pitch = �����@4������K�C5���g���₷��
//     len   = ���̒���[ms]
//===============================================
void Buzzer_Beep( int freq, int pitch, int len )
{
	if( freq > 0 && buzzer_flg == BUZZER_ON ){			// 0�̓��͂͋x��
		freq = freq * pow( 2, pitch - 4 );				// ���g���v�Z
		int prescaler = APB2_TIMER_F / freq / 100;		// Prescaler�v�Z
		Buzzer_Set_Prescaler( prescaler, 5 );			// Prescaler��Duty 5%����
		HAL_Delay( len );								// len�̎��Ԃő҂�
		Buzzer_Set_Prescaler( 0, 0 );						// Beep��~
	}else{
		Buzzer_Set_Prescaler( 0, 0 );						// Beep��~
	}
}

//===============================================
// �u�U�[ : ���莞�̉�
//===============================================
void Buzzer_Set_Confirm( void )
{
	Buzzer_Beep( TONE_DO, 6, 50 );	// ���艹: ����6�̃h�C50 ms
	Buzzer_Beep( TONE_DO, 7, 100 );	// ���艹: ����7�̃h�C100 ms
}

//===============================================
// �u�U�[ : ����炷 (���荞��)
//     freq  = ��{���g���i�h���~�j:�s�b�`4�̎��g��[Hz]
//     pitch = �����@4������K�C5���g���₷��
//     len   = ���̒���[ms]
//===============================================
void Buzzer_Beep_Tick( int freq, int pitch, int len )
{
	int buzzerFreq = freq * pow( 2, pitch - 4 );
	tick_buzzerPrescaler = APB2_TIMER_F /  buzzerFreq / 100;
	tick_buzzerTime = len;
}

