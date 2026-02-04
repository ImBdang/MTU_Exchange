/********************************************************************************************************
 * @file    app_att.c
 *
 * @brief   This is the source file for BLE SDK
 *
 * @author  BLE GROUP
 * @date    06,2022
 *
 * @par     Copyright (c) 2022, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
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
#include "tl_common.h"

#include "stack/ble/ble.h"
#include "app.h"
#include "app_att.h"

/**
 *  @brief  connect parameters structure for ATT
 */
typedef struct
{
  /** Minimum value for the connection event (interval. 0x0006 - 0x0C80 * 1.25 ms) */
  u16 intervalMin;
  /** Maximum value for the connection event (interval. 0x0006 - 0x0C80 * 1.25 ms) */
  u16 intervalMax;
  /** Number of LL latency connection events (0x0000 - 0x03e8) */
  u16 latency;
  /** Connection Timeout (0x000A - 0x0C80 * 10 ms) */
  u16 timeout;
} gap_periConnectParams_t;

static const u16 clientCharacterCfgUUID = GATT_UUID_CLIENT_CHAR_CFG;

static const u16 extReportRefUUID = GATT_UUID_EXT_REPORT_REF;

static const u16 reportRefUUID = GATT_UUID_REPORT_REF;

static const u16 characterPresentFormatUUID = GATT_UUID_CHAR_PRESENT_FORMAT;

static const u16 userdesc_UUID	= GATT_UUID_CHAR_USER_DESC;

static const u16 serviceChangeUUID = GATT_UUID_SERVICE_CHANGE;

static const u16 my_primaryServiceUUID = GATT_UUID_PRIMARY_SERVICE;

static const u16 my_characterUUID = GATT_UUID_CHARACTER;

static const u16 my_devServiceUUID = SERVICE_UUID_DEVICE_INFORMATION;

static const u16 my_PnPUUID = CHARACTERISTIC_UUID_PNP_ID;

static const u16 my_devNameUUID = GATT_UUID_DEVICE_NAME;

static const u16 my_gapServiceUUID = SERVICE_UUID_GENERIC_ACCESS;

static const u16 my_appearanceUUID = GATT_UUID_APPEARANCE;

static const u16 my_periConnParamUUID = GATT_UUID_PERI_CONN_PARAM;

static const u16 my_appearance = GAP_APPEARE_UNKNOWN;

static const u16 my_gattServiceUUID = SERVICE_UUID_GENERIC_ATTRIBUTE;

static const gap_periConnectParams_t my_periConnParameters = {20, 40, 0, 1000};

_attribute_data_retention_	static u16 serviceChangeVal[2] = {0};

_attribute_data_retention_	static u8 serviceChangeCCC[2] = {0,0};

static const u8 my_devName[] = {'B','d','a','n','g',' ', 'T', 'e', 'l', 'i', 'n', 'k'};

static const u8 my_PnPtrs [] = {0x02, 0x8a, 0x24, 0x66, 0x82, 0x01, 0x00};


#if (BLE_OTA_SERVER_ENABLE)
//////////////////////// OTA //////////////////////////////////
static const  u8 my_OtaServiceUUID[16]				= WRAPPING_BRACES(TELINK_OTA_UUID_SERVICE);
static const  u8 my_OtaUUID[16]						= WRAPPING_BRACES(TELINK_SPP_DATA_OTA);
_attribute_data_retention_ 		static 		u8 my_OtaData[20] = {0};
_attribute_data_retention_ 		  		  	u8 otaDataCCC[2] 						= {0,0};
static const  u8 my_OtaName[] 						= {'O', 'T', 'A'};
#endif

//// GAP attribute values
static const u8 my_devNameCharVal[5] = {
	CHAR_PROP_READ,
	U16_LO(GenericAccess_DeviceName_DP_H), U16_HI(GenericAccess_DeviceName_DP_H),
	U16_LO(GATT_UUID_DEVICE_NAME), U16_HI(GATT_UUID_DEVICE_NAME)
};
static const u8 my_appearanceCharVal[5] = {
	CHAR_PROP_READ,
	U16_LO(GenericAccess_Appearance_DP_H), U16_HI(GenericAccess_Appearance_DP_H),
	U16_LO(GATT_UUID_APPEARANCE), U16_HI(GATT_UUID_APPEARANCE)
};
static const u8 my_periConnParamCharVal[5] = {
	CHAR_PROP_READ,
	U16_LO(CONN_PARAM_DP_H), U16_HI(CONN_PARAM_DP_H),
	U16_LO(GATT_UUID_PERI_CONN_PARAM), U16_HI(GATT_UUID_PERI_CONN_PARAM)
};


#if (BLE_OTA_SERVER_ENABLE)
//// OTA attribute values
static const u8 my_OtaCharVal[19] = {
	CHAR_PROP_READ | CHAR_PROP_WRITE_WITHOUT_RSP | CHAR_PROP_NOTIFY | CHAR_PROP_WRITE,
	U16_LO(OTA_CMD_OUT_DP_H), U16_HI(OTA_CMD_OUT_DP_H),
	TELINK_SPP_DATA_OTA,
};
#endif


/*<! BDANG */
static const u8 nus_service_uuid[16] = { 0x9E,0xCA,0xDC,0x24,0x0E,0xE5,0xA9,0xE0,0x93,0xF3,0xA3,0xB5,0x01,0x00,0x40,0x6E };
static const u8 nus_rx_uuid[16]      = { 0x9E,0xCA,0xDC,0x24,0x0E,0xE5,0xA9,0xE0,0x93,0xF3,0xA3,0xB5,0x02,0x00,0x40,0x6E };
static const u8 nus_tx_uuid[16]      = { 0x9E,0xCA,0xDC,0x24,0x0E,0xE5,0xA9,0xE0,0x93,0xF3,0xA3,0xB5,0x03,0x00,0x40,0x6E };

_attribute_data_retention_ static u8 nus_tx_ccc[2] = {0,0};
_attribute_data_retention_ static u8 nus_tx_buf[20] = {0}; 
_attribute_data_retention_ static u8 nus_rx_buf[20] = {0}; 

static const u8 nus_tx_charDecl[19] = {
    CHAR_PROP_NOTIFY,                
    U16_LO(NUS_TX_DP_H), U16_HI(NUS_TX_DP_H),
    0x9E,0xCA,0xDC,0x24,0x0E,0xE5,0xA9,0xE0,0x93,0xF3,0xA3,0xB5,0x03,0x00,0x40,0x6E
};

static const u8 nus_rx_charDecl[19] = {
    CHAR_PROP_WRITE_WITHOUT_RSP | CHAR_PROP_WRITE,
   	U16_LO(NUS_RX_DP_H), U16_HI(NUS_RX_DP_H),
    0x9E,0xCA,0xDC,0x24,0x0E,0xE5,0xA9,0xE0,0x93,0xF3,0xA3,0xB5,0x02,0x00,0x40,0x6E
};

static const u8 nus_name[] = {'N','U','S'};
static void dump_hex(const u8 *p, u16 len)
{
    for (u16 i = 0; i < len; i++) tlkapi_printf(UART_PRINT_DEBUG_ENABLE, "%02X ", p[i]);
    tlkapi_printf(UART_PRINT_DEBUG_ENABLE, "\r\n");
}

int nus_rx_write(void *p)
{
    rf_packet_att_write_t *pw = (rf_packet_att_write_t *)p;
    if (pw->l2capLen < 3) return 0;

    u16 len = pw->l2capLen - 3;
    u8 *dat = ((u8 *)&pw->handle) + 2;

    dump_hex(dat, len);

    if (len == 6 && dat[0]=='1' && dat[2]=='2' && dat[4]=='3') {
        u8 s1 = (dat[1] == '1');
        u8 s2 = (dat[3] == '1');
        u8 s3 = (dat[5] == '1');
        touchpad_led_set_by_id(1, s1);
        touchpad_led_set_by_id(2, s2);
        touchpad_led_set_by_id(3, s3);
        tlkapi_printf(UART_PRINT_DEBUG_ENABLE, "PARSED: S1=%d S2=%d S3=%d\r\n", s1, s2, s3);
    }

    return 0;
}

static void nus_tx_notify(u8 *data, u16 len)
{
    if (blc_ll_getCurrentState() != BLS_LINK_STATE_CONN) return;
    if (!(nus_tx_ccc[0] & 0x01)) return;
    bls_att_pushNotifyData(NUS_TX_DP_H, data, len);
}

void nus_notify_3switch_state(u8 s1, u8 s2, u8 s3)
{
    static u8 msg[6];
    msg[0] = '1'; msg[1] = s1 ? '1' : '0';
    msg[2] = '2'; msg[3] = s2 ? '1' : '0';
    msg[4] = '3'; msg[5] = s3 ? '1' : '0';
    nus_tx_notify(msg, 6);
}





// TM : to modify
static const attribute_t my_Attributes[] = {

	{ATT_END_H - 1, 0,0,0,0,0,0,0},	// total num of attribute


	//GAP
	{7,ATT_PERMISSIONS_READ,2,2,(u8*)(&my_primaryServiceUUID), 	(u8*)(&my_gapServiceUUID), 0, 0},

	{0,ATT_PERMISSIONS_READ,2,sizeof(my_devNameCharVal),(u8*)(&my_characterUUID), (u8*)(my_devNameCharVal), 0, 0},
	{0,ATT_PERMISSIONS_READ,2,sizeof(my_devName), (u8*)(&my_devNameUUID), (u8*)(my_devName), 0, 0},

	{0,ATT_PERMISSIONS_READ,2,sizeof(my_appearanceCharVal),(u8*)(&my_characterUUID), (u8*)(my_appearanceCharVal), 0, 0},
	{0,ATT_PERMISSIONS_READ,2,sizeof (my_appearance), (u8*)(&my_appearanceUUID), 	(u8*)(&my_appearance), 0, 0},

	{0,ATT_PERMISSIONS_READ,2,sizeof(my_periConnParamCharVal),(u8*)(&my_characterUUID), (u8*)(my_periConnParamCharVal), 0, 0},
	{0,ATT_PERMISSIONS_READ,2,sizeof (my_periConnParameters),(u8*)(&my_periConnParamUUID), 	(u8*)(&my_periConnParameters), 0, 0},


	// ================= NUS service =================
	{6, ATT_PERMISSIONS_READ, 2, 16, (u8*)(&my_primaryServiceUUID), (u8*)(nus_service_uuid), 0, 0},

	// TX Characteristic Declaration 
	{0, ATT_PERMISSIONS_READ, 2, sizeof(nus_tx_charDecl), (u8*)(&my_characterUUID), (u8*)(nus_tx_charDecl), 0, 0},

	// TX Value (uuid = nus_tx_uuid)  --- NOTIFY
	{0, ATT_PERMISSIONS_READ, 16, sizeof(nus_tx_buf), (u8*)(nus_tx_uuid), (u8*)(nus_tx_buf), 0, 0},

	// TX CCCD 
	{0, ATT_PERMISSIONS_RDWR, 2, sizeof(nus_tx_ccc), (u8*)(&clientCharacterCfgUUID), 	(u8*)(nus_tx_ccc), 0, 0},

	
	// RX Characteristic Declaration
	{0, ATT_PERMISSIONS_READ, 2, 	sizeof(nus_rx_charDecl),(u8*)(&my_characterUUID), 	(u8*)(nus_rx_charDecl), 0, 				0},

	// RX Value (uuid = nus_rx_uuid)  --- WRITE / WRITE_NO_RSP
	{0, ATT_PERMISSIONS_RDWR, 16, 	sizeof(nus_rx_buf), 	(u8*)(nus_rx_uuid), 		(u8*)(nus_rx_buf), 		&nus_rx_write, 	0},


#if (BLE_OTA_SERVER_ENABLE)
	////////////////////////////////////// OTA /////////////////////////////////////////////////////
	{5,ATT_PERMISSIONS_READ, 2, 16,						(u8*)(&my_primaryServiceUUID), 	(u8*)(&my_OtaServiceUUID), 	0, 0},
	{0,ATT_PERMISSIONS_READ, 2, sizeof(my_OtaCharVal),	(u8*)(&my_characterUUID), 		(u8*)(my_OtaCharVal), 		0, 0},				//prop
	{0,ATT_PERMISSIONS_RDWR, 16,sizeof(my_OtaData),		(u8*)(&my_OtaUUID),				(u8*)my_OtaData, 			&otaWrite, NULL},	//value
	{0,ATT_PERMISSIONS_RDWR, 2, sizeof(otaDataCCC),		(u8*)(&clientCharacterCfgUUID), (u8*)(otaDataCCC), 			0, 0},				//value
	{0,ATT_PERMISSIONS_READ, 2, sizeof(my_OtaName),		(u8*)(&userdesc_UUID), 			(u8*)(my_OtaName), 			0, 0},
#endif
};


/**
 * @brief      Initialize the attribute table
 * @param[in]  none
 * @return     none
 */
void	my_att_init(void)
{
	bls_att_setAttributeTable((u8 *)my_Attributes);
}


