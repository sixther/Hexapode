#include "telemetre.h"

void vCalculDistanceCm(Telemetre *xTelemetre)
{
	xTelemetre->fVoltValue = (float)xTelemetre->uiAdcValue / RATIO_ADC;
	
	xTelemetre->fCmValue = ((xTelemetre->fVoltValue - POINTA_CAPTEUR_Y) / (COEFF_DIRECTEUR)) + POINTA_CAPTEUR_X;
}
