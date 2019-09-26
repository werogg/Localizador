#include <SoftwareSerial.h>
//#include <TinyGPS.h>

SoftwareSerial gprsSerial(7, 8);
//SoftwareSerial gpsSerial(4, 3);

boolean sonando;
char a;
const int buzz = 13;
float lat,lon;

//TinyGPS gps; // create gps object

void setup()
{
  gprsSerial.begin(19200);
  Serial.begin(19200);
  pinMode(buzz, OUTPUT);

  Serial.println("Config SIM900...");
  delay(2000);
  Serial.println("Done!...");
  gprsSerial.flush();
  Serial.flush();

  gprsSerial.println("AT+CPIN=\"\"");
  delay(25000);
  toSerial();

  // attach or detach from GPRS service 
  gprsSerial.println("AT+CGATT?");
  delay(2000);
  toSerial();


  // bearer settings
  gprsSerial.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");
  delay(2000);
  toSerial();

  // bearer settings
  gprsSerial.println("AT+SAPBR=3,1,\"APN\",\"youinternet\"");
  delay(2000);
  toSerial();

  // bearer settings
  gprsSerial.println("AT+SAPBR=3,1,\"USER\",\"\"");
  delay(2000);
  toSerial();

  // bearer settings
  gprsSerial.println("AT+SAPBR=3,1,\"PWD\",\"\"");
  delay(2000);
  toSerial();

  // bearer settings
  gprsSerial.println("AT+SAPBR=1,1");
  delay(2000);
  toSerial();

  digitalWrite( buzz, HIGH);
  delay(500);
  digitalWrite( buzz, LOW);
  delay(500);
  digitalWrite( buzz, HIGH);
  delay(500);
  digitalWrite( buzz, LOW);
  delay( 500);
   
}


void loop()
{
   delay(2000);
   lat=41.438689;
   lon=2.228596;

   // initialize http service
   gprsSerial.println("AT+HTTPINIT");
   delay(2000); 
   toSerial();

   // set http param value
   gprsSerial.println("AT+HTTPPARA=\"URL\",\"http://foro.battlepvpmine.es/write_data.php?longitude=" + String(lon, 7) + "&latitude=" + String(lat, 7) + "&key=8A621E21A96A6E36\""); 
   delay(2000);
   toSerial();

   // set http action type 0 = GET, 1 = POST, 2 = HEAD
   gprsSerial.println("AT+HTTPACTION=0");
   delay(2000);
   toSerial();

   // read server response
   gprsSerial.println("AT+HTTPREAD"); 
   delay(2000);
   toSerial();

   gprsSerial.println("");
   gprsSerial.println("AT+HTTPTERM");
   delay(2000);
   toSerial();
   delay(2000);

   gprsSerial.println("AT+HTTPINIT"); //init the HTTP request
   delay(2000); 
   toSerial();
 
   gprsSerial.println("AT+HTTPPARA=\"URL\",\"http://foro.battlepvpmine.es/get_buzzing.php?key=8A621E21A96A6E36\"");// setting the httppara, 
   //the second parameter is the website from where you want to access data 
   delay(2000);
   toSerial();


   gprsSerial.println();
   gprsSerial.println("AT+HTTPACTION=0");//submit the GET request
   delay(2000);
   toSerial();
   
   gprsSerial.println("AT+HTTPREAD=0,60");
   
   gprsSerial.println("");
   delay(2000);
   toRead();
   gprsSerial.println("AT+HTTPTERM");// terminate HTTP service
   Serial.write("\nAntes del HTTPTERM\n");
   toSerial();
   
}


void toSerial()
{
  while(gprsSerial.available()!=0)
  {
    Serial.write(gprsSerial.read());
  }
}

void toRead() {
    a = gprsSerial.read();
    while( a != '{' ) {
      Serial.write(a);
      a = gprsSerial.read();
    }
    int active = gprsSerial.read() - '0';
      if (active == 1) {
        if (!sonando) {
          Serial.println("Funciona1");
          sonando = true;
          digitalWrite(buzz, HIGH);
          delay (15000);
          digitalWrite(buzz, LOW);
        }
      } else {
        sonando = false;
        Serial.println("Funciona2");
        digitalWrite(buzz, LOW);
      }
      Serial.write(a);
}
