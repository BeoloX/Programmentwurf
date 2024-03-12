/**
 * @file DisplayModule.h
 * @author Andreas Schmidt (a.v.schmidt81@gmail.com)
 * @brief Header File for the 7-Segment display module
 *
 * @version 0.1
 * @date 2023-02-22
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef _DISPLAY_MODULE_H_
#define _DISPLAC_MODULE_H_

#include <stdint.h>

/*
 * Public Defines
*/
#define DISPLAY_ERR_OK                  0           //!< No error occured
#define DISPLAY_ERR_INIT_FAILURE        -1          //!< Error during display initialization

/* Defines for special digits for 7-Segment display */
#define DIGIT_DASH                      (16)        //!< Index in the encoding table for "-"
#define DIGIT_UPPER_O                   (17)        //!< Index in the encoding table for upper "o"
#define DIGIT_LOWER_O                   (18)        //!< Index in the encoding table for lower "o"
#define DIGIT_OFF                       (19)        //!< Index in the encoding table all segments off

/**
 * @brief Enumeration for the selected display
 *
 */
typedef enum _Display
{
    FLOOR_DISPLAY,                                  //!< Display to show the current floor
    ERROR_DISPLAY                                   //!< Display to show the current error code
} Display_t;

/**
 * @brief Initializes the Display Module
 *
 * @return Returns DISPLAY_ERR_OK if no error occured, otherwiese DISPLAY_ERR_INIT_FAILURE
 */
int32_t displayInitialize();

/**
 * @brief Displays a digit on the 7-Segment display
 *
 * @param outputDisplay Display to output to
 * @param digit The digit (0-9 and A-F)
 *
 * @return Returns DISPLAY_ERR_OK if no error occured
 */
int32_t displayShowDigit(Display_t outputDisplay, int8_t digit);

#endif