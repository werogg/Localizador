// Incloem les llibreries que utilitzarem
#include <SoftwareSerial.h>
#include <TinyGPS.h>

// Establim els ports de entrada i sortida d'informació del arduino que utilitzarem pel GPRS i GPS.
SoftwareSerial gprsSerial(7, 8);
SoftwareSerial gpsSerial(4, 3);

//Definim varies variables que utilitzarem posteriorment
boolean sonando;
char a;
int portSpeak(13);  //porta ligada no speaker
float lat,lon;
int melodia[] = {660,660,660,510,660,770,380,510,380,320,440,480,450,430,380,660,760,860,700,760,660,520,580,480,510,380,320,440,480,450,430,380,660,760,860,700,760,660,520,580,480,500,760,720,680,620,650,380,430,500,430,500,570,500,760,720,680,620,650,1020,1020,1020,380,500,760,720,680,620,650,380,430,500,430,500,570,585,550,500,380,500,500,500,500,760,720,680,620,650,380,430,500,430,500,570,500,760,720,680,620,650,1020,1020,1020,380,500,760,720,680,620,650,380,430,500,430,500,570,585,550,500,380,500,500,500,500,500,500,500,580,660,500,430,380,500,500,500,500,580,660,870,760,500,500,500,500,580,660,500,430,380,660,660,660,510,660,770,380};
int duracaodasnotas[] = {100,100,100,100,100,100,100,100,100,100,100,80,100,100,100,80,50,100,80,50,80,80,80,80,100,100,100,100,80,100,100,100,80,50,100,80,50,80,80,80,80,100,100,100,100,150,150,100,100,100,100,100,100,100,100,100,100,150,200,80,80,80,100,100,100,100,100,150,150,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,150,150,100,100,100,100,100,100,100,100,100,100,150,200,80,80,80,100,100,100,100,100,150,150,100,100,100,100,100,100,100,100,100,100,100,100,100,60,80,60,80,80,80,80,80,80,60,80,60,80,80,80,80,80,60,80,60,80,80,80,80,80,80,100,100,100,100,100,100,100};
int pausadepoisdasnotas[] ={150,300,300,100,300,550,575,450,400,500,300,330,150,300,200,200,150,300,150,350,300,150,150,500,450,400,500,300,330,150,300,200,200,150,300,150,350,300,150,150,500,300,100,150,150,300,300,150,150,300,150,100,220,300,100,150,150,300,300,300,150,300,300,300,100,150,150,300,300,150,150,300,150,100,420,450,420,360,300,300,150,300,300,100,150,150,300,300,150,150,300,150,100,220,300,100,150,150,300,300,300,150,300,300,300,100,150,150,300,300,150,150,300,150,100,420,450,420,360,300,300,150,300,150,300,350,150,350,150,300,150,600,150,300,350,150,150,550,325,600,150,300,350,150,350,150,300,150,600,150,300,300,100,300,550,575};
// Creem un objecte amb les llibreries de TinyGPS per facilitar la gestió de la informació d'aquest
TinyGPS gps; // create gps object

// Codi d'execució única
void setup()
{
  // Establim la frecuencia a la que funcionara l'arduino, el GPRS i el GPS.
  gprsSerial.begin(19200);
  gpsSerial.begin(19200);
  Serial.begin(19200);

  // Missatge de desenvolupament (no accesible per l'usuari)
  Serial.println("Config SIM900...");
  delay(2000);
  Serial.println("Done!...");
  gprsSerial.flush();
  Serial.flush();

  // Establim el PIN de la SIM
  gprsSerial.println("AT+CPIN=\"4640\"");
  delay(25000);
  toSerial();

  // Solicitud de conexió a la xarxa GPRS 
  gprsSerial.println("AT+CGATT?");
  delay(2000);
  toSerial();

  // Establim el tipus de connexió com a GPRS
  gprsSerial.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");
  delay(2000);
  toSerial();

  // Establim l'APN de la xarxa GPRS a la que ens connectarem
  gprsSerial.println("AT+SAPBR=3,1,\"APN\",\"orangeworld\"");
  delay(2000);
  toSerial();

  // Establim el nom d'usuari de connexió a la xarxa GPRS
  gprsSerial.println("AT+SAPBR=3,1,\"USER\",\"orange\"");
  delay(2000);
  toSerial();

  // Establim la contrasenya de connexió a la xarxa GPRS
  gprsSerial.println("AT+SAPBR=3,1,\"PWD\",\"orange\"");
  delay(2000);
  toSerial();

  // Obrim una connexió amb la xarxa GPRS
  gprsSerial.println("AT+SAPBR=1,1");
  delay(2000);
  toSerial();

  // Senyal sonora per indicar que el dispositiu s'ha iniciat completament
  digitalWrite( portSpeak, HIGH);
  delay(500);
  digitalWrite( portSpeak, LOW);
  delay(500);
  digitalWrite( portSpeak, HIGH);
  delay(500);
  digitalWrite( portSpeak, LOW);
  delay( 500);
   
}

// Codi d'execució indefinida (fins a falla)
void loop()
{
   delay(2000);
   // Comprobem que el GPS estigui disponible, sino insistim fins que ho estigui
   while(gpsSerial.available()){
      // Llegim el missatge rebut pel GPS i el descodifiquem
      if(gps.encode(gpsSerial.read())){
        // Seleccionem les dades de posició i les establim per les variables "lat" i "lon" (latitud i longitud)
        gps.get_position(&lat,&lon);
        // Missatge de desenvolupament (no accesible per l'usuari)
        Serial.print("Position: ");
        Serial.print("lat: ");Serial.print(lat);Serial.print(" ");
        Serial.print("lon: ");Serial.println(lon);
      }
   }


   // Inicialitzem un servei HTTP
   gprsSerial.println("AT+HTTPINIT");
   delay(2000); 
   toSerial();

   // Establim els parametres de connexió HTTP (per escriure les dades de latitud i longitud obtingudes a la base de dades)
   gprsSerial.println("AT+HTTPPARA=\"URL\",\"http://foro.battlepvpmine.es/write_data.php?longitude=" + String(lon, 7) + "&latitude=" + String(lat, 7) + "&key=8A621E21A96A6E36\""); 
   delay(2000);
   toSerial();

   // Establim el tipus de connexió HTTP
   gprsSerial.println("AT+HTTPACTION=0");
   delay(2000);
   toSerial();

   // Llegim la resposta del servidor davant la nostra connexió HTTP
   gprsSerial.println("AT+HTTPREAD"); 
   delay(2000);
   toSerial();

   // Finalitzem la connexió HTTP
   gprsSerial.println("");
   gprsSerial.println("AT+HTTPTERM");
   delay(2000);
   toSerial();
   delay(2000);
  
   // Iniciem un altre servei HTTP
   gprsSerial.println("AT+HTTPINIT");
   delay(2000); 
   toSerial();
 
   // Establim els parametres de connexió HTTP (per obtenir dades de senyal sonora)
   gprsSerial.println("AT+HTTPPARA=\"URL\",\"http://foro.battlepvpmine.es/get_buzzing.php?key=8A621E21A96A6E36\"");// setting the httppara, 
   //the second parameter is the website from where you want to access data 
   delay(2000);
   toSerial();
  
   // Establim el tipus de connexió HTTP
   gprsSerial.println();
   gprsSerial.println("AT+HTTPACTION=0");
   delay(2000);
   toSerial();
   
   // Llegim la resposta i la guardem
   gprsSerial.println("AT+HTTPREAD=0,60");
   gprsSerial.println("");
   delay(2000);
   toRead();
  
   // Finalitzem la connexió HTTP
   gprsSerial.println("AT+HTTPTERM");// terminate HTTP service
   // Missatge de desenvolupament (no accesible per l'usuari)
   Serial.write("\nAntes del HTTPTERM\n");
   toSerial();
   
}

// Clase serialitzadora de la consola principal del GPRS
void toSerial()
{
  // Mentres el GPRS estigui disponible executar la línia segent
  while(gprsSerial.available()!=0)
  {
    // Serialitzar missatge i enviarlo a la consola principal de l'arduino
    Serial.write(gprsSerial.read());
  }
}

// Clase per llegir resposta HTTP i interpretarla segons si la variable de la senyal sonora esta activada "1" o no "0"
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
          // Reproduïm la senyal sonora
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
