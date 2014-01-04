typedef struct
{
	unsigned char ucTorValue;
	unsigned char ucTorNum;
}Tor;

void vInitTor(Tor *xTor, unsigned char ucTorNum);
void ucReadTor(Tor *xTor);
