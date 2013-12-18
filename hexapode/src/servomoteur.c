#include "servomoteur.h"

void vInitPwm(ServoMoteur *pxServoMoteur, unsigned char ucAngle)
{
	pxServoMoteur->ucAngle = ucAngle;
	pxServoMoteur->ucCount = 0;
	pxServoMoteur->ucGpio = 0;
}

void vSetPwm(ServoMoteur *pxServoMoteur, unsigned char ucPasCount)
{
	pxServoMoteur->ucCount += ucPasCount;
	
	if(pxServoMoteur->ucCount < pxServoMoteur->ucAngle)
	{
		pxServoMoteur->ucGpio = 1;
	}
	else
	{
		pxServoMoteur->ucGpio = 0;
	}
}
