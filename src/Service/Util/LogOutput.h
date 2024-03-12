/**
 * @file LogOutput.h
 * @author Andreas Schmidt (a.v.schmidt81@gmail.com)
 * @brief Header file for debug and log outputs
 *
 * @version 0.1
 * @date 2023-02-26
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef _LOG_OUTPUT_H_
#define _LOG_OUTPUT_H_

/*
 * Public Interface
*/

/**
 * @brief Outputs a simple string message to the UART output
 *
 * @param msg Zero terminated string to output
 */
void outputLog(const char* msg);

/**
 * @brief Outputs a formatted string to the UART output
 *
 *
 * @param format    Format string accroding printf specification
 * @param ...       Variable parameter
 *
 * @return Returns number of chars written to UART
 */
int outputLogf(const char* format, ...);

/**
 * @brief Outputs a simple string message to the UART output
 *
 * @remark Does not send anything to UART if DEBUG_BUILD is not defined
 *
 * @param msg Zero terminated string to output
 */
void outputDebugLog(const char* msg);

/**
 * @brief Outputs a formatted string to the UART output
 *
 * @remark Does not send anything to UART if DEBUG_BUILD is not defined
 *
 *
 * @param format    Format string accroding printf specification
 * @param ...       Variable parameter
 *
 * @return Returns number of chars written to UART
 */
int outputDebugLogf(const char* format, ...);

#endif