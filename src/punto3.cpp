#include <Arduino.h>

#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "CESJT";
const char* password = "itisjtsmg";

WebServer server(80);

int rojo = 10;
int amarillo = 12;
int verde = 13;

// pagina
const char pagina_template[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta charset='utf-8'>
  <title>Servidor Web ESP32</title>
  <style>
    body { 
        background-image: url(https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcT7WtTVBRAt5Me8izKHAhcjfimuCnh4_d6koYfmPplaQrqijJRHPuK2Ze7S&s=10); 
        text-align: center; 
        background-attachment: fixed;
    }
    .titulo { 
        font-family: Impact; 
        font-weight: bold;  
        font-size: 45px; 
        color: rgb(252, 0, 248);
        text-decoration: underline; 
    }
    .lento { 
        width: 200px; 
        height: 200px; 
        background-color: red; 
        color: black; 
        border: 3px solid black; 
        border-radius: 100px; 
        font-size: 23px; 
        font-weight: bold; 
        cursor: pointer; 
    }
    .normal { 
        width: 200px; 
        height: 200px; 
        background-color: yellow; 
        color: black; 
        border: 3px solid black; 
        border-radius: 100px; 
        font-size: 23px; 
        font-weight: bold; 
        cursor: pointer; 
    }
    .rapido { 
        width: 200px; 
        height: 200px; 
        background-color: green; 
        color: black; 
        border: 3px solid black; 
        border-radius: 100px; 
        font-size: 23px; 
        font-weight: bold; 
        cursor: pointer; 
    }
    .emergencia { 
        width: 200px; 
        height: 200px; 
        background-color: orange; 
        color: black; 
        border: 3px solid black; 
        border-radius: 100px; 
        font-size: 23px; 
        font-weight: bold; 
        cursor: pointer; 
    }
    .span{
        width: 200px; 
        height: 200px; 
        background-color: white; 
        color: black; 
        border: 3px solid black; 
        border-radius: 100px; 
        font-size: 23px; 
        font-weight: bold; 
        cursor: pointer; 
        padding-left: 15px;
        padding-right: 15px;
        padding-top: 15px;
        padding-bottom: 15px;
        margin-top: 30px;
    }
  </style>
</head>
<body>
  <h1 class='titulo'>SEMAFORO</h1>
  <p><a href='/lento'><button class='lento'>LENTO</button></a></p>
  <p><a href='/normal'><button class='normal'>NORMAL</button></a></p>
  <p><a href='/rapido'><button class='rapido'>RAPIDO</button></a></p>
  <p><a href='/emergencia'><button class='emergencia'>EMERGENCIA</button></a></p>

  <p><a class="span">Modo: __MODO_SEMAFORO__</a></p>
</body>
</html>
)rawliteral";

void setup() {
  Serial.begin(115200);

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

  server.on("/lento", []() {
    String pagina = pagina_template;

    pagina.replace("__MODO_SEMAFORO__", "LENTO");

    digitalWrite(rojo, HIGH);
    digitalWrite(amarillo, LOW);
    digitalWrite(verde, LOW);
    delay(70000);
    digitalWrite(rojo, LOW);
    digitalWrite(amarillo, HIGH);
    digitalWrite(verde, LOW);
    delay(3000);
    digitalWrite(rojo, LOW);
    digitalWrite(amarillo, HIGH);
    digitalWrite(verde, LOW);
    delay(50000);

  });
  server.on("/normal", []() {
    String pagina = pagina_template;

    pagina.replace("__MODO_SEMAFORO__", "NORMAL");

    digitalWrite(rojo, HIGH);
    digitalWrite(amarillo, LOW);
    digitalWrite(verde, LOW);
    delay(45000);
    digitalWrite(rojo, LOW);
    digitalWrite(amarillo, HIGH);
    digitalWrite(verde, LOW);
    delay(2000);
    digitalWrite(rojo, LOW);
    digitalWrite(amarillo, HIGH);
    digitalWrite(verde, LOW);
    delay(65000);
  });
  server.on("/rapido", []() {
    String pagina = pagina_template;

    pagina.replace("__MODO_SEMAFORO__", "RAPIDO");

    digitalWrite(rojo, HIGH);
    digitalWrite(amarillo, LOW);
    digitalWrite(verde, LOW);
    delay(20000);
    digitalWrite(rojo, LOW);
    digitalWrite(amarillo, HIGH);
    digitalWrite(verde, LOW);
    delay(1000);
    digitalWrite(rojo, LOW);
    digitalWrite(amarillo, HIGH);
    digitalWrite(verde, LOW);
    delay(40000);
  });
  server.on("/emergencia", []() {
    String pagina = pagina_template;

    pagina.replace("__MODO_SEMAFORO__", "EMERGENCIA");

    digitalWrite(rojo, LOW);
    digitalWrite(amarillo, LOW);
    digitalWrite(verde, LOW);
    delay(1500);
    digitalWrite(rojo, HIGH);
    digitalWrite(amarillo, HIGH);
    digitalWrite(verde, LOW);
    delay(1500);
    
  });

  server.begin();
}

void loop(){
    server.handleClient();
}