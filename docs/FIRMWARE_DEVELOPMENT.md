# Firmware Development Guide

## Setting Up the Development Environment

### Prerequisites
- VS Code installed
- PlatformIO extension for VS Code
- Python 3.6+ installed
- USB cable for ESP32 upload

### Installation Steps

1. **Install PlatformIO Extension**
   - Open VS Code
   - Go to Extensions (Ctrl+Shift+X)
   - Search for "PlatformIO IDE"
   - Click Install

2. **Open the firmware folder**
   - File → Open Folder
   - Select `/firmware/` directory
   - PlatformIO will auto-install dependencies

3. **Configure Serial Port**
   - Connect ESP32 via USB
   - PlatformIO will auto-detect the port
   - Or manually set in `platformio.ini`: `upload_port = /dev/ttyUSB0` (Linux) or `COM3` (Windows)

## Project Structure

```
firmware/
├── src/
│   └── main.cpp          # Main firmware code
├── lib/                  # Custom libraries (optional)
├── include/              # Header files (optional)
├── platformio.ini        # Project configuration
└── .git/                 # Version control
```

## Building & Uploading

### Using PlatformIO CLI

```bash
cd firmware

# Install dependencies
pio lib install

# Build for simulator (Wokwi)
pio run -e heltec_wifi_lora_32_V2_sim

# Build for real hardware
pio run -e heltec_wifi_lora_32_V2_hw

# Upload to device
pio run -e heltec_wifi_lora_32_V2_hw --target upload

# Monitor serial output
pio device monitor
```

### Using VS Code UI

- Click the PlatformIO icon in the sidebar
- Use "Build" to compile
- Use "Upload" to flash to device
- Use "Serial Monitor" to view debug output

## Customizing for Your Setup

### 1. Update WiFi Credentials

In `src/main.cpp`:

```cpp
const char* SSID = "YOUR_WIFI_SSID";
const char* PASSWORD = "YOUR_WIFI_PASSWORD";
```

### 2. Update Firebase Credentials

```cpp
const char* SERVER_URL = "https://YOUR_PROJECT_ID.firebaseio.com";
const char* API_KEY = "YOUR_API_KEY";
```

### 3. Adjust Sensor Calibration

The conversion formulas in `readSensors()` depend on your specific sensors:

```cpp
// Example for temperature sensor
data.temperature = (raw_temp / 4095.0) * 50.0;  // 0-50°C
```

Modify based on your sensor's voltage range and specifications.

## Adding Sensor Libraries

To use sensor libraries with automatic calibration:

Add to `platformio.ini`:

```ini
lib_deps = 
    DHT sensor library@latest
    Adafruit Unified Sensor@latest
```

## Debugging Tips

### Enable Debug Logging

```cpp
// In platformio.ini
build_flags = 
    -D CORE_DEBUG_LEVEL=3
```

### Serial Monitor
Check the serial output (115200 baud) for:
- WiFi connection status
- Sensor readings
- Cloud sync status
- Error messages

### Common Issues

| Problem | Solution |
|---------|----------|
| Upload fails | Check USB cable, update CH340 driver, change upload_speed |
| No WiFi connection | Verify SSID/password, check router 2.4GHz band, move closer to router |
| Sensor reads garbage | Check analog pin connections, verify power supply voltage |
| Firebase timeout | Check internet connection, verify API key, check firewall |

## Advanced Features

### Over-The-Air (OTA) Updates

Add to `platformio.ini`:

```ini
[env:heltec_ota]
platform = espressif32
board = heltec_wifi_lora_32_V2
framework = arduino
upload_protocol = espota
upload_port = 192.168.0.XX  # Your device IP
```

### LoRa Features

If using LoRa capabilities:

```cpp
#include <LoRa.h>

void setupLoRa() {
  LoRa.setPins(SS, RST, DIO0);
  if (!LoRa.begin(868E6)) {
    while (1);
  }
}
```

### Power Management

For battery operation:

```cpp
#include "esp_sleep.h"

void goToDeepSleep(uint64_t microseconds) {
  esp_sleep_enable_timer_wakeup(microseconds);
  esp_deep_sleep_start();
}
```

## Testing Checklist

- [ ] WiFi connection is stable
- [ ] All sensors are reading correctly
- [ ] Data is being sent to Firebase correctly
- [ ] Pump control works as expected
- [ ] No data loss during operation
- [ ] Device recovers from WiFi disconnection
- [ ] Firmware can be updated via OTA

## Further Learning

- [PlatformIO Docs](https://docs.platformio.org/)
- [ESP32 Arduino Core](https://github.com/espressif/arduino-esp32)
- [Firebase REST API](https://firebase.google.com/docs/database/rest/start)
