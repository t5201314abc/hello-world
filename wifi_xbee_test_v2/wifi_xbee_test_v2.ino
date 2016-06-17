#include <SoftwareSerial.h>
#define _baudrate   115200
#define _rxpin      2 // Wire this to Tx Pin of ESP8266
#define _txpin      3 // Wire this to Rx Pin of ESP8266
SoftwareSerial debug( _rxpin, _txpin ); // RX, TX
//*-- IoT Information
#define SSID "Leo's iPhone 2"
#define PASS "123456789"
#define IP "184.106.153.149" // ThingSpeak IP Address: 184.106.153.149
// 使用 GET 傳送資料的格式
// GET /update?key=[THINGSPEAK_KEY]&field1=[data 1]&filed2=[data 2]...;
String GET = "GET /update?key=QMTKBWEI035CNZY4";

//xbee RX
char inData[24];
byte index;
boolean started = false;
boolean ended = false;

void setup() {
    Serial.begin( _baudrate );
    //Serial.println("Temperature & Humidity");
    debug.begin( _baudrate );
    sendDebug("AT");
    Loding("sent AT");
    connectWiFi();
}
void loop() {
  int temp;
  int hum;
  delay(5000);   
  //void temp_hum(); //SentOnCloud( String(windVal), String(temp) );
  while(Serial.available() > 0)
  {
  char aChar = Serial.read();
  if(aChar == '<')
  {
      started = true;
      index = 0;
      inData[index] = '\0';
  }
  else if(aChar == '>')
  {
      ended = true;
  }
  else if(started)
  {
      inData[index] = aChar;
      index++;
      inData[index] = ',';
  }
  }

  if(started && ended)
  {
  // Use the value
  if(inData[0] == 'T')
  {
     inData[0] = ' ';
     int temp = atoi(inData);
     Serial.println(" ");
     Serial.print("Temp:");
     Serial.print(inData);
     Serial.print("C");
     Serial.println(" ");
     SentOnCloudT( String(temp) );
  }
  else if(inData[0] == 'H')
  {
     inData[0] = ' ';
     int hum = atoi(inData);
     Serial.println(" ");
     Serial.print("Humidity:");
     Serial.print(inData);
     Serial.print("%");
     Serial.println(" ");
     SentOnCloudH( String(hum) );
   }
   else if(inData[0] == 'U')
    {
      inData[0] = ' ';
      int uv = atoi(inData);
      Serial.println(" ");
      Serial.print("UV Index:");
      Serial.print(inData);
      //Serial.print("%");
      Serial.println(" ");
      //digitalWrite(ledPin, HIGH);
      SentOnCloudU( String(uv) );
    }

  started = false;
  ended = false;

  index = 0;
  inData[index] = '\0';
  }
  
}

boolean connectWiFi()
{
    debug.println("AT+CWMODE=1");
    Wifi_connect();
}

//void SentOnCloud( String T, String H )
void SentOnCloudT( String T )
{
    // 設定 ESP8266 作為 Client 端
    String cmd = "AT+CIPSTART=\"TCP\",\"";
    cmd += IP;
    cmd += "\",80";
    sendDebug(cmd);
    if( debug.find( "Error" ) )
    {
        Serial.print( "RECEIVED: Error\nExit1" );
        return;
    }
   // cmd = GET + "&field1=" + T + "&field2=" + H +"\r\n";
   cmd = GET + "&field1=" + T +"\r\n";
    debug.print( "AT+CIPSEND=" );
    debug.println( cmd.length() );
    if(debug.find( ">" ) )
    {
        Serial.print(">");
        Serial.print(cmd);
        debug.print(cmd);
    }
    else
    {
        debug.print( "AT+CIPCLOSE" );
    }
    if( debug.find("OK") )
    {
        Serial.println( "RECEIVED: OK" );
    }
    else
    {
        Serial.println( "RECEIVED: Error\nExit2" );
    }
}

void SentOnCloudH( String H )
{
    // 設定 ESP8266 作為 Client 端
    String cmd = "AT+CIPSTART=\"TCP\",\"";
    cmd += IP;
    cmd += "\",80";
    sendDebug(cmd);
    if( debug.find( "Error" ) )
    {
        Serial.print( "RECEIVED: Error\nExit1" );
        return;
    }
   // cmd = GET + "&field1=" + T + "&field2=" + H +"\r\n";
   cmd = GET + "&field2=" + H +"\r\n";
    debug.print( "AT+CIPSEND=" );
    debug.println( cmd.length() );
    if(debug.find( ">" ) )
    {
        Serial.print(">");
        Serial.print(cmd);
        debug.print(cmd);
    }
    else
    {
        debug.print( "AT+CIPCLOSE" );
    }
    if( debug.find("OK") )
    {
        Serial.println( "RECEIVED: OK" );
    }
    else
    {
        Serial.println( "RECEIVED: Error\nExit2" );
    }
}

void SentOnCloudU( String U )
{
    // 設定 ESP8266 作為 Client 端
    String cmd = "AT+CIPSTART=\"TCP\",\"";
    cmd += IP;
    cmd += "\",80";
    sendDebug(cmd);
    if( debug.find( "Error" ) )
    {
        Serial.print( "RECEIVED: Error\nExit1" );
        return;
    }
   // cmd = GET + "&field1=" + T + "&field2=" + H +"\r\n";
   cmd = GET + "&field3=" + U +"\r\n";
    debug.print( "AT+CIPSEND=" );
    debug.println( cmd.length() );
    if(debug.find( ">" ) )
    {
        Serial.print(">");
        Serial.print(cmd);
        debug.print(cmd);
    }
    else
    {
        debug.print( "AT+CIPCLOSE" );
    }
    if( debug.find("OK") )
    {
        Serial.println( "RECEIVED: OK" );
    }
    else
    {
        Serial.println( "RECEIVED: Error\nExit2" );
    }
}

void Wifi_connect()
{
    String cmd="AT+CWJAP=\"";
    cmd+=SSID;
    cmd+="\",\"";
    cmd+=PASS;
    cmd+="\"";
    sendDebug(cmd);
    Loding("Wifi_connect");
}
void Loding(String state){
    for (int timeout=0 ; timeout<10 ; timeout++)
    {
      if(debug.find("OK"))
      {
          Serial.println("RECEIVED: OK");
          break;
      }
      else if(timeout==9){
        Serial.print( state );
        Serial.println(" fail...\nExit2");
      }
      else
      {
        Serial.print("Wifi Loading...");
        delay(500);
      }
    }
}
void sendDebug(String cmd)
{
    Serial.print("SEND: ");
    Serial.println(cmd);
    debug.println(cmd);
} 
