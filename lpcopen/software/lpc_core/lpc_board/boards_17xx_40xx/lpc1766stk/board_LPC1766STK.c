/*
 * @brief NXP lpc1766stk board file
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2012
 * All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * LPC products.  This software is supplied "AS IS" without any warranties of
 * any kind, and NXP Semiconductors and its licensor disclaim any and
 * all warranties, express or implied, including all implied warranties of
 * merchantability, fitness for a particular purpose and non-infringement of
 * intellectual property rights.  NXP Semiconductors assumes no responsibility
 * or liability for the use of the software, conveys no license or rights under any
 * patent, copyright, mask work right, or any other intellectual property rights in
 * or to any products. NXP Semiconductors reserves the right to make changes
 * in the software without notification. NXP Semiconductors also makes no
 * representation or warranty that such application will be suitable for the
 * specified use without further testing or modification.
 *
 * @par
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors' and its
 * licensor's relevant copyrights in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers.  This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
 */

#include "board.h"
#include "string.h"

#include "retarget.c"

/** @ingroup BOARD_LPC1766STK
 * @{
 */

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/
#define LED0_GPIO_PORT_NUM                      1
#define LED0_GPIO_BIT_NUM                       25
#define LED1_GPIO_PORT_NUM											0
#define LED1_GPIO_BIT_NUM												4

#define PWM0_GPIO_PORT_NUM											1
#define PWM0_GPIO_BIT_NUM												0

#define PWM1_GPIO_PORT_NUM											1
#define PWM1_GPIO_BIT_NUM												1

#define PWM2_GPIO_PORT_NUM											1
#define PWM2_GPIO_BIT_NUM												4

#define PWM3_GPIO_PORT_NUM											1
#define PWM3_GPIO_BIT_NUM												8

#define PWM4_GPIO_PORT_NUM											1
#define PWM4_GPIO_BIT_NUM												9

#define PWM5_GPIO_PORT_NUM											1
#define PWM5_GPIO_BIT_NUM												10

#define PWM6_GPIO_PORT_NUM											1
#define PWM6_GPIO_BIT_NUM												14

#define PWM7_GPIO_PORT_NUM											1
#define PWM7_GPIO_BIT_NUM												15

#define PWM8_GPIO_PORT_NUM											1
#define PWM8_GPIO_BIT_NUM												16

#define PWM9_GPIO_PORT_NUM											1
#define PWM9_GPIO_BIT_NUM												17

#define PWM10_GPIO_PORT_NUM											1
#define PWM10_GPIO_BIT_NUM											18

#define PWM11_GPIO_PORT_NUM											1
#define PWM11_GPIO_BIT_NUM											19

#define PWM12_GPIO_PORT_NUM											1
#define PWM12_GPIO_BIT_NUM											20

#define PWM13_GPIO_PORT_NUM											1
#define PWM13_GPIO_BIT_NUM											21

#define PWM14_GPIO_PORT_NUM											1
#define PWM14_GPIO_BIT_NUM											22

#define PWM15_GPIO_PORT_NUM											1
#define PWM15_GPIO_BIT_NUM											23

#define PWM16_GPIO_PORT_NUM											1
#define PWM16_GPIO_BIT_NUM											24

#define PWM17_GPIO_PORT_NUM											1
#define PWM17_GPIO_BIT_NUM											25

#define PWM18_GPIO_PORT_NUM											1
#define PWM18_GPIO_BIT_NUM											26

#define PWM19_GPIO_PORT_NUM											1
#define PWM19_GPIO_BIT_NUM											27

#define TOR0_GPIO_PORT_NUM											1
#define TOR0_GPIO_BIT_NUM												28

#define TOR1_GPIO_PORT_NUM											1
#define TOR1_GPIO_BIT_NUM												29

#define TOR2_GPIO_PORT_NUM											1
#define TOR2_GPIO_BIT_NUM												30

#define TOR3_GPIO_PORT_NUM											2
#define TOR3_GPIO_BIT_NUM												0

#define TOR4_GPIO_PORT_NUM											2
#define TOR4_GPIO_BIT_NUM												1

#define TOR5_GPIO_PORT_NUM											2
#define TOR5_GPIO_BIT_NUM												7

#define TELE0_ADC_PORT_NUM											1
#define TELE0_ADC_BIT_NUM												31
/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

/*!< System Clock Frequency (Core Clock) */
uint32_t SystemCoreClock;

/*****************************************************************************
 * Private functions
 ****************************************************************************/

/* Initializes board LED(s) */
static void Board_LED_Init(void)
{
	/* Pin PIO0_22 is configured as GPIO pin during SystemInit */
	/* Set the PIO_22 as output */
	Chip_GPIO_WriteDirBit(LPC_GPIO, LED0_GPIO_PORT_NUM, LED0_GPIO_BIT_NUM, true);
	Chip_GPIO_WriteDirBit(LPC_GPIO, LED1_GPIO_PORT_NUM, LED1_GPIO_BIT_NUM, true);
}

/*****************************************************************************
 * Public functions
 ****************************************************************************/

/* Update system core clock rate, should be called if the system has
   a clock rate change */
void SystemCoreClockUpdate(void)
{
	/* CPU core speed */
	SystemCoreClock = Chip_Clock_GetSystemClockRate();
}

/* Initialize UART pins */
void Board_UART_Init(LPC_USART_T *pUART)
{
	/* Pin Muxing has already been done during SystemInit */
}

/* Initialize debug output via UART for board */
void Board_Debug_Init(void)
{
#if defined(DEBUG_ENABLE)
	Board_UART_Init(DEBUG_UART);

	/* Setup UART for 115.2K8N1 */
	Chip_UART_Init(DEBUG_UART);
	Chip_UART_SetBaud(DEBUG_UART, 115200);
	Chip_UART_ConfigData(DEBUG_UART, UART_DATABIT_8, UART_PARITY_NONE, UART_STOPBIT_1);

	/* Enable UART Transmit */
	Chip_UART_TxCmd(DEBUG_UART, ENABLE);
#endif
}

/* Sends a character on the UART */
void Board_UARTPutChar(char ch)
{
#if defined(DEBUG_ENABLE)
	while (Chip_UART_SendByte(DEBUG_UART, (uint8_t) ch) == ERROR) {}
#endif
}

/* Gets a character from the UART, returns EOF if no character is ready */
int Board_UARTGetChar(void)
{
#if defined(DEBUG_ENABLE)
	uint8_t data;

	if (Chip_UART_ReceiveByte(DEBUG_UART, &data) == SUCCESS) {
		return (int) data;
	}
#endif
	return EOF;
}

/* Outputs a string on the debug UART */
void Board_UARTPutSTR(char *str)
{
#if defined(DEBUG_ENABLE)
	while (*str != '\0') {
		Board_UARTPutChar(*str++);
	}
#endif
}

void Board_TELE_Init(void)
{
	
}

/*Initializes board GPIO TOR */
void Board_TOR_Init(void)
{
	Chip_GPIO_WriteDirBit(LPC_GPIO, TOR0_GPIO_PORT_NUM, TOR0_GPIO_BIT_NUM, false);
	Chip_GPIO_WriteDirBit(LPC_GPIO, TOR1_GPIO_PORT_NUM, TOR1_GPIO_BIT_NUM, false);
	Chip_GPIO_WriteDirBit(LPC_GPIO, TOR2_GPIO_PORT_NUM, TOR2_GPIO_BIT_NUM, false);
	Chip_GPIO_WriteDirBit(LPC_GPIO, TOR3_GPIO_PORT_NUM, TOR3_GPIO_BIT_NUM, false);
	Chip_GPIO_WriteDirBit(LPC_GPIO, TOR4_GPIO_PORT_NUM, TOR4_GPIO_BIT_NUM, false);
	Chip_GPIO_WriteDirBit(LPC_GPIO, TOR5_GPIO_PORT_NUM, TOR5_GPIO_BIT_NUM, false);
}

/* Initializes board GPIO PWM */
void Board_PWM_Init(void)
{
	Chip_GPIO_WriteDirBit(LPC_GPIO, PWM0_GPIO_PORT_NUM, PWM0_GPIO_BIT_NUM, true);
	Chip_GPIO_WriteDirBit(LPC_GPIO, PWM1_GPIO_PORT_NUM, PWM1_GPIO_BIT_NUM, true);
	Chip_GPIO_WriteDirBit(LPC_GPIO, PWM2_GPIO_PORT_NUM, PWM2_GPIO_BIT_NUM, true);
	Chip_GPIO_WriteDirBit(LPC_GPIO, PWM3_GPIO_PORT_NUM, PWM3_GPIO_BIT_NUM, true);
	Chip_GPIO_WriteDirBit(LPC_GPIO, PWM4_GPIO_PORT_NUM, PWM4_GPIO_BIT_NUM, true);
	Chip_GPIO_WriteDirBit(LPC_GPIO, PWM5_GPIO_PORT_NUM, PWM5_GPIO_BIT_NUM, true);
	Chip_GPIO_WriteDirBit(LPC_GPIO, PWM6_GPIO_PORT_NUM, PWM6_GPIO_BIT_NUM, true);
	Chip_GPIO_WriteDirBit(LPC_GPIO, PWM7_GPIO_PORT_NUM, PWM7_GPIO_BIT_NUM, true);
	Chip_GPIO_WriteDirBit(LPC_GPIO, PWM8_GPIO_PORT_NUM, PWM8_GPIO_BIT_NUM, true);
	Chip_GPIO_WriteDirBit(LPC_GPIO, PWM9_GPIO_PORT_NUM, PWM9_GPIO_BIT_NUM, true);
	Chip_GPIO_WriteDirBit(LPC_GPIO, PWM10_GPIO_PORT_NUM, PWM10_GPIO_BIT_NUM, true);
	Chip_GPIO_WriteDirBit(LPC_GPIO, PWM11_GPIO_PORT_NUM, PWM11_GPIO_BIT_NUM, true);
	Chip_GPIO_WriteDirBit(LPC_GPIO, PWM12_GPIO_PORT_NUM, PWM12_GPIO_BIT_NUM, true);
	Chip_GPIO_WriteDirBit(LPC_GPIO, PWM13_GPIO_PORT_NUM, PWM13_GPIO_BIT_NUM, true);
	Chip_GPIO_WriteDirBit(LPC_GPIO, PWM14_GPIO_PORT_NUM, PWM14_GPIO_BIT_NUM, true);
	Chip_GPIO_WriteDirBit(LPC_GPIO, PWM15_GPIO_PORT_NUM, PWM15_GPIO_BIT_NUM, true);
	Chip_GPIO_WriteDirBit(LPC_GPIO, PWM16_GPIO_PORT_NUM, PWM16_GPIO_BIT_NUM, true);
	Chip_GPIO_WriteDirBit(LPC_GPIO, PWM17_GPIO_PORT_NUM, PWM17_GPIO_BIT_NUM, true);
	Chip_GPIO_WriteDirBit(LPC_GPIO, PWM18_GPIO_PORT_NUM, PWM18_GPIO_BIT_NUM, true);
	Chip_GPIO_WriteDirBit(LPC_GPIO, PWM19_GPIO_PORT_NUM, PWM19_GPIO_BIT_NUM, true);
}

void Board_PWM_Set(uint8_t PWMNumber, bool On)
{
	switch(PWMNumber)
	{
		case 0: Chip_GPIO_WritePortBit(LPC_GPIO, PWM0_GPIO_PORT_NUM, PWM0_GPIO_BIT_NUM, On); break;
		case 1: Chip_GPIO_WritePortBit(LPC_GPIO, PWM1_GPIO_PORT_NUM, PWM1_GPIO_BIT_NUM, On); break;
		case 2: Chip_GPIO_WritePortBit(LPC_GPIO, PWM2_GPIO_PORT_NUM, PWM2_GPIO_BIT_NUM, On); break;
		case 3: Chip_GPIO_WritePortBit(LPC_GPIO, PWM3_GPIO_PORT_NUM, PWM3_GPIO_BIT_NUM, On); break;
		case 4: Chip_GPIO_WritePortBit(LPC_GPIO, PWM4_GPIO_PORT_NUM, PWM4_GPIO_BIT_NUM, On); break;
		case 5: Chip_GPIO_WritePortBit(LPC_GPIO, PWM5_GPIO_PORT_NUM, PWM5_GPIO_BIT_NUM, On); break;
		case 6: Chip_GPIO_WritePortBit(LPC_GPIO, PWM6_GPIO_PORT_NUM, PWM6_GPIO_BIT_NUM, On); break;
		case 7: Chip_GPIO_WritePortBit(LPC_GPIO, PWM7_GPIO_PORT_NUM, PWM7_GPIO_BIT_NUM, On); break;
		case 8: Chip_GPIO_WritePortBit(LPC_GPIO, PWM8_GPIO_PORT_NUM, PWM8_GPIO_BIT_NUM, On); break;
		case 9: Chip_GPIO_WritePortBit(LPC_GPIO, PWM9_GPIO_PORT_NUM, PWM9_GPIO_BIT_NUM, On); break;
		case 10: Chip_GPIO_WritePortBit(LPC_GPIO, PWM10_GPIO_PORT_NUM, PWM10_GPIO_BIT_NUM, On); break;
		case 11: Chip_GPIO_WritePortBit(LPC_GPIO, PWM11_GPIO_PORT_NUM, PWM11_GPIO_BIT_NUM, On); break;
		case 12: Chip_GPIO_WritePortBit(LPC_GPIO, PWM12_GPIO_PORT_NUM, PWM12_GPIO_BIT_NUM, On); break;
		case 13: Chip_GPIO_WritePortBit(LPC_GPIO, PWM13_GPIO_PORT_NUM, PWM13_GPIO_BIT_NUM, On); break;
		case 14: Chip_GPIO_WritePortBit(LPC_GPIO, PWM14_GPIO_PORT_NUM, PWM14_GPIO_BIT_NUM, On); break;
		case 15: Chip_GPIO_WritePortBit(LPC_GPIO, PWM15_GPIO_PORT_NUM, PWM15_GPIO_BIT_NUM, On); break;
		case 16: Chip_GPIO_WritePortBit(LPC_GPIO, PWM16_GPIO_PORT_NUM, PWM16_GPIO_BIT_NUM, On); break;
		case 17: Chip_GPIO_WritePortBit(LPC_GPIO, PWM17_GPIO_PORT_NUM, PWM17_GPIO_BIT_NUM, On); break;
		case 18: Chip_GPIO_WritePortBit(LPC_GPIO, PWM18_GPIO_PORT_NUM, PWM18_GPIO_BIT_NUM, On); break;
		case 19: Chip_GPIO_WritePortBit(LPC_GPIO, PWM19_GPIO_PORT_NUM, PWM19_GPIO_BIT_NUM, On); break;
		default: break;
	}
}
uint32_t TOR_GetStatus(void)
{
	uint8_t ret = NO_TOR_PRESSED;
	
	if (Chip_GPIO_ReadPortBit(LPC_GPIO, TOR0_GPIO_PORT_NUM, TOR0_GPIO_BIT_NUM) == 0x00) {
		ret |= TOR_TOR0;
	}
	if (Chip_GPIO_ReadPortBit(LPC_GPIO, TOR1_GPIO_PORT_NUM, TOR1_GPIO_BIT_NUM) == 0x00) {
		ret |= TOR_TOR1;
	}
	if (Chip_GPIO_ReadPortBit(LPC_GPIO, TOR2_GPIO_PORT_NUM, TOR2_GPIO_BIT_NUM) == 0x00) {
		ret |= TOR_TOR2;
	}
	if (Chip_GPIO_ReadPortBit(LPC_GPIO, TOR3_GPIO_PORT_NUM, TOR3_GPIO_BIT_NUM) == 0x00) {
		ret |= TOR_TOR3;
	}
	if (Chip_GPIO_ReadPortBit(LPC_GPIO, TOR4_GPIO_PORT_NUM, TOR4_GPIO_BIT_NUM) == 0x00) {
		ret |= TOR_TOR4;
	}
	if (Chip_GPIO_ReadPortBit(LPC_GPIO, TOR5_GPIO_PORT_NUM, TOR5_GPIO_BIT_NUM) == 0x00) {
		ret |= TOR_TOR5;
	}	
	
	return ret;
}

/* Sets the state of a board LED to on or off */
void Board_LED_Set(uint8_t LEDNumber, bool On)
{
	/* There is only one LED */
	if (LEDNumber == 0) {
		Chip_GPIO_WritePortBit(LPC_GPIO, LED0_GPIO_PORT_NUM, LED0_GPIO_BIT_NUM, On);
	}
	if (LEDNumber == 1) {
		Chip_GPIO_WritePortBit(LPC_GPIO, LED1_GPIO_PORT_NUM, LED1_GPIO_BIT_NUM, On);
	}
}

/* Returns the current state of a board LED */
bool Board_LED_Test(uint8_t LEDNumber)
{
	if (LEDNumber == 0) {
		return Chip_GPIO_ReadPortBit(LPC_GPIO, LED0_GPIO_PORT_NUM, LED0_GPIO_BIT_NUM);
	}
	if (LEDNumber == 1) {
		return Chip_GPIO_ReadPortBit(LPC_GPIO, LED1_GPIO_PORT_NUM, LED1_GPIO_BIT_NUM);
	}
	return 0;
}

/* Set up and initialize all required blocks and functions related to the
   board hardware */
void Board_Init(void)
{
	/* Sets up DEBUG UART */
	DEBUGINIT();

	/* Updates SystemCoreClock global var with current clock speed */
	SystemCoreClockUpdate();

	/* Initializes GPIO */
	Chip_GPIO_Init(LPC_GPIO);
	Chip_IOCON_Init(LPC_IOCON);

	/* Initialize LEDs */
	Board_LED_Init();
	
	Board_TOR_Init();
	
	Board_PWM_Init();
}


/**
 * @}
 */
 //THOMAS WAQUET
