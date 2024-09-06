#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <ESP8266WiFi.h>
#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include "./klima.h"
#include "./tv.h"
#include "./supurge.h"

const uint16_t kIrLed = 4;  // ESP8266 GPIO pin to use. Recommended: 4 (D2).

IRsend irsend(kIrLed);  // Set the GPIO to be used to sending the message.



#define LED D1


const char* ssid = "WİFİ NAME";
const char* password = "wifi Password";// 
unsigned char status_led=0;
WiFiServer server(80);


// Set your Static IP address
IPAddress local_IP(192, 168, 1, 141);
// Set your Gateway IP address
IPAddress gateway(192, 168, 1, 1);

IPAddress subnet(255, 255, 0, 0);
IPAddress primaryDNS(8, 8, 8, 8);   //optional
IPAddress secondaryDNS(8, 8, 4, 4); //optional

void setup() {


    
  //Serial.begin(115200);
  pinMode(LED, OUTPUT);
  Serial.println();
  Serial.println();
irsend.begin();
#if ESP8266
  Serial.begin(115200, SERIAL_8N1, SERIAL_TX_ONLY);
#else  // ESP8266
  Serial.begin(115200, SERIAL_8N1);
#endif  // ESP8266
if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
    Serial.println("STA Failed to configure");
  }
  
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  server.begin();
  Serial.println("Server started");
  Serial.println(WiFi.localIP());


  // Port defaults to 8266
  // ArduinoOTA.setPort(8266);

  // Hostname defaults to esp8266-[ChipID]
  // ArduinoOTA.setHostname("myesp8266");

  // No authentication by default
  // ArduinoOTA.setPassword("admin");

  // Password can be set with it's md5 value as well
  // MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
  // ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");

  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH)
      type = "sketch";
    else // U_SPIFFS
      type = "filesystem";

    // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
    Serial.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });
  ArduinoOTA.begin();
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  ArduinoOTA.handle();

WiFiClient client = server.available();
  if (!client) {
    return;
  }
  
  Serial.println("new client");
  while(!client.available())
  {
    delay(1);
  }
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();
  if (req.indexOf("/ledoff") != -1)
  {
    status_led=0;   
    digitalWrite(LED,LOW);
    Serial.println("LED OFF");
  }

  ///////////////////////////////elektrikli süpürge////////////////////////////////



else if(req.indexOf("/kademe4") != -1)
  {
  irsend.sendNEC(OK, 32);  // Send a raw data capture at 38kHz.
    Serial.println("kademe 4");
    delay(150);
  }


else if(req.indexOf("/yikama") != -1)
  {
  irsend.sendNEC(OK, 32);  // Send a raw data capture at 38kHz.
    Serial.println("yikama modu açıldı.");
    delay(150);
  }
  else if(req.indexOf("/eksiltme") != -1)
  {
  irsend.sendNEC(OK, 32);  // Send a raw data capture at 38kHz.
    Serial.println("yikama modu açıldı.");
    delay(150);
  }
  

////////////////////////////////// LG TV KONSOL ///////////////////////////////////////



   else if(req.indexOf("/OK") != -1)
  {
  irsend.sendNEC(OK, 32);  // Send a raw data capture at 38kHz.
    Serial.println("OK tuşuna basıldı.");
    delay(150);
  }


else if(req.indexOf("/OK") != -1)
  {
  irsend.sendNEC(OK, 32);  // Send a raw data capture at 38kHz.
    Serial.println("TAMAM tuşuna basıldı.");
    delay(150);
  }

else if(req.indexOf("/servisMenu") != -1)
   {   
for (int i=0; i<10; i++){
  irsend.sendRaw(servisMenu1, 67, 32);  // Send a raw data capture at 38kHz. servis menu sifre=0413
  Serial.println("servis menusuna giris 2 döngü");
  delay(250);} 
  }

  

 else if(req.indexOf("/servisMenu2") != -1)
  {
    for (int i=0; i<5; i++){
  irsend.sendNEC(servisMenu2, 32); //menu sifre=0413
  Serial.println("servis menusuna giris 2 döngü");
  delay(250);}
    
 
  }


  else if(req.indexOf("/servisMenu2") != -1)
  {
    for (int i=0; i<2; i++){
  irsend.sendNEC(servisMenu2); 
  Serial.println("servis menusuna giris 2 döngü");
  delay(250);}
    
 
  }



 else if(req.indexOf("/sesKismaTus") != -1)
  {
    for (int i=0; i<2; i++){
  irsend.sendNEC(sesKisma, 32); 
  Serial.println("ses kısılıyor 2kademe");
  delay(150);}
    
 
  }



  else if(req.indexOf("/sesAcTus") != -1)
  { 
   
     for (int i=0; i<2; i++)
     {
  irsend.sendNEC(sesAc);  // Send a raw data capture at 38kHz.
  Serial.println("ses açılıyor 2kademe");
  delay(150);}
    }
  
 
  else if(req.indexOf("/sesKisma") != -1)
  {
    for (int i=0; i<6; i++){
  irsend.sendNEC(sesKisma, 32); 
  Serial.println("ses kısılıyor 6kez");
  delay(150);}
    
 
  }



  else if(req.indexOf("/sesAc") != -1)
  { 
   
     for (int i=0; i<6; i++)
     {
  irsend.sendNEC(sesAc);  // Send a raw data capture at 38kHz.
  Serial.println("ses açılıyor 6kez");
  delay(150);}
    }
  

  
else if(req.indexOf("/kanalileri") != -1)
  {
  irsend.sendNEC(kanalileri, 32);  // Send a raw data capture at 38kHz.
    Serial.println("kanal ilerledi");
    delay(150);
  }


else if(req.indexOf("/kanalgeri") != -1)
  {  
  irsend.sendNEC(kanalgeri, 32);  // Send a raw data capture at 38kHz.
    Serial.println("kanal geri tuşuna basıldı.");
    delay(150);
  }
  

 
  
   else if(req.indexOf("/mute") != -1)
  {
    irsend.sendNEC(mute, 32); // Send a raw data capture at 38kHz.
    Serial.println("sessize alındı");
    delay(150);
  }

   else if(req.indexOf("/tvoff") != -1)
  {   
  irsend.sendNEC(tvoff);  // Send a raw data capture at 38kHz.
  Serial.println("TV kapatıldı");
   delay(50);
  }



 else if(req.indexOf("/tvon") != -1)
  {   
  irsend.sendNEC(tvon);  // Send a raw data capture at 38kHz.
  Serial.println("TV Acıldı..");
   delay(50);
  }


   else if(req.indexOf("/ucboyut") != -1)
  {   
  irsend.sendNEC(ucboyut);  // Send a raw data capture at 38kHz.
  Serial.println("TV 3D ye geçti");
   delay(50);
  }


     else if(req.indexOf("/ucboyutcikis") != -1)
  {   
  irsend.sendNEC(ucboyutcikis);  // Send a raw data capture at 38kHz.
  Serial.println("TV 3d çıkış oldu");
   delay(50);
  }
  
  else if(req.indexOf("/favorilerim") != -1)
  {   
  irsend.sendNEC(favorilerim);  // Send a raw data capture at 38kHz.
  Serial.println("favorilerim");
   delay(50);
  }
  
  else if(req.indexOf("/kanal1") != -1)
  {   
  irsend.sendNEC(kanal1);  // Send a raw data capture at 38kHz.
  Serial.println("TV 1");
   delay(250);
  }

  else if(req.indexOf("/kanal2") != -1)
  {   
  irsend.sendNEC(kanal2);  // Send a raw data capture at 38kHz.
  Serial.println("TV 2");
   delay(250);
  }


 else if(req.indexOf("/kanal3") != -1)
  {   
  irsend.sendNEC(kanal3);  // Send a raw data capture at 38kHz.
  Serial.println("TV 3");
   delay(250);
  }


 else if(req.indexOf("/kanal4") != -1)
  {   
  irsend.sendNEC(kanal4);  // Send a raw data capture at 38kHz.
  Serial.println("TV 4");
   delay(250);
  }


 else if(req.indexOf("/kanal5") != -1)
  {   
  irsend.sendNEC(kanal5);  // Send a raw data capture at 38kHz.
  Serial.println("TV 5");
   delay(250);
  }


 else if(req.indexOf("/kanal6") != -1)
  {   
  irsend.sendNEC(kanal6);  // Send a raw data capture at 38kHz.
  Serial.println("TV 6");
   delay(250);
  }


 else if(req.indexOf("/kanal7") != -1)
  {   
  irsend.sendNEC(kanal7);  // Send a raw data capture at 38kHz.
  Serial.println("TV 7");
   delay(250);
  }


 else if(req.indexOf("/kanal8") != -1)
  {   
  irsend.sendNEC(kanal8);  // Send a raw data capture at 38kHz.
  Serial.println("TV 8");
   delay(250);
  }


 else if(req.indexOf("/kanal9") != -1)
  {   
  irsend.sendNEC(kanal9);  // Send a raw data capture at 38kHz.
  Serial.println("TV 9");
   delay(250);
  }


 else if(req.indexOf("/kanal0") != -1)
  {   
  irsend.sendNEC(kanal0);  // Send a raw data capture at 38kHz.
  Serial.println("TV 0");
   delay(250);
  }


 else if(req.indexOf("/kanal0") != -1)
  {   
  irsend.sendNEC(kanal1);  // Send a raw data capture at 38kHz.
  delay(150);
  irsend.sendNEC(kanal0); 
  Serial.println("TV 10 tuşlandı.");
   delay(150);
  }

else if(req.indexOf("/kanal11") != -1)
  {   
  irsend.sendNEC(kanal1);  // Send a raw data capture at 38kHz.
  delay(150);
  irsend.sendNEC(kanal1); 
  Serial.println("TV 11 tuşlandı.");
delay(150);
  }


else if(req.indexOf("/kanal2") != -1)
  {   
  irsend.sendNEC(kanal1);  // Send a raw data capture at 38kHz.
  delay(150);
  irsend.sendNEC(kanal2); 
  Serial.println("TV 12 tuşlandı.");
   delay(150);
  }

else if(req.indexOf("/kanal3") != -1)
  {   
  irsend.sendNEC(kanal1);  // Send a raw data capture at 38kHz.
  delay(150);
  irsend.sendNEC(kanal3); 
  Serial.println("TV 13 tuşlandı.");
delay(150);
  }

else if(req.indexOf("/kanal4") != -1)
  {   
  irsend.sendNEC(kanal1);  // Send a raw data capture at 38kHz.
  delay(150);
  irsend.sendNEC(kanal4); 
  Serial.println("TV 14 tuşlandı.");
  delay(150);
  }


else if(req.indexOf("/kanal5") != -1)
  {   
  irsend.sendNEC(kanal1);  // Send a raw data capture at 38kHz.
  delay(150);
  irsend.sendNEC(kanal5); 
  Serial.println("TV 15 tuşlandı.");
 delay(150);
  }

else if(req.indexOf("/kanal6") != -1)
  {   
  irsend.sendNEC(kanal1);  // Send a raw data capture at 38kHz.
  delay(150);
  irsend.sendNEC(kanal6); 
  Serial.println("TV 16 tuşlandı.");
 delay(150);
  }


else if(req.indexOf("/kanal7") != -1)
  {   
  irsend.sendNEC(kanal1);  // Send a raw data capture at 38kHz.
  delay(150);
  irsend.sendNEC(kanal7); 
  Serial.println("TV 17 tuşlandı.");
   delay(150);
  }


else if(req.indexOf("/kanal18") != -1)
  {   
  irsend.sendNEC(kanal1);  // Send a raw data capture at 38kHz.
  delay(150);
  irsend.sendNEC(kanal8); 
  Serial.println("TV 18 tuşlandı.");
   delay(50);
  }

else if(req.indexOf("/kanal19") != -1)
  {   
  irsend.sendNEC(kanal1);  // Send a raw data capture at 38kHz.
  delay(150);
  irsend.sendNEC(kanal9); 
  Serial.println("TV 19 tuşlandı.");
   delay(50);
  }


else if(req.indexOf("/kanal20") != -1)
  {   
  irsend.sendNEC(kanal2);  // Send a raw data capture at 38kHz.
  delay(150);
  irsend.sendNEC(kanal0); 
  Serial.println("TV 20 tuşlandı.");
   delay(50);
  }


  else if(req.indexOf("/netflixAc") != -1)
  { 
    irsend.sendNEC(tvon);  // Send a raw data capture at 38kHz.
  Serial.println("TV kapandı..");
   delay(5000);  
    irsend.sendNEC(tvon);  // Send a raw data capture at 38kHz.
  Serial.println("TV Acıldı..");
   delay(17000);  
   irsend.sendNEC(ayarlar);  // Send a raw data capture at 38kHz.
  delay(3550);
  irsend.sendNEC(asagi); 
  delay(550);
  irsend.sendNEC(asagi); 
  delay(550);
  irsend.sendNEC(sagOK); 
  delay(550);
  for (int i=0; i<6; i++){
  irsend.sendNEC(kanal0); 
  delay(650);}
   
  irsend.sendNEC(yukari); 
  delay(450);
  irsend.sendNEC(sagOK); 
  delay(650);

  for (int i=0; i<4; i++){
  irsend.sendNEC(asagi); 
  delay(850);}

  irsend.sendNEC(sagOK); 
  delay(450);
  irsend.sendNEC(cikis); 

  
  
  Serial.println("netflix Açıldı tuşlandı.");
   delay(150);
  }


   else if(req.indexOf("/netflixKapat") != -1)
  {   
     irsend.sendNEC(tvon);  // Send a raw data capture at 38kHz.
  Serial.println("TV kapandı..");
   delay(5000);  
    irsend.sendNEC(tvon);  // Send a raw data capture at 38kHz.
  Serial.println("TV Acıldı..");
   delay(17000);  
   irsend.sendNEC(ayarlar);  // Send a raw data capture at 38kHz.
  delay(3550);
  irsend.sendNEC(asagi); 
  delay(450);
  irsend.sendNEC(asagi); 
  delay(450);
  irsend.sendNEC(sagOK); 
  delay(550);
  for (int i=0; i<6; i++){
  irsend.sendNEC(kanal0); 
  delay(650);}
   
  irsend.sendNEC(yukari); 
  delay(450);
  irsend.sendNEC(sagOK); 
  delay(650);

  for (int i=0; i<4; i++){
  irsend.sendNEC(asagi); 
  delay(850);}

  irsend.sendNEC(sagOK); 
  delay(450);
  irsend.sendNEC(cikis); 

  
  
  Serial.println("netflix kapat tuşlandı.");
   delay(50);
  }


   else if(req.indexOf("/oyunuAc") != -1)
  {  
      irsend.sendNEC(tvon);  // Send a raw data capture at 38kHz.
  Serial.println("TV kapandı..");
   delay(5000);  
    irsend.sendNEC(tvon);  // Send a raw data capture at 38kHz.
  Serial.println("TV Acıldı..");
   delay(17000);  
   irsend.sendNEC(ayarlar);  // Send a raw data capture at 38kHz.
  delay(3550);
  irsend.sendNEC(asagi); 
  delay(450);
  irsend.sendNEC(asagi); 
  delay(450);
  irsend.sendNEC(sagOK); 
  delay(550);
  for (int i=0; i<6; i++){
  irsend.sendNEC(kanal0); 
  delay(650);}
   
  irsend.sendNEC(yukari); 
  delay(450);
  irsend.sendNEC(sagOK); 
  delay(650);

  for (int i=0; i<6; i++){
  irsend.sendNEC(asagi); 
  delay(850);}

  irsend.sendNEC(sagOK); 
  delay(450);
  irsend.sendNEC(cikis); 

  
  
  Serial.println("oyun Açıldı tuşlandı.");
   delay(50);
  }



   else if(req.indexOf("/oyunuKapat") != -1)
  {   
   irsend.sendNEC(tvon);  // Send a raw data capture at 38kHz.
  Serial.println("TV kapandı..");
   delay(5000);  
    irsend.sendNEC(tvon);  // Send a raw data capture at 38kHz.
  Serial.println("TV Acıldı..");
   delay(17000);  
   irsend.sendNEC(ayarlar);  // Send a raw data capture at 38kHz.
  delay(3550);
  irsend.sendNEC(asagi); 
  delay(450);
  irsend.sendNEC(asagi); 
  delay(450);
  irsend.sendNEC(sagOK); 
  delay(550);
  for (int i=0; i<6; i++){
  irsend.sendNEC(kanal0); 
  delay(650);}
   
  irsend.sendNEC(yukari); 
  delay(450);
  irsend.sendNEC(sagOK); 
  delay(650);

  for (int i=0; i<6; i++){
  irsend.sendNEC(asagi); 
  delay(850);}

  irsend.sendNEC(sagOK); 
  delay(450);
  irsend.sendNEC(cikis); 

  
  
  Serial.println("oyun kapatıldı tuşlandı.");
   delay(50);
  }






else if(req.indexOf("/Home") != -1)
  {   
  irsend.sendNEC(Home);  // Send a raw data capture at 38kHz.
  
  Serial.println("TV Home tuşuna basıldı.");
   delay(50);
  }




  else if(req.indexOf("/ayarlar") != -1)
  {   
  irsend.sendNEC(ayarlar);  // Send a raw data capture at 38kHz.
  Serial.println("TV ayarlarına girildi");
   delay(50);
  }

 else if(req.indexOf("/back") != -1)
  {   
  irsend.sendNEC(back);  // Send a raw data capture at 38kHz.
  Serial.println("TV geri tuşlandı.");
   delay(50);
  }
  

 else if(req.indexOf("/cikis") != -1)
  {   
  irsend.sendNEC(cikis);  // Send a raw data capture at 38kHz.
  Serial.println("TV çıkıs tuşlandı.");
   delay(50);
  }

else if(req.indexOf("/kirmizi") != -1)
  {   
  irsend.sendNEC(kirmizi);  // Send a raw data capture at 38kHz.
  Serial.println("TV kirmizi button tuşlandı.");
   delay(50);
  }

else if(req.indexOf("/yesil") != -1)
  {   
  irsend.sendNEC(cikis);  // Send a raw data capture at 38kHz.
  Serial.println("TV yeşil button tuşlandı.");
   delay(50);
  }

else if(req.indexOf("/sari") != -1)
  {   
  irsend.sendNEC(sari);  // Send a raw data capture at 38kHz.
  Serial.println("TV sari button tuşlandı.");
   delay(50);
  }

else if(req.indexOf("/mavi") != -1)
  {   
  irsend.sendNEC(mavi);  // Send a raw data capture at 38kHz.
  Serial.println("TV mavi button tuşlandı.");
   delay(50);
  }

else if(req.indexOf("/input") != -1)
  {   
  irsend.sendNEC(input);  // Send a raw data capture at 38kHz.
  Serial.println("TV input button tuşlandı.");
   delay(50);
  }

  
else if(req.indexOf("/kanallistesi") != -1)
  {   
  irsend.sendNEC(kanallistesi);  // Send a raw data capture at 38kHz.
  Serial.println("TV Kanal listesi buttonu tuşlandı.");
   delay(50);
  }




else if(req.indexOf("/sagOK") != -1)
  {   
  irsend.sendNEC(sagOK);  // Send a raw data capture at 38kHz.
  Serial.println("TV sagOK buttonu tuşlandı.");
   delay(50);
  }


  else if(req.indexOf("/solOK") != -1)
  {   
  irsend.sendNEC(solOK);  // Send a raw data capture at 38kHz.
  Serial.println("TV solOK buttonu tuşlandı.");
   delay(50);
  }


  else if(req.indexOf("/yukari") != -1)
  {   
  irsend.sendNEC(yukari);  // Send a raw data capture at 38kHz.
  Serial.println("TV yukari buttonu tuşlandı.");
   delay(50);
  }

else if(req.indexOf("/yukari2") != -1)
  {
    for (int i=0; i<2; i++){
  irsend.sendNEC(yukari2, 32); 
  Serial.println("yukarı tuşuna 2 kez basıldı.");
  delay(450);}
    
 
  }


 else if(req.indexOf("/asagi") != -1)
  {   
  irsend.sendNEC(asagi);  // Send a raw data capture at 38kHz.
  Serial.println("TV asagi buttonu tuşlandı.");
   delay(50);
  }

else if(req.indexOf("/asagi2") != -1)
  {   
  irsend.sendNEC(asagi2);  // Send a raw data capture at 38kHz.
  delay(250);
  irsend.sendNEC(asagi2);  // Send a raw data capture at 38kHz.
  Serial.println("TV asagi buttonu 2 tuşlandı.");
   delay(150);
  }





/////////////////////// KLİMA KONTROL ///////////////////////////////////////////////////////



else if(req.indexOf("/klimaAc") != -1)
  {   
  irsend.sendRaw(klimaAc, 211, 38);  // Send a raw data capture at 38kHz.
  Serial.println("klima açıldı.");
   delay(50);
  }

else if(req.indexOf("/klimaKapat") != -1)
  {   
  irsend.sendRaw(klimaKapat, 211, 38);  // Send a raw data capture at 38kHz.
  Serial.println("klima kapatıldı.");
   delay(50);
  }

else if(req.indexOf("/derece25fan2") != -1)
  {   
  irsend.sendRaw(derece25fan2, 211, 38);  // Send a raw data capture at 38kHz.
  Serial.println("25derece fan2.");
   delay(50);
  }

else if(req.indexOf("/derece20fan3") != -1)
  {   
  irsend.sendRaw(derece20fan3, 211, 38);  // Send a raw data capture at 38kHz.
  Serial.println("20derece fan2.");
   delay(50);
  }



else if(req.indexOf("/derece18fan3") != -1)
  {   
  irsend.sendRaw(derece18fan3, 211, 38);  // Send a raw data capture at 38kHz.
  Serial.println("18 derece fan3");
   delay(50);
  }

  else if(req.indexOf("/iyonizerAc") != -1)
  {   
  irsend.sendRaw(iyonizerAc, 211, 38);  // Send a raw data capture at 38kHz.
  Serial.println("iyonizer açıldı.");
   delay(50);
  }

else if(req.indexOf("/iyonizerKapat") != -1)
  {   
  irsend.sendRaw(iyonizerKapat, 211, 38);  // Send a raw data capture at 38kHz.
  Serial.println("iyonizer kapatıldı.");
   delay(50);
  }


else if(req.indexOf("/fankademe1") != -1)
  {   
  irsend.sendRaw(fankademe1, 211, 38);  // Send a raw data capture at 38kHz.
  Serial.println("fan kademe 1"); 
   delay(50);
  }

else if(req.indexOf("/fankademe2") != -1)
  {   
  irsend.sendRaw(fankademe2, 211, 38);  // Send a raw data capture at 38kHz.
  Serial.println("fan kademe 2."); 
   delay(50);
  }


else if(req.indexOf("/fankademe3") != -1)
  {   
  irsend.sendRaw(fankademe3, 211, 38);  // Send a raw data capture at 38kHz.
  Serial.println("fan kademe 3."); 
   delay(50);
  }



else if(req.indexOf("/fanotomatik") != -1)
  {   
  irsend.sendRaw(fanotomatik, 211, 38);  // Send a raw data capture at 38kHz.
  Serial.println("fan kademe Otomatik"); 
   delay(50);
  }

else if(req.indexOf("/swingAc") != -1)
  {   
  irsend.sendRaw(swingAc, 211, 38);  // Send a raw data capture at 38kHz.
  Serial.println("pervane açıldı"); 
   delay(50);
  }

else if(req.indexOf("/swingKapat") != -1)
  {   
  irsend.sendRaw(swingKapat, 211, 38);  // Send a raw data capture at 38kHz.
  Serial.println("pervane kapatıldı"); 
   delay(50);
  }

else if(req.indexOf("/temizleme") != -1)
  {   
  irsend.sendRaw(kendiniTemizleme, 211, 38);  // Send a raw data capture at 38kHz.
  Serial.println("klima temizleniyor bekleyiniz...."); 
   delay(50);
  }

else if(req.indexOf("/acma1Saat") != -1)
  {   
  irsend.sendRaw(acma1Saat, 211, 38);  // Send a raw data capture at 38kHz.
  Serial.println("bir saat sonra klima acılacak..."); 
   delay(50);
  }


  else if(req.indexOf("/acma2Saat") != -1)
  {   
  irsend.sendRaw(acma2Saat, 211, 38);  // Send a raw data capture at 38kHz.
  Serial.println("2 saat sonra klima acılacak..."); 
   delay(50);
  }

 else if(req.indexOf("/acma3Saat") != -1)
  {   
  irsend.sendRaw(acma3Saat, 211, 38);  // Send a raw data capture at 38kHz.
  Serial.println("3 saat sonra klima acılacak..."); 
   delay(50);
  }

else if(req.indexOf("/acma4Saat") != -1)
  {   
  irsend.sendRaw(acma4Saat, 211, 38);  // Send a raw data capture at 38kHz.
  Serial.println("4 saat sonra klima acılacak..."); 
   delay(50);
  }


  else if(req.indexOf("/kapanma2Saat") != -1)
  {   
  irsend.sendRaw(kapanma2Saat, 211, 38);  // Send a raw data capture at 38kHz.
  Serial.println("2 saat sonra klima kapatılacak..."); 
   delay(50);
  }


  else if(req.indexOf("/kapanma3Saat") != -1)
  {   
  irsend.sendRaw(kapanma3Saat, 211, 38);  // Send a raw data capture at 38kHz.
  Serial.println("3 saat sonra klima kapatılacak..."); 
   delay(50);
  }

else if(req.indexOf("/kapanma4Saat") != -1)
  {   
  irsend.sendRaw(kapanma4Saat, 211, 38);  // Send a raw data capture at 38kHz.
  Serial.println("4 saat sonra klima kapatılacak..."); 
   delay(50);
  }



else if(req.indexOf("/cancel") != -1)
  {   
  irsend.sendRaw(cancel, 211, 38);  // Send a raw data capture at 38kHz.
  Serial.println("Ayar silindi..."); 
   delay(50);
  }
  /////////////////////////////////elektirikli süpürge/////////////////////////

else if(req.indexOf("/SupAc") != -1)
  {   
  irsend.sendRaw(SupAc, 25, 38);  // Send a raw data capture at 38kHz.
  Serial.println("supurge açıldı...."); 
   delay(50);
  }
  else if(req.indexOf("/Supkapat") != -1)
  {   
  irsend.sendRaw(Supkapat, 25, 38);  // Send a raw data capture at 38kHz.
  Serial.println("supurge kapatıldı...."); 
   delay(50);
  }
  else if(req.indexOf("/supKademe1") != -1)
  {   
  irsend.sendRaw(supKademe1, 25, 38);  // Send a raw data capture at 38kHz.
  Serial.println("supurge supKademe1...."); 
   delay(50);
  }
  else if(req.indexOf("/supKademe2") != -1)
  {   
  irsend.sendRaw(supKademe2, 25, 38);  // Send a raw data capture at 38kHz.
  Serial.println("supurge supKademe2...."); 
   delay(50);
  }
  else if(req.indexOf("/supKademe3") != -1)
  {   
  irsend.sendRaw(supKademe3, 25, 38);  // Send a raw data capture at 38kHz.
  Serial.println("supurge supKademe3...."); 
   delay(50);
  }
  else if(req.indexOf("/supKademe4") != -1)
  {   
  irsend.sendRaw(supKademe4, 25, 38);  // Send a raw data capture at 38kHz.
  Serial.println("supurge supKademe4...."); 
   delay(50);
  }
  else if(req.indexOf("/supKademe5") != -1)
  {   
  irsend.sendRaw(supKademe5, 25, 38);  // Send a raw data capture at 38kHz.
  Serial.println("supurge supKademe5...."); 
   delay(50);
  }
   else if(req.indexOf("/supionizer") != -1)
  {   
  irsend.sendRaw(supionizer, 25, 38);  // Send a raw data capture at 38kHz.
  Serial.println("supurge ionizer açıldı....."); 
   delay(50);
  }
   else if(req.indexOf("/yikamaAc") != -1)
  {   
  irsend.sendRaw(yikamaAc, 25, 38);  // Send a raw data capture at 38kHz.
  Serial.println("supurge yikama açıldı....."); 
   delay(50);
  }
 else if(req.indexOf("/yikamaKapat") != -1)
  {   
  irsend.sendRaw(yikamaKapat, 25, 38);  // Send a raw data capture at 38kHz.
  Serial.println("supurge yikama kapatıldı....."); 
   delay(50);
  }


  
  String web = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
  web += "<html>\r\n";
  web += "<body>\r\n";
  web += "<h1>LED Status</h1>\r\n";
  web += "<p>\r\n";
  if(status_led==1)
      web += "LED On\r\n";
  else
      web += "LED Off\r\n";
  web += "</p>\r\n";
  web += "</p>\r\n";
  web += "<a href=\"/seskisiliyor\">\r\n";
  web += "<button>LED On</button >\r\n";
  web += "</a>\r\n";
  web += "</p>\r\n";
  
  web += "<a href=\"/ledoff\">\r\n";
  web += "<button>LED Off</button >\r\n";
  web += "</a>\r\n";
  
  web += "</body>\r\n";
  web += "</html>\r\n";
  
  client.print(web);

}
