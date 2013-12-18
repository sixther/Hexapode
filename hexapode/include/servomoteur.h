typedef struct
{
		unsigned char ucAngle;
		unsigned char ucCount;
		unsigned char ucGpio;
}ServoMoteur;

void vInitPwm(ServoMoteur *pxServoMoteur, unsigned char ucAngle);
void vSetPwm(ServoMoteur *pxServoMoteur, unsigned char ucPasCount);
