/**
 * @file main.c
 * @author Andreas Schmidt (a.v.schmidt81@gmail.com)
 * @brief Main file for the VP elevator control
 *
 * @version 0.1
 * @date 2023-02-13
 *
 * @copyright Copyright (c) 2023
 *
 */
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

#include "GlobalObjects.h"


int main(void)
{
    while (1)
    {
    	CycleStateMachine();
    }
}
