#include "servomoteur.h"
#include "telemetre.h"
#include "tor.h"

#define PPM_1MS											20

#define FEET_LEFT_FRONT_PWMNUM1 		0
#define FEET_LEFT_FRONT_PWMNUM2 		1
#define FEET_LEFT_FRONT_PWMNUM3 		2

#define FEET_LEFT_MID_PWMNUM1				3 	
#define FEET_LEFT_MID_PWMNUM2				4
#define FEET_LEFT_MID_PWMNUM3 			5
		
#define FEET_LEFT_BACK_PWMNUM1			6
#define FEET_LEFT_BACK_PWMNUM2 			7
#define FEET_LEFT_BACK_PWMNUM3 			8

#define FEET_RIGHT_FRONT_PWMNUM1 		9
#define FEET_RIGHT_FRONT_PWMNUM2 		10
#define FEET_RIGHT_FRONT_PWMNUM3 		11

#define FEET_RIGHT_MID_PWMNUM1			12	
#define FEET_RIGHT_MID_PWMNUM2			13
#define FEET_RIGHT_MID_PWMNUM3 			14
		
#define FEET_RIGHT_BACK_PWMNUM1			15
#define FEET_RIGHT_BACK_PWMNUM2 		16
#define FEET_RIGHT_BACK_PWMNUM3 		17

#define HEAD_PWMNUM1								18
#define HEAD_PWMNUM2								19

#define FEET_LEFT_FRONT_TORNUM			0x01		
#define FEET_LEFT_MID_TORNUM				0x02
#define FEET_LEFT_BACK_TORNUM				0x04

#define FEET_RIGHT_FRONT_TORNUM			0x08
#define FEET_RIGHT_MID_TORNUM				0x10
#define FEET_RIGHT_BACK_TORNUM			0x20


typedef struct
{
	ServoMoteur xServo1;
	ServoMoteur xServo2;
	Telemetre xTelemetre1;
}HeadHexapode;

typedef struct
{
	ServoMoteur xServo1;
	ServoMoteur xServo2;
	ServoMoteur xServo3;
	Tor xTor1;
}FeetHexapode;

void vInitHead(HeadHexapode *pxHead, unsigned char ucAngle1, unsigned char ucAngle2, 
																	unsigned char ucPwmNum1, unsigned char ucPwmNum2);
void vSetHead(HeadHexapode *pxHead, unsigned char ucAngle1, unsigned char ucAngle2);
void vMoveHead(HeadHexapode *pxHead, unsigned char ucPasCount1, unsigned char ucPasCount2);


void vInitFeet(FeetHexapode *pxFeet, unsigned char ucAngle1, unsigned char ucAngle2, unsigned char ucAngle3, 
																							unsigned char ucPwmNum1, unsigned char ucPwmNum2, unsigned char ucPwmNum3,
																							unsigned char ucTorNum);
void vSetFeet(FeetHexapode *pxFeet, unsigned char ucAngle1, unsigned char ucAngle2, unsigned char ucAngle3);
void vMoveFeet(FeetHexapode *pxFeet, unsigned char ucPasCount1, unsigned char ucPasCount2, unsigned char ucPasCount3);


