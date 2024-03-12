/**
 * @file Debounce.h
 * @author Andreas Schmidt (a.v.schmidt81@gmail.com)
 * @brief Header file for a generic debouncing algorithm
 *
 * @version 0.1
 * @date 2023-02-25
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef _DEBOUNCE_H_
#define _DEBOUNCE_H_

#include <stdint.h>

/*
 * Public defines
*/
#define DEBOUNCE_ERR_OK                 0   //!< No error occured
#define DEBOUNCE_ERR_INVALID_PTR        -1  //!< Invalid pointer
#define DEBOUNCE_ERR_INVALUD_PARAMETER  -2  //!< Invalid parameter values

/*
 * Public Types
*/

/**
 * @brief Enumeration for possible input values to the debouncer
 * These value must be mapped from the used inputs (e.g. for buttons)
 *
 */
typedef enum _DebounceInputValue
{
    DEBOUNCE_INPUT_ACTIVATED,                        //!< Input status for "activated"
    DEBOUNCE_INPUT_DEACTIVATE,                       //!< Input status for "deactivated"
    DEBOUNCE_INPUT_UNKNOWN                           //!< Input status for "unknown"
} DebounceInputValue_t;

/**
 * @brief Enumeration for possible, already debounced output values
 *
 */
typedef enum _DebounceOutputValue
{
    DEBOUNCE_OUTPUT_ACTIVATED,                       //!< Output status for a debounced "activated"
    DEBOUNCE_OUTPUT_DEACTIVATE                       //!< Output status for a decounved "deactviated"
} DebounceOutputValue_t;

/**
 * @brief Struct to define a single debounce instance for a
 * digital input.
 *
 */
typedef struct _DebounceInstance
{
    int16_t debounceID;                             //!< ID for a debouncer (used to identify it in the list)
    int16_t debouncePressTime;                      //!< Debounce time for "press event" in ms
    int16_t debounceReleaseTime;                    //!< Debounce time for "release event" in ms

    int16_t debounceCycle;                          //!< Cycle time for the debouncer in ms
    int16_t debounceCycleCount;                     //!< Cycle counter for the debouncer

    DebounceInputValue_t lastInputValue;            //!< Last input value fed into the debouncer
    DebounceOutputValue_t lastOutputValue;          //!< Last output value provided by the debouncer
} DebounceInstance_t;

/**
 * @brief Struct which represents a kind of "debouncing manager" to handle
 * multiple debounce instances
 *
 */
typedef struct _Debouncer
{
    DebounceInstance_t* pDebounceList;              //!< Pointer to list of debounce instances
    int16_t debouncerCount;                         //!< Number of debounce instances in the list
    int16_t mainDebounceCycle;                      //!< Cycle time of the debounce manager
} Debouncer_t;

/*
 * Public Interface
*/

/**
 * @brief Initializes the debouncer with the provided paramter
 *
 * @param pDebouncer            Pointer to debounce manager
 * @param pDebounceList         Pointer to list of debounce instances
 * @param debounceCount         Number of debounc instances in the öist
 * @param debounceMainCycle     Cycle time of the debounce manager in ms
 *
 * @return Returns DEBOUNCE_ERR_OK if no error occured
 */
int32_t debounceInitialize(Debouncer_t* pDebouncer, DebounceInstance_t* pDebounceList, int16_t debounceCount, int16_t debounceMainCycle);

/**
 * @brief Main cycle function for debouncer.
 * The provided inputs represents the values (mapped to activated/deactivated)
 * of the different signal inputs.
 *
 * @remark The size of the input value array and the order of the entries in+
 * the input array must match the array size and order of the debounce instance
 * list of the debouncer
 *
 * @param pDebouncer        Pointer to the debouncer
 * @param pInputValues      Poitner to the array of input values (same size as debounceCount)
 *
 * @return Returns DEBOUNCE_ERR_OK if no error occurred
 */
int32_t debounceCycle(Debouncer_t* pDebouncer, DebounceInputValue_t* pInputValues);

/**
 * @brief Returns the current debounced value for a specific input specified
 * by the debounceID
 *
 * @param pDebouncer        Poitner to the debouncer
 * @param debounceID        ID of the debouncer to return
 * @param pDebounceValue    Pointer to store the result of the output
 *
 * @return Returns DEBOUNCE_ERR_OK if no error occured
 */
int32_t debounceGetValue(Debouncer_t* pDebouncer, int32_t debounceID, DebounceOutputValue_t* pDebounceValue);

#endif