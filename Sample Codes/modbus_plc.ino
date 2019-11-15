#include <CPLC.h> 
/* Reading the device MFR 2810 */
uint8_t funCode = 0x04; //read holding register
uint8_t slave_id = 1;
uint16_t start_addr = 3850; //address to read Line to Neutral Voltage for device MFR 2810
uint16_t len = 1; //datatype is 32-bit Float for MFR 2810
uint32_t data[110] = {0};
uint8_t result = 0;

void setup()
{
  CPLC_Modbus_Master_Init();
}

void loop()
{
  Serial.print("Line to Neutral Voltage(raw value) = ");
  CPLC_Modbus_Master_Read_Raw(funCode, slave_id, start_addr, len, data);
  delay(2000);
}

