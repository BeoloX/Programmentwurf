/**
 * @file ButtonModule.h
 * @author Andreas Schmidt (a.v.schmidt81@gmail.com)
 * @brief Header file for the Button Module
 *
 * @version 0.1
 * @date 2023-02-23
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef _BUTTON_MODULE_H_
#define _BUTTON_MODULE_H_

/*
 * Public Defines
*/
#define BUTTON_ERR_OK      0            //!< No error occured

/**
 * @brief Enumeration of available Buttons and their usage
 *
 */
typedef enum _Button_t
{
    BTN_ACTIVATE,                   	//!< Button used to activate/deactivate the system (SW1)
    BTN_RACE_MODE                     	//!< Button used for race mode (SW2)
} Button_t;

/**
 * @brief Enumeration for possible Button states
 *
 */
typedef enum _Button_Status_t
{
    BUTTON_PRESSED,                     //!< Button is pressed
    BUTTON_RELEASED                     //!< Button is released
} Button_Status_t;

/**
 * @brief Initialize the GPIOs for the Button inputs
 *
 * @return Returns BUTTON_ERR_OK if no error occured
 */
int32_t buttonInitialize();

/**
 * @brief Reads the input status of the button
 *
 * @param button Button to read the status from
 *
 * @returns Returns the button status (pressed or released)
 *
 * @remark This function doesn't do any debouncing. It just reads
 * the pure GPIO state
 */
Button_Status_t buttonGetButtonStatus(Button_t button);


#endif
