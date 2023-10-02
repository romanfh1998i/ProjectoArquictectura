
#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
#include <ESP8266WebServer.h>




const char* ssid = "Galaxy S10f06f";
const char* password = "fxae3577";// Reemplaza con la contraseña de tu red Wi-Fi
SoftwareSerial espSerial(2, 3); // RX, TX (puertos de software serial)
WiFiServer server(80);
String doorStatus = "Cerrada"; // Estado inicial de la puerta

void setup() {
  Serial.begin(9600);
  espSerial.begin(9600);   // Inicia la comunicación serial con el Arduino Uno

  Serial.println("antes delay");
  delay(10);
  Serial.println("pasando credenciales");
  // Conectar a la red Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {

    delay(1000);
    Serial.println("Conectando a WiFi...");
  }
  Serial.println("Conexión exitosa a Wi-Fi");
  Serial.print("Dirección IP: ");
  Serial.println(WiFi.localIP());

  server.begin();
  Serial.println("Servidor web iniciado");
}

void loop() {
  WiFiClient client = server.accept();
  if (client) {
    Serial.println("Nuevo cliente conectado.");
    String currentLine = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        if (c == '\n') {
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            String response = "<!DOCTYPE html><html><body>";
            response += "<h1>Control de Puerta</h1>";
            response += "<p>Estado de la Puerta: " + doorStatus + "</p>";
            response += "<p><a href=\"/abrir\">Abrir Puerta</a></p>";
            response += "<p><a href=\"/cerrar\">Cerrar Puerta</a></p>";
            response += "</body></html>";
            
            client.println(response);
            client.println();
            break;
          }
          else {
            currentLine = "";
          }
        }
        else if (c != '\r') {
          currentLine += c;
        }
        
        if (currentLine.endsWith("GET /abrir")) {
          openDoor();
          doorStatus = "Abierta";
          // Envía el comando al Arduino para abrir la puerta
          Serial.write('O');
        }
        if (currentLine.endsWith("GET /cerrar")) {
          closeDoor();
          doorStatus = "Cerrada";
          // Envía el comando al Arduino para cerrar la puerta
          Serial.write('C');
        }
      }
    }
    delay(10);
    client.stop();
    Serial.println("Cliente desconectado.");
  }
}

void openDoor() {
  // Agrega aquí el código necesario para abrir la puerta
  espSerial.println("O"); // mandar a abrir la puera
  Serial.println("Abriendo la puerta...");
  
}

void closeDoor() {
  // Agrega aquí el código necesario para cerrar la puerta
  espSerial.println("C"); // mandar a cerrar la puera
 
  Serial.println("Cerrando la puerta...");
}