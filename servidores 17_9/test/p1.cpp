#include <Arduino.h>

#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "CESJT";
const char* password = "itisjtsmg";

int ventilador = 1;
int apagado=0;
int baja=50;
int media=150;
int alta=225;

WebServer server(80);


const char pagina_template[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="es">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">

    <title>CONTROL DE VENTILADOR</title>

    <style>

        body {
            background-color: #ecf0f1;
            text-align: center;
        }

        h1 {
            font-family: "Arial Black", Arial, sans-serif;
            color: #2c3e50;
        }

        .boton {
            width: 180px;
            height: 60px;
            border: 1px solid black;
            border-radius: 15px;
            display: block;
            margin: 10px auto;
            font-size: 18px;
            color: white;
            cursor: pointer;
        }

        .off {
            background-color: #c0392b;
        }

        .low {
            background-color: #2980b9;
        }

        .medium {
            background-color: #27ae60;
        }

        .high {
            background-color: #f39c12;
        }

    </style>

</head>

<body>

    <h1>CONTROL DE VENTILADOR</h1>

    <span>
        Velocidad Actual: <strong>Apagado</strong>
    </span>

    <br><br>

    <button class="boton off">
        APAGADO
    </button>

    <button class="boton low">
        BAJA
    </button>

    <button class="boton medium">
        MEDIA
    </button>

    <button class="boton high">
        ALTA
    </button>

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

  server.on("/apagado", []() {
    String pagina = pagina_template;

    pagina.replace("Modo", "apagado");
    digitalWrite(ventilador,LOW);
    

     });
      server.on("/baja", []() {
    String pagina = pagina_template;
    pagina.replace("Modo", "baja");
    
    
     });
 }
       void loop(){

       }