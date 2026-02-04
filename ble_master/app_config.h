/********************************************************************************************************
 * @file    app_config.h
 *
 * @brief   This is the header file for BLE SDK
 *
 * @author  BLE GROUP
 * @date    06,2020
 *
 * @par     Copyright (c) 2020, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
 *
 *          Licensed under the Apache License, Version 2.0 (the "License");
 *          you may not use this file except in compliance with the License.
 *          You may obtain a copy of the License at
 *
 *              http://www.apache.org/licenses/LICENSE-2.0
 *
 *          Unless required by applicable law or agreed to in writing, software
 *          distributed under the License is distributed on an "AS IS" BASIS,
 *          WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *          See the License for the specific language governing permissions and
 *          limitations under the License.
 *
 *******************************************************************************************************/
#pragma once

#include  	"application/audio/audio_common.h"
#include 	"user_conf.h"

#define FW_VERSION   				FW_VER


/////////////////// MODULE /////////////////////////////////
#define BLE_HOST_SMP_ENABLE				    1  //Master SMP strongly recommended enabled
#define ACL_CENTRAL_SIMPLE_SDP_ENABLE		1  //simple service discovery


#define BLE_MASTER_OTA_ENABLE			    0  //slave ota test

/* Flash Protection:
 * 1. Flash protection is enabled by default in SDK. User must enable this function on their final mass production application.
 * 2. User should use "Unlock" command in Telink BDT tool for Flash access during development and debugging phase.
 * 3. Flash protection demonstration in SDK is a reference design based on sample code. Considering that user's final application may
 *    different from sample code, for example, user's final firmware size is bigger, or user have a different OTA design, or user need
 *    store more data in some other area of Flash, all these differences imply that Flash protection reference design in SDK can not
 *    be directly used on user's mass production application without any change. User should refer to sample code, understand the
 *    principles and methods, then change and implement a more appropriate mechanism according to their application if needed.
 */
#define APP_FLASH_PROTECTION_ENABLE			1


///////////////////////// DEBUG  Configuration ////////////////////////////////////////////////
#define DEBUG_GPIO_ENABLE							0

/* debug channel select */
#define TLKAPI_DEBUG_CHANNEL_USB   			1 //USB debug
#define TLKAPI_DEBUG_CHANNEL_UART  			2 //GPIO simulate UART debug
#define TLKAPI_DEBUG_CHANNEL				TLKAPI_DEBUG_CHANNEL_UART


#define UART_PRINT_DEBUG_ENABLE             USER_UART_PRINT_DEBUG_ENABLE   //GPIO simulate uart print func

#define APP_LOG_EN									1
#define APP_FLASH_INIT_LOG_EN						1

/////////////////////// Master Dongle Board Select Configuration ///////////////////////////////
#if(__PROJECT_8258_MASTER_KMA_DONGLE__ )
	#define BOARD_SELECT								BOARD_825X_DONGLE_C1T139A3
#elif(__PROJECT_8278_MASTER_KMA_DONGLE__ )
	#define BOARD_SELECT								BOARD_827X_DONGLE_C1T201A3
#endif


#define CLOCK_SYS_CLOCK_HZ  								32000000



/////////////////// watchdog  //////////////////////////////
#define MODULE_WATCHDOG_ENABLE		0
#define WATCHDOG_INIT_TIMEOUT		500  //ms





/////////////////////////////////////// PRINT DEBUG INFO ///////////////////////////////////////
#if (UART_PRINT_DEBUG_ENABLE)
	#define DEBUG_INFO_TX_PIN           					GPIO_PB1
	#define PULL_WAKEUP_SRC_PB5         					PM_PIN_PULLUP_10K
	#define PB1_OUTPUT_ENABLE         						1
	#define PB1_DATA_OUT                                    1 
#endif



/////////////////// set default   ////////////////

#include "vendor/common/default_config.h"
