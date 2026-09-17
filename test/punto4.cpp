#include <Arduino.h>

#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "CESJT";
const char* password = "itisjtsmg";

WebServer server(80);

bool cambio = false;
int led = 3;
int potenciometro = 6;
int brillo = 0;

String tension="0", toggle="ON";

// pagina
const char pagina_template[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<meta http-equiv ="refresh" content "2">
  <meta charset='utf-8'>
  <title>Servidor Web ESP32</title>
  <style>
    body { background-color: red; text-align: center; 
    .titulo { font-family: 'Courier', monospace; font-weight: bold; font-style: italic; font-size: 32px; color: white; }
.borde {
  width: 170px;
  height: 100px;
  border: 5px solid black;
  border-radius: 18px;
  background-color: black;
}
.pantalla {
  width: 160px;
  height: 90px;
  border: 1px solid black;
  border-radius: 10px;
  background-color: cyan;
  margin-top: 4px;
  margin-bottom: 4px;
  margin-right: 4px;
  margin-left: 4px;
}
.boton{
 width: 80px;
 height: 45px;
 background-color: yellow;
 border: 2px solid;
 border-radius: 80px;
 text-align: center;
}
    }
  </style>
</head>
<body>
  <h1 class='titulo'>MONITOR DE TENSIÓN</h1>
    <div class="borde">
        <div class="pantalla">
            <span><p>Tension:</p>
            <p> __TEXTO_TENSION__ </p>
            <P>V</P>
            <p><a href='/cambio'><button class='boton'>__TOGGLE__</button></a></p>
        </span>
        </div>   
    </div>


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

  pinMode(led, OUTPUT);
  pinMode(potenciometro, INPUT);

   server.on("/", []() {
    
    String pagina = pagina_template; //hago una variable para no modificar a la original
    
    pagina.replace("__TEXTO_TENSION__", tension);
    pagina.replace("__TOGGLE__", toggle);

    server.send(200, "text/html", pagina);
  });

  server.on("/cambio", []() {
      String pagina = pagina_template;
      
      cambio = !cambio;
      if(cambio = 1){
        analogWrite(led, HIGH);
        toggle="OFF";
    }else{
        if(cambio = 0){
            analogWrite(led, LOW);
            toggle="ON";
        }
    }
  });
  server.begin();
}

void loop(){
    server.handleClient();
    int Lectura = analogRead(potenciometro);
    brillo = map(Lectura, 0, 4095, 0, 255);
    tension = brillo;
    analogWrite(led, brillo);
}