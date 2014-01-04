/*
 * @brief LPC1766STK board file
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

#ifndef __BOARD_LPC1766STK_H_
#define __BOARD_LPC1766STK_H_

#include "chip.h"
#include "board_api.h"
#include "lpc_phy.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup BOARD_LPC1766STK  * @ingroup BOARDS_17XX
 * @{
 */


#define BOARD_LPC1766STK	

/**
 * LED defines
 */
#define LEDS_LED1           0x01
#define LEDS_LED2           0x02
#define LEDS_NO_LEDS        0x00

/**
 * TOR defines
 */
#define TOR_TOR0     0x01
#define TOR_TOR1     0x02
#define TOR_TOR2     0x04
#define TOR_TOR3     0x08
#define TOR_TOR4     0x10
#define TOR_TOR5     0x20
#define NO_TOR_PRESSED   0x00

/**
 * @brief	Initialize pin muxing for a UART
 * @param	pUART	: Pointer to UART register block for UART pins to init
 * @return	Nothing
 */
void Board_UART_Init(LPC_USART_T *pUART);

void Board_PWM_Set(uint8_t PWMNumber, bool On);

uint32_t TOR_GetStatus(void);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __BOARD_LPC1766STK_H_ */
//THOMAS WAQUET
