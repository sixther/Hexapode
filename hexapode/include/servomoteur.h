typedef struct
{
		unsigned int ucAngle;
		unsigned int ucCount;
		unsigned char ucGpio;
}ServoMoteur;

void vInitPwm(ServoMoteur *pxServoMoteur, unsigned char ucAngle);
void vSetPwm(ServoMoteur *pxServoMoteur, unsigned char ucPasCount);
