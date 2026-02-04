/********************************************************************************************************
 * @file    app_att.h
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
#ifndef APP_ATT_H_
#define APP_ATT_H_




///////////////////////////////////// ATT  HANDLER define ///////////////////////////////////////
typedef enum {
    ATT_H_START = 0,                    // 0x0000: Attribute đầu tiên (tổng số attribute)

    //// ================= GAP Service ================= ////
    GenericAccess_PS_H,                 // 0x0001: Primary Service - GAP (UUID: 0x1800)
    GenericAccess_DeviceName_CD_H,      // 0x0002: Characteristic Declaration - Device Name
    GenericAccess_DeviceName_DP_H,      // 0x0003: Characteristic Value - Device Name (UUID: 0x2A00)
    GenericAccess_Appearance_CD_H,      // 0x0004: Characteristic Declaration - Appearance
    GenericAccess_Appearance_DP_H,      // 0x0005: Characteristic Value - Appearance (UUID: 0x2A01)
    CONN_PARAM_CD_H,                    // 0x0006: Characteristic Declaration - Connection Parameters
    CONN_PARAM_DP_H,                    // 0x0007: Characteristic Value - Connection Parameters (UUID: 0x2A04)

    //// ================= NUS Service ================= ////
    NUS_PS_H,                           // 0x0008: Primary Service - NUS (UUID: 6E400001...)
    NUS_TX_CD_H,                        // 0x0009: Characteristic Declaration - TX
    NUS_TX_DP_H,                        // 0x000A: Characteristic Value - TX (UUID: 6E400003...) NOTIFY
    NUS_TX_CCC_H,                       // 0x000B: Client Characteristic Config - TX CCCD (UUID: 0x2902)
    NUS_RX_CD_H,                        // 0x000C: Characteristic Declaration - RX
    NUS_RX_DP_H,                        // 0x000D: Characteristic Value - RX (UUID: 6E400002...) WRITE/WRITE_NO_RSP

#if (BLE_OTA_SERVER_ENABLE)
    //// ================= OTA Service ================= ////
    OTA_PS_H,                           // 0x000E: Primary Service - OTA
    OTA_CMD_OUT_CD_H,                   // 0x000F: Characteristic Declaration - OTA Command
    OTA_CMD_OUT_DP_H,                   // 0x0010: Characteristic Value - OTA Data
    OTA_CMD_INPUT_CCB_H,                // 0x0011: Client Characteristic Config - OTA CCCD
    OTA_CMD_OUT_DESC_H,                 // 0x0012: User Description - OTA Name
#endif

    ATT_END_H,                    
} ATT_HANDLE;


/**
 * @brief      Initialize the attribute table
 * @param[in]  none
 * @return     none
 */
void my_att_init(void);


#endif /* APP_ATT_H_ */
