#ifndef CLOUD_PLC_H
#define CLOUD_PLC_H
#include <Arduino.h>
#include <Wire.h>
#include <Nanoshield_ADC.h>
#include "ADS1X15.h"
#include "FS.h"
#include "SD.h"
#include "SPI.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <PubSubClient.h>
#include "Adafruit_MCP4728.h"



#define FTPWRITE



const int DO1=25,DO2=26,DO3=27,DO4=14;
const int NETWORK_LED=12;
const int Relay[]={13,15};
const int DI1=33,DI2=32,DI3=35,DI4=34;

/* ################### Function Declaration ##################### */
//1
void Cloud_PLC_initialisation(void);
 /* @Brief  : Configures digital pins O1,O2,O3 and O4 as OUTPUT
  *         and digital pins IN1,IN2,IN3 and IN4 as INPUT
  *         and the Network led as output
  *         and Configures Relay 1 and Relay 2 as output
 * @Params : None
 * @return : None 
 */
 //Function call Example:- Cloud_PLC_initialisation();


//2
void Cloud_PLC_Digital_Write(uint8_t pin, uint8_t value);
 /* @Brief  : Writes the Digital pin
 * @Params : pin[IN] - pin number to be configured.
 *           value[IN] - high/low
 * @return : None 
 */
//Function call Example:- Cloud_PLC_Digital_Write(O1,HIGH);



//3 
void Cloud_PLC_Digital_Write_HIGH(uint8_t pin);
/* @Brief  : Writes the Digital pin as HIGH
 * @Params : pin[IN] - pin number to be configured.
 *           value[IN] - low
 * @return : None 
 */
//Function call Example:- Cloud_PLC_Digital_Write_HIGH(O1);

//4
void Cloud_PLC_Digital_Write_LOW(uint8_t pin);
/* @Brief  : Writes the Digital pin as LOW
 * @Params : pin[IN] - pin number to be configured.
 *           value[IN] - high/low
 * @return : None 
 */
//Function call Example:- Cloud_PLC_Digital_Write_LOW(O1);

//5
void Cloud_PLC_Digital_Toggle(uint8_t pin,uint8_t value);
/* @Brief  : Toggles the given pin
 * @Params : pin[IN] - pin number to be configured.
 *          value - Duration
 * @return : 
 */
//Function call Example:- Cloud_PLC_Digital_Toggle(O2,500);

//6
uint8_t Cloud_PLC_Digital_Read(uint8_t pin);
/* @Brief  : Reads the Digital pin
 * @Params : pin[IN] - pin number to be configured.
 * @return : value - high/low
 */
//Function call Example:- Cloud_PLC_Digital_Read(IN3);


//7
void Cloud_PLC_NETWORK_LED_Write(uint8_t value);
/* @Brief  : controls the network led pin state
 * @Params :value[IN] - high/low
 * @return : None 
 */
//Function call Example:- Cloud_PLC_NETWORK_LED_Write(HIGH);

//8
void Cloud_PLC_Relay_state(uint8_t relay ,uint8_t value);
/* @Brief  : controls the Relay and respective pin state
 * @Params :relay - relay-1 or relay-2(0 or 1)
 *          value[IN] - high/low
 * @return : None 
 */
//Function call Example:- Cloud_PLC_Relay_state(0,HIGH);

//9
void Cloud_PLC_config_read4_20mA(void);
/* @Brief  : config 4_20ma value
 * @Params :None
 * @return : None 
 */
//Function call Example:- Cloud_PLC_config_read4_20mA();

//10
float Cloud_PLC_read4_20mA(uint8_t value);
/* @Brief  : read 4_20ma value on specified channel
 * @Params :value[channel]-0 to 3
 * @return : Value of the specified channel 
 */
//Function call Example:- Cloud_PLC_read4_20mA(0);

//11
void Cloud_PLC_config_readADC(void);
/* @Brief  : config adc value
 * @Params :None
 * @return : None 
 */
//Function call Example:- Cloud_PLC_config_readADC();

//12
uint16_t Cloud_PLC_readADC(uint8_t channel);
/* @Brief  : read adc value on specified channel
 * @Params :value [channel]-0 to 3
 * @return : Value of the specified channel 
 */
 // This will give raw adc value
 // This has to be multiplied with max voltage
 //library file :-  https://www.arduinolibraries.info/libraries/ads1-x15
 //Function call Example:- Cloud_PLC_readADC(0);
 //12.5
float Cloud_PLC_getVoltage(uint8_t channel, float v_ref = 6.144, float scale_factor = 6.0);

//11.5  DAC_OUT

void Cloud_PLC_initDAC(void);
/* @Brief  : Configures DAC output
 * @Params : None
 * @return : None 
 */
// Function call Example:- Cloud_PLC_config_writeDAC();

void setDACValue(MCP4728_channel_t channel, uint16_t value);
/* @Brief  : Writes value to the specified DAC channel and value
 * @Params : channel - Channel number (0 to 10)
 *           value - 12-bit value to write (0 to 4095)
 * @return : None 
 */
// Function call Example:- Cloud_PLC_SetChannelDAC;


//12.5

void Cloud_PLC_4_20output(void);
/* @Brief  : Configures DAC output
 * @Params : None
 * @return : None 
 */
// Function call Example:- Cloud_PLC_config_writeDAC();

void Cloud_PLC_set4_20output(MCP4728_channel_t channel, uint16_t value);
/* @Brief  : Writes value to the specified DAC channel and value
 * @Params : channel - Channel number (0 to 10)
 *           value - 12-bit value to write (0 to 4095)
 * @return : None 
 */
// Function call Example:- Cloud_PLC_SetChannelDAC;





//13
bool Cloud_PLC_Arithmetic_Compare_LessThan(uint32_t num1, uint32_t num2);
/**
  * @brief  This function compares if num1 is less than num2.
  * @param  num1 - number1.
  *         num2 - number2.
  * @retval true if num1 < num2.
  */
  //Function call Example:- Cloud_PLC_Arithmetic_Compare_LessThan(4,7);
  
//14
bool Cloud_PLC_Arithmetic_Compare_LessThanOrEqualTo(uint32_t num1, uint32_t num2);
/**
  * @brief  This function compares if num1 is less than or equal to num2.
  * @param  num1 - number1.
  *         num2 - number2.
  * @retval true if num1 <= num2.
  */
  //Function call Example:- Cloud_PLC_Arithmetic_Compare_LessThanOrEqualTo(7,7);
  
//15
bool Cloud_PLC_Arithmetic_Compare_GreaterThan(uint32_t num1, uint32_t num2);
/**
  * @brief  This function compares if num1 is Greater than num2.
  * @param  num1 - number1.
  *         num2 - number2.
  * @retval true if num1 > num2.
  */
  //Function call Example:- Cloud_PLC_Arithmetic_Compare_GreaterThan(8,9);

  
//16
bool Cloud_PLC_Arithmetic_Compare_GreaterThanOrEqualTo(uint32_t num1, uint32_t num2);
/**
  * @brief  This function compares if num1 is Greater than or equal to num2.
  * @param  num1 - number1.
  *         num2 - number2.
  * @retval true if num1 >= num2.
  */
  //Function call Example:- Cloud_PLC_Arithmetic_Compare_GreaterThanOrEqualTo(6,6);

  
//17
bool Cloud_PLC_Arithmetic_Compare_EqualsTo(uint32_t num1, uint32_t num2);
/**
  * @brief  This function compares if num1 is equal to num2.
  * @param  num1 - number1.
  *         num2 - number2.
  * @retval true if num1 == num2.
  */
  //Function call Example:- Cloud_PLC_Arithmetic_Compare_EqualsTo(3,3);
  

//18
uint8_t Cloud_PLC_Logical_ShiftLeft(uint32_t Data, uint32_t shift);
/**
  * @brief  This function shifts the data to the left.
  * @param  data - data to be shifted.
  *         shift - number to be shifted left.
  * @retval None
  */
  //Function call Example:- Cloud_PLC_Logical_ShiftLeft(40,1);

//19
uint8_t Cloud_PLC_Logical_ShiftRight(uint32_t Data, uint32_t shift);
/**
  * @brief  This function shifts the data to the right.
  * @param  data - data to be shifted.
  *         shift - number to be shifted right.
  * @retval None
  */
  //Function call Example:- Cloud_PLC_Logical_ShiftRight(16,4);
  

//20
void Cloud_PLC_Delay(uint8_t value);
  /* @Brief  : This function causes the program to halt for a specified time
 * @Params :value - the required time for program to halt in milisecond
 * @return : None 
 */
 //Function call Example:- Cloud_PLC_Delay(3000);

//21
uint16_t Cloud_PLC_Arithmetic_Add(uint32_t num1, uint32_t num2);
/* @Brief  : This function adds num1 with num2
 * @Params :num1-first number
 *          num2-second number
 * @return : sum(add of num1 and num2) 
 */
 //Function call Example:- Cloud_PLC_Arithmetic_Add(3,8);
 

//22 
uint16_t Cloud_PLC_Arithmetic_Subtract(uint32_t num1, uint32_t num2);
/* @Brief  : This function Subtract num1 with num2
 * @Params :num1-first number
 *          num2-second number
 * @return : difference(difference of num1 and num2) 
 */
 //Function call Example:- Cloud_PLC_Arithmetic_Subtract(6,2);
 

//23
uint16_t Cloud_PLC_Arithmetic_Multiply(uint8_t num1, uint8_t num2);
/* @Brief  : This function Multiplies num1 with num2
 * @Params :num1-first number
 *          num2-second number
 * @return : multiply(multiple of num1 and num2) 
 */
 //Function call Example:- Cloud_PLC_Arithmetic_Multiply(5,5);

//24
float Cloud_PLC_Arithmetic_Divide(uint32_t num1, uint32_t num2);
 /* @Brief  : This function Divides num1 with num2
 * @Params :num1-first number
 *          num2-second number
 * @return : Divide(Divide num1 with num2) 
 */
 //Function call Example:- Cloud_PLC_Arithmetic_Divide(42,7);


//25
void Cloud_PLC_Config_WIFI(const char* ssid,const char* password); 
 /* @Brief  : This function will config WIFI
 * @Params :ssid- WIFI_name
 *          password-Password
 * @return : None
 */
//Function call Example:- Cloud_PLC_Config_WIFI("Wifi","password");

//26
void Cloud_PLC_JSON(const char* serverurl, const char* Sensor, const char* Value);
 /* @Brief  : JSON funtion
 * @Params :serverurl- Server_URL
 *          Sensor- channel name
 *          value - value from the channels
 * @return : None
 */
//Function call Example:- For 1 value:- Cloud_PLC_JSON("http://iotpi.in/dataloggertesting/dataloggerinsert.php/", "temperature", "26.4");
                        //  For Multiple value:- Cloud_PLC_JSON("http://iotpi.in/dataloggertesting/dataloggerinsert.php/", "temperature", "26.4,24.5,27.8,25.8");

//27
void Cloud_PLC_Config_MQTT(const char* mqttServer, uint16_t mqttPort, const char* mqttUser, const char* mqttPassword);
 /* @Brief  : MQTT funtion configuration
 * @Params :mqttServer- Server_URL
 *          mqttPort -port number 
 *          mqttUser - User_name
 *          mqttPassword - Password
 * @return : None
 */
 //Function call Example:-  Cloud_PLC_Config_MQTT("hairdresser.cloudmqtt.com", 15520, "qckwnpwm", "n4KBne_O5Mr9");

//28
void Cloud_PLC_MQTT_Publish(const char* Data, const char* Message);
 /* @Brief  : Publish funtion for sending message from hardware to server
 * @Params :Data - Topic
 *          Message - Message
 * @return : None
 */
//Function call Example:- Cloud_PLC_MQTT_Publish("ASD","hii asd");

//29
void Cloud_PLC_MQTT_Subscribe(const char* Data);
 /* @Brief  : Subscribe funtion for sending message from server to Hardware
 * @Params :Data - Topic
 * @return : None
 */
//Function call Example:- Cloud_PLC_MQTT_Subscribe("Topic_name");

//30
void callback(char* topic, byte* payload, unsigned int length);
 /* @Brief  : callback funtion for printing message
 * @Params :topic - topic
 *          payload - message content
 *          length - length of the message
 * @return : None
 */

//31
void Cloud_PLC_MQTT_Repeat(void);
 /* @Brief  : Repeat funtion repeativly sending message from server to hardware
 * @Params :None
 * @return : None
 */
//Function call Example:- Cloud_PLC_MQTT_Repeat();

//32
void Cloud_PLC_File_Init(void);
 /* @Brief  : File_Init funtion for initialize SD_card/File
 * @Params :None
 * @return : None
 */
//Function call Example:- Cloud_PLC_File_Init();

//33
void Cloud_PLC_File_Write(fs::FS &fs, const char * path, const char * message);
 /* @Brief  : File_Write funtion for writting file
 * @Params :&fs - priints the type of file 
 *          path - Name of File
 *          message - Message
 * @return : None
 */
//Function call Example:- Cloud_PLC_File_Write(SD, "/ajith.txt", "Hello \n");

//34
void Cloud_PLC_File_Append(fs::FS &fs, const char * path, const char * message);
 /* @Brief  : File_Append funtion for appending message to exsisting file
 * @Params :&fs - priints the type of file 
 *          path - Name of File
 *          message - Message
 * @return : None
 */
//Function call Example:- Cloud_PLC_File_Append(SD, "/ajith.txt", "How are you?\n");

//35
void Cloud_PLC_File_Read(fs::FS &fs, const char * path);
 /* @Brief  : File_Read funtion for reading message from exsisting file
 * @Params :&fs - priints the type of file 
 *          path - Name of File
 * @return : None
 */
//Function call Example:-  Cloud_PLC_File_Read(SD, "/ajith.txt");

//36
byte Cloud_PLC_FTP_Setup(char* Serverurl,int Port,char* Username, char* Password,  char* Filename, char* Message);
  /* @Brief  : Function for FTP Setup
 * @Params :Serverurl - Server URL
 *          Port - port
 *          Username - Username for login
 *          Password - password
 *          Filename - file name to be created
 *          Message - message 
 * @return : byte - 0/1 ( Respective to the function it will send the value)
 */
  //Function call Example:- Cloud_PLC_FTP_Setup("server_url",port_no,"User_name", "Password",  "File_name.type", "Message");

//37
byte eRcv();
 /* @Brief  : Function for receiving Message
 * @Params :None
 * @return :None
 */ 
 
//38
void efail();
  /* @Brief  : Function disconnecting and stoping
 * @Params :None
 * @return :None
 */ 
 #endif 
