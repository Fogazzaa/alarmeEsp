
void handleAlarme(AdafruitIO_Data *data) {

  String valor = data->toString();

  Serial.print(F("Valor Recebido do Feed: "));
  Serial.println(valor);

  if (valor == "true") {
    alarmeAtivo = true;
    Serial.println("Alarme ARMADO no/pelo Adafruit/Mobile");
    digitalWrite(pinoLedAmarelo, HIGH);
    digitalWrite(pinoLedVerde, LOW);
  } else {
    alarmeAtivo = false;
    Serial.println("Alarme DESARMADO no/pelo Adafruit/Mobile");
    digitalWrite(pinoLedAmarelo, LOW);
    digitalWrite(pinoLedVerde, HIGH);
  }
}

void ativarAlerta() {
  digitalWrite(pinoBuzzer, HIGH);
  digitalWrite(pinoLed, HIGH);
}

void desativarAlerta() {
  digitalWrite(pinoBuzzer, LOW);
  digitalWrite(pinoLed, LOW);
}