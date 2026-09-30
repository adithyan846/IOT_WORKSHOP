#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// Hardware
#define LED_PIN D1

// WiFi credentials
const char* ssid = "IoT_Workshop";
const char* password = "12345678";

// Web server on port 80
ESP8266WebServer server(80);


// Webpage
void handleRoot() {

    String page = R"rawliteral(
    <!DOCTYPE html>
    <html>
    <head>
        <title>IoT LED Control</title>

        <meta name="viewport"
        content="width=device-width, initial-scale=1">

        <style>
            body {
                text-align: center;
                font-family: Arial;
                margin-top: 60px;
            }

            button {
                padding: 20px 40px;
                margin: 10px;
                font-size: 20px;
            }
        </style>
    </head>

    <body>
        <h1>ESP8266 LED Control</h1>

        <button onclick="fetch('/on')">
            ON
        </button>

        <button onclick="fetch('/off')">
            OFF
        </button>

    </body>
    </html>
    )rawliteral";

    server.send(200, "text/html", page);
}


// Turn LED ON
void handleLEDOn() {

    digitalWrite(LED_PIN, HIGH);

    server.send(200, "text/plain", "LED ON");
}


// Turn LED OFF
void handleLEDOff() {

    digitalWrite(LED_PIN, LOW);

    server.send(200, "text/plain", "LED OFF");
}


void setup() {

    Serial.begin(115200);

    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);

    // Create WiFi Access Point
    WiFi.softAP(ssid, password);

    // Print IP address
    Serial.print("AP IP: ");
    Serial.println(WiFi.softAPIP());

    // Define webpage routes
    server.on("/", handleRoot);
    server.on("/on", handleLEDOn);
    server.on("/off", handleLEDOff);

    // Start server
    server.begin();

    Serial.println("Web server started");
}


void loop() {

    server.handleClient();

}