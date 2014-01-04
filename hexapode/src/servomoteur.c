#include "servomoteur.h"
#include "board.h"

void vInitPwm(ServoMoteur *pxServoMoteur, unsigned char ucAngle, unsigned char ucPwmNum)
{
	if(ucAngle>40)
		ucAngle=40;	
	
	pxServoMoteur->ucAngle = ucAngle;
	pxServoMoteur->ucCount = 0;
	pxServoMoteur->ucPwmNum = ucPwmNum;
}

void vSetAngle(ServoMoteur *pxServoMoteur, unsigned char ucAngle)
{
	if(ucAngle>40)
		ucAngle=40;	
	
	pxServoMoteur->ucAngle = ucAngle;
	pxServoMoteur->ucCount = 0;
}

void vSetPwm(ServoMoteur *pxServoMoteur, unsigned char ucPasCount)
{	
	pxServoMoteur->ucCount += ucPasCount;
	
	if(pxServoMoteur->ucCount < pxServoMoteur->ucAngle)
	{
		Board_PWM_Set(pxServoMoteur->ucPwmNum, 1);
	}
	else
	{
		Board_PWM_Set(pxServoMoteur->ucPwmNum, 0);
	}
}
