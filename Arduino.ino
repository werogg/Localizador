#include <SoftwareSerial.h>
//#include <TinyGPS.h>

SoftwareSerial gprsSerial(7, 8);
//SoftwareSerial gpsSerial(4, 3);

boolean sonando;
char a;
int portSpeak(13);  //porta ligada no speaker
float lat,lon;
int melodia[] = {660,660,660,510,660,770,380,510,380,320,440,480,450,430,380,660,760,860,700,760,660,520,580,480,510,380,320,440,480,450,430,380,660,760,860,700,760,660,520,580,480,500,760,720,680,620,650,380,430,500,430,500,570,500,760,720,680,620,650,1020,1020,1020,380,500,760,720,680,620,650,380,430,500,430,500,570,585,550,500,380,500,500,500,500,760,720,680,620,650,380,430,500,430,500,570,500,760,720,680,620,650,1020,1020,1020,380,500,760,720,680,620,650,380,430,500,430,500,570,585,550,500,380,500,500,500,500,500,500,500,580,660,500,430,380,500,500,500,500,580,660,870,760,500,500,500,500,580,660,500,430,380,660,660,660,510,660,770,380};
int duracaodasnotas[] = {100,100,100,100,100,100,100,100,100,100,100,80,100,100,100,80,50,100,80,50,80,80,80,80,100,100,100,100,80,100,100,100,80,50,100,80,50,80,80,80,80,100,100,100,100,150,150,100,100,100,100,100,100,100,100,100,100,150,200,80,80,80,100,100,100,100,100,150,150,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,150,150,100,100,100,100,100,100,100,100,100,100,150,200,80,80,80,100,100,100,100,100,150,150,100,100,100,100,100,100,100,100,100,100,100,100,100,60,80,60,80,80,80,80,80,80,60,80,60,80,80,80,80,80,60,80,60,80,80,80,80,80,80,100,100,100,100,100,100,100};
int pausadepoisdasnotas[] ={150,300,300,100,300,550,575,450,400,500,300,330,150,300,200,200,150,300,150,350,300,150,150,500,450,400,500,300,330,150,300,200,200,150,300,150,350,300,150,150,500,300,100,150,150,300,300,150,150,300,150,100,220,300,100,150,150,300,300,300,150,300,300,300,100,150,150,300,300,150,150,300,150,100,420,450,420,360,300,300,150,300,300,100,150,150,300,300,150,150,300,150,100,220,300,100,150,150,300,300,300,150,300,300,300,100,150,150,300,300,150,150,300,150,100,420,450,420,360,300,300,150,300,150,300,350,150,350,150,300,150,600,150,300,350,150,150,550,325,600,150,300,350,150,350,150,300,150,600,150,300,300,100,300,550,575};
//TinyGPS gps; // create gps object

void setup()
{
  gprsSerial.begin(19200);
  Serial.begin(19200);

  Serial.println("Config SIM900...");
  delay(2000);
  Serial.println("Done!...");
  gprsSerial.flush();
  Serial.flush();

  gprsSerial.println("AT+CPIN=\"4640\"");
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
  gprsSerial.println("AT+SAPBR=3,1,\"APN\",\"orangeworld\"");
  delay(2000);
  toSerial();

  // bearer settings
  gprsSerial.println("AT+SAPBR=3,1,\"USER\",\"orange\"");
  delay(2000);
  toSerial();

  // bearer settings
  gprsSerial.println("AT+SAPBR=3,1,\"PWD\",\"orange\"");
  delay(2000);
  toSerial();

  // bearer settings
  gprsSerial.println("AT+SAPBR=1,1");
  delay(2000);
  toSerial();

  digitalWrite( portSpeak, HIGH);
  delay(500);
  digitalWrite( portSpeak, LOW);
  delay(500);
  digitalWrite( portSpeak, HIGH);
  delay(500);
  digitalWrite( portSpeak, LOW);
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
          for (int nota = 0; nota < 156; nota++) {
            int duracaodanota = duracaodasnotas[nota];
            tone(portSpeak, melodia[nota],duracaodanota);
            delay(pausadepoisdasnotas[nota]);
          }
          noTone(portSpeak);
        }
      } else {
        sonando = false;
        Serial.println("Funciona2");
        noTone(portSpeak);
      }
      Serial.write(a);
}
