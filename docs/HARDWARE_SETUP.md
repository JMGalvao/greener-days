# Hardware Setup & Wiring Guide

## Heltec WiFi LoRa 32 V2 Pinout

The Heltec board has the following available pins:

### Analog Input Pins (for sensors)
- **GPIO 36 (VP)** - Light Sensor 1
- **GPIO 39 (VN)** - Light Sensor 2
- **GPIO 34** - Temperature Sensor
- **GPIO 35** - Soil Humidity Sensor
- **GPIO 32** - Water Level Sensor

### Digital Output Pin (for pump control)
- **GPIO 25** - Water Pump Control (relay or transistor)

### Power Supply
- **5V USB** - Main power for ESP32 and sensors
- **GND** - Ground (common)

## Sensor Connection Diagram

```
                    HELTEC ESP32
           ┌────────────────────────────┐
           │                            │
    5V ────┼──► Power Rail              │
    GND ───┼──► GND Rail                │
           │                            │
    GP36 ──┼── Light Sensor 1 (Analog)  │
    GP39 ──┼── Light Sensor 2 (Analog)  │
    GP34 ──┼── Temp Sensor (Analog)     │
    GP35 ──┼── Soil Humidity (Analog)   │
    GP32 ──┼── Water Level (Analog)     │
    GP25 ──┼── Water Pump (Digital Out) │
           │                            │
           └────────────────────────────┘
```

## Component Details

### Sensors
1. **Light Sensors (2x)** - Analog photoresistors or LDR
   - Voltage divider circuit recommended
   - Connect to 5V power rail through resistor
   
2. **Temperature Sensor** - DHT22 or LM35
   - 3-pin analog temperature sensor
   - Connect to 5V and GND
   
3. **Soil Humidity Sensor** - Capacitive soil moisture sensor
   - Analog output (0-5V)
   - Analog input to GPIO 35
   
4. **Water Level Sensor** - Float switch or analog level sensor
   - Outputs analog voltage proportional to water level

### Water Pump Control
- **Relay Module** or **MOSFET Transistor** required
  - ESP32 GPIO 25 → Relay signal pin
  - Relay/MOSFET switches pump on/off
  - Pump connected to main power supply (12V/5V)

## Calibration

Before deployment, calibrate each sensor:

1. **Light Sensors**: Measure in bright light (100%) and dark (0%)
2. **Temperature**: Compare with known temperature source
3. **Soil Humidity**: Test in wet soil (100%) and dry soil (0%)
4. **Water Level**: Measure at min and max levels

Adjust the conversion formulas in `main.cpp` based on your sensor specs.

## Power Considerations

- ESP32 draws ~80-150mA during WiFi operation
- Use a good quality 5V power supply (at least 1A)
- Add a 1000µF capacitor near the ESP32 power pins for stability
- Water pump may require separate power supply if current exceeds 500mA

## Safety Notes

- **Never** connect pump directly to ESP32 pin (too much current)
- Always use relay or MOSFET for pump control
- Protect outdoor installation with proper enclosure (IP65 rated)
- Use waterproof connectors for sensor wiring
