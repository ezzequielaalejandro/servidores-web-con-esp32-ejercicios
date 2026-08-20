#include <Arduino.h>

#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "CESJT";
const char* password = "itisjtsmg";

WebServer server(80);

int display1 [7] = {13,12,14,27,26,25,33};
int display2 [7] = {15,2,4,16,17,5,18};

int animacion [10] [7] = {
    {1,1,1,1,1,1,0}, //0
    {0,1,1,0,0,0,0}, //1
    {1,1,0,1,1,0,1}, //2
    {1,1,1,1,0,0,1}, //3
    {0,1,1,0,0,1,1}, //4
    {1,0,1,1,0,1,1}, //5
    {1,0,1,1,1,1,1}, //6
    {1,1,1,0,0,0,0}, //7
    {1,1,1,1,1,1,1}, //8
    {1,1,1,0,0,1,1}, //9
   //a,b,c,d,e,f,g  
};

volatile int numero = 0;
volatile int display = 0;

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
    .boton { width: 120px; height: 45px; background-color: rgb(255, 255, 255); color: black; border: 2px solid black; border-radius: 80px; font-size: 14px; font-weight: bold; cursor: pointer;} 
    .teclado {width: 90px; height: 30px; background-color: rgb(197, 197, 216); color: rgb(255, 255, 255); border: 5px; border-radius: 50px; font-size: 20px; cursor: pointer; margin-top: 15px; margin-left: 15px;}

  </style>
</head>
<body>
  <h1 class='titulo'>Reflejo y control de 7 segmentos</h1>

  <p><a href='/7seg1'><button class='boton'>Display 1</button></a></p>
  <p><a href='/7seg2'><button class='boton'>Display 2</button></a></p>

  <p><a href= '/1'><button class='teclado'>1</a></p>
  <p><a href= '/2'><button class='teclado'>2</a></p>
  <p><a href= '/3'><button class='teclado'>3</a></p>

  <p><a href= '/4'><button class='teclado'>4</a></p>
  <p><a href= '/5'><button class='teclado'>5</a></p>
  <p><a href= '/6'><button class='teclado'>6</a></p>

  <p><a href= '/7'><button class='teclado'>7</a></p>
  <p><a href= '/8'><button class='teclado'>8</a></p>
  <p><a href= '/9'><button class='teclado'>9</a></p>
  
  <p><a href= '/0'><button class='teclado'>0</a></p>

</body>
</html>
)rawliteral";


void setup() {
  Serial.begin(115200);
  
  for(int i = 0; i < 7; i++){
    pinMode(display1[i], OUTPUT);
  }
  
  for(int i = 0; i < 7; i++){
    pinMode(display2[i], OUTPUT);
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

  server.on("/",[](){
    server.send(200, "text/html", pagina_template);
  });
  server.on("/7seg1",[](){
    display=1;
    server.sendHeader("Location", "/"); // dice que la página se vaya a /
    server.send(302, "text/plain", ""); // 302 dice que el /toggle no está y que vaya a la locación de antes

  });
  
  server.on("/7seg2",[](){
    display=2;
    server.sendHeader("Location", "/"); // dice que la página se vaya a /
    server.send(302, "text/plain", ""); // 302 dice que el /toggle no está y que vaya a la locación de antes

  });
  
  server.on("/0",[](){
    numero=0;
    server.sendHeader("Location", "/"); // dice que la página se vaya a /
    server.send(302, "text/plain", ""); // 302 dice que el /toggle no está y que vaya a la locación de antes

  });
  server.on("/1",[](){
    numero=1;
    server.sendHeader("Location", "/"); // dice que la página se vaya a /
    server.send(302, "text/plain", ""); // 302 dice que el /toggle no está y que vaya a la locación de antes

  });
  server.on("/2",[](){
    numero=2;
    server.sendHeader("Location", "/"); // dice que la página se vaya a /
    server.send(302, "text/plain", ""); // 302 dice que el /toggle no está y que vaya a la locación de antes

  });
  server.on("/3",[](){
    numero=3;
    server.sendHeader("Location", "/"); // dice que la página se vaya a /
    server.send(302, "text/plain", ""); // 302 dice que el /toggle no está y que vaya a la locación de antes

  });
  server.on("/4",[](){
    numero=4;
    server.sendHeader("Location", "/"); // dice que la página se vaya a /
    server.send(302, "text/plain", ""); // 302 dice que el /toggle no está y que vaya a la locación de antes

  });
  server.on("/5",[](){
    numero=5;
    server.sendHeader("Location", "/"); // dice que la página se vaya a /
    server.send(302, "text/plain", ""); // 302 dice que el /toggle no está y que vaya a la locación de antes

  });
  server.on("/6",[](){
    numero=6;
    server.sendHeader("Location", "/"); // dice que la página se vaya a /
    server.send(302, "text/plain", ""); // 302 dice que el /toggle no está y que vaya a la locación de antes

  });
  server.on("/7",[](){
    numero=7;
    server.sendHeader("Location", "/"); // dice que la página se vaya a /
    server.send(302, "text/plain", ""); // 302 dice que el /toggle no está y que vaya a la locación de antes

  });
  server.on("/8",[](){
    numero=8;
    server.sendHeader("Location", "/"); // dice que la página se vaya a /
    server.send(302, "text/plain", ""); // 302 dice que el /toggle no está y que vaya a la locación de antes

  });
  server.on("/9",[](){
    numero=9;
    server.sendHeader("Location", "/"); // dice que la página se vaya a /
    server.send(302, "text/plain", ""); // 302 dice que el /toggle no está y que vaya a la locación de antes

  });

  server.begin();
}

void loop() {
  server.handleClient();

     switch (display){

    case 1:
        for(int i = 0; i < 7; i++){
            digitalWrite(display2 [i], LOW);
            digitalWrite(display1 [i], animacion [numero] [i]);
        }
        break;

    case 2:
        for(int i = 0; i < 7; i++){
            digitalWrite(display1 [i], LOW);
            digitalWrite(display2 [i], animacion [numero] [i]);
        }
        break;
    
    default:
        break;
    }

}