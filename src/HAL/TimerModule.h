/**
 * @file TimerModule.h
 * @author Andreas Schmidt (a.v.schmidt81@gmail.com)
 * @brief Header file for the Timer Module
 *
 * @version 0.1
 * @date 2023-02-21
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef _TIMER_MODULE_H_
#define _TIMER_MODULE_H_

#include <stdint.h>

/*
 * Public Defines
*/
#define TIMER_ERR_OK                  0         //!< No error occured
#define TIMER_ERR_INIT_FAILURE        -1        //!< Error during timer initialization

/**
 * @brief Initializes the Timer Module
 *
 * @return Returns TIMER_ERR_OK if no error occured, otherwiese TIMER_ERR_INIT_FAILURE
 */
int32_t timerInitialize();

#endif