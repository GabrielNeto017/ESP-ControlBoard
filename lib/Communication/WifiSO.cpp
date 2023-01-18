//Bibliotecas


#include <Arduino.h>
#include <WifiSO.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <DNSServer.h>
#include <WebServer.h>
#include "nvs_flash.h"
#include <Flash.h>
#include <WiFiServer.h>
#include <WiFiManager.h>

#include <AsyncTCP.h>
#include <WiFi.h>
#include <WiFiManager.h>
#include <PinDefinition.h>
#include <Queue.h>
#include<CommunicationHandler.h>

//WiFiManager wifi;

//WiFiServer wifiServer(502);

AsyncServer *server = new AsyncServer(502); // start listening on tcp port 502

WiFiServer wifiServer(502);
WiFiManager wifiManager;
//WiFiClient client;
HTTPClient http;
static std::vector<AsyncClient *> clients; // a list to hold all clients
//AsyncClient _client;
AsyncClient* client2;

bool cliente = false;
void configModeCallback(WiFiManager *myWiFiManager);
void saveConfigCallback();




static void handleError(void *arg, AsyncClient *client, int8_t error)
{
  //Serial.printf("\n connection error %s from client %s \n", client->errorToString(error), client->remoteIP().toString().c_str());
}

static void handleData(void* arg, AsyncClient* client, void *data, size_t len) {

  //Serial.printf("\n data received from client %s \n", client->remoteIP().toString().c_str());


  // reply to client
 
  client2 = client;
 
  char* pointer = static_cast<char*>(data);  //converte o ponteiro tipo *void para ponteiro tipo char



  if(!strncmp(pointer, "*IDN?", 5))
  {
    //DataRxForm ReceivedData2;
    //strcpy(ReceivedData2.Message,"*IDN?");
    //ReceivedData2.ID=WIFI;
    //ReceivedData2.client= *client;
    //Write_QueueRx(ReceivedData2);

    String NET;

    NET.clear();
    NET.concat(Company_Name);
    NET.concat(",");
    NET.concat(Product_Name);
    NET.concat(",");
    NET.concat(Serial_Number);
    NET.concat(",");
    NET.concat(Software_Version);
    NET.concat("\n");

    char reply[NET.length()];
    strcpy(reply,NET.c_str());
    client2->add(reply, strlen(reply));
    client2->send();
  }

 else{
    DataRxForm ReceivedData2;
    strcpy(ReceivedData2.Message,pointer);
    //Serial.printf(ReceivedData2.Message);
    ReceivedData2.ID=WIFI;
    ReceivedData2.client = 0;
    Write_QueueRx(ReceivedData2);
  }
  
}






static void handleDisconnect(void *arg, AsyncClient *client)
{
  //Serial.printf("\n client %s disconnected \n", client->remoteIP().toString().c_str());
  cliente = false;
}

static void handleTimeOut(void *arg, AsyncClient *client, uint32_t time)
{
  //Serial.printf("\n client ACK timeout ip: %s \n", client->remoteIP().toString().c_str());
}

/* server events */
static void handleNewClient(void *arg, AsyncClient *client)
{
  //Serial.printf("\n new client has been connected to server, ip: %s", client->remoteIP().toString().c_str());


  // add to list
  //_client = *client;

  //register events
  client->onData(&handleData, NULL);
  client->onError(&handleError, NULL);
  client->onDisconnect(&handleDisconnect, NULL);
  client->onTimeout(&handleTimeOut, NULL);
 
}

void Wifi_Init()
{


  //callback para quando entra em modo de configuração AP
  wifiManager.setAPCallback(configModeCallback);
  //callback para quando se conecta em uma rede, ou seja, quando passa a trabalhar em modo estação
  wifiManager.setSaveConfigCallback(saveConfigCallback);

  if (ReadFlash("IP") != "fail")
  {
    IPAddress _sta_static_ip;
    IPAddress _sta_static_gw;
    IPAddress _sta_static_sn;

    _sta_static_ip.fromString(ReadFlash("IP"));
    _sta_static_gw.fromString(ReadFlash("GW"));
    _sta_static_sn.fromString(ReadFlash("SN"));

    wifiManager.setSTAStaticIPConfig(_sta_static_ip, _sta_static_gw, _sta_static_sn);
  }
}


void InitializeWifiAP(void *pvParameters) //Core 1 communication process
{
  while(true)
  {

  //AsyncServer *server = new AsyncServer(502); // start listening on tcp port 502
  //Se o botão for pressionado
  if (digitalRead(21) == HIGH)
  {

      Serial.println("Abertura Portal"); //Abre o portal
      digitalWrite(16, HIGH);            //Acende LED Vermelho
      digitalWrite(17, LOW);
      wifiManager.resetSettings(); //Apaga rede salva anteriormente
      if (!wifiManager.startConfigPortal())
      {                                      //Nome da Rede e Senha gerada pela ESP
        //Serial.println("Falha ao conectar"); //Se caso não conectar na rede mostra mensagem de falha
        delay(2000);
        ESP.restart(); //Reinicia ESP após não conseguir conexão na rede
      }
      else
      { //Se caso conectar
        //Serial.println("Conectado na Rede!!!");
        ESP.restart(); //Reinicia ESP após conseguir conexão na rede
      }
  }


  

  if (WiFi.status() == WL_CONNECTED)
  { //Se conectado na rede
    //client.send();
    //client.freeable();
    //client.canSend();
    //AsyncServer *server = new AsyncServer(502); 
    //server->onClient(&handleData, NULL);
    //server->onClient(&handleNewClient2, server);
    
  }

  else
  {                        //se não conectado na rede
    wifiManager.autoConnect();                  //Função para se autoconectar na rede
    server->onClient(&handleNewClient, server);
    server->begin();
  }
  

   

  vTaskDelay(pdMS_TO_TICKS(1));
  
  }
}
//callback que indica que o ESP entrou no modo AP
void configModeCallback(WiFiManager *myWiFiManager)
{
  //Serial.println("Entrou no modo de configuração");
  //Serial.println(WiFi.softAPIP());                      //imprime o IP do AP
  //Serial.println(myWiFiManager->getConfigPortalSSID()); //imprime o SSID criado da rede
}

//Callback que indica o save de uma nova rede para se conectar (modo estação)
void saveConfigCallback()
{
  //Serial.println("Configuração salva");
}




  
void ReplyToClient(String Response)
{

  String Message = Response;
  char reply2[Message.length()];
  strcpy(reply2,Message.c_str());

 if (client2->space() > 32 && client2->canSend())
    {
      client2->add(reply2, strlen(reply2));
      client2->send();
      //client2->stop();
    }
 
}


