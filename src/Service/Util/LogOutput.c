/**
 * @file LogOutput.c
 * @author Andreas Schmidt (a.v.schmidt81@gmail.com)
 * @brief Implementation of Log debug outputs
 *
 * @version 0.1
 * @date 2023-02-26
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <stdint.h>
#include <string.h>

#include "Util/Global.h"
#include "Util/printf.h"

#include "stm32g4xx_hal.h"
#include "UARTModule.h"

/*
 * Private Defines
*/
#define MAX_OUTPUT_BUFFER         128

/*
 * Private Module Globals
*/

/**
 * @brief Buffer used to store the strings create by internalFormattedOutput() calls
 * The buffer has a total size of MAX_OUTPUT_BUFFER. Therefore only MAX_OUTPUT_BUFFER - 1
 * chars can be stored.
 *
 */
static char gOutputBuffer[MAX_OUTPUT_BUFFER];

static int internalFormattedOutput(const char* format, va_list va);

/**
 * @brief Formats a string according the format string spec and the arguments and
 * sends it to the UART
 *
 * @param format    Format string spec according printf()
 * @param va        Variable argument list
 *
 * @return Returns number of chars prepared for the string
 */
static int internalFormattedOutput(const char* format, va_list va)
{
    int ret = 0;
    ret = vsnprintf_(gOutputBuffer, MAX_OUTPUT_BUFFER, format, va);

    if (ret > 0 && ret <= MAX_OUTPUT_BUFFER)
    {
        uartSendData((uint8_t*)gOutputBuffer, ret);
    }

    return ret;
}

void outputLog(const char* msg)
{
    // send buffer to UART
    int32_t bufferLength = strlen(msg);
    uartSendData((uint8_t*)msg, bufferLength);
}

void outputDebugLog(const char* msg)
{
#ifdef DEBUG_BUILD
    outputLog(msg);
#endif
}

int outputLogf(const char* format, ...)
{
    int ret = 0;
    va_list va;
    va_start(va, format);

    ret = internalFormattedOutput(format, va);
    va_end(va);

    return ret;
}

int outputDebugLogf(const char* format, ...)
{
    int ret = 0;

#ifdef DEBUG_BUILD
    va_list va;
    va_start(va, format);

    ret = internalFormattedOutput(format, va);
    va_end(va);
#endif

    return ret;
}
