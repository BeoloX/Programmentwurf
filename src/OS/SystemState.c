#include "SystemState.h"
#include "HardwareConfig.h"


#include "stm32g4xx_hal.h"

#include "Util/Global.h"
#include "Util/printf.h"
#include "LogOutput.h"
#include "string.h"

#include "System.h"

#include "UARTModule.h"
#include "ButtonModule.h"
#include "LEDModule.h"
#include "ADCModule.h"
#include "TimerModule.h"
#include "DisplayModule.h"
#include "Util/Filter/Filter.h"
#include "Tasks.h"

#include "Scheduler.h"

#define Sysstate_Undefined  -1
#define Sysstate_Startup     0
#define Sysstate_Running     1
#define Sysstate_Failure     2

#define ERROR_OK             0
#define ERROR_FAILURE       -1

int32_t gSystemState;

Scheduler myScheduler;



static int32_t initializePeripherals()
{
    // Initializue UART used for Debug-Outputs
    uartInitialize(115200);
    // Initialize GPIOs for Buttons
    buttonInitialize();
    // Initialize GPIOs for LED and 7-Segment output
    ledInitialize();
    // Initialize Display
    //displayInitialize();
    // Initialize Timer, DMA and ADC for sensor measurements
    timerInitialize();
    // Initialize ADC
    adcInitialize();

    return ERROR_OK;
}

int32_t initializeSystemState(){
	gSystemState = Sysstate_Startup;
	return ERROR_OK;
}



static int32_t performStartup(){

	// Initialize the HAL
	HAL_Init();
	// Initialize System Clock
	SystemClock_Config();
	// Initialize Peripherals
	initializePeripherals();
	// Initialize System State
	initializeSystemState();

	schedInitialize(&myScheduler);

	initFilters();
	sampleAppInitialize();



	memset(&myScheduler, 0, sizeof(Scheduler));



	myScheduler.pTask_1ms = myTask1ms;
	myScheduler.pTask_10ms = myTask10ms;
	myScheduler.pTask_100ms = myTask100ms;
	myScheduler.pTask_250ms = myTask250ms;
	myScheduler.pTask_1000ms = myTask1000ms;

	return ERROR_OK;
}

static void performStartupTransition(int32_t initResult){
	if (initResult == ERROR_OK){
		gSystemState = Sysstate_Running;
	}
	else{
		gSystemState = Sysstate_Failure;
	}
}

static int32_t performRunningState(){
	//HAL_GPIO_TogglePin(LED0_GPIO_PORT, LED0_PIN);
	schedCycle(&myScheduler);
	//HAL_Delay(250);
	return ERROR_OK;

}

static void SafeState()
{

	ledSetLED(LED4_BRAKE_STATUS, LED_OFF);
	ledSetLED(LED1_DOOR_STATUS, LED_OFF);
	while(true)
	{

	}
}

int32_t CycleStateMachine(){
	switch (gSystemState)
	{
		case Sysstate_Startup:
		{
			int32_t initResult = performStartup();
			performStartupTransition(initResult);
		}
		break;

		case Sysstate_Running:
		{
			performRunningState();
		}
		break;

		case Sysstate_Failure:
		{
			SafeState();
		}
		break;

		default:
		{
			break;
		}
	}
	return ERROR_OK;
}
