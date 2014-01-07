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
#include "Hexapode.h"
#include "board.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timer_17xx_40xx.h"
#include "chip.h"
#include "basic_io.h"
#include "Protopode.h"
#include <string.h>

//define pour la fréquence du timer0 hard: 50µs
#define TICKRATE1_HZ		20000
//define pour la fréquence de la tache réarmage de la PWM: 20ms
#define TICKRATE2_HZ 		50
//define pour la fréquence de la tache lecture TOR et Telemetre: 500ms
#define TICKRATE3_HZ		2
//define pour la fréquence de la tache TX/RX de la com: 100ms
#define TICKRATE4_HZ		10

unsigned char ucTemoin = 0;
unsigned long ulTaskNumber[configEXPECTED_NO_RUNNING_TASKS];

static ADC_Clock_Setup_T ADCSetup;

typedef struct
{
	char cData[50];
}Message;


xQueueHandle xQueue;
Message xMessage;

FeetHexapode xFeetLeftFront;
FeetHexapode xFeetLeftMid;
FeetHexapode xFeetLeftBack;
FeetHexapode xFeetRightFront;
FeetHexapode xFeetRightMid;
FeetHexapode xFeetRightBack;
HeadHexapode xHead;

Trame xTrame;

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

void vADC_Init()
{
	Chip_ADC_Init(LPC_ADC, &ADCSetup);
	Chip_ADC_Channel_Enable_Cmd(LPC_ADC, ADC_C, ENABLE);
	Chip_ADC_Burst_Cmd(LPC_ADC, DISABLE);
}

void vInit_Hexapode()
{
		//Initialisation des PPM et TOR
		vInitFeet(&xFeetLeftFront, PPM_1MS, PPM_1MS, PPM_1MS, FEET_LEFT_FRONT_PWMNUM1, FEET_LEFT_FRONT_PWMNUM2, FEET_LEFT_FRONT_PWMNUM3, FEET_LEFT_FRONT_TORNUM);
		vInitFeet(&xFeetLeftMid, PPM_1MS, PPM_1MS, PPM_1MS, FEET_LEFT_MID_PWMNUM1, FEET_LEFT_MID_PWMNUM2, FEET_LEFT_MID_PWMNUM3, FEET_LEFT_MID_TORNUM);
		vInitFeet(&xFeetLeftBack, PPM_1MS, PPM_1MS, PPM_1MS, FEET_LEFT_BACK_PWMNUM1, FEET_LEFT_BACK_PWMNUM2, FEET_LEFT_BACK_PWMNUM3, FEET_LEFT_BACK_TORNUM);
		vInitFeet(&xFeetRightFront, PPM_1MS, PPM_1MS, PPM_1MS, FEET_RIGHT_FRONT_PWMNUM1, FEET_RIGHT_FRONT_PWMNUM2, FEET_RIGHT_FRONT_PWMNUM3, FEET_RIGHT_FRONT_TORNUM);
		vInitFeet(&xFeetRightMid, PPM_1MS, PPM_1MS, PPM_1MS, FEET_RIGHT_MID_PWMNUM1, FEET_RIGHT_MID_PWMNUM2, FEET_RIGHT_MID_PWMNUM3, FEET_RIGHT_MID_TORNUM);
		vInitFeet(&xFeetRightBack, PPM_1MS, PPM_1MS, PPM_1MS, FEET_RIGHT_BACK_PWMNUM1, FEET_RIGHT_BACK_PWMNUM2, FEET_RIGHT_BACK_PWMNUM3, FEET_RIGHT_BACK_TORNUM);
		vInitHead(&xHead, PPM_1MS, PPM_1MS, HEAD_PWMNUM1, HEAD_PWMNUM2, 10.0);
}

/* TIMER0 HARD */
void TIMER0_IRQHandler()
{
	if(Chip_TIMER_MatchPending(LPC_TIMER0, 0)) 
	{
		Board_LED_Set(0, true);
		
		Chip_TIMER_ClearMatch(LPC_TIMER0, 0);
		
		vMoveFeet(&xFeetLeftFront, 1, 1, 1);
		vMoveFeet(&xFeetLeftMid, 1, 1, 1);
		vMoveFeet(&xFeetLeftBack, 1, 1, 1);
		vMoveFeet(&xFeetRightFront, 1, 1, 1);
		vMoveFeet(&xFeetRightMid, 1, 1, 1);
		vMoveFeet(&xFeetRightBack, 1, 1, 1);
		
		vMoveHead(&xHead, 1, 1);
		
		Board_LED_Set(0, false);
	}
}

/* Tache Timer 20 pour réarmer la PWM */
static portTASK_FUNCTION(vTimerPWMTask, pvParameters) {	
	while (1) {

		vSetFeet(&xFeetLeftFront, PPM_1MS, PPM_1MS, PPM_1MS);
		vSetFeet(&xFeetLeftMid, PPM_1MS, PPM_1MS, PPM_1MS);
		vSetFeet(&xFeetLeftBack, PPM_1MS, PPM_1MS, PPM_1MS);
		vSetFeet(&xFeetRightFront, PPM_1MS, PPM_1MS, PPM_1MS);
		vSetFeet(&xFeetRightMid, PPM_1MS, PPM_1MS, PPM_1MS);
		vSetFeet(&xFeetRightBack, PPM_1MS, PPM_1MS, PPM_1MS);
		
		vSetHead(&xHead, PPM_1MS, PPM_1MS);
		
		vTaskDelay(configTICK_RATE_HZ / TICKRATE2_HZ);
	}
}

/* Tache pour la lecture des TOR et du telemetre */
static portTASK_FUNCTION(vTORTask, pvParameters) {	

	while (1) {
		
		/* Start A/D conversion */
		Chip_ADC_Set_StartMode(LPC_ADC, ADC_START_NOW, ADC_TRIGGERMODE_RISING);
		/* Waiting for A/D conversion complete */
		while (Chip_ADC_Read_Status(LPC_ADC, ADC_C, ADC_DR_DONE_STAT) != SET) {}
		/* Read ADC value */
		Chip_ADC_Read_Value(LPC_ADC, ADC_C, &xHead.xTelemetre1.usAdcValue);
		
		vCalculSecuriteTelemetre(&xHead);
					
		vTaskDelay(configTICK_RATE_HZ / TICKRATE3_HZ);
	}
}

/* Tache pour TX/RX de la com: 100ms */
static portTASK_FUNCTION(vComTask, pvParameters) {
portBASE_TYPE xStatus;

	
	while (1) {
		xStatus = xQueueReceive( xQueue, &xMessage, configTICK_RATE_HZ / TICKRATE4_HZ );

		if( xStatus == pdPASS )
		{
			//Decodage de la trame
			vDcdTrame(&xTrame, xMessage.cData);
						
			//En fonction du résultat on va remplir les ressources ciblées
			//Feet
			if(!strcmp(xTrame.cType,"F"))
			{
				
			}
			//Head
			else if (!strcmp(xTrame.cType,"H"))
			{
				
			}
			//Telemetre
			else if (!strcmp(xTrame.cType,"TELE"))
			{

			}
			//TOR
			else if (!strcmp(xTrame.cType,"TOR"))
			{

			}
			//CMUCAM
			else if (!strcmp(xTrame.cType,"CAM"))
			{

			}
		}	
	}
}

int main()
{
	Board_Init();

	vInit_Hexapode();
	
	vTIMER0_Init();

	xQueue = xQueueCreate( 50, sizeof( Message ) );
	
	//xQueueSendToBack( xQueue, "$F,L,M,1,45\n", 0 );
	
	
	
	xTaskCreate(vTimerPWMTask, (signed char *) "vTaskTimerPWM",
				configMINIMAL_STACK_SIZE, NULL, 1,
				(xTaskHandle *) NULL);
	
	xTaskCreate(vTORTask, (signed char *) "vTaskTOR",
				configMINIMAL_STACK_SIZE, NULL, 5,
				(xTaskHandle *) NULL);
	
	xTaskCreate(vComTask, (signed char *) "vTaskCom",
				configMINIMAL_STACK_SIZE, NULL, 3,
				(xTaskHandle *) NULL);
	
	Board_LED_Set(0, false);
	Board_LED_Set(1, false);
	
	/* Start the scheduler */
	vTaskStartScheduler();


	while(1);
}

