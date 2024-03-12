/**
 * @file SampleApplication.c
 * @author Andreas Schmidt (a.v.schmidt81@gmail.com)
 * @brief Implementation of small sample application based on
 * state machine table
 *
 * @version 0.1
 * @date 2023-02-24
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <string.h>
#include "Util/Global.h"
#include "Util/printf.h"

#include "UARTModule.h"
#include "ButtonModule.h"
#include "LEDModule.h"

#include "Util/StateTable/StateTable.h"

#include "SampleApplication.h"
#include "ADCValues.h"
#include "LogOutput.h"

#define distanceTillError 20  //in 10cm
#define Distance_Min 500000	// in µV
#define Distance_Max 2500000	// in µV
#define Voltage_Range 2000000	// in µV
#define Distance_Range 95		//in m

/*
 * Private Functions
*/

// State realte functions (on-Entry, on-State and on-Exit)
static int32_t onEntryStartup(State_t* pState, int32_t eventID);
static int32_t onStateRunning(State_t* pState, int32_t eventID);
static int32_t onExitRunning(State_t* pState, int32_t eventID);
static int32_t onEntryFailure(State_t* pState, int32_t eventID);
static int32_t onEntryEmergency(State_t* pState, int32_t eventID);
static int32_t onStateEmergency(State_t* pState, int32_t eventID);

/**
 * @brief List of State for the State Machine
 *
 * This list only constructs the state objects for each possible state
 * in the state machine. There are no transistions or events defined
 *
 */
static State_t gStateList[] =
{
    {STATE_ID_STARTUP,			onEntryStartup,  	0,					0,              false},
    {STATE_ID_RUNNING_NORMAL,	0,					onStateRunning, 	onExitRunning,  false},
	{STATE_ID_RUNNING_RACE, 	0,					onStateRunning, 	onExitRunning,  false},
	{STATE_ID_EMERGENCY, 		onEntryEmergency,	onStateEmergency, 	0,  			false},
    {STATE_ID_FAILURE, 			onEntryFailure,  	0,					0,              false}
};

/**
 * @brief Definition of the transistion table of the state machine. Each row
 * contains FROM_STATE_ID, TO_STATE_ID, EVENT_ID, Function Pointer Guard Function
 *
 * The last two members of a transistion row are only the initialization of dynamic
 * members used durin runtim
 */
static StateTableEntry_t gStateTableEntries[] =
{
    {STATE_ID_STARTUP,          		STATE_ID_RUNNING_NORMAL,           	EVT_ID_INIT_READY,          0,      0,      0},
    {STATE_ID_STARTUP,          		STATE_ID_FAILURE,           		EVT_ID_SENSOR_FAILED,       0,      0,      0},
    {STATE_ID_RUNNING_NORMAL,          	STATE_ID_RUNNING_RACE,           	EVT_ID_NORMAL2RACE,       	0,      0,      0},
	{STATE_ID_RUNNING_RACE,          	STATE_ID_RUNNING_NORMAL,           	EVT_ID_RACE2NORMAL,       	0,      0,      0},
    {STATE_ID_RUNNING_NORMAL,          	STATE_ID_EMERGENCY,           		EVT_ID_EMERGENCY,       	0,      0,      0},
	{STATE_ID_RUNNING_RACE,          	STATE_ID_EMERGENCY,           		EVT_ID_EMERGENCY,       	0,      0,      0},
    {STATE_ID_RUNNING_NORMAL,          	STATE_ID_FAILURE,           		EVT_ID_SENSOR_FAILED,       0,      0,      0},
	{STATE_ID_RUNNING_RACE,          	STATE_ID_FAILURE,           		EVT_ID_SENSOR_FAILED,       0,      0,      0}
};

/**
 * @brief Global State Table instance
 *
 */
static StateTable_t gStateTable;


int32_t sampleAppInitialize()
{
    gStateTable.pStateList = gStateList;
    gStateTable.stateCount = sizeof(gStateList) / sizeof(State_t);
    int32_t result = stateTableInitialize(&gStateTable, gStateTableEntries, sizeof(gStateTableEntries) / sizeof(StateTableEntry_t), STATE_ID_STARTUP);

    return result;
}

int32_t sampleAppRun()
{
    int32_t result = stateTableRunCyclic(&gStateTable);
    return result;
}

int32_t sameplAppSendEvent(int32_t eventID)
{
    int32_t result = stateTableSendEvent(&gStateTable, eventID);
    return result;
}

static int32_t onEntryStartup(State_t* pState, int32_t eventID)
{
    return sameplAppSendEvent(EVT_ID_INIT_READY);
}

static int32_t onStateRunning(State_t* pState, int32_t eventID)
{

//	if(50mspassed){
//		if(distance<=20){
//			brake;
//		}
//
//	}

	int32_t Sensor1MicroVolt = filteredChannel1();
	int32_t Sensor2MicroVolt = filteredChannel2();

	if(Sensor1MicroVolt<=Distance_Min || Sensor1MicroVolt>=Distance_Max){
		return sameplAppSendEvent(EVT_ID_SENSOR_FAILED);
	}
	if(Sensor2MicroVolt<=Distance_Min || Sensor2MicroVolt>=Distance_Max){
		return sameplAppSendEvent(EVT_ID_SENSOR_FAILED);
	}

	int32_t Sensor_1_10cm=((Sensor1MicroVolt-Distance_Min)*Distance_Range * 10) /Voltage_Range;
	int32_t Sensor_2_10cm=((Sensor2MicroVolt-Distance_Min)*Distance_Range * 10) /Voltage_Range;

	if((Sensor_1_10cm - Sensor_2_10cm) <= -distanceTillError || (Sensor_1_10cm - Sensor_2_10cm) >= distanceTillError){

		return sameplAppSendEvent(EVT_ID_EMERGENCY);
	}

    ledToggleLED(LED1_DOOR_STATUS);
    //ledSetLED(LED4_BRAKE_STATUS);
    return 0;
}

static int32_t onEntryEmergency(State_t* pState, int32_t eventID){

	char message [] = "Emergency!";
	outputLog(message);
	//UART<-"EMERGENCY"

	return 0;
}

static int32_t onStateEmergency(State_t* pState, int32_t eventID){


	//nothing

	return 0;
}

static int32_t onExitRunning(State_t* pState, int32_t eventID)
{
    return 0;
}

static int32_t onEntryFailure(State_t* pState, int32_t eventID)
{
    ledSetLED(LED3_MOTOR_STATUS, LED_ON);
    return 0;
}
