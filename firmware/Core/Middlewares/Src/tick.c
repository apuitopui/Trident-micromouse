//################################################
// ���荞�݃^�C�}�[
//                                      K.Richardo
//################################################
#include "tick.h"

//************************************************
// �ϐ��錾
//************************************************
TIME_T activeTime;
uint16_t tick_buzzerPrescaler;
int16_t tick_buzzerTime;

uint8_t led1_irq_flg;
uint8_t led2_irq_flg;
uint8_t led3_irq_flg;
uint8_t led4_irq_flg;

uint16_t led1_ct;
uint16_t led2_ct;
uint16_t led3_ct;
uint16_t led4_ct;

uint16_t fs_speed_ct;
uint16_t fs_angular_ct;
uint16_t fs_angle_ct;
//===============================================
// ���荞�� : ������
//===============================================
void Tick_Init( void )
{
    HAL_TIM_Base_Start_IT( &htim5 );
    HAL_TIM_Base_Start_IT( &htim6 );
    HAL_TIM_Base_Start_IT( &htim7 );

    activeTime.ms = 0;
    activeTime.s = 0;
    activeTime.min = 0;

    tick_buzzerTime = -1;
}

//===============================================
// ���荞�݃^�C�}�[ : ���荞�ݏ���
//===============================================
void HAL_TIM_PeriodElapsedCallback( TIM_HandleTypeDef *htim )
{
	//---------------------------------------------
	// TIM5�����ݏ��� 1ms ( �V�X�e���֘A )
	if( htim == &htim5 )
	{

		//---------------------------------------------
		// �o�b�e���Ď�
//		if( Batt_Get_V() < 7.0 && activeTime.s > 5 ){	// 7.0V�ȉ����������Ɨ����
//			Buzzer_Beep_Tick( TONE_DO, 4, 10 );
//		}

		//---------------------------------------------
		// �d���t���ςȂ��h�~
		if( activeTime.min > 15 ){
			Buzzer_Beep_Tick( TONE_DO, 4, 10 );
		}

        //---------------------------------------------
        // �}�E�X���N������̎��Ԃ𑪒�
        activeTime.ms++;                        // ms�P�ʂ̃C���N�������g
        if( activeTime.ms >= 1000 ){            // 1000ms -> 1s
            activeTime.s++;                     // s�P�ʂ̃C���N�������g
            activeTime.ms -= 1000;              // ms�P�ʂ̃��Z�b�g
        }else if( activeTime.s >= 60 ){         // 60s -> 1min
            activeTime.min++;                   // min�P�ʂ̃C���N�������g
            activeTime.s -= 60;                 // s�P�ʂ̃��Z�b�g
        }else if( activeTime.min >= 65536 ){    // 16bit�̏������
            activeTime.min = 0;                 // min�P�ʂ̃��Z�b�g
        }

        //---------------------------------------------
        // �ǃZ���T�̍X�V�񐔂𑪒�
        WallSen.Update = WallSen.Update_Ct;
        WallSen.Update_Ct = 0;

//        //---------------------------------------------
//        // �u�U�[�̊��荞�ݏ���
//        if( buzzer_flg == BUZZER_ON ){
//			if( tick_buzzerTime > -1 ){
//				tick_buzzerTime--;
//				Buzzer_Set_Prescaler( tick_buzzerPrescaler, 5 );
//
//				if( tick_buzzerTime <= 0 ){
//					Buzzer_Set_Prescaler( 0, 0 );
//					tick_buzzerTime = -1;
//				}
//			}
//        }

        //---------------------------------------------
        // ���O�f�[�^�擾
        Log_Get_Data();

        //---------------------------------------------
        // LED�̊��荞�ݏ���
        if( led1_irq_flg == 1 && led1_ct == 0 ){
			LED1_ON();
			led1_ct++;
		}else if( led1_irq_flg == 1 && led1_ct < LED_TIME ){
			led1_ct++;
		}else if( led1_irq_flg == 1 && led1_ct >= LED_TIME ){
			LED1_OFF();
			led1_ct = 0;
			led1_irq_flg = 0;
		}

		if( led2_irq_flg == 1 && led2_ct == 0 ){
			LED2_ON();
			led2_ct++;
		}else if( led2_irq_flg == 1 && led2_ct < LED_TIME ){
			led2_ct++;
		}else if( led2_irq_flg == 1 && led2_ct >= LED_TIME ){
			LED2_OFF();
			led2_ct = 0;
			led2_irq_flg = 0;
		}

		if( led3_irq_flg == 1 && led3_ct == 0 ){
			LED3_ON();
			led3_ct++;
		}else if( led3_irq_flg == 1 && led3_ct < LED_TIME ){
			led3_ct++;
		}else if( led3_irq_flg == 1 && led3_ct >= LED_TIME ){
			LED3_OFF();
			led3_ct = 0;
			led3_irq_flg = 0;
		}

		if( led4_irq_flg == 1 && led4_ct == 0 ){
			LED4_ON();
			led4_ct++;
		}else if( led4_irq_flg == 1 && led4_ct < LED_TIME ){
			led4_ct++;
		}else if( led4_irq_flg == 1 && led4_ct >= LED_TIME ){
			LED4_OFF();
			led4_ct = 0;
			led4_irq_flg = 0;
		}

				//---------------------------------------------
        // �t�F�C���Z�[�t����
		if( Machine.State.Running == true && Machine.State.FailSafe == false ){
			// ���{�^���������ꂽ��
			if( SW_Read_L() == SW_ON ){
				Machine.State.FailSafe = true;
			}
//			// �ڕW���x���x����
//			else if( (fabs(Machine.V.Current - Enc.Speed.lr) > Machine.V.Current*0.3) && Ctrl_Angular.Use == false ){
//				fs_speed_ct++;				// ���ԑ���
//				if( fs_speed_ct > 2000 ){		// 0.5s�ȏ�̎�
//					Machine.State.FailSafe = true;
//				}
//			}
//
			//�@���񎞂ɍő厞�Ԃ�݂���
			else if( Machine.Angular.Current > 0 ){
				fs_angular_ct++;
				if( fs_angular_ct > 3000 ){
					Machine.State.FailSafe = true;
				}
			}
			// �������ڕW�p�x�Ƃ̍���30���ȏ㎞
			else if( (fabs(Machine.Angle.Target - IMU.Angle.z) > 30) && Ctrl_Angular.Use == false ){
				fs_angle_ct++;
				if( fs_angle_ct > 100 )
				Machine.State.FailSafe = true;
			}
			else{
				fs_angle_ct = 0;
				fs_angular_ct = 0;
				fs_speed_ct = 0;
			}

			// �p���x�̌덷����莞�Ԃő傫����
//			else if( Machine.State.Turning == true ){
//				if( fabs(IMU.Gyro.z - Machine.Angular.Current) >= 500.0){
//					FS_Turn_ct++;
//				}
//				if( FS_Turn_ct >= 2000 ){
//					Machine.State.FailSafe = true;
//					FS_Turn_ct = 0;
//				}
//			}
//			// �Z���T�l
//			else if( (WallSen.Value[R] >= 740 && WallSen.Value[FR] >= 1600) || (WallSen.Value[L] >= 1040 && WallSen.Value[FL] >= 3250) ){
//				Machine.State.FailSafe = true;
//			}

		}else{
			Machine.State.FailSafe = false;
			fs_angular_ct = 0;
			fs_speed_ct = 0;
		}

    }

    //---------------------------------------------
	// TIM6�����ݏ��� 1ms ( �f�[�^�擾�֘A )
	if( htim == &htim6 )
	{
		IMU_Read();								// IMU�Z���T�l�̎擾
		ENC_Read();								// �G���R�[�_�l�̎擾

    }

    //---------------------------------------------
	// TIM7�����ݏ��� 1ms (  )
	if( htim == &htim7 )
	{
		Control_Side_Wall();
		//Control_Front_Wall();
		Control_Side_WallEnd();
		//Control_Front_WallDist();
		Control_Motor();

    }
}
