#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DHT.h>

// Hardware
#define LED_PIN D1
#define DHT_PIN D2
#define DHT_TYPE DHT11

DHT dht(DHT_PIN, DHT_TYPE);

// WiFi credentials
const char* ssid = "IoT_Workshop";
const char* password = "12345678";

// Web server
ESP8266WebServer server(80);


// Main webpage
void handleRoot() {

    String page = R"rawliteral(
    <!DOCTYPE html>
    <html>

    <head>
        <title>IoT Environment Monitor</title>

        <meta name="viewport"
        content="width=device-width, initial-scale=1">

        <style>
            body {
                font-family: Arial;
                text-align: center;
                background: #eeeeee;
                padding: 20px;
            }

            .card {
                background: white;
                padding: 20px;
                margin: 15px auto;
                max-width: 350px;
                border-radius: 12px;
            }

            button {
                padding: 15px 30px;
                margin: 10px;
                font-size: 18px;
            }
        </style>
    </head>

    <body>

        <h2>ESP8266 Smart Monitor</h2>

        <div class="card">
            <h3>Temperature</h3>
            <h1 id="temp">-- °C</h1>

            <h3>Humidity</h3>
            <h1 id="hum">-- %</h1>
        </div>

        <div class="card">
            <h3>LED Control</h3>

            <button onclick="fetch('/on')">
                ON
            </button>

            <button onclick="fetch('/off')">
                OFF
            </button>
        </div>

        <script>

            function updateData() {

                fetch('/data')
                .then(response => {
                    if (!response.ok) {
                        throw new Error("Sensor error");
                    }
                    return response.json();
                })
                .then(data => {

                    document.getElementById('temp')
                    .innerHTML = data.temperature + ' °C';

                    document.getElementById('hum')
                    .innerHTML = data.humidity + ' %';

                })
                .catch(error => {
                    console.log(error);
                });

            }

            // Update every 3 seconds
            setInterval(updateData, 3000);

            updateData();

        </script>

    </body>
    </html>
    )rawliteral";

    server.send(200, "text/html", page);
}


// Sensor data endpoint
void handleData() {

    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();

    if (isnan(temperature) || isnan(humidity)) {

        server.send(
            500,
            "application/json",
            "{\"error\":\"Sensor read failed\"}"
        );

        return;
    }

    String json = "{";

    json += "\"temperature\":";
    json += String(temperature, 1);

    json += ",\"humidity\":";
    json += String(humidity, 1);

    json += "}";

    server.send(200, "application/json", json);
}


// LED ON
void handleLEDOn() {

    digitalWrite(LED_PIN, HIGH);

    server.send(200, "text/plain", "LED ON");
}


// LED OFF
void handleLEDOff() {

    digitalWrite(LED_PIN, LOW);

    server.send(200, "text/plain", "LED OFF");
}


void setup() {

    Serial.begin(115200);

    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);

    dht.begin();

    // Create WiFi network
    WiFi.softAP(ssid, password);

    Serial.print("AP IP: ");
    Serial.println(WiFi.softAPIP());

    // Register routes
    server.on("/", handleRoot);
    server.on("/data", handleData);
    server.on("/on", handleLEDOn);
    server.on("/off", handleLEDOff);

    server.begin();

    Serial.println("Web server started");
}


void loop() {

    server.handleClient();

}