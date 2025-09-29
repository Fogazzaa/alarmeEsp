import React from "react";
import { View, Button, ActivityIndicator, Text } from "react-native";
import { useNavigation } from "@react-navigation/native";
import { useState, useEffect } from "react";
import api from "./services/axios";

const HomeScreen = () => {
  const [stateLed, setStateLed] = useState({ value: false });
  const [stateAlarm, setStateAlarm] = useState({ value: null });
  const navigation = useNavigation();

  async function getAlarme() {
    try {
      const response = await api.getAlarm();
      const value = response.data.last_value === "true";
      setStateAlarm({ value: value });
    } catch (error) {
      setStateAlarm({ value: false });
    }
  }

  useEffect(() => {
    getAlarme();
  }, []);

  const handleCam = () => {
    navigation.navigate("Cam");
  };

  async function ledToogle() {
    try {
      await api.toggleLed({ value: `${!stateLed.value}` });
      setStateLed({ value: !stateLed.value });
    } catch (error) {
    }
  }

  async function alarmToogle() {
    if (stateAlarm.value === null) {
      return;
    }

    try {
      const newValue = !stateAlarm.value;
      await api.toggleAlarm({ value: `${newValue}` });
      setStateAlarm({ value: newValue });
    } catch (error) {
    }
  }

  if (stateAlarm.value === null) {
    return (
      <View style={{ flex: 1, justifyContent: "center", alignItems: "center" }}>
        <ActivityIndicator size="large" color="#0000ff" />
        <Text style={{ marginTop: 10 }}>Carregando estado do alarme...</Text>
      </View>
    );
  }

  return (
    <View style={{ flex: 1, justifyContent: "center", alignItems: "center" }}>
      <View style={{ marginBottom: 20 }}>
        <Button title="Abrir Câmera" onPress={handleCam} color="black" />
      </View>
      <View style={{ marginBottom: 20 }}>
        <Button
          title={stateLed.value ? "Desligar LED" : "Ligar LED"}
          onPress={ledToogle}
          color={stateLed.value ? "red" : "green"}
        />
      </View>
      <View style={{ marginBottom: 20 }}>
        <Button
          title={stateAlarm.value ? "Desligar ALARME" : "Ligar ALARME"}
          onPress={alarmToogle}
          color={stateAlarm.value ? "red" : "green"}
        />
      </View>
      <View>
        <Button
          title="Listar Eventos"
          onPress={() => navigation.navigate("Eventos")}
        />
      </View>
    </View>
  );
};

export default HomeScreen;