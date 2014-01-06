#include "telemetre.h"

void vInitTelemetre(Telemetre *xTelemetre, float fSecuriteCm)
{
	xTelemetre->fSecuriteCm = fSecuriteCm;
	xTelemetre->ucSecuriteFlag = 0;
}

void vCalculDistanceCm(Telemetre *xTelemetre)
{
	xTelemetre->fVoltValue = (float)xTelemetre->usAdcValue / RATIO_ADC;
	
	xTelemetre->fCmValue = ((xTelemetre->fVoltValue - POINTA_CAPTEUR_Y) / (COEFF_DIRECTEUR)) + POINTA_CAPTEUR_X;
}

void vCalculSecurite(Telemetre *xTelemetre)
{
	if(xTelemetre->fCmValue < xTelemetre->fSecuriteCm)
	{
		xTelemetre->ucSecuriteFlag = 1;
	}
	else
	{
		xTelemetre->ucSecuriteFlag = 0;
	}
}
