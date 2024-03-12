/**
 * @file UARTModule.h
 * @author Andreas Schmidt (a.v.schmidt81@gmail.com)
 * @brief Header File for UART module
 *
 * @version 0.1
 * @date 2023-02-16
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef _UART_MODULE_H_
#define _UART_MODULE_H_

#include <stdint.h>

/*
 * Public Defines
*/
#define UART_ERR_OK                  0          //!< No error occured
#define UART_ERR_INIT_FAILURE        -1         //!< Error during UART initialization
#define UART_ERR_TRANSMIT            -2         //!< Error during UART tranmission


/**
 * @brief Initializes the UART2 peripheral to the specified baudrate
 *
 * Additionally, the communication parameter are set to 8 data bit,
 * 1 stop bit and none parity
 *
 * @param baudrate Baudrate to setup the UART to
 *
 * @return Returns UART_ERR_OK if no error occured
 */
int32_t uartInitialize(uint32_t baudrate);

/**
 * @brief Sends data to the UART interface
 *
 * @param pDataBuffer Pointer to the data buffer which should be send out
 * @param bufferLength Length of the buffer (number of bytes) to send
 *
 * @return Returns UART_ERR_OK if no error occured, otherwise UART_ERR_TRANSMIT
 */
int32_t uartSendData(uint8_t* pDataBuffer, int32_t bufferLength);

#endif