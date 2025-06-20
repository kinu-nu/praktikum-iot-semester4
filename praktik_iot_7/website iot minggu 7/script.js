const client = mqtt.connect("ws://test.mosquitto.org:8080");

client.on("connect", () => {
  console.log("Terhubung ke broker MQTT");
  client.subscribe("IOT/Test1/temp");
  client.subscribe("IOT/Test1/hum");
});

client.on("message", (topic, message) => {
  const data = message.toString();
  const time = new Date().toLocaleTimeString();

  if (topic === "IOT/Test1/temp") {
    document.getElementById("temp").innerText = data;
    suhuTerakhir = parseFloat(data);
  } else if (topic === "IOT/Test1/hum") {
    document.getElementById("hum").innerText = data;
    kelembapanTerakhir = parseFloat(data);
  }

  // Update chart hanya jika keduanya sudah ada
  if (suhuTerakhir !== null && kelembapanTerakhir !== null) {
    updateChart(time, suhuTerakhir, kelembapanTerakhir);
    suhuTerakhir = null;
    kelembapanTerakhir = null;
  }
});

function turnOn() {
  client.publish("IOT/Test1/mqtt", "1");
  console.log("Kirim: 1 (LED ON)");
}

function turnOff() {
  client.publish("IOT/Test1/mqtt", "0");
  console.log("Kirim: 0 (LED OFF)");
}

// Variabel penampung nilai sementara
let suhuTerakhir = null;
let kelembapanTerakhir = null;

// Inisialisasi Chart.js
const ctx = document.getElementById("sensorChart").getContext("2d");

const sensorChart = new Chart(ctx, {
  type: "line",
  data: {
    labels: [],
    datasets: [
      {
        label: "Suhu (°C)",
        borderColor: "#e74c3c",
        backgroundColor: "rgba(231, 76, 60, 0.1)",
        data: [],
        tension: 0.4
      },
      {
        label: "Kelembapan (%)",
        borderColor: "#3498db",
        backgroundColor: "rgba(52, 152, 219, 0.1)",
        data: [],
        tension: 0.4
      }
    ]
  },
  options: {
    responsive: true,
    scales: {
      x: {
        title: { display: true, text: "Waktu" }
      },
      y: {
        title: { display: true, text: "Nilai Sensor" },
        min: -20,
        max: 50
      }
    }
  }
});


// Fungsi update grafik suhu dan kelembapan
function updateChart(label, suhu, kelembapan) {
  sensorChart.data.labels.push(label);
  sensorChart.data.datasets[0].data.push(suhu);        // suhu
  sensorChart.data.datasets[1].data.push(kelembapan);  // kelembapan

  if (sensorChart.data.labels.length > 10) {
    sensorChart.data.labels.shift();
    sensorChart.data.datasets[0].data.shift();
    sensorChart.data.datasets[1].data.shift();
  }

  sensorChart.update();
}
