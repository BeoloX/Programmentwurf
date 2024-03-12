/**
 * @file ADCModule.h
 * @author Andreas Schmidt (a.v.schmidt81@gmail.com)
 * @brief Header File for the ADC Service Layer Module
 *
 * @version 0.1
 * @date 2023-02-14
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef _ADC_MODULE_H
#define _ADC_MODULE_H

#include <stdint.h>

/*
 * Public Defines
*/
#define ADC_ERR_OK                  0               //!< No error occured
#define ADC_ERR_INIT_FAILURE        -1              //!< Error during ADC initialization

/**
 * @brief Enumeration for used ADC channels
 *
 */
typedef enum _ADC_Channel_
{
    ADC_INPUT0,             //!< ADC Channel 0 used for Pot 1 (Position Sensor)
    ADC_INPUT1,             //!< ADC Channel 1 used for Pot 2 (Force Sensor)
    ADC_TEMP,               //!< ADC Channel 2 used for internal Temperature Sensor
	ADC_VBAT,				//!< ADC Channel 3 used for internal VBat voltage
    ADC_VREF                //!< ADC Channel 4 used for internal reference voltage
} ADC_Channel_t;

/**
 * @brief Initialize the ADC peripheral block
 *
 * @return Returns ADC_ERR_OK if no error occured
 */
int32_t adcInitialize();

/**
 * @brief Reads an ADC channel by returning the global ADC value read via
 * interrupt and DMA and converts it to millivolt
 *
 * @param adcChannel Channel to read
 *
 * @return Returns value of ADC channel in microvolt [µV]
 */
int32_t adcReadChannel(ADC_Channel_t adcChannel);

/**
 * @brief Reads an ADC channel by returning the global ADC value read via
 * interrupt and DMA
 *
 * @param adcChannel Channel to read
 *
 * @return Returns value of ADC channel in digits
 */
int32_t adcReadChannelRaw(ADC_Channel_t adcChannel);

#endif
