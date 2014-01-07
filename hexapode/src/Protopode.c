#include "Protopode.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void vDcdTrame(Trame *xTrame, char *xcTrame)
{
	char xcBuffer[50];
	char xcDcdTrame[50];
	unsigned int i = 0;
	unsigned int j = 0;
	
	xTrame->ucErr = 0;
	
	if(xcTrame[0] == '$')
	{	
		while(xcTrame[i] != ',')
		{
			i++;
			xcBuffer[i-1] = xcTrame[i];
		}
		
		//suprime la virgule de fin
		xcBuffer[i-1] = 0;
		
		//suprime la virgule pour le début
		i++;
		
		for(j = i; xcTrame[j] != '\n'; j++)
		{
			xcDcdTrame[j-i] = xcTrame[j];
		}
		xcDcdTrame[j-i] = '\n';
		xcDcdTrame[j-i+1] = 0;
		
		//Feet
		if(!strcmp(xcBuffer,"F"))
		{
			strcpy(xTrame->cType,"F");
			vDcdFeetTrame(xTrame, xcDcdTrame);
		}
		//Head
		else if (!strcmp(xcBuffer,"H"))
		{
			strcpy(xTrame->cType,"H");
			vDcdHeadTrame(xTrame, xcDcdTrame);			
		}
		//Telemetre
		else if (!strcmp(xcBuffer,"TELE"))
		{
			strcpy(xTrame->cType,"TELE");
			vDcdTeleTrame(xTrame, xcDcdTrame);
		}
		//TOR
		else if (!strcmp(xcBuffer,"TOR"))
		{
			strcpy(xTrame->cType,"TOR");
			vDcdTorTrame(xTrame, xcDcdTrame);
		}
		//CMUCAM
		else if (!strcmp(xcBuffer,"CAM"))
		{
			strcpy(xTrame->cType,"CMUCAM");
			vDcdCamTrame(xTrame, xcDcdTrame);
		}
	}
	else
	{
		xTrame->ucErr = 1;
	}
}

void vDcdFeetTrame(Trame *xTrame, char *xcTrame)
{
	unsigned char i,j;
	char xcBuffer[10];
	j = 0;
	
	if(xcTrame[1] == ',')
	{
		xTrame->xTrameFeet.cSide = xcTrame[0];
	}
	else
	{
		xTrame->ucErr = 1;
	}
	
	if(xcTrame[3] == ',')
	{
		xTrame->xTrameFeet.cPosition = xcTrame[2];
	}
	else
	{
		xTrame->ucErr = 1;
	}
	
	if(xcTrame[5] == ',')
	{	
		xTrame->xTrameFeet.cNum = xcTrame[4];
	}
	else
	{
		xTrame->ucErr = 1;
	}
		
	for(i = 6; xcTrame[i] != '\n'; i++)
	{
		xcBuffer[j]=xcTrame[i];
		j++;
	}
	
	xTrame->xTrameFeet.ucDegres = atoi(xcBuffer);
}

void vDcdHeadTrame(Trame *xTrame, char *xcTrame)
{
	unsigned char i,j;
	char xcBuffer[10];
	j = 0;
	
	if(xcTrame[2] == ',')
	{	
		xTrame->xTrameHead.cPivo = xcTrame[1];
	}
	else
	{
		xTrame->ucErr = 1;
	}
	
	for(i = 3; xcTrame[i] != '\n'; i++)
	{
		xcBuffer[j]=xcTrame[i];
		j++;
	}
	
	xTrame->xTrameHead.ucDegres = atoi(xcBuffer);
}

void vDcdTeleTrame(Trame *xTrame, char *xcTrame)
{
	unsigned char i,j;
	char xcBuffer[10];
	j = 0;
	
	if(xcTrame[1] == ',')
	{
		xTrame->xTrameTelemetre.cNum = xcTrame[0];
	}
	else
	{
		xTrame->ucErr = 1;
	}
	
	for(i = 2; xcTrame[i] != '\n'; i++)
	{
		xcBuffer[j]=xcTrame[i];
		j++;
	}
	
	xTrame->xTrameTelemetre.fDistanceSecuCm = atof(xcBuffer);
}

void vDcdTorTrame(Trame *xTrame, char *xcTrame)
{
	unsigned char i,j;
	char xcBuffer[10];
	j = 0;

	if(xcTrame[1] == ',')
	{
	xTrame->xTrameTor.cSide = xcTrame[0];
	}
	else
	{
		xTrame->ucErr = 1;
	}

	if(xcTrame[3] == ',')
	{	
		xTrame->xTrameTor.cPosition = xcTrame[2];
	}
	else
	{
		xTrame->ucErr = 1;
	}
	
	
	for(i = 4; xcTrame[i] != '\n'; i++)
	{
		xcBuffer[j]=xcTrame[i];
		j++;
	}
	
	xTrame->xTrameTor.cTimeout = atoi(xcBuffer);
}

void vDcdCamTrame(Trame *xTrame, char *xcTrame)
{
	
}
