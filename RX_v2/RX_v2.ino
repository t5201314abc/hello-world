char inData[24];
byte index;
boolean started = false;
boolean ended = false;

const int ledPin = 13;

void setup()
{
  Serial.begin(115200);
  Serial.println("Temperature & Humidity & UV Index");
}

void loop()
{
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
      int windVal = atoi(inData);
      Serial.println(" ");
      Serial.print("Temp:");
      Serial.print(inData);
      Serial.print("C");
      Serial.println(" ");
      //digitalWrite(ledPin, HIGH);
    }
    else if(inData[0] == 'H')
    {
      inData[0] = ' ';
      int temp = atoi(inData);
      Serial.println(" ");
      Serial.print("Humidity:");
      Serial.print(inData);
      Serial.print("%");
      Serial.println(" ");
      //digitalWrite(ledPin, HIGH);
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
    }

    started = false;
    ended = false;

    index = 0;
    inData[index] = '\0';
    
  }
  //digitalWrite(ledPin, LOW);
}
