import axios from "axios";

const api = axios.create({
  baseURL: "https://io.adafruit.com/api/v2/fogazza/feeds/",
  headers: {
    accept: "application/json",
    "Content-Type": "application/json",
    "X-AIO-Key": "aio_okjk27xGTyg1fh1V41HWKQ60BKGK",
  },
});

const sheets = {
  toggleLed: (stateLed) => api.post(`botaoled/data`, stateLed),
  toggleAlarm: (stateAlarm) => api.post(`botaoalarme/data`, stateAlarm),
  getAlarm: () => api.get(`botaoalarme/`),
};

export default sheets;
