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
#define BUTTONS_BUTTON1_GPIO_PORT_NUM           0
#define BUTTONS_BUTTON1_GPIO_BIT_NUM            23
#define LED0_GPIO_PORT_NUM                      1
#define LED0_GPIO_BIT_NUM                       25
#define LED1_GPIO_PORT_NUM											0
#define LED1_GPIO_BIT_NUM												4



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
}

void Board_Buttons_Init(void)
{
	Chip_GPIO_WriteDirBit(LPC_GPIO, BUTTONS_BUTTON1_GPIO_PORT_NUM, BUTTONS_BUTTON1_GPIO_BIT_NUM, false);
}

uint32_t Buttons_GetStatus(void)
{
	uint8_t ret = NO_BUTTON_PRESSED;
	if (Chip_GPIO_ReadPortBit(LPC_GPIO, BUTTONS_BUTTON1_GPIO_PORT_NUM, BUTTONS_BUTTON1_GPIO_BIT_NUM) == 0x00) {
		ret |= BUTTONS_BUTTON1;
	}
	return ret;
}



/**
 * @}
 */
 //THOMAS WAQUET
