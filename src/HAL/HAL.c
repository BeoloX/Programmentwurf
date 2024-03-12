/**
 * @file HAL.c
 * @author Andreas Schmidt (a.v.schmidt81@gmail.com)
 * @brief Implementation of general HAL functions incl. glue code
 * for the STM32Cube HAL
 *
 * @version 0.1
 * @date 2023-02-14
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "stm32g4xx_hal.h"

/**
  * @brief Initializes the Global MSP.
  *
  * @remark: this HAL_MspInit function is called automatically by the
  * STM32 HAL library
  */
void HAL_MspInit(void)
{
    __HAL_RCC_SYSCFG_CLK_ENABLE();
    __HAL_RCC_PWR_CLK_ENABLE();

    /* System interrupt init*/

    /** Disable the internal Pull-Up in Dead Battery pins of UCPD peripheral
    */
    HAL_PWREx_DisableUCPDDeadBattery();
}
