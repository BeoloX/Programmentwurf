#include "stm32g4xx_hal.h"

#include "Util/Global.h"
#include "Util/printf.h"
#include "LogOutput.h"

#include "System.h"

#include "UARTModule.h"
#include "ButtonModule.h"
#include "LEDModule.h"
#include "ADCModule.h"
#include "TimerModule.h"
#include "DisplayModule.h"

#include "Scheduler.h"
#include "string.h"
#include "stm32g4xx_hal.h"
#include "HardwareConfig.h"
#include "ADCModule.h"
#include "ADCValues.h"
#include "SampleApplication.h"




void myTask1ms(void){
//	HAL_GPIO_TogglePin(LED0_GPIO_PORT, LED0_PIN);
	sampleAppRun();
}
void myTask10ms(void){
	//HAL_GPIO_TogglePin(LED1_GPIO_PORT, LED1_PIN);
}
void myTask100ms(void){
	//HAL_GPIO_TogglePin(LED1_GPIO_PORT, LED1_PIN);
}
void myTask250ms(void){
	//HAL_GPIO_TogglePin(LED2_GPIO_PORT, LED2_PIN);
}
void myTask1000ms(void){
	//HAL_GPIO_TogglePin(LED3_GPIO_PORT, LED3_PIN);
}
