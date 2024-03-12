/**
 * @file FilterEMA.c
 * @author Andreas Schmidt (a.v.schmidt81@gmail.com)
 * @brief Implementation of fixed-point EMA filter
 *
 * @version 0.1
 * @date 2023-02-23
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "Util/Filter/Filter.h"

int32_t filterInitEMA(EMAFilterData_t* pEMA, int32_t scalingFactor, int32_t alpha, bool resetFilter)
{
    if (pEMA == 0)
    {
        return FILTER_ERR_INVALID_PTR;
    }

    if (resetFilter == true)
    {
        filterResetEMA(pEMA);
    }

    int32_t result = FILTER_ERR_OK;

    if (alpha >= 0 && alpha <= (1 * scalingFactor))
    {
        pEMA->alpha         = alpha;
        pEMA->scalingFactor = scalingFactor;
    }
    else
    {
        result = FILTER_ERR_INVALID_PARAM;
    }

    return result;
}

int32_t filterResetEMA(EMAFilterData_t* pEMA)
{
    if (pEMA == 0)
    {
        return FILTER_ERR_INVALID_PTR;
    }

    pEMA->previousValue         = 0;
    pEMA->firstValueAvailable   = false;

    return FILTER_ERR_OK;
}

int32_t filterEMA(EMAFilterData_t* pEMA, int32_t sensorValue)
{
	int32_t filteredValue = 0;

	if (pEMA->firstValueAvailable == true)
	{
        // Perform filtering (with scaling)
		filteredValue = pEMA->previousValue * (pEMA->scalingFactor - pEMA->alpha) + sensorValue * pEMA->alpha;
        // Scale down the result
		filteredValue = filteredValue / pEMA->scalingFactor;
	}
	else
	{
		filteredValue               = sensorValue;
		pEMA->firstValueAvailable   = true;
	}

	pEMA->previousValue = filteredValue;

	return filteredValue;
}