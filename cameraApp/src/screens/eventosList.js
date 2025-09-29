import React, { useEffect, useState } from "react";
import { View, Text, FlatList, Image, StyleSheet } from "react-native";
import { getEventos } from "../services/api";

export default function EventosList() {
  const [eventos, setEventos] = useState([]);

  useEffect(() => {
    const fetchEventos = async () => {
      try {
        const response = await getEventos();
        setEventos(response.data.eventos);
      } catch (error) {
        console.error("Erro ao buscar eventos:", error);
      }
    };

    fetchEventos();
  }, []);

  const renderItem = ({ item }) => (
    <View style={styles.card}>
      <Text style={styles.nome}>{item.nome}</Text>
      <Text>{item.local}</Text>
      <Text>{new Date(item.data_hora).toLocaleString()}</Text>

      {/* Aqui puxamos a imagem pelo endpoint da API */}
      <Image
        source={{ uri: `http://10.89.240.91:5000/api/v1/evento/imagem/${item.id_evento}` }}
        style={styles.imagem}
      />
    </View>
  );

  return (
    <FlatList
      data={eventos}
      keyExtractor={(item) => item.id_evento.toString()}
      renderItem={renderItem}
    />
  );
}

const styles = StyleSheet.create({
  card: {
    backgroundColor: "#f2f2f2",
    padding: 15,
    marginVertical: 10,
    marginHorizontal: 20,
    borderRadius: 10,
  },
  nome: {
    fontSize: 18,
    fontWeight: "bold",
  },
  imagem: {
    width: "100%",
    height: 200,
    marginTop: 10,
    borderRadius: 8,
  },
});