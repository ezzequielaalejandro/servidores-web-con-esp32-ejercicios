#include <Arduino.h>

#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "CESJT";
const char* password = "itisjtsmg";

WebServer server(80);

int leds [5] {5,6,7,8,9};

volatile int animacion = 0;

int anima1 [3] [5] {
   {1,0,0,0,1},
   {0,1,1,1,0},
   {0,0,1,0,0}
  //1,2,3,4,5
};
int anima2 [3] [5] {
   {0,1,0,1,0},
   {1,0,1,0,1},
   {1,1,0,1,0}
  //1,2,3,4,5
};

// pagina
const char pagina_template[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta charset='utf-8'>
  <title>Servidor Web ESP32</title>
  <style>
    body { background-color: black; text-align: center; }
    .titulo { font-family: 'Courier', monospace; font-weight: bold; font-style: italic; font-size: 32px; color: white; }
    .boton { width: 120px; height: 45px; background-color: yellow; color: black; border: 2px solid black; border-radius: 80px; font-size: 14px; font-weight: bold; cursor: pointer; }
  </style>
</head>
<body>
  <h1 class='titulo'>ANIMACION DE LEDS</h1>
  <p><a href='/animacion1'><button class='boton'>ANIMACION 1</button></a></p>
  <p><a href='/animacion2'><button class='boton'>ANIMACION 2</button></a></p>
  <p><a href='/apagado'><button class='boton'>APAGAR</button></a></p>
</body>
</html>
)rawliteral";


void animacion1(){
    for(int i = 0; i <= 3; i ++){
      for(int j = 0; j <= 5; j++){
        digitalWrite(leds [j], anima1 [j] [i]);
      }
    }
  }

void animacion2(){
    for(int i = 0; i <= 3; i ++){
      for(int j = 0; j <= 5; j++){
        digitalWrite(leds [j], anima2 [j] [i]);
      }
    }
  }

void apagado(){
      for(int j = 0; j <= 5; j++){
        digitalWrite(leds [j], LOW);
      }
    }

void setup() {
  Serial.begin(115200);
  for(int i; i <= 5; i++){
    pinMode(leds[i], OUTPUT);
  }

  // conexion al wifi como antes
  Serial.print("Conectando a ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  int timeout = 20; // 20 intentos de 500ms = 10 segundos
  while (WiFi.status() != WL_CONNECTED && timeout > 0) {
    delay(500);
    Serial.print(".");
    timeout--;
  }

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("\nFallo la conexion. Reiniciando...");
    delay(1000);
    ESP.restart();
  }
  Serial.println("\nWiFi conectado!");
  Serial.print("Dirección IP: http://");
  Serial.println(WiFi.localIP());

  server.on("/animacion1",[](){
    animacion=1;
    server.sendHeader("Location", "/"); // dice que la página se vaya a /
    server.send(302, "text/plain", ""); // 302 dice que el /toggle no está y que vaya a la locación de antes

  });
  
  server.on("/animacion2",[](){
    animacion=2;
    server.sendHeader("Location", "/"); // dice que la página se vaya a /
    server.send(302, "text/plain", ""); // 302 dice que el /toggle no está y que vaya a la locación de antes

  });
  
  server.on("/apagado",[](){
    animacion=0;
    server.sendHeader("Location", "/"); // dice que la página se vaya a /
    server.send(302, "text/plain", ""); // 302 dice que el /toggle no está y que vaya a la locación de antes

  });

  server.begin();
}

void loop() {
  server.handleClient();
  if(animacion==1) animacion1();
  if(animacion==2) animacion2();
  if(animacion==0) apagado();

}