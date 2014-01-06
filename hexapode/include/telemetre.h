#define BIT_ADC									4095.0
#define VOLT_MAX_ADC						3.3
#define RATIO_ADC								BIT_ADC / VOLT_MAX_ADC

//calcul du coeff directeur avec les points de la documentation
#define POINTA_CAPTEUR_Y				3.1
#define POINTA_CAPTEUR_X				10.0
#define POINTB_CAPTEUR_Y				0.6
#define POINTB_CAPTEUR_X				80.0
#define COEFF_DIRECTEUR					(POINTB_CAPTEUR_Y - POINTA_CAPTEUR_Y) / (POINTB_CAPTEUR_X - POINTA_CAPTEUR_X)

typedef struct
{
	unsigned short usAdcValue;
	unsigned char ucSecuriteFlag;
	float fSecuriteCm;
	float fVoltValue;
	float	fCmValue; 	
}Telemetre;

void vInitTelemetre(Telemetre *xTelemetre, float fSecuriteCm);
void vCalculDistanceCm(Telemetre *xTelemetre);
void vCalculSecurite(Telemetre *xTelemetre);
