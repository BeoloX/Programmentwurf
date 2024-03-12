/**
 * @file Scheduler.c
 * @author Andreas Schmidt (a.v.schmidt81@gmail.com)
 * @brief Implementation of the cooperative scheduler with a 
 * pre-defined set of cyclic "task slots"
 *
 * @version 0.1
 * @date 2023-02-16
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "Scheduler.h"
#include "stm32g4xx_hal.h"
#include "ADCModule.h"
/*
 * Private Defines
*/
#define HAL_TICK_VALUE_1MS      1       //!< Number of HAL Ticks used for 1ms Tasks
#define HAL_TICK_VALUE_10MS     10      //!< Number of HAL Ticks used for 10ms Tasks
#define HAL_TICK_VALUE_100MS    100     //!< Number of HAL Ticks used for 100ms Tasks
#define HAL_TICK_VALUE_250MS    250     //!< Number of HAL Ticks used for 250ms Tasks
#define HAL_TICK_VALUE_1000MS   1000    //!< Number of HAL Ticks used for 1000ms Tasks

static uint32_t schedGetElapsedTime (uint32_t savedTimestamp, uint32_t currentTime);

int32_t schedInitialize(Scheduler* pScheduler)
{

	if (pScheduler == 0)
	{
		return SCHED_ERR_INVALID_PTR;
	}


	pScheduler->halTick_1ms = 		0;
	pScheduler->halTick_10ms = 		0;
	pScheduler->halTick_100ms = 	0;
	pScheduler->halTick_250ms = 	0;
	pScheduler->halTick_1000ms =	0;

	pScheduler->pTask_1ms = 		0;
	pScheduler->pTask_10ms = 		0;
	pScheduler->pTask_100ms = 		0;
	pScheduler->pTask_250ms = 		0;
	pScheduler->pTask_1000ms = 		0;


    return SCHED_ERR_OK;
}


int32_t schedCycle(Scheduler* pScheduler)
{
	if (pScheduler == 0)
		{
			return SCHED_ERR_INVALID_PTR;
		}

		uint32_t timeElapsed = 0;
		uint32_t actualTick = 0;


		actualTick = HAL_GetTick();
		timeElapsed = schedGetElapsedTime(pScheduler->halTick_1ms, actualTick);
		if(timeElapsed >= HAL_TICK_VALUE_1MS)
		{
			pScheduler->halTick_1ms = actualTick;
			if(pScheduler->halTick_1ms != 0)
			{
				pScheduler->pTask_1ms();
			}
		}

		actualTick = HAL_GetTick();
		timeElapsed = schedGetElapsedTime(pScheduler->halTick_10ms, actualTick);
		if(timeElapsed >= HAL_TICK_VALUE_10MS)
		{
			pScheduler->halTick_10ms = actualTick;
			if(pScheduler->halTick_10ms != 0)
			{
				pScheduler->pTask_10ms();
			}
		}

		actualTick = HAL_GetTick();
		timeElapsed = schedGetElapsedTime(pScheduler->halTick_100ms, actualTick);
		if(timeElapsed >= HAL_TICK_VALUE_100MS)
		{
			pScheduler->halTick_100ms = actualTick;
			if(pScheduler->halTick_100ms != 0)
			{
				pScheduler->pTask_100ms();
			}
		}

		actualTick = HAL_GetTick();
		timeElapsed = schedGetElapsedTime(pScheduler->halTick_250ms, actualTick);
		if(timeElapsed >= HAL_TICK_VALUE_250MS)
		{
			pScheduler->halTick_250ms = actualTick;
			if(pScheduler->halTick_250ms != 0)
			{
				pScheduler->pTask_250ms();
			}
		}

		actualTick = HAL_GetTick();
		timeElapsed = schedGetElapsedTime(pScheduler->halTick_1000ms, actualTick);
		if(timeElapsed >= HAL_TICK_VALUE_1000MS)
		{
			pScheduler->halTick_1000ms = actualTick;
			if(pScheduler->halTick_1000ms != 0)
			{
				pScheduler->pTask_1000ms();
			}
		}

    return SCHED_ERR_OK;
}
static uint32_t schedGetElapsedTime (uint32_t savedTimestamp, uint32_t currentTime)
{
	uint32_t timeDiff = currentTime - savedTimestamp;
	return timeDiff;
}
