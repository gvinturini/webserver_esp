#include "WiFi.h"
#include "ESPAsyncWebServer.h"

const char* ssid = "Giovini";
const char* password = "navi2517";

char dados[] = "";
size_t tam;

AsyncWebServer server(80);

void array_to_string(byte array[], unsigned int len, char buffer[]);

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.println("Conectando ao WiFi...");
  }

  Serial.println(WiFi.localIP());

  server.on(
    "/post",
    HTTP_POST,
    [](AsyncWebServerRequest * request){},
    NULL,
    [](AsyncWebServerRequest * request, uint8_t *data, size_t len, size_t index, size_t total) {
      
      for (size_t i = 0; i < len; i++) {
        Serial.write(data[i]);
        dados[i] = (char)data[i];        
      }
      tam = len;
      Serial.println();
      //Serial.println(dados);
 
      request->send(200);
  });

   server.on("/get", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", "Hello World");
  });
 
  server.begin();
}

void loop() {
  delay(2000);
  Serial.println(tam);
  Serial.println(dados);
}
