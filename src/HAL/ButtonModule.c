/**
 * @file ButtonModule.c
 * @author Andreas Schmidt (a.v.schmidt81@gmail.com)
 * @brief Implementation of the Button Module
 *
 * @version 0.1
 * @date 2023-02-23
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "stm32g4xx_hal.h"

#include "HardwareConfig.h"
#include "ButtonModule.h"


int32_t buttonInitialize()
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	  /* GPIO Ports Clock Enable */
	  __HAL_RCC_GPIOC_CLK_ENABLE();
	  __HAL_RCC_GPIOF_CLK_ENABLE();
	  __HAL_RCC_GPIOA_CLK_ENABLE();
	  __HAL_RCC_GPIOB_CLK_ENABLE();


	  /*Configure GPIO pin : PtPin */
	  GPIO_InitStruct.Pin 	= B1_PIN;
	  GPIO_InitStruct.Mode 	= GPIO_MODE_INPUT;
	  GPIO_InitStruct.Pull 	= GPIO_NOPULL;
	  HAL_GPIO_Init(B1_GPIO_PORT, &GPIO_InitStruct);


	  /*Configure GPIO pin : PtPin */
	  GPIO_InitStruct.Pin = SW1_PIN;
	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	  GPIO_InitStruct.Pull = GPIO_PULLUP;
	  HAL_GPIO_Init(SW1_GPIO_PORT, &GPIO_InitStruct);

	  /*Configure GPIO pin : PtPin */
	  GPIO_InitStruct.Pin = SW2_PIN;
	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	  GPIO_InitStruct.Pull = GPIO_PULLUP;
	  HAL_GPIO_Init(SW2_GPIO_PORT, &GPIO_InitStruct);

    return BUTTON_ERR_OK;
}

Button_Status_t buttonGetButtonStatus(Button_t button)
{
    GPIO_PinState gpioStatus = GPIO_PIN_RESET;
    Button_Status_t buttonStatus = BUTTON_RELEASED;

    switch (button)
    {
        // Read the Ground Floor button (internal pull-up --> GPIO=1 ==> Button released)
        case BTN_ACTIVATE:
        {
            gpioStatus = HAL_GPIO_ReadPin(SW1_GPIO_PORT, SW1_PIN);
            if (gpioStatus == GPIO_PIN_RESET)
                buttonStatus = BUTTON_PRESSED;
            else
                buttonStatus = BUTTON_RELEASED;
        }
        break;

        // Read the First Floor button (internal pull-up --> GPIO=1 ==> Button released)
        case BTN_RACE_MODE:
        {
            gpioStatus = HAL_GPIO_ReadPin(SW2_GPIO_PORT, SW2_PIN);
            if (gpioStatus == GPIO_PIN_RESET)
                buttonStatus = BUTTON_PRESSED;
            else
                buttonStatus = BUTTON_RELEASED;
        }
        break;
    }

    return buttonStatus;
}
