/*
MANUFACTURER_SPECIFIC_DATA         = 0xFF  /**< Manufacturer Specific Data
BLE_GAP_AD_TYPE_MANUFACTURER_SPECIFIC_DATA

uint8_t nrfRandom()
{
     NRF_RNG->TASKS_START = 1; 
     NRF_RNG->EVENTS_VALRDY = 0;
     while ( NRF_RNG->EVENTS_VALRDY == 0){}
     return (uint8_t)NRF_RNG->VALUE;
}

*/
