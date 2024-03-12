/**
 * @file Debounce.c
 * @author Andreas Schmidt (a.v.schmidt81@gmail.com)
 * @brief Implementation of the generic debouncer
 *
 * @version 0.1
 * @date 2023-02-26
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "Debounce.h"

static int32_t debounceInternalDebounce(DebounceInstance_t* pDebounceInstance, DebounceInputValue_t pInput, DebounceOutputValue_t* pOutput);

int32_t debounceInitialize(Debouncer_t* pDebouncer, DebounceInstance_t* pDebounceList, int16_t debounceCount, int16_t debounceMainCycle)
{
    if (pDebouncer == 0 || pDebounceList == 0)
        return DEBOUNCE_ERR_INVALID_PTR;

    pDebouncer->pDebounceList       = pDebounceList;
    pDebouncer->debouncerCount      = debounceCount;
    pDebouncer->mainDebounceCycle   = debounceMainCycle;

    for (int32_t i=0; i<debounceCount; i++)
    {
        pDebouncer->pDebounceList[i].debounceCycle  = pDebouncer->mainDebounceCycle;
    }

    return DEBOUNCE_ERR_OK;
}

int32_t debounceCycle(Debouncer_t* pDebouncer, DebounceInputValue_t* pInputValues)
{
    if (pDebouncer == 0 || pInputValues == 0)
        return DEBOUNCE_ERR_INVALID_PTR;

    for (int32_t i=0; i<pDebouncer->debouncerCount; i++)
    {
        DebounceInstance_t* pInstance = &(pDebouncer->pDebounceList[i]);
        DebounceInputValue_t input = pInputValues[i];
        DebounceOutputValue_t output = DEBOUNCE_OUTPUT_DEACTIVATE;

        debounceInternalDebounce(pInstance, input, &output);
    }

    return DEBOUNCE_ERR_OK;
}

int32_t debounceGetValue(Debouncer_t* pDebouncer, int32_t debounceID, DebounceOutputValue_t* pDebounceValue)
{
    if (pDebouncer == 0 || pDebounceValue == 0)
        return DEBOUNCE_ERR_INVALID_PTR;

    return DEBOUNCE_ERR_OK;
}

static int32_t debounceInternalDebounce(DebounceInstance_t* pDebounceInstance, DebounceInputValue_t input, DebounceOutputValue_t* pOutput)
{
    if (pDebounceInstance == 0)
        return DEBOUNCE_ERR_INVALID_PTR;

    if (pDebounceInstance->lastInputValue != input)
    {
        // Store the current input as last input
        pDebounceInstance->lastInputValue = input;

        // Depending on the input state, we calculate the counter value for release or press event
        if (input == DEBOUNCE_INPUT_ACTIVATED)
        {
            pDebounceInstance->debounceCycleCount = pDebounceInstance->debouncePressTime / pDebounceInstance->debounceCycle;
        }
        else
        {
            pDebounceInstance->debounceCycleCount = pDebounceInstance->debounceReleaseTime / pDebounceInstance->debounceCycle;
        }
    }

    // decrement the counter
    pDebounceInstance->debounceCycleCount--;

    if (pDebounceInstance->debounceCycleCount <= 0)
    {
        if (input == DEBOUNCE_INPUT_ACTIVATED)
        {
            *pOutput = DEBOUNCE_OUTPUT_ACTIVATED;
            pDebounceInstance->debounceCycleCount = pDebounceInstance->debouncePressTime / pDebounceInstance->debounceCycle;
        }
        else
        {
            *pOutput = DEBOUNCE_INPUT_DEACTIVATE;
            pDebounceInstance->debounceCycleCount = pDebounceInstance->debounceReleaseTime / pDebounceInstance->debounceCycle;
        }

        pDebounceInstance->lastOutputValue = *pOutput;
    }

    return DEBOUNCE_ERR_OK;
}