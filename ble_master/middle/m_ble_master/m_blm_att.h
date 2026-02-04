/********************************************************************************************************
 * @file    blm_att.h
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
#ifndef BLM_ATT_H_
#define BLM_ATT_H_

#include "types.h"

/**
 * @brief       this function serves to set current ReadRequest attribute handle
 * @param[in]	handle - connect handle
 * @return      none
 */
void app_setCurrentReadReq_attHandle(u16 handle);
u16 app_getCurrentReadReq_attHandle(void);
void host_att_set_current_readByTypeReq_uuid(u8 *uuid, u8 uuid_len);


#endif /* BLM_ATT_H_ */
