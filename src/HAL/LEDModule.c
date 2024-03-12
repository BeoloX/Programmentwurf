/**
 * @file LEDModule.c
 * @author Andreas Schmidt (a.v.schmidt81@gmail.com)
 * @brief Implementation of the LED module
 *
 * @version 0.1
 * @date 2023-02-13
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "stm32g4xx_hal.h"

#include "HardwareConfig.h"
#include "LEDModule.h"

int32_t ledInitialize()
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOF_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOC, _7SEGF_PIN | _7SEGG_PIN | LED2_PIN, GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOA, _7SEGA_PIN | _7SEGB_PIN | _7SEGC_PIN | _7SEGD_PIN | _7SEGE_PIN, GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOB, _7SEG_COM_PIN | LED1_PIN | LED0_PIN | LED4_PIN | LED3_PIN, GPIO_PIN_RESET);


	/*Configure GPIO pins : PCPin PCPin PCPin */
	GPIO_InitStruct.Pin 	= _7SEGF_PIN | _7SEGG_PIN | LED2_PIN;
	GPIO_InitStruct.Mode 	= GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull 	= GPIO_NOPULL;
	GPIO_InitStruct.Speed	= GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	/*Configure GPIO pins : PAPin PAPin PAPin PAPin
						   PAPin */
	GPIO_InitStruct.Pin 	= _7SEGA_PIN | _7SEGB_PIN | _7SEGC_PIN | _7SEGD_PIN | _7SEGE_PIN;
	GPIO_InitStruct.Mode 	= GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull 	= GPIO_NOPULL;
	GPIO_InitStruct.Speed	 = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/*Configure GPIO pins : PBPin PBPin PBPin PBPin
						   PBPin PBPin */
	GPIO_InitStruct.Pin 	= _7SEG_COM_PIN | LED1_PIN | LED0_PIN | LED4_PIN | LED3_PIN;
	GPIO_InitStruct.Mode 	= GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull 	= GPIO_NOPULL;
	GPIO_InitStruct.Speed 	= GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    return LED_ERR_OK;
}

void ledToggleLED(LED_t led)
{
    switch(led)
    {
        case LED0_APP_STATUS:
            HAL_GPIO_TogglePin(LED0_GPIO_PORT, LED0_PIN);
            break;

        case LED1_DOOR_STATUS:
            HAL_GPIO_TogglePin(LED1_GPIO_PORT, LED1_PIN);
            break;

        case LED2_EMERGENCY:
            HAL_GPIO_TogglePin(LED2_GPIO_PORT, LED2_PIN);
            break;

        case LED3_MOTOR_STATUS:
            HAL_GPIO_TogglePin(LED3_GPIO_PORT, LED3_PIN);
            break;

        case LED4_BRAKE_STATUS:
            HAL_GPIO_TogglePin(LED4_GPIO_PORT, LED4_PIN);
            break;

        default:
            break;
    }
}

void ledSetLED(LED_t led, LED_Status_t ledStatus)
{
    switch(led)
    {
        case LED0_APP_STATUS:
            HAL_GPIO_WritePin(LED0_GPIO_PORT, LED0_PIN, ledStatus);
            break;

        case LED1_DOOR_STATUS:
            HAL_GPIO_WritePin(LED1_GPIO_PORT, LED1_PIN, ledStatus);
            break;

        case LED2_EMERGENCY:
            HAL_GPIO_WritePin(LED2_GPIO_PORT, LED2_PIN, ledStatus);
            break;

        case LED3_MOTOR_STATUS:
            HAL_GPIO_WritePin(LED3_GPIO_PORT, LED3_PIN, ledStatus);
            break;

        case LED4_BRAKE_STATUS:
            HAL_GPIO_WritePin(LED4_GPIO_PORT, LED4_PIN, ledStatus);
            break;

        default:
            break;
    }
}
