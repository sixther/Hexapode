#include "servomoteur.h"
#include "board.h"
#include "FreeRTOS.h"
#include "task.h"
#include "timer_17xx_40xx.h"
#include "chip.h"
#include "basic_io.h"

void vInitPwm(ServoMoteur *pxServoMoteur, unsigned char ucAngle, unsigned char ucPwmNum)
{
	if(ucAngle>40)
		ucAngle=40;	
	
	pxServoMoteur->ucAngle = ucAngle;
	pxServoMoteur->ucCount = 0;
	pxServoMoteur->ucPwmNum = ucPwmNum;
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
