void handleAlarme(AdafruitIO_Data *data) {

  String valor = data->toString();

  if (!isInitialSync) {
    Serial.print(F("Valor Recebido do Feed: "));
    Serial.println(valor);
  }

  if (valor == "true") {
    alarmeAtivo = true;
    if (!isInitialSync) {
      Serial.println("Alarme ARMADO no/pelo Adafruit/Mobile");
    }
    digitalWrite(pinoLedAmarelo, HIGH);
    digitalWrite(pinoLedVerde, LOW);
  } else {
    alarmeAtivo = false;
    if (!isInitialSync) {
      Serial.println("Alarme DESARMADO no/pelo Adafruit/Mobile");
    }
    digitalWrite(pinoLedAmarelo, LOW);
    digitalWrite(pinoLedVerde, HIGH);
  }
}

void ativarAlerta() {

  digitalWrite(pinoLedAmarelo, HIGH);
  digitalWrite(pinoLedVerde, LOW);

  digitalWrite(pinoBuzzer, HIGH);
  digitalWrite(pinoLedVermelho, HIGH);

  delay(750);

  digitalWrite(pinoBuzzer, LOW);
  digitalWrite(pinoLedVermelho, LOW);
}

void desativarAlerta() {
  digitalWrite(pinoBuzzer, LOW);
  digitalWrite(pinoLedVermelho, LOW);

  digitalWrite(pinoLedAmarelo, LOW);
  digitalWrite(pinoLedVerde, HIGH);
}