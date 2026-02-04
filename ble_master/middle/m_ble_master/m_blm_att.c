/********************************************************************************************************
 * @file    blm_att.c
 *
 * @brief   This is the source file for BLE SDK
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
#include <m_blm_att.h>
#include <m_blm_host.h>

#include "tl_common.h"
#include "drivers.h"
#include "stack/ble/ble.h"

#include "app.h"
#define     TELINK_UNPAIR_KEYVALUE		0xFF  //conn state, unpair


u8 read_by_type_req_uuid[16] = {};
u8 read_by_type_req_uuidLen;

u16 	current_read_req_handle;

/**
 * @brief       host layer set current readByTypeRequest UUID
 * @param[in]	uuid
 * @param[in]	uuid_len - uuid byte number
 * @return      none
 */
void host_att_set_current_readByTypeReq_uuid(u8 *uuid, u8 uuid_len)
{
	read_by_type_req_uuidLen = uuid_len;
	memcpy(read_by_type_req_uuid, uuid, uuid_len);
}


/**
 * @brief       this function serves to set current ReadRequest attribute handle
 * @param[in]	handle - connect handle
 * @return      none
 */
void app_setCurrentReadReq_attHandle(u16 handle)
{
	current_read_req_handle = handle;
}

/**
 * @brief       this function serves to get current ReadRequest attribute handle
 * @param[in]	none
 * @return      current ReadRequest attribute handle
 */
u16 app_getCurrentReadReq_attHandle(void)
{
	return current_read_req_handle;
}

