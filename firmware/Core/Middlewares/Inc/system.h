//################################################
// �}�E�X�̑����V�X�e��
//                                      K.Richardo
//################################################
#ifndef MIDDLEWARES_SYSTEM_H_
#define MIDDLEWARES_SYSTEM_H_

//************************************************
// Include�錾
//************************************************
#include "main.h"

//************************************************
// Define�錾
//************************************************
#define MODEMAX			16					// ���샂�[�h��
#define DISP			0					// ���[�h�\��
#define EXEC			1					// ���[�h���s

//************************************************
// �֐��v���g�^�C�v�錾
//************************************************
void System_Init( void );
void System_Loop( void );
void change_mode( int x );
void exec_mode( void );
void mode0( int x );
void mode1( int x );
void mode2( int x );
void mode3( int x );
void mode4( int x );
void mode5( int x );
void mode6( int x );
void mode7( int x );
void mode8( int x );
void mode9( int x );
void mode10( int x );
void mode11( int x );
void mode12( int x );
void mode13( int x );
void mode14( int x );
void mode15( int x );
int Select_Number( int min, int max );
int Select_YesNo( void );
void Select_Map( void );
void Select_Goal( void );
void Select_Change_S45_RE( void );
void Select_Change_S135_RE( void );
void Select_Change_S45( void );
void Select_Change_S135( void );
void Select_Change_V90( void );
void Select_Change_W90( void );
void Select_Change_S90( void );
void Select_Straight( void );

#endif /* MIDDLEWARES_SYSTEM_H_ */
