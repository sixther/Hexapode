typedef struct
{
		unsigned int ucAngle;
		unsigned int ucCount;
		unsigned char ucPwmNum;
	
}ServoMoteur;

void vInitPwm(ServoMoteur *pxServoMoteur, unsigned char ucAngle, unsigned char ucPwmNum);
void vSetPwm(ServoMoteur *pxServoMoteur, unsigned char ucPasCount);
