# ESP8266 IoT Workshop Kit

Beginner-friendly IoT workshop with progressive projects using ESP8266 (NodeMCU).

## Hardware Requirements

| Component | Quantity |
|-----------|----------|
| NodeMCU ESP8266 | 1 per group |
| LED | 1 |
| 220Ω resistor | 1 |
| DHT11 sensor/module | 1 |
| Breadboard | 1 |
| Jumper wires | As needed |
| Micro USB cable | 1 |

## Arduino IDE Setup

1. Install Arduino IDE
2. Add ESP8266 board manager URL: `https://arduino.esp8266.com/stable/package_esp8266com_index.json`
3. Open Boards Manager → Install ESP8266
4. Select **NodeMCU 1.0 (ESP-12E Module)**
5. Select correct COM/USB port
6. Install libraries via Library Manager:
   - **DHT sensor library** by Adafruit
   - **Adafruit Unified Sensor**

## Project Structure

```
iot-workshop/
├── README.md
├── 01_led/
│   ├── external_led.ino
│   └── builtin_led.ino
├── 02_wifi/
│   └── wifi_led.ino
├── 03_sensor/
│   ├── smart_monitor.ino
│   └── dht_test.ino
└── diagrams/
    ├── led_connection.png
    └── dht11_connection.png
```

## Projects

### Project 1: Make an LED Blink (10 min)
- `external_led.ino` - External LED on D1
- `builtin_led.ino` - Onboard LED (active LOW)

### Project 2: Control LED through Wi-Fi (20 min)
- `wifi_led.ino` - Creates AP "IoT_Workshop", control LED via web browser at `192.168.4.1`

### Project 3: Smart Environment Monitor (20 min)
- `smart_monitor.ino` - Adds DHT11 sensor, JSON endpoint `/data`, auto-refreshing dashboard
- `dht_test.ino` - Standalone sensor test for troubleshooting

### Project 4: Automation Challenge
- Modify `smart_monitor.ino` to auto-turn LED on when temperature > 30°C

## Wi-Fi Credentials (All Projects)
- **SSID:** `IoT_Workshop`
- **Password:** `12345678`
- **AP IP:** `192.168.4.1`

## Troubleshooting

See `TROUBLESHOOTING.md` for common issues with:
- Arduino IDE & upload problems
- LED wiring issues
- Wi-Fi connection problems
- DHT11 sensor issues

## Pin Reference (NodeMCU Labels → GPIO)

| Label | GPIO |
|-------|------|
| D0 | GPIO16 |
| D1 | GPIO5 |
| D2 | GPIO4 |
| D3 | GPIO0 |
| D4 | GPIO2 |
| D5 | GPIO14 |
| D6 | GPIO12 |
| D7 | GPIO13 |
| D8 | GPIO15 |

⚠️ Avoid D3, D4, D8 for external hardware (boot configuration pins)

## Teaching Strategy

| Project | Students Receive | Students Do |
|---------|------------------|-------------|
| LED | Complete code | Modify delay |
| Wi-Fi LED | Complete code | Change Wi-Fi name & webpage title |
| Smart Monitor | Complete code | Modify webpage & observe readings |
| Automation | Code snippet | Add temperature condition |

**Core Learning Outcome:** Sense → Process → Communicate → Act