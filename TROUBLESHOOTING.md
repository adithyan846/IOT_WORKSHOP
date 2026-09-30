# Troubleshooting Guide

Keep this section available during the workshop. These are the problems most likely to eat your 60 minutes.

## A. Arduino IDE and Upload Problems

| Problem | Possible Cause | Solution |
|---------|---------------|----------|
| ESP8266 board not visible | Board package missing | Install ESP8266 Core |
| Port not appearing | USB cable / driver issue | Try data cable, check USB-UART driver |
| Upload timeout | Wrong port or board | Check board and port |
| `Failed to connect` | ESP8266 not entering bootloader | Hold FLASH while uploading, if required by board |
| Compilation error: `DHT.h` not found | Library missing | Install Adafruit DHT library |
| `ESP8266WebServer.h` not found | Wrong board selected | Select ESP8266 board |

## B. LED Problems

| Problem | Possible Cause | Solution |
|---------|---------------|----------|
| External LED doesn't glow | Wrong polarity | Reverse LED |
| LED doesn't glow | Missing GND connection | Check common ground |
| LED doesn't glow | Wrong pin | Verify D1 |
| Onboard LED behaves inversely | Active-low wiring | LOW = ON, HIGH = OFF |
| Onboard LED not blinking | Different board LED configuration | Verify board schematic |

Remember: D1 and D4 are NodeMCU board labels, not actual GPIO numbers.

| NodeMCU Label | ESP8266 GPIO |
|---------------|--------------|
| D0 | GPIO16 |
| D1 | GPIO5 |
| D2 | GPIO4 |
| D3 | GPIO0 |
| D4 | GPIO2 |
| D5 | GPIO14 |
| D6 | GPIO12 |
| D7 | GPIO13 |
| D8 | GPIO15 |

⚠️ Avoid using D3, D4 and D8 casually for external hardware during the workshop. They are involved in ESP8266 boot configuration.

## C. Wi-Fi Problems

| Problem | Possible Cause | Solution |
|---------|---------------|----------|
| `IoT_Workshop` not visible | AP not started | Check Serial Monitor |
| Password rejected | Incorrect password | Use `12345678` |
| Cannot open webpage | Wrong IP | Use `192.168.4.1` |
| Page keeps loading | Server not handling requests | Check `server.handleClient()` |
| Phone says no internet | Expected behaviour | Stay connected to ESP network |
| Phone disconnects automatically | Mobile network switching | Disable automatic network switching or mobile data temporarily |
| Multiple students cannot connect | AP capacity / connection issues | Limit connected phones and test beforehand |

The ESP8266 is creating a local network, not providing internet. A phone warning about no internet is normal.

## D. DHT11 Problems

| Problem | Possible Cause | Solution |
|---------|---------------|----------|
| `DHT.h` missing | Library not installed | Install Adafruit DHT library |
| `NaN` readings | Incorrect wiring | Check VCC, GND and DATA |
| Readings fluctuate | Sensor limitations | DHT11 has limited accuracy |
| Readings always fail | Wrong sensor pin/type | Check D2 and `DHT11` configuration |
| Sensor gets hot | Incorrect supply/wiring | Disconnect immediately and inspect wiring |

### DHT11 Test Program

Use this small test program to isolate sensor issues:

```cpp
#include <DHT.h>

#define DHT_PIN D2
#define DHT_TYPE DHT11

DHT dht(DHT_PIN, DHT_TYPE);

void setup() {
    Serial.begin(115200);
    dht.begin();
}

void loop() {

    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();

    Serial.print("Temperature: ");
    Serial.print(temperature);

    Serial.print(" C | Humidity: ");
    Serial.print(humidity);

    Serial.println(" %");

    delay(2000);
}
```

If this works, the sensor and basic wiring are probably fine. You can then investigate the web server separately.