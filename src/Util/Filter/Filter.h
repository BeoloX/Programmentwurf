/**
 * @file filter.h
 * @author Andreas Schmidt (a.v.schmidt81@gmail.com)
 * @brief Header file for Filter library
 *
 * @version 0.1
 * @date 2023-02-23
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef _FILTER_API_H_
#define _FILTER_API_H_

#include <stdbool.h>
#include <stdint.h>

/*
 * Public Defines
*/
#define FILTER_ERR_OK                   0       //!< No error occured
#define FILTER_ERR_GENERAL              -1      //!< General error during filter processing
#define FILTER_ERR_INVALID_PTR          -2      //!< Invalid pointer (Null Pointer)
#define FILTER_ERR_INVALID_PARAM        -3      //!< Invalid parameter value

/*
 * Public Types
*/

/**
 * @brief Struct which represents a EMA filter
 *
 */
typedef struct _EMAFilterData
{
    bool firstValueAvailable;                   //!< Flag to indicate whether there was already a value set as prev value
    int32_t alpha;                              //!< Alpha value (filter constant) as scaled value
    int32_t previousValue;                      //!< Previous value of the filter output
    int32_t scalingFactor;                      //!< Used scaling factor
} EMAFilterData_t;

/**
 * @brief Initialize an EMA filter with the provided parameter
 *
 * @param pEMA              Poitner to the EMA filter struct
 * @param scalingFactor     Scaling factor used for internal calculations
 * @param alpha             Already scaled alpha factor (must be scaled with same scaling factor as supplied via parameter)
 * @param resetFilter       Flag to indicate whether the filter should be reset
 *
 * @return Return FILTER_ERR_OK is no error occured
 */
int32_t filterInitEMA(EMAFilterData_t* pEMA, int32_t scalingFactor, int32_t alpha, bool resetFilter);

int32_t filterResetEMA(EMAFilterData_t* pEMA);

int32_t filterEMA(EMAFilterData_t* pEMA, int32_t sensorValue);

#endif