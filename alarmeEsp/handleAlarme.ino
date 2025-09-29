void handleAlarme(AdafruitIO_Data *data) {
  String valor = data->toString();

  if (isInitialSync) {
    Serial.print(F("Sincronizando Estado do Alarme: "));
    Serial.println(valor);
    Serial.println();
  }

  if (valor == "true") {
    alarmeAtivo = true;

    if (!isInitialSync) {
      Serial.println("Alarme ARMADO no/pelo Adafruit/Mobile");
      Serial.println();
    }
    digitalWrite(pinoLedAmarelo, HIGH);
    digitalWrite(pinoLedVerde, LOW);
  } else {
    alarmeAtivo = false;

    if (!isInitialSync) {
      Serial.println("Alarme DESARMADO no/pelo Adafruit/Mobile");
      Serial.println();
    }
    digitalWrite(pinoLedAmarelo, LOW);
    digitalWrite(pinoLedVerde, HIGH);
  }

  if (isInitialSync) {
    isInitialSync = false;
  }
}

void ativarAlerta() {
  digitalWrite(pinoBuzzer, HIGH);
  digitalWrite(pinoLedVermelho, HIGH);

  delay(200);

  digitalWrite(pinoBuzzer, LOW);
  digitalWrite(pinoLedVermelho, LOW);
}

void desativarAlerta() {
  digitalWrite(pinoBuzzer, LOW);
  digitalWrite(pinoLedVermelho, LOW);

  if (alarmeAtivo) {
    digitalWrite(pinoLedAmarelo, HIGH);
    digitalWrite(pinoLedVerde, LOW);
  } else {
    digitalWrite(pinoLedAmarelo, LOW);
    digitalWrite(pinoLedVerde, HIGH);
  }
}