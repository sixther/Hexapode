typedef struct
{
	char cSide;
	char cPosition;
	char cNum;
	unsigned char ucDegres;
}TrameFeet;

typedef struct
{
	char cPivo;
	unsigned char ucDegres;
}TrameHead;

typedef struct
{
	char cNum;
	float fDistanceSecuCm;
}TrameTelemetre;

typedef struct
{
	char cSide;
	char cPosition;
	char cTimeout;	
}TrameTor;

typedef struct
{
	char cMode[10];
}TrameCam;

typedef struct
{
	unsigned char ucErr;
	char cType[10];
	TrameFeet xTrameFeet;
	TrameHead xTrameHead;
	TrameTelemetre xTrameTelemetre;
	TrameTor xTrameTor;
	TrameCam xTrameCam;
}Trame;

void vDcdTrame(Trame *xTrame, char *xcTrame);
void vDcdFeetTrame(Trame *xTrame, char *xcTrame);
void vDcdHeadTrame(Trame *xTrame, char *xcTrame);
void vDcdTeleTrame(Trame *xTrame, char *xcTrame);
void vDcdTorTrame(Trame *xTrame, char *xcTrame);
void vDcdCamTrame(Trame *xTrame, char *xcTrame);
