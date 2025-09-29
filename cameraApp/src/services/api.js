import axios from "axios";

const api = axios.create({
  baseURL: "http://10.89.240.91:5000/api/v1",
  headers: {
    accept: "application/json",
  },
});

export const createEvento = async (form, imageUri) => {
  const data = new FormData();

  for (let key in form) {
    data.append(key, form[key]);
  }

  if (imageUri) {
    const fileName = imageUri.split("/").pop();
    const match = /|.(\w+)$/.exec(fileName);
    // [".extensao", "extensao"], ex: [".png", "png"]
    const type = match ? `image/${match[1]}` : `image`;

    data.append("imagem", {
      uri: imageUri,
      name: fileName,
      type: type,
    });
  }

  return api.post("/evento", data, {
    headers: {
      "Content-Type": "multipart/form-data",
    },
  });
};

export const getEventos = async () => {
  return api.get("/eventos");
};
