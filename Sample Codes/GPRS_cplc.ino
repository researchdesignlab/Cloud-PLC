#include <CPLC.h> 
char data[] = "Hello RDL111!!";
char* host = "mm.cloudmqtt.com";  //Your host ID
//char* host = "52.3.184.147";
char* port = "11000";            //Your port number
char* username = "*****";        //Your username
char* password = "******";       / Your password
char* topic = "ethernet";
//char *APN = "tp://airtelgprs.com"; //for airtel sim
//char *APN = "internet"; //for Idea sim 
char *APN = "TATA.DOCOMO.INTERNET"; //for DoCoMo sim 
void setup(){
Serial.begin(9600);
Serial.println("Start..");
CPLC_GPRS_Upload_MQTT(data, APN, host, port, username, password, topic);
}
void loop()
{
}
