#include "tor.h"
#include "board.h"

void vInitTor(Tor *xTor, unsigned char ucTorNum)
{
	xTor->ucTorNum = ucTorNum;
}

void ucReadTor(Tor *xTor)
{
	if(TOR_GetStatus()&xTor->ucTorNum)
		xTor->ucTorValue = 1;
	else
		xTor->ucTorValue = 0;
}
