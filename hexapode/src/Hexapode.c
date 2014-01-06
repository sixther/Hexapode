#include "Hexapode.h"

void vInitFeet(FeetHexapode *pxFeet, unsigned char ucAngle1, unsigned char ucAngle2, unsigned char ucAngle3, 
																							unsigned char ucPwmNum1, unsigned char ucPwmNum2, unsigned char ucPwmNum3,
																							unsigned char ucTorNum)
{
	vInitPwm(&pxFeet->xServo1, ucAngle1, ucPwmNum1);
	vInitPwm(&pxFeet->xServo2, ucAngle2, ucPwmNum2);
	vInitPwm(&pxFeet->xServo3, ucAngle3, ucPwmNum3);
	vInitTor(&pxFeet->xTor1, ucTorNum);
}

void vSetFeet(FeetHexapode *pxFeet, unsigned char ucAngle1, unsigned char ucAngle2, unsigned char ucAngle3)
{
	vSetAngle(&pxFeet->xServo1, ucAngle1);
	vSetAngle(&pxFeet->xServo2, ucAngle2);
	vSetAngle(&pxFeet->xServo3, ucAngle3);
}

void vMoveFeet(FeetHexapode *pxFeet, unsigned char ucPasCount1, unsigned char ucPasCount2, unsigned char ucPasCount3)
{
	vSetPwm(&pxFeet->xServo1, ucPasCount1);
	vSetPwm(&pxFeet->xServo2, ucPasCount2);
	vSetPwm(&pxFeet->xServo3, ucPasCount3);
}

void vGetTorFeet(FeetHexapode *pxFeet)
{
	
}

void vInitHead(HeadHexapode *pxHead, unsigned char ucAngle1, unsigned char ucAngle2, 
																	unsigned char ucPwmNum1, unsigned char ucPwmNum2,
																	float SecuriteTelemetreCm)
{
	vInitPwm(&pxHead->xServo1, ucAngle1, ucPwmNum1);
	vInitPwm(&pxHead->xServo2, ucAngle2, ucPwmNum2);
	vInitTelemetre(&pxHead->xTelemetre1, SecuriteTelemetreCm);
}

void vSetHead(HeadHexapode *pxHead, unsigned char ucAngle1, unsigned char ucAngle2)
{
	vSetAngle(&pxHead->xServo1, ucAngle1);
	vSetAngle(&pxHead->xServo2, ucAngle2);
}

void vMoveHead(HeadHexapode *pxHead, unsigned char ucPasCount1, unsigned char ucPasCount2)
{
	vSetPwm(&pxHead->xServo1, ucPasCount1);
	vSetPwm(&pxHead->xServo2, ucPasCount2);
}

void vCalculSecuriteTelemetre(HeadHexapode *pxHead)
{
	vCalculDistanceCm(&pxHead->xTelemetre1);
	vCalculSecurite(&pxHead->xTelemetre1);
}
