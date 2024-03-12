/**
 * @file SampleApplication.h
 * @author Andreas Schmidt (a.v.schmidt81@gmail.com)
 * @brief Header File for sample application
 *
 * @version 0.1
 * @date 2023-02-24
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef _SAMPLE_APPLICATION_H_
#define _SAMPLE_APPLICATION_H_

#include <stdint.h>

/*
 * Public Defines
*/
#define STATE_ID_STARTUP        		1       //!< Example State for Startup
#define STATE_ID_RUNNING_NORMAL        	2       //!< Example State for Runing
#define STATE_ID_RUNNING_RACE        	3       //!< Example State for Runing
#define STATE_ID_FAILURE        		4       //!< Example State for Failure
#define STATE_ID_EMERGENCY        		5       //!< Example State for Failure

#define EVT_ID_INIT_READY       		1       //!< Event ID for INIT_READY
#define EVT_ID_SENSOR_FAILED    		2       //!< Event ID for Sensor Failure
#define EVT_ID_NORMAL2RACE  			3       //!< Event ID for Sensor Failure
#define EVT_ID_RACE2NORMAL  			4       //!< Event ID for Sensor Failure
#define EVT_ID_EMERGENCY	 			4       //!< Event ID for Sensor Failure
/*
 * Public Interface
*/

int32_t sampleAppInitialize();

int32_t sampleAppRun();

int32_t sameplAppSendEvent(int32_t eventID);

#endif
