#define pinoBuzzer 27
#define pinoBotao 26
#define pinoLed 13
#define pinoTrigger 12
#define pinoEcho 14

#define pinoLedAmarelo 25
#define pinoLedVerde 32

#include "AdafruitIO_WiFi.h"
#include "NewPing.h"

// // Configuração do WiFi
#define WIFI_SSID "fogazzaa"
#define WIFI_PASS "fogazzaa"

// // Autenticação AdafuritIO
#define IO_USERNAME "fogazza"
#define IO_KEY "aio_Ymaa42WF9j7LgA6Lq1DBEqIzdOB5"

bool alarmeAtivo = false;
unsigned int distancia = 0;
int limiteDistancia = 15;
int maxDistancia = 100;

AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

NewPing sensorUltra(pinoTrigger, pinoEcho, maxDistancia);

AdafruitIO_Feed *botaoalarme = io.feed("botaoalarme");
AdafruitIO_Feed *sensorultrassonico = io.feed("sensorultrassonico");

void setup() {

  pinMode(pinoLed, OUTPUT);
  pinMode(pinoBuzzer, OUTPUT);
  pinMode(pinoBotao, INPUT);
  Serial.begin(115200);

  while (!Serial)
    ;

  Serial.println("Conectando com AdafruitIO");
  io.connect();

  int numTentativas = 0;

  while (io.status() < AIO_CONNECTED) {
    Serial.print(numTentativas);
    Serial.println(" - Conexão Ainda Não Realizada");
    numTentativas = numTentativas + 1;
    delay(500);
  }

  // Mostra status da conexão

  Serial.println();
  Serial.println(io.statusText());

  // Configuração do Callback, quando o feed recebe(atualizar) um valor

  botaoalarme->onMessage(handleAlarme);

  Serial.println("Solicitando o Estado Inicial do Alarme: ");
  botaoalarme->get();

  delay(1000);
}

void loop() {

  io.run();  // Manter a conexão com a AdrafuitIO Ativa

  if (digitalRead(pinoBotao) == 1) {
    delay(200);
    alarmeAtivo = !alarmeAtivo;
    botaoalarme->save(String(alarmeAtivo ? "true" : "false"));
    Serial.println(alarmeAtivo ? "Alarme ARMADO pelo Botão Físico" : "Alarme DESARMADO pelo Botão Físico");
    Serial.println("");
  }

  distancia = sensorUltra.ping_cm();

  Serial.print(F("Distância Lida: "));
  Serial.println(distancia);

  if (alarmeAtivo && distancia > 0 && distancia < limiteDistancia) {
    ativarAlerta();
  } else {
    desativarAlerta();
  }

  delay(3000);

  if (distancia != 0) {
    sensorultrassonico->save(distancia);
  }
}
