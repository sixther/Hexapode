/*! \mainpage My Personal Index Page
 *
 * \section intro_sec Introduction
 *
 * This is the introduction.
 *
 * \section install_sec Installation
 *
 * \subsection step1 Step 1: Opening the box
 *
 * etc...
 */
 
#include "board.h"
#include "FreeRTOS.h"
#include "task.h"
#include "timer_17xx_40xx.h"
#include "chip.h"

//define pour la fréquence du timer0 hard: 50µs
#define TICKRATE1_HZ 20000
//define pour la fréquence de la tache réarmage de la PWM: 20ms
#define TICKRATE2_HZ 50

unsigned char ucTemoin = 0;

void vTIMER0_Init()
{
	uint32_t timerFreq;
	
	Chip_TIMER_Init(LPC_TIMER0);
	/* on recupére la fréquence du périphérique */
	timerFreq = Chip_Clock_GetPeripheralClockRate(SYSCTL_PCLK_TIMER0);
	Chip_TIMER_Reset(LPC_TIMER0);
	/* on active l'interruption sur match0 */
	Chip_TIMER_MatchEnableInt(LPC_TIMER0, 0);
	/* on défini la fréquence du timer */
	Chip_TIMER_SetMatch(LPC_TIMER0, 0, (timerFreq / TICKRATE1_HZ));
	/* on reset le timer quand match */
	Chip_TIMER_ResetOnMatchEnable(LPC_TIMER0, 0);
	/* activation du timer */
	Chip_TIMER_Enable(LPC_TIMER0);
	/* Enable timer interrupt */
	NVIC_EnableIRQ(TIMER0_IRQn);
	NVIC_ClearPendingIRQ(TIMER0_IRQn);
}

/* TIMER0 HARD */
void TIMER0_IRQHandler()
{
	if(Chip_TIMER_MatchPending(LPC_TIMER0, 0)) 
	{
		Chip_TIMER_ClearMatch(LPC_TIMER0, 0);
		
		if(ucTemoin)
			Board_LED_Set(1, false);
		else
			Board_LED_Set(1, true);

		ucTemoin=~ucTemoin;
	}
}

/* Tache Timer 20 pour réarmer la PWM */
static portTASK_FUNCTION(vTimerTask, pvParameters) {
	bool LedState = false;

	while (1) {
		Board_LED_Set(0, LedState);
		LedState = (bool) !LedState;

		vTaskDelay(configTICK_RATE_HZ / TICKRATE2_HZ);
	}
}

int main()
{
	Board_Init();
	
	vTIMER0_Init();

	xTaskCreate(vTimerTask, (signed char *) "vTaskTimer",
				configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 1UL),
				(xTaskHandle *) NULL);	
	
	Board_LED_Set(0, false);
	Board_LED_Set(1, false);
	
	/* Start the scheduler */
	vTaskStartScheduler();


	while(1);
}

