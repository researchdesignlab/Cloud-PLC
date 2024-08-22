#include "Cloud_PLC.h"

  WiFiClient espClient;
  PubSubClient client(espClient);
  WiFiClient Client;
  WiFiClient dclient;
  char outBuf[128];
  char outCount;
  
  ADS1115 ADS(0x49);
  Adafruit_MCP4728 mcp;
String receivedMessage;

  
  
//1
void Cloud_PLC_initialisation(void)
{
  pinMode(DO1, OUTPUT);   
  pinMode(DO2, OUTPUT);   
  pinMode(DO3, OUTPUT);   
  pinMode(DO4, OUTPUT);
  pinMode(DI1, INPUT);   
  pinMode(DI2, INPUT);   
  pinMode(DI3, INPUT);   
  pinMode(DI4, INPUT);
  pinMode(NETWORK_LED, OUTPUT);
  pinMode(Relay[0],OUTPUT);
  pinMode(Relay[1],OUTPUT);
 /* @Brief  : Configures digital pins O1,O2,O3 and O4 as OUTPUT
  *         and digital pins IN1,IN2,IN3 and IN4 as INPUT
  *         and the Network led as output
  *         and Configures Relay 1 and Relay 2 as output
 * @Params : None
 * @return : None 
 */
  //Function call Example:- Cloud_PLC_initialisation();
  }


//2
void Cloud_PLC_Digital_Write(uint8_t pin, uint8_t value)
{
  digitalWrite(pin, value);
 /* @Brief  : Writes the Digital pin
 * @Params : pin[IN] - pin number to be configured.
 *           value[IN] - high/low
 * @return : None 
 */
//Function call Example:- Cloud_PLC_Digital_Write(O1,HIGH);
}

//3
void Cloud_PLC_Digital_Write_HIGH(uint8_t pin)
{
  digitalWrite(pin, HIGH);
 /* @Brief  : Writes the Digital pin as HIGH
 * @Params : pin[IN] - pin number to be configured
 * @return : None 
 */
 //Function call Example:- Cloud_PLC_Digital_Write_HIGH(O1);
}

//4
void Cloud_PLC_Digital_Write_LOW(uint8_t pin)
{
  digitalWrite(pin, LOW);
 /* @Brief  : Writes the Digital pin as LOW
 * @Params : pin[IN] - pin number to be configured.
 * @return : None 
 */
 //Function call Example:- Cloud_PLC_Digital_Write_LOW(O1);
}

//5
void Cloud_PLC_Digital_Toggle(uint8_t pin,uint8_t value)
{
  digitalWrite(pin,HIGH);
  delay(value);
  digitalWrite(pin,LOW);
  delay(value);
 /* @Brief  : Toggles the given pin
 * @Params : pin[IN] - pin number to be configured.
 *           value[IN] - Duration
 * @return : None 
 */
 //Function call Example:- Cloud_PLC_Digital_Toggle(O2,500);
}

//6
uint8_t Cloud_PLC_Digital_Read(uint8_t pin)
{
  return digitalRead(pin);
 /* @Brief  : Reads the Digital pin
 * @Params : pin[IN] - pin number to be configured.
 * @return : value - high/low
 */
 //Function call Example:- Cloud_PLC_Digital_Read(IN3);
}


//7
void Cloud_PLC_NETWORK_LED_Write(uint8_t value)
{
  digitalWrite(NETWORK_LED, value);
 /* @Brief  :  to control the Network pin state
 * @Params :value[IN] - high/low
 * @return : None
 */
 //Function call Example:- Cloud_PLC_NETWORK_LED_Write(HIGH);
}


//8
void Cloud_PLC_Relay_state(uint8_t relay ,uint8_t value)
{
  digitalWrite(Relay[relay], value);
 /* @Brief  : controls the Relay and respective pin state
 * @Params :relay - relay-1 or relay-2(0 or 1)
 *          value[IN] - high/low
 * @return : None 
 */
 //Function call Example:- Cloud_PLC_Relay_state(0 , HIGH);
}

//9
void Cloud_PLC_config_read4_20mA(void){
  Nanoshield_ADC adc;
  adc.begin();
  adc.setGain(GAIN_TWO);
/* @Brief  : config 4_20ma pin
 * @Params :None
 * @return : None 
 */
 //Function call Example:- Cloud_PLC_config_read4_20mA();
}



//10
float Cloud_PLC_read4_20mA(uint8_t value){
    Nanoshield_ADC adc;
    return adc.read4to20mA(value);
 /* @Brief  : read 4_20ma value
 * @Params :value[channel]-0 to 3
 * @return : Value of the specified channel 
 */
 //Function call Example:- Cloud_PLC_read4_20mA(0);
  }
                                                                    //4-20mA output
//11
void Cloud_PLC_config_readADC(void){
  Wire.begin();
  ADS.begin();
  ADS.setGain(0);  // Gain = 2/3, full-scale range = ±6.144V
 /* @Brief  : config adc value on specified channel
 * @Params :None
 * @return : None 
 */
 //Function call Example:- Cloud_PLC_config_readADC();
  }


//12
uint16_t Cloud_PLC_readADC(uint8_t channel) {
    if (channel > 3) return 0;  // Ensure the channel is within 0-3

    // Averaging multiple readings
    const int num_samples = 10;
    int32_t sum = 0;
    for (int i = 0; i < num_samples; i++) {
        sum += ADS.readADC(channel);
        delay(10);  // Short delay between samples
    }
    return sum / num_samples;



 /* @Brief  : read adc value on specified channel
 * @Params :value [channel]-0 to 3
 * @return : Value of the specified channel 
 */
 // This will give raw adc value
 // This has to be multiplied with max voltage
 //library file :-  https://www.arduinolibraries.info/libraries/ads1-x15
 //Function call Example:- Cloud_PLC_readadc(0);
}

float Cloud_PLC_getVoltage(uint8_t channel, float v_ref, float scale_factor) {
    uint16_t raw_adc_value = Cloud_PLC_readADC(channel);
    float voltage = (raw_adc_value * (v_ref / 32768.0)) * scale_factor;
	if(voltage >= 20.0) {
		voltage=0;
	}
    return voltage;
}



//13 DAC Output
void Cloud_PLC_initDAC(void) {
  // Try to initialize!
  if (!mcp.begin()) {
    Serial.println("Failed to find MCP4728 chip");
    while (1) {
      delay(10);
    }
  } else {
    Serial.println("Found MCP4728 chip");
  }
}
  
  // Initialize the DAC with its I2C address (0x60)
  // You can adjust the address as per your setup if needed
  // Additional configuration settings can be done here


/* @Brief  : Write a value to the DAC channel
 * @Params : channel - DAC channel number (0 to 3)
 *           value   - Value to write to the DAC (12-bit, 0 to 4095)
 * @return : None 
 */

//14
void setDACValue(MCP4728_channel_t channel, uint16_t value) {
  mcp.setChannelValue(channel, value);
}



//12.5

void Cloud_PLC_4_20output(void) {
  // Try to initialize!
  if (!mcp.begin()) {
    Serial.println("Failed to find MCP4728 chip");
    while (1) {
      delay(10);
    }
  } else {
    Serial.println("Found MCP4728 chip");
  }
}
  
  // Initialize the DAC with its I2C address (0x60)
  // You can adjust the address as per your setup if needed
  // Additional configuration settings can be done here


/* @Brief  : Write a value to the DAC channel
 * @Params : channel - DAC channel number (0 to 3)
 *           value   - Value to write to the DAC (12-bit, 0 to 4095)
 * @return : None 
 */

//14
void Cloud_PLC_set4_20output(MCP4728_channel_t channel, uint16_t value) {
	 value = map(value, 0,4095, 650, 3250);
  mcp.setChannelValue(channel, value);
}


//13
bool Cloud_PLC_Arithmetic_Compare_LessThan(uint32_t num1, uint32_t num2)
{
  if(num1 < num2)
    return true;
  else
    return false;
/**
  * @brief  This function compares if num1 is less than num2.
  * @param  num1 - number1.
  *         num2 - number2.
  * @retval true if num1 < num2.
  */
  //Function call Example:- Cloud_PLC_Arithmetic_Compare_LessThan(4,7);
  }

//14
bool Cloud_PLC_Arithmetic_Compare_LessThanOrEqualTo(uint32_t num1, uint32_t num2)
{
  if(num1 <= num2)
    return true;
  else
    return false;
/**
  * @brief  This function compares if num1 is less than or equal to num2.
  * @param  num1 - number1.
  *         num2 - number2.
  * @retval true if num1 <= num2.
  */
  //Function call Example:- Cloud_PLC_Arithmetic_Compare_LessThanOrEqualTo(7,7);
  }

//15
bool Cloud_PLC_Arithmetic_Compare_GreaterThan(uint32_t num1, uint32_t num2)
{
  if(num1 > num2)
    return true;
  else
    return false;
/**
  * @brief  This function compares if num1 is Greater than num2.
  * @param  num1 - number1.
  *         num2 - number2.
  * @retval true if num1 > num2.
  */
  //Function call Example:- Cloud_PLC_Arithmetic_Compare_GreaterThan(8,9);
  }

//16
bool Cloud_PLC_Arithmetic_Compare_GreaterThanOrEqualTo(uint32_t num1, uint32_t num2)
{
  if(num1 >= num2)
    return true;
  else
    return false;
/**
  * @brief  This function compares if num1 is Greater than or equal to num2.
  * @param  num1 - number1.
  *         num2 - number2.
  * @retval true if num1 >= num2.
  */
  //Function call Example:- Cloud_PLC_Arithmetic_Compare_GreaterThanOrEqualTo(6,6);
  }

//17
bool Cloud_PLC_Arithmetic_Compare_EqualsTo(uint32_t num1, uint32_t num2)
{
  if(num1 == num2)
    return true;
  else
    return false;
/**
  * @brief  This function compares if num1 is equal to num2.
  * @param  num1 - number1.
  *         num2 - number2.
  * @retval true if num1 == num2.
  */
  //Function call Example:- Cloud_PLC_Arithmetic_Compare_EqualsTo(3,3);
  }


//18
uint8_t Cloud_PLC_Logical_ShiftLeft(uint32_t Data, uint32_t shift)
{
  return (Data << shift); 
/**
  * @brief  This function shifts the data to the left.
  * @param  data - data to be shifted.
  *         shift - number to be shifted left.
  * @retval None
  */
  //Function call Example:- Cloud_PLC_Logical_ShiftLeft(40,1);
  }

//19
uint8_t Cloud_PLC_Logical_ShiftRight(uint32_t Data, uint32_t shift)
{
  return (Data >> shift); 
/**
  * @brief  This function shifts the data to the right.
  * @param  data - data to be shifted.
  *         shift - number to be shifted right.
  * @retval None
  */
  //Function call Example:- Cloud_PLC_Logical_ShiftRight(16,4);
  }

//20
void Cloud_PLC_Delay(uint8_t value)
{
  delay(value);
  /* @Brief  : This function causes the program to halt for a specified time
 * @Params :value - the required time for program to halt in milisecond
 * @return : None 
 */
 //Function call Example:- Cloud_PLC_Delay(3000);
  }

//21
uint16_t Cloud_PLC_Arithmetic_Add(uint32_t num1, uint32_t num2)
{
  uint16_t sum = num1 + num2;
  return sum;
  /* @Brief  : This function adds num1 with num2
 * @Params :num1-first number
 *          num2-second number
 * @return : sum(add of num1 and num2) 
 */
 //Function call Example:- Cloud_PLC_Arithmetic_Add(3,8);
  }

//22
uint16_t Cloud_PLC_Arithmetic_Subtract(uint32_t num1, uint32_t num2)
{
  uint16_t difference= num1 - num2;
  return difference;
  /* @Brief  : This function Subtract num1 with num2
 * @Params :num1-first number
 *          num2-second number
 * @return : difference(difference of num1 and num2) 
 */
 //Function call Example:- Cloud_PLC_Arithmetic_Subtract(6,2);
  }

//23
uint16_t Cloud_PLC_Arithmetic_Multiply(uint8_t num1, uint8_t num2)
{
  uint16_t multiply= (num1*num2);
  return multiply;
/* @Brief  : This function Multiplies num1 with num2
 * @Params :num1-first number
 *          num2-second number
 * @return : multiply(multiple of num1 and num2) 
 */
 //Function call Example:- Cloud_PLC_Arithmetic_Multiply(5,5);
}

//24
float Cloud_PLC_Arithmetic_Divide(uint32_t num1, uint32_t num2)
{
  float divide=(num1/num2);
  return divide;
 /* @Brief  : This function Divides num1 with num2
 * @Params :num1-first number
 *          num2-second number
 * @return : Divide(Divide num1 with num2) 
 */
 //Function call Example:- Cloud_PLC_Arithmetic_Divide(42,7);
 }

 
//25
void Cloud_PLC_Config_WIFI(const char* ssid,const char* password) 
{
  // Connect to Wi-Fi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
	Cloud_PLC_NETWORK_LED_Write(HIGH);
	delay(500);
	Cloud_PLC_NETWORK_LED_Write(LOW);
	
  }
  if (WiFi.status() == WL_CONNECTED) {
    // Connected to Wi-Fi
    Serial.println("Connected to the WiFi network");
    Cloud_PLC_NETWORK_LED_Write(HIGH); // Turn LED on to indicate connection
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
  } else {
    // Handle the case where Wi-Fi is not connected
    Serial.println("WiFi is disconnected or failed to connect");
    Cloud_PLC_NETWORK_LED_Write(LOW); // Turn LED off to indicate no connection
    // Optionally, you can add reconnection attempts or error handling here
  }
 /* @Brief  : This function will config WIFI
 * @Params :ssid- WIFI_name
 *          password-Password
 * @return : None
 */
  //Function call Example:- Cloud_PLC_Config_WIFI("Wifi","password");
}

//26
void Cloud_PLC_JSON(const char* serverurl, const char* Sensor, const char* Value){
  // Create JSON object
  StaticJsonDocument<200> jsonDoc;
  jsonDoc["sensor"] = Sensor;
  jsonDoc["value"] = Value;

  // Serialize JSON to string
  String jsonStr;
  serializeJson(jsonDoc, jsonStr);

  // Create HTTP client
  HTTPClient httpClient;

  // Send HTTP POST request with JSON data
  httpClient.begin(serverurl);
  httpClient.addHeader("Content-Type", "application/json");
  int httpCode = httpClient.POST(jsonStr);
  String response = httpClient.getString();

  // Print response
  Serial.println("HTTP code: " + String(httpCode));
  Serial.println("Response: " + response);

  // Close HTTP connection
  httpClient.end();

  delay(5000);

 /* @Brief  : JSON funtion
 * @Params :serverurl- Server_URL
 *          Sensor- channel name
 *          value - value from the channels
 * @return : None
 */
  //Function call Example:- For 1 value:- Cloud_PLC_JSON("http://iotpi.in/dataloggertesting/dataloggerinsert.php/", "temperature", "26.4");
                         //For Multiple value:- Cloud_PLC_JSON("http://iotpi.in/dataloggertesting/dataloggerinsert.php/", "temperature", "26.4,24.5,27.8,25.8");
}

//27
void Cloud_PLC_Config_MQTT(const char* mqttServer, uint16_t mqttPort, const char* mqttUser, const char* mqttPassword)
{
//mqttServer hairdresser.cloudmqtt.com
//mqttPort 15520
//mqttUser qckwnpwm
//mqttpassword n4KBne_O5Mr9
//https://api.cloudmqtt.com/console/82662738/websocket
  

  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
  /* Connecting to CloudMqtt */
  while (!client.connected())
  {
    Serial.println("Connecting to MQTT...");
    if (client.connect("ESP32Client", mqttUser, mqttPassword ))
    {
      Serial.println("connected");
      /* Sending message to Topic "test1" */
       client.subscribe("RX");
       delay(100);
      client.publish("RDL","hi RDL");
      //Receives message sent to the topic "test"
    }
    else
    {
      Serial.print("failed with state ");
      Serial.println(client.state());
      delay(2000);
    }
  } 
 /* @Brief  : MQTT funtion Configuration
 * @Params :mqttServer- Server_URL
 *          mqttPort -port number 
 *          mqttUser - User_name
 *          mqttPassword - Password
 * @return : None
 */
  //Function call Example:-  Cloud_PLC_Config_MQTT("hairdresser.cloudmqtt.com", 15520, "qckwnpwm", "n4KBne_O5Mr9");
 }

//28
void Cloud_PLC_MQTT_Publish(const char* Data, const char* Message)
{
  client.publish(Data,Message);
 /* @Brief  : Publish funtion for sending message from hardware to server
 * @Params :Data - Topic
 *          Message - Message
 * @return : None
 */
  //Function call Example:- Cloud_PLC_MQTT_Publish("ASD","hii asd");
  }

//29
void Cloud_PLC_MQTT_Subscribe(const char* Data)
{
  client.subscribe(Data);
 /* @Brief  : Subscribe funtion for sending message from server to Hardware
 * @Params :Data - Topic
 * @return : None
 */
//Function call Example:- Cloud_PLC_MQTT_Subscribe("Topic_name");
  }

  
//30
void callback(char* topic, byte* payload, unsigned int length)
{
uint8_t s;
Serial.print("Message arrived in topic: ");
Serial.println(topic);
Serial.print("Message:");
for (int i = 0; i < length; i++)
{
s= payload[i];
Serial.write(s);
}
}



//31
void Cloud_PLC_MQTT_Repeat(void)
{
  client.loop();
 /* @Brief  : Repeat funtion repeativly sending message from server to hardware
 * @Params :None
 * @return : None
 */
  //Function call Example:- Cloud_PLC_MQTT_Repeat();
  }

//32
void Cloud_PLC_File_Init(void)
{
   if(!SD.begin()){
        Serial.println("Card Mount Failed");
        return;
    }
    uint8_t cardType = SD.cardType();

    if(cardType == CARD_NONE){
        Serial.println("No SD card attached");
        return;
    }
    uint64_t cardSize = SD.cardSize() / (1024 * 1024);
    Serial.printf("SD Card Size: %lluMB\n", cardSize);
 /* @Brief  : File_Init funtion for initialize SD_card/File
 * @Params :None
 * @return : None
 */
  //Function call Example:- Cloud_PLC_File_Init();
 }

//33
void Cloud_PLC_File_Write(fs::FS &fs, const char * path, const char * message)
{
    Serial.printf("Writing file: %s\n", path);

    File file = fs.open(path, FILE_WRITE);
    if(!file){
        Serial.println("Failed to open file for writing");
        return;
    }
    if(file.print(message)){
        Serial.println("File written");
    } else {
        Serial.println("Write failed");
    }
    file.close();
 /* @Brief  : File_Write funtion for writting file
 * @Params :&fs - priints the type of file 
 *          path - Name of File
 *          message - Message
 * @return : None
 */
  //Function call Example:- Cloud_PLC_File_Write(SD, "/ajith.txt", "Hello \n");
}

//34
void Cloud_PLC_File_Append(fs::FS &fs, const char * path, const char * message)
{
    Serial.printf("Appending to file: %s\n", path);

    File file = fs.open(path, FILE_APPEND);
    if(!file){
        Serial.println("Failed to open file for appending");
        return;
    }
    if(file.print(message)){
        Serial.println("Message appended");
    } else {
        Serial.println("Append failed");
    }
    file.close();
 /* @Brief  : File_Append funtion for appending message to exsisting file
 * @Params :&fs - priints the type of file 
 *          path - Name of File
 *          message - Message
 * @return : None
 */
  //Function call Example:- Cloud_PLC_File_Write(SD, "/ajith.txt", "Hello \n");
}

//35
void Cloud_PLC_File_Read(fs::FS &fs, const char * path)
{
    Serial.printf("Reading file: %s\n", path);

    File file = fs.open(path);
    if(!file){
        Serial.println("Failed to open file for reading");
        return;
    }

    Serial.print("Read from file: ");
    while(file.available()){
        Serial.write(file.read());
    }
    file.close();
 /* @Brief  : File_Read funtion for reading message from exsisting file
 * @Params :&fs - priints the type of file 
 *          path - Name of File
 * @return : None
 */
  //Function call Example:- Cloud_PLC_File_Write(SD, "/ajith.txt", "Hello \n");
}

//36
byte Cloud_PLC_FTP_Setup(char* Serverurl,int Port,char* Username, char* Password,  char* Filename, char* Message)
{
  char* firstname ="USER ";
  int len1 =strlen(firstname);
  int len2 = strlen(Username);
  char* result = new char[len1+ len2+1];
  strcpy(result,firstname);
  strcat(result,Username);

  char* pass ="PASS ";
  int len3 =strlen(pass);
  int len4 = strlen(Password);
  char* result1 = new char[len3+ len4+1];
  strcpy(result1,pass);
  strcat(result1,Password);
  int clientCount = strlen(Message);
  int i=1;
  while(i==1)
  {
    Serial.println(F("SD opened"));
    if (Client.connect(Serverurl,Port)) 
    {
      Serial.println(F("Command connected"));
    }
    else
    {
      Serial.println(F("Command connection failed"));
      return 0;
    }
     if(!eRcv()) 
      return 0;
    /* ftp username */
    Client.println(F(result));
    if(!eRcv()) 
      return 0;
    /* ftp password */
    Client.println(F(result1));
    if(!eRcv()) 
      return 0;
    Client.println(F("SYST"));
    if(!eRcv()) 
      return 0;
    Client.println(F("Type I"));
    if(!eRcv()) 
      return 0;
    Client.println(F("PASV"));
    if(!eRcv()) 
      return 0;
    char *tStr = strtok(outBuf,"(,");
    int array_pasv[6];
    for ( int i = 0; i < 6; i++) 
    {
      tStr = strtok(NULL,"(,");
      array_pasv[i] = atoi(tStr);
      if(tStr == NULL)
      {
       Serial.println(F("Bad PASV Answer")); 
      }
    }
    unsigned int hiPort,loPort;
    hiPort = array_pasv[4] << 8;
    loPort = array_pasv[5] & 255;
    Serial.print(F("Data port: "));
    hiPort = hiPort | loPort;
    Serial.println(hiPort);
    if (dclient.connect(Serverurl,hiPort)) 
    {
      Serial.println(F("Data connected"));
    }
    else 
    {
      Serial.println(F("Data connection failed"));
      Client.stop();
      return 0;
    }
    #ifdef FTPWRITE
    Client.print(F("STOR "));
    Client.println(Filename);
    #else
    Client.print(F("RETR "));
    Client.println(Filename);
    #endif
    if(!eRcv())
    {
     dclient.stop();
     return 0;
    }
    #ifdef FTPWRITE
    Serial.println(F("Writing"));
    if(clientCount > 0) 
      dclient.write(Message,clientCount);
    #else
    while(dclient.connected())
    {
     while(dclient.available())
     {
       char c = dclient.read();
       Serial.write(c);
     }
    }
    #endif
    dclient.stop();
    Serial.println(F("Data disconnected"));
    if(!eRcv()) 
      return 0;
    Client.println(F("QUIT"));
    if(!eRcv()) 
      return 0;
    Client.stop();
    Serial.println(F("Command disconnected"));
    Serial.println(F("SD closed"));
    return 1;
    i--;
    Serial.println("FTP ok");
  }
  if(i==0) Serial.println("FTP Fall");
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
}

//37
byte eRcv()
{
  byte respCode;
  byte thisByte;

  while(!Client.available()) delay(1);
  respCode = Client.peek();
  outCount = 0;
  while(Client.available())
   {
     thisByte = Client.read(); 
     Serial.write(thisByte);
     if(outCount < 127)
     {
       outBuf[outCount] = thisByte;
       outCount++; 
       outBuf[outCount] = 0;
    
     }
  }
  if(respCode >= '4')
  {
   efail();
   return 0;
  }
  return 1;
 /* @Brief  : Function for receiving Message
 * @Params :None
 * @return :None
 */  
}

//38
void efail()
  {
  byte thisByte = 0;
  Client.println(F("QUIT"));
  while(!Client.available()) delay(1);
  while(Client.available())
  {
   thisByte = Client.read(); 
   Serial.write(thisByte);
  }
  Client.stop();
  Serial.println(F("Command disconnected"));
  Serial.println(F("SD closed"));
  /* @Brief  : Function disconnecting and stoping
 * @Params :None
 * @return :None
 */ 
}
