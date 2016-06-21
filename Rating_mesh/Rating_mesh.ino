/*Author: Shirish Jadav
 * Date: 6/21/2016
 * Project: Bytelens Rating Devices
 * Discription: Implementing Advertiser based Meshing protocol
 *              purpose is to keep it simple and able to send 
 *              data over nodes to a gateway.
 * Your are allowed to copy the code and use it in any project 
 * Related to Bytelens Any outside use is not allowed.
 */
#include <BLE_API.h>
#include "Packet.h"
#include "Hardware.h"

#define DEVICE_NAME "BYTELENS"
BLE ble;

Ticker switcher;
Ticker butup;

bool advertising=false;
void updateAdv()
{
    ble.clearAdvertisingPayload();
    ble.accumulateAdvertisingPayload(GapAdvertisingData::BREDR_NOT_SUPPORTED | GapAdvertisingData::LE_GENERAL_DISCOVERABLE);
    ble.accumulateAdvertisingPayload(GapAdvertisingData::MANUFACTURER_SPECIFIC_DATA,(const uint8_t*)&p,sizeof(p));
    ble.accumulateAdvertisingPayload(GapAdvertisingData::SHORTENED_LOCAL_NAME,(const uint8_t *)"BLM", sizeof("BLM") - 1);

    ble.setAdvertisingType(GapAdvertisingParams::ADV_CONNECTABLE_UNDIRECTED);
    ble.setDeviceName((const uint8_t* )DEVICE_NAME);
    // set tx power,valid values are -40, -20, -16, -12, -8, -4, 0, 4
    ble.setAdvertisingInterval(160);
    ble.setAdvertisingTimeout(0);
}
void initBLE()
{
    ble.init();
    //ble.onDisconnection(disconnectionCallBack);
    //ble.onDataWritten(writtenHandle);
//    AddressType_t tp;
//    ble.getAddress(&tp,myAddr);
//    Serial.println("MAC ADDRESS of this Device:");
//    for(int i=0;i<6;i++)  
//    {      Serial.print(myAddr[6]);Serial.print(" ");   }
    updateAdv();
    ble.setTxPower(0);
}

uint32_t ble_advdata_parser(uint8_t type, uint8_t advdata_len, uint8_t *p_advdata, uint8_t *len, uint8_t *p_field_data)
{
    uint8_t index=0;
    uint8_t field_length, field_type;

    while(index<advdata_len)
    {
        field_length = p_advdata[index];
        field_type   = p_advdata[index+1];
        if(field_type == type)
        {
            memcpy(p_field_data, &p_advdata[index+2], (field_length-1));
            *len = field_length - 1;
            return NRF_SUCCESS;
        }
        index += field_length + 1;
    }
    return NRF_ERROR_NOT_FOUND;
}
void scanCallBack(const Gap::AdvertisementCallbackParams_t *params)
{
    Serial.print(",.");
//    Serial.print("PerrAddress: ");
//    for(uint8_t index=0; index<6; index++)
//    {
//        Serial.print(params->peerAddr[index], HEX);
//        Serial.print(" ");
//    }
//    Serial.println(" ");

//    Serial.print("The Rssi : ");
//    Serial.println(params->rssi, DEC);
//
//    Serial.print("The adv_data : ");
//    Serial.println((const char*)params->advertisingData);

    uint8_t len;
    uint8_t adv_name[31];
    if( NRF_SUCCESS == ble_advdata_parser(BLE_GAP_AD_TYPE_SHORT_LOCAL_NAME, params->advertisingDataLen, (uint8_t *)params->advertisingData, &len, adv_name) )
    {
      Serial.println("");
//        Serial.print("Short name len : ");
//        Serial.println(len, DEC);
        Serial.print("Short name is : ");
        Serial.println((const char*)adv_name);

        if( (len == 3) && (memcmp("BLM", adv_name, len) == 0x00) )
        {
            Serial.println("Got device, stop scan ");
            ble.stopScan();
            Packet q;
            if( NRF_SUCCESS == ble_advdata_parser(BLE_GAP_AD_TYPE_MANUFACTURER_SPECIFIC_DATA, params->advertisingDataLen, (uint8_t *)params->advertisingData, &len, (uint8_t *)&q) )
              {
                
                Serial.println("found packet");
                Serial.print("Packet Size: ");Serial.println(len);
                Serial.print("Token: ");Serial.print(q.token[0]);Serial.print(":");Serial.println(q.token[1]);
                Serial.print("Mac Addr: ");
                for(int i=0;i<6;i++)
                {
                  Serial.print(q.mac[i]);
                  if(i<5)
                  Serial.print(" : ");
                  else
                  Serial.println("");
                }
                Serial.print("Data: ");
                for(int i=0;i<5;i++)
                {
                  Serial.print(q.data[i]);
                  if(i<4)
                  Serial.print(" : ");
                  else
                  Serial.println("");
                }
              }
//            ble.connect(params->peerAddr, Gap::ADDR_TYPE_RANDOM_STATIC, NULL, NULL);
        }
    }
    Serial.println(" ");
}
void adv()
{
 if(dRole==NODE)
 {
  if(isData)
  {
    setPack(bButtons,5,DATA);
    updateAdv();
    isData=false;
  }
  Serial.print("advertising");
  ble.stopScan();
  ble.startAdvertising();
 }
}

void scan()
{
    Serial.println("scan started");
    ble.stopAdvertising();
    ble.startScan(scanCallBack); 
}

void sw()
{

 if(dRole==NODE)
 {
  if(advertising)
    {
      advertising=false;
      adv();
    }else
    {
      advertising=true;
      scan();
    }
 }else
    scan();
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(8000);
  initHardware(false);
  RoleSelector();
  initHardware(true);
  switcher.attach(sw,5);

  initBLE();
//  dRole=NODE;
//  adv();
}

void loop() {
  // put your main code here, to run repeatedly:
ble.waitForEvent();
}

/*Author: Shirish Jadav
 * Date: 6/21/2016
 * Project: Bytelens Rating Devices
 * Discription: Implementing Advertiser based Meshing protocol
 *              purpose is to keep it simple and able to send 
 *              data over nodes to a gateway.
 * Your are allowed to copy the code and use it in any project 
 * Related to Bytelens Any outside use is not allowed.
 */
