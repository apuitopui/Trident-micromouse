//################################################
// �}�E�X�ړ����W���[��
//                             		 K.Richardo
//################################################
#include "move.h"

//===============================================
// �ړ� :�@�X�����[������(ver2)
//===============================================
void Move_Slalom_Turn2( PARAM_SLALOM_T *sla, int dir )
{
	int angle;
	if( dir == L_TURN )	angle = sla->Angle * -1;
	else angle = sla->Angle;

	Enc.Position.y = 0;
	Enc.Position.x = 0;
	IMU.Angle.z = 0;
	bool decel_flg = false;
	Machine.V.Target = sla->Speed;

	if( sla->Speed != 0 ) Machine.Angular.Target = sla->Speed / sla->Radius * 180.0 / M_PI;
	else Machine.Angular.Target = 800;

	double decel_deg = angle / 4.0 ;
	Machine.Alpha.Target = Machine.Angular.Target * Machine.Angular.Target / (2.0 * decel_deg * 1000.0) ;
	if( angle < 0 ) Machine.Alpha.Target *= -1;

	IMU.Angle.z = 0;

	Ctrl_Speed.Use = true;
	Ctrl_Speed_L.Use = false;
	Ctrl_Speed_R.Use = false;
	Ctrl_SideWall.Use = false;


	Ctrl_Angular.Kp = sla->Kp;
	Ctrl_Angular.Ki = sla->Ki;
	Ctrl_Angular.Kd = sla->Kd;
	Machine.State.Turning = true;
	Machine.Control = true;

	if( angle > 0 ){
		Ctrl_Angular.Use = true;
		while( 1 ){
			if( (angle - decel_deg) <= IMU.Angle.z ){
				Machine.Angular.Target = 0.0;
				decel_flg = true;
			}
			if( (IMU.Gyro.z <= 0.0 || IMU.Angle.z >= angle)  && decel_flg == true )
				break;

			if( Machine.State.FailSafe == true )
					break;
		}
	}else{
		Ctrl_Angular.Use = true;
		Machine.Angular.Target *= -1;
		while( 1 ){
			if( angle - decel_deg >= IMU.Angle.z ){
				Machine.Angular.Target = 0.0;
				decel_flg = true;
			}
			if( (IMU.Gyro.z >= 0.0 || IMU.Angle.z <= angle)  && decel_flg == true )
				break;

			if( Machine.State.FailSafe == true )
				break;
		}
	}

	Machine.State.TurnDir = dir;
	Ctrl_Angular.Use = false;
	Machine.Alpha.Target = 0;
	Machine.Angular.Target = 0;
	Machine.Angular.Current = 0;
	IMU.Angle.z -= angle;
//	Enc.Position.angle -= sla->Angle;
	Enc.Position.y = 0;
	Enc.Position.x = 0;
	Enc.Position.angle = 0;

}
//===============================================
// �ړ� :�@�X�����[������(ver1)
//===============================================
void Move_Slalom_Turn( PARAM_SLALOM_T *sla, int dir )
{
	int angle;
	if( dir == L_TURN )	angle = sla->Angle * -1;
	else angle = sla->Angle;

	Enc.Position.y = 0;
	Enc.Position.x = 0;

	bool decel_flg = false;
	Machine.V.Target = sla->Speed;

	if( sla->Speed != 0 ) Machine.Angular.Target = sla->Speed / sla->Radius * 180.0 / M_PI;
	else Machine.Angular.Target = 350.0;

	Machine.Alpha.Target = Machine.Angular.Target * Machine.Angular.Target / angle / 500.0;
	if( angle < 0 ) Machine.Alpha.Target *= -1;

	double decel_deg = Machine.Angular.Target * Machine.Angular.Target/ ( 2.0 * Machine.Alpha.Target * 1000 );
	IMU.Angle.z = 0;

	Ctrl_Speed.Use = true;
	Ctrl_Speed_L.Use = false;
	Ctrl_Speed_R.Use = false;
	Ctrl_SideWall.Use = false;
	Global_WSen.SideEnd.Use = false;

	Ctrl_Angular.Kp = sla->Kp;
	Ctrl_Angular.Ki = sla->Ki;
	Ctrl_Angular.Kd = sla->Kd;
	Machine.State.Turning = true;
	Machine.Control = true;

	if( angle > 0 ){
		Ctrl_Angular.Use = true;
		while( 1 ){
			if( angle - decel_deg <= IMU.Angle.z ){
				Machine.Angular.Target = 0.0;
				decel_flg = true;
			}
			if( (IMU.Gyro.z <= 0.0 || IMU.Angle.z >= angle)  && decel_flg == true )
				break;

			if( Machine.State.FailSafe == true )
					break;
		}
	}else{
		Ctrl_Angular.Use = true;
		Machine.Angular.Target *= -1;
		while( 1 ){
			if( angle + decel_deg >= IMU.Angle.z ){
				Machine.Angular.Target = 0.0;
				decel_flg = true;
			}
			if( (IMU.Gyro.z >= 0.0 || IMU.Angle.z <= angle)  && decel_flg == true )
				break;

			if( Machine.State.FailSafe == true )
					break;
		}
	}

	Machine.State.Turning = false;
	Ctrl_Angular.Use = false;
	Machine.Alpha.Target = 0;
	Machine.Angular.Target = 0;
	IMU.Angle.z -= angle;
//	Enc.Position.angle -= sla->Angle;
	Enc.Position.y = 0;
	Enc.Position.x = 0;
	Enc.Position.angle = 0;


}
//===============================================
// �ړ� :�@�X�����[������O�̒��i
//===============================================
void Move_Sla_In( int16_t y, int16_t v, uint16_t a )
{
	Enc.Position.y = 0;
	Enc.Position.x = 0;
	Enc.Position.angle = 0;

	// �ڕW�l����
	Machine.Angular.Target = 0;							// �p���x�̑��
	Machine.Angle.Target = 0;							// �p�x�̑��
	Machine.V.Target = v;								// ���x�̑��
	Machine.Acc.Target = a;								// �����x�̑��
	Machine.Deacc.Target = a;							// �����x�̑��

	Ctrl_Speed.Use = false;								// ���xFB��L����
	Ctrl_Speed_L.Use = true;
	Ctrl_Speed_R.Use = true;
	Ctrl_Angular.Use = false;

	Machine.Control = true;								// ����J�n

	if(fwall == 1){
		while( (WallDist_FL + WallDist_FR)/2.0 < y ){
			if( Machine.State.FailSafe == true )
				break;
		}
	}else{
		while( Enc.Position.y < ( y ) ){
			if( Machine.State.FailSafe == true )
				break;
		}		//�@�����E�葬�̋����܂ňړ�
	}

}
//===============================================
// �ړ� :�@���J�o���[
//===============================================
void Move_Recovery( void )
{
	Ctrl_SideWall.Use = false;
	Move_Straight2Half(Global_Straight.Dist.Half, Global_Straight.Speed.Low, Global_Straight.Speed.Acc);

	if(lwall == 1 && fwall == 1){
		Move_Slalom_Turn( &Global_T90, R_TURN );	Move_Stop();
		Move_Straight_Stop(Global_Straight.Dist.Back, -Global_Straight.Speed.Low, Global_Straight.Speed.Acc );
		Move_Straight_Stop(Global_Straight.Dist.WalltoMiddle, Global_Straight.Speed.Low, Global_Straight.Speed.Acc );
		Move_Slalom_Turn( &Global_T90, R_TURN );	Move_Stop();
		Move_Straight_Stop(Global_Straight.Dist.Back, -Global_Straight.Speed.Low, Global_Straight.Speed.Acc);

		Ctrl_SideWall.Use = true;
		Move_Straight(Global_Straight.Dist.Start, Global_Straight.Speed.Normal, Global_Straight.Speed.Acc);
	}else if(rwall == 1 && fwall == 1){
		Move_Slalom_Turn( &Global_T90, L_TURN );	Move_Stop();
		Move_Straight_Stop(Global_Straight.Dist.Back, -Global_Straight.Speed.Low, Global_Straight.Speed.Acc );
		Move_Straight_Stop(Global_Straight.Dist.WalltoMiddle, Global_Straight.Speed.Low, Global_Straight.Speed.Acc );
		Move_Slalom_Turn( &Global_T90, L_TURN );	Move_Stop();
		Move_Straight_Stop(Global_Straight.Dist.Back, -Global_Straight.Speed.Low, Global_Straight.Speed.Acc);

		Ctrl_SideWall.Use = true;
		Move_Straight(Global_Straight.Dist.Start, Global_Straight.Speed.Normal, Global_Straight.Speed.Acc);
	}else if(fwall == 1){
		Move_Slalom_Turn( &Global_T180, R_TURN);				Move_Stop();
		Move_Straight_Stop(Global_Straight.Dist.Back, -Global_Straight.Speed.Low, Global_Straight.Speed.Acc);

		Ctrl_SideWall.Use = true;
		Move_Straight(Global_Straight.Dist.Start, Global_Straight.Speed.Normal, Global_Straight.Speed.Acc);
	}else{
		Move_Slalom_Turn( &Global_T180, R_TURN);				Move_Stop();
		Move_Straight(80, Global_Straight.Speed.Normal, Global_Straight.Speed.Acc);

	}
}
//===============================================
// �ړ� :�@���i
//===============================================
void Move_Straight( int16_t y, int16_t v, uint16_t a )
{
	Enc.Position.y = 0;
	Enc.Position.x = 0;
	Enc.Position.angle = 0;
	IMU.Acc.Speed = 0;
	// �ڕW�l����
	Machine.Angular.Target = 0;							// �p���x�̑��
	Machine.Angle.Target = 0;							// �p�x�̑��
	Machine.V.Target = v;								// ���x�̑��
	Machine.Acc.Target = a;								// �����x�̑��
	Machine.Deacc.Target = a;							// �����x�̑��

	Ctrl_Speed.Use = false;								// ���xFB��L����
	Ctrl_Speed_L.Use = true;
	Ctrl_Speed_R.Use = true;
	Ctrl_Angular.Use = false;

	Machine.Control = true;								// ����J�n

	if( y > 0 ){										// �O�i�̎�
		while( Enc.Position.y < ( y ) ){
			if( Machine.State.FailSafe == true )
				break;
		}		//�@�����E�葬�̋����܂ňړ�

	}else if( y < 0 ){									// ��i�̎�
		while( Enc.Position.y > ( y ) ){
			if( Machine.State.FailSafe == true )
				break;
		}		// �����E�葬�̋����܂ňړ�

	}
}
//===============================================
// �ړ� :�@���i -> ��~���W���[��
//===============================================
void Move_Straight_Stop( int32_t y, int32_t v, uint16_t a )
{
	Enc.Position.y = 0;
	Enc.Position.x = 0;
	Enc.Position.angle = 0;
	IMU.Acc.Speed = 0;
	// �ڕW�l����
	Machine.Angular.Target = 0;							// �p���x�̑��
	Machine.Angle.Target = 0;							// �p�x�̑��
	Machine.V.Target = v;								// ���x�̑��
	Machine.Acc.Target = a;								// �����x�̑��
	Machine.Deacc.Target = a;							// �����x�̑��

	int32_t deacc_y = (( v * v )) / ( 2 * a * 1000 );	// �����������v�Z

	Ctrl_Speed.Use = false;								// ���xFB��L����
	Ctrl_Speed_L.Use = true;
	Ctrl_Speed_R.Use = true;
	Ctrl_Angular.Use = false;

	Machine.Control = true;								// ����J�n

	if( y > 0 ){										// �O�i�̎�
		while( Enc.Position.y < ( y - deacc_y ) ){
			if( Machine.State.FailSafe == true )
				break;
		}		//�@�����E�葬�̋����܂ňړ�
		Machine.V.Target = 50;							// ���x��50mmps�ɂ���(�����ɒ�~�ł��鑬�x)
		while( Enc.Position.y < y ){					//�@�����̋����܂�
			if( Machine.State.FailSafe == true )
				break;
		}

	}else if( y < 0 ){									// ��i�̎�
		while( Enc.Position.y > ( y + deacc_y ) ){		//�@�����̋����܂�
			if( Machine.State.FailSafe == true )
				break;
		}		// �����E�葬�̋����܂ňړ�
		Machine.V.Target = -50;							// ���x��50mmps�ɂ���(�����ɒ�~�ł��鑬�x)
		while( Enc.Position.y < y ){
			if( Machine.State.FailSafe == true )		//�@�����̋����܂�
				break;
		}

	}

	Move_Stop();
}
//===============================================
// �ړ� :�@���i -> ��~���W���[��
//===============================================
void Move_Straight2Half( int32_t y, int32_t v, uint16_t a )
{
	Enc.Position.y = 0;
	Enc.Position.x = 0;
	Enc.Position.angle = 0;
	IMU.Acc.Speed = 0;

	// �ڕW�l����
	Machine.Angular.Target = 0;							// �p���x�̑��
	Machine.Angle.Target = 0;							// �p�x�̑��
	Machine.V.Target = v;								// ���x�̑��
	Machine.Acc.Target = a;								// �����x�̑��
	Machine.Deacc.Target = a;							// �����x�̑��

	int32_t deacc_y = (( v * v )) / ( 2 * a * 1000 );	// �����������v�Z

	Ctrl_Speed.Use = false;								// ���xFB��L����
	Ctrl_Speed_L.Use = true;
	Ctrl_Speed_R.Use = true;
	Ctrl_Angular.Use = false;

	Machine.Control = true;								// ����J�n

	if( y > 0 ){										// �O�i�̎�
		while( Enc.Position.y < ( y - deacc_y ) ){
			if(fwall == 1 && ((WallSen.Value[FL] >= 3300) || (WallSen.Value[FR] >= 2800))){
				Enc.Position.y = y;
				break;
			}
			if( Machine.State.FailSafe == true )
				break;
		}		//�@�����E�葬�̋����܂ňړ�
		Machine.V.Target = 50;							// ���x��50mmps�ɂ���(�����ɒ�~�ł��鑬�x)
		while( Enc.Position.y < y ){					//�@�����̋����܂�
			if(fwall == 1 && ((WallSen.Value[FL] >= 3300) || (WallSen.Value[FR] >= 2800))){
				Enc.Position.y = y;
				break;
			}
			if( Machine.State.FailSafe == true )
				break;
		}

	}else if( y < 0 ){									// ��i�̎�
		while( Enc.Position.y > ( y + deacc_y ) ){		//�@�����̋����܂�
			if( Machine.State.FailSafe == true )
				break;
		}		// �����E�葬�̋����܂ňړ�
		Machine.V.Target = -50;							// ���x��50mmps�ɂ���(�����ɒ�~�ł��鑬�x)
		while( Enc.Position.y < y ){
			if( Machine.State.FailSafe == true )		//�@�����̋����܂�
				break;
		}

	}

	Move_Stop();
}

//===============================================
// �ړ� :�@���������i( )
//===============================================
void Move_Straight_Acc( uint8_t mass, uint16_t v1, uint16_t v2, uint16_t v3, uint16_t acc, uint16_t deacc )
{
	uint32_t y, v;
	uint8_t deacc_mass;
	if( mass <= 1 ){
		y = Global_Straight.Dist.Full;
		v = v1;
		deacc_mass = 0;
	}else{
		y = mass* Global_Straight.Dist.Full;
		v = sqrt((2 * acc * y/4*3 * 1000) + pow(v1, 2));
		if( v > v3 ) v = v3;
		deacc_mass = ceil(((pow(v, 2) - pow(v1, 2)) / (2.0 * deacc  * 1000))/180.0);
		//if( v > 3800 ) deacc_mass ++;
	}

	Ctrl_SideWall.Use = true;
	if( deacc_mass == 0 ){
		for( int i = 0; i < mass; i++ ){
			read_wall_data();
			Global_WSen.SideEnd.Use = true;
			Move_Straight( Global_Straight.Dist.Full, v, acc );
		}
	}else{
		for( int i = 0; i < (mass-deacc_mass); i++){
			//read_wall_data();
			Global_WSen.SideEnd.Use = false;
			Move_Straight( Global_Straight.Dist.Full, v, acc);
		}
		for( int i = 0; i < deacc_mass - 1; i++ ){
			//read_wall_data();
			Global_WSen.SideEnd.Use = false;
			Move_Straight( Global_Straight.Dist.Full, v1, deacc );
		}

		read_wall_data();
		Global_WSen.SideEnd.Use = true;
		Move_Straight( Global_Straight.Dist.Full, v1, deacc );
	}
/* ----------------------------------------------
	uint16_t v;
	uint8_t deacc_mass;
	uint8_t add_y = 0;
//	uint32_t acc_v3_y = ((pow(v3, 2) - pow(v1, 2)) / (2.0 * acc * 1000));
//	uint32_t acc_v2_y = ((pow(v2, 2) - pow(v1, 2)) / (2.0 * acc * 1000));
	uint32_t deacc_v3_y = ((pow(v3, 2) - pow(v1, 2)) / (2.0 * deacc  * 1000));
	uint32_t deacc_v2_y = ((pow(v2, 2) - pow(v1, 2)) / (2.0 * deacc  * 1000));
//
//	if( (acc_v3_y + deacc_v3_y )/180 < mass ){
//		v = v3;
//		deacc_mass = ceil((deacc_v3_y/180)) + 1;
//	}else if( mass >= 6){
//		v = v3;
//		deacc_mass = ceil((deacc_v3_y/180)) + 1;
//	}else if( (acc_v2_y + deacc_v2_y)/180 < mass){
//		v = v2;
//		deacc_mass = ceil((deacc_v2_y/180)) + 1  ;
//	}else{
//		v = v1;
//		deacc_mass = 0 ;
//	}

	if( mass >= 8 ){
		v = v3;
		deacc_mass = ceil((deacc_v3_y/180)) + 1;
	}else if(mass > 2){
		v = v2;
		deacc_mass = ceil((deacc_v2_y/180)) + 1  ;
	}else{
		v = v1;
		deacc_mass = 0;
	}
	Ctrl_SideWall.Use = true;
	if( deacc_mass == 0 ){
		for( int i = 0; i < mass; i++ ){
			read_wall_data();
			Global_WSen.SideEnd.Use = true;
			Move_Straight( Global_Straight.Dist.Full, v, acc );
		}
	}else{
		for( int i = 0; i < (mass-deacc_mass); i++){
//			if( v >= 3800 ){
//				add_y = 1;
//			}
			Global_WSen.SideEnd.Use = false;
			Move_Straight( Global_Straight.Dist.Full + add_y, v, acc);
		}
		for( int i = 0; i < deacc_mass; i++ ){
			if( deacc_mass == i - 1){
			read_wall_data();
			Global_WSen.SideEnd.Use = true;
			}
			Move_Straight( Global_Straight.Dist.Full, v1, deacc );
		}
	}
---------------------------------------------- */

}

//===============================================
// �ړ� :�@�΂߂̉��������i( )
//==============================================
void Move_DStraight_Acc( uint8_t mass, uint16_t v1, uint16_t v2, uint16_t v3, uint16_t acc, uint16_t deacc )
{
	uint32_t y, v;
	uint8_t deacc_mass;
	if( mass <= 2 ){
		y = 127;
		v = v1;
		deacc_mass = 0;
	}else{
		y = mass* 127;
		v = sqrt((2 * acc * y/2 * 1000) + pow(v1, 2));
		if( v > v2 ) v = v2;
		deacc_mass = ceil(((pow(v, 2) - pow(v1, 2)) / (2.0 * deacc  * 1000))/127.0);
		if( v > 3800 ) deacc_mass ++;
	}

	Ctrl_SideWall.Use = true;
	if( deacc_mass == 0 ){
		for( int i = 0; i < mass; i++ ){
			Move_Straight( 127, v, acc );
		}
	}else{
		for( int i = 0; i < (mass-deacc_mass); i++){
			Move_Straight( 127, v, acc);
		}
		for( int i = 0; i < deacc_mass - 1; i++ ){
			Move_Straight( 127, v1, deacc );
		}

		Move_Straight( 127, v1, deacc );
	}
/* ----------------------------------------------
	uint16_t v;
	uint8_t deacc_mass;
	uint8_t add_y = 0;
//	uint32_t acc_v3_y = ((pow(v3, 2) - pow(v1, 2)) / (2.0 * acc * 1000));
//	uint32_t acc_v2_y = ((pow(v2, 2) - pow(v1, 2)) / (2.0 * acc * 1000));
	uint32_t deacc_v3_y = ((pow(v3, 2) - pow(v1, 2)) / (2.0 * deacc  * 1000));
	uint32_t deacc_v2_y = ((pow(v2, 2) - pow(v1, 2)) / (2.0 * deacc  * 1000));
//
//	if( (acc_v3_y + deacc_v3_y )/180 < mass ){
//		v = v3;
//		deacc_mass = ceil((deacc_v3_y/180)) + 1;
//	}else if( mass >= 6){
//		v = v3;
//		deacc_mass = ceil((deacc_v3_y/180)) + 1;
//	}else if( (acc_v2_y + deacc_v2_y)/180 < mass){
//		v = v2;
//		deacc_mass = ceil((deacc_v2_y/180)) + 1  ;
//	}else{
//		v = v1;
//		deacc_mass = 0 ;
//	}

	if( mass >= 8 ){
		v = v3;
		deacc_mass = ceil((deacc_v3_y/180)) + 1;
	}else if(mass > 2){
		v = v2;
		deacc_mass = ceil((deacc_v2_y/180)) + 1  ;
	}else{
		v = v1;
		deacc_mass = 0;
	}
	Ctrl_SideWall.Use = true;
	if( deacc_mass == 0 ){
		for( int i = 0; i < mass; i++ ){
			read_wall_data();
			Global_WSen.SideEnd.Use = true;
			Move_Straight( Global_Straight.Dist.Full, v, acc );
		}
	}else{
		for( int i = 0; i < (mass-deacc_mass); i++){
//			if( v >= 3800 ){
//				add_y = 1;
//			}
			Global_WSen.SideEnd.Use = false;
			Move_Straight( Global_Straight.Dist.Full + add_y, v, acc);
		}
		for( int i = 0; i < deacc_mass; i++ ){
			if( deacc_mass == i - 1){
			read_wall_data();
			Global_WSen.SideEnd.Use = true;
			}
			Move_Straight( Global_Straight.Dist.Full, v1, deacc );
		}
	}
---------------------------------------------- */

}
//===============================================
// �ړ� : ��~���W���[��
//===============================================
void Move_Stop( void )
{
	Machine.V.Target = 0;
	Machine.Angular.Target = 0;

	// ��~����܂ő҂�
	while( Enc.Speed.lr != 0 ){
		MOT_Set_Dir( BRAKE, BRAKE );		// ���[�^���u���[�L
		HAL_Delay( 1 );						// 1ms��҂�
	}

	Ctrl_Speed.Use = CONTROL_DISABLE;		// ���xFB�𖳌���
	Ctrl_Speed_L.Use = CONTROL_DISABLE;
	Ctrl_Speed_R.Use = CONTROL_DISABLE;
	Machine.Control = CONTROL_DISABLE;		// �����~
	Ctrl_SideWall.Use = CONTROL_DISABLE;
	Ctrl_Angular.Use = CONTROL_DISABLE;
	Ctrl_FrontWall.Use = CONTROL_DISABLE;
	HAL_Delay(10);							// 10ms�҂�
}
