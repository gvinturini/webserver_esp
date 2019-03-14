//----- Bibliotecas necessárias ------
#include "WiFi.h"
#include "ESPAsyncWebServer.h"

//------ Variáveis Globais ------

//Variáveis para a conexão WiFi
const char* ssid = "Giovini";
const char* password = "navi2517";

//Variáveis para tratamento dos dados vindos do POST
char dados[] = "";
size_t tam;

//Declaração do WebServer
AsyncWebServer server(80);

// Set your Static IP address
IPAddress local_IP(192, 168, 1, 184);
// Set your Gateway IP address
IPAddress gateway(192, 168, 1, 1);

IPAddress subnet(255, 255, 0, 0);

void setup() {
  //Inicializando o serial
  Serial.begin(115200);

  //Inicializando o WiFi
  
  if (!WiFi.config(local_IP, gateway, subnet)) {
    Serial.println("STA Failed to configure");
  }
  WiFi.begin(ssid, password);
  //Primeira conexão com o WiFi
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.println("Conectando ao WiFi...");
  }

  //Printa o IP no monitor serial
  Serial.println(WiFi.localIP());

  //Cria o método POST
  server.on(
    "/post", //URL para acessar o POST
    HTTP_POST,
    [](AsyncWebServerRequest * request){},
    NULL,
    [](AsyncWebServerRequest * request, uint8_t *data, size_t len, size_t index, size_t total) {
      
      dados[0] = '\0'; //Limpa o array de dados
      
      for (size_t i = 0; i < len; i++) {
        dados[i] = (char)data[i]; //Salva todos os caracteres vindos pelo POST no array       
      }
      tam = len;//Salva o tamanho dos dados vindos do POST em outra variável
 
      request->send(200); //Envia mensagem OK
  });

   //Cria o método GET
   server.on("/get", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", "Hello World"); //Envia "Hello World toda vez que o GET é requisitado
  });
 
  server.begin(); //Inicia o servidor
}

void loop() {
  delay(2000);
  Serial.println(tam); //Printa o tamanho dos dados
  for (size_t i = 0; i< tam; i++){
    Serial.print(dados[i]); //Printa os dados separados por uma linha
  }
  
}
