# WOKWI Simulator Setup Guide

## Quick Start (5 Minutes)

### 1. Install WOKWI Extension
- Open VS Code
- Go to Extensions (`Ctrl+Shift+X`)
- Search for `WOKWI Simulator`
- Install

### 2. Build Simulator Firmware

Preferred:
```bash
cd /home/jfgalvao/GreenerDays/greener-days
bash scripts/sim-build.sh
```

Alternative:
```bash
cd /home/jfgalvao/GreenerDays/greener-days/firmware
pio run -e heltec_wifi_lora_32_V2_sim
```

### 3. Run WOKWI
- Open `firmware/diagram.json`
- Press `Ctrl+Shift+P`
- Run `WOKWI: Run`

### 4. First Test
- Open Serial Monitor
- Type `pump on` then Enter
- Type `pump off` then Enter

If the build fails with `pio: command not found`, use the helper script command above.

## What is WOKWI?

**WOKWI** is a free online simulator for Arduino, ESP32, and other microcontrollers. It allows you to:
- Test code without physical hardware
- Simulate sensors with virtual potentiometers
- Debug using Serial Monitor
- Build virtual circuits
- Test before deploying to real hardware

## Getting Started

### Option 1: VS Code Integration (Recommended)

1. **Install WOKWI Extension**
   - Open VS Code
   - Go to Extensions (Ctrl+Shift+X)
   - Search for "WOKWI Simulator"
   - Click Install

2. **Open the Project**
   ```bash
   cd /home/jfgalvao/GreenerDays/greener-days/firmware
   ```

3. **Build the Project**
   - Press `Ctrl+Alt+B` in VS Code (PlatformIO build)
   - Or in terminal: `pio run -e heltec_wifi_lora_32_V2_sim`

4. **Run the Simulator**
   - With `diagram.json` open, press `F1`
   - Type "WOKWI: Run" and press Enter
   - The simulator will open in a webview

### Option 2: Online at wokwi.com

1. Go to https://wokwi.com
2. Create a new project
3. Select "ESP32 DevKit"
4. Copy the code from [firmware/src/main_simulator.cpp](src/main_simulator.cpp)
5. Upload `diagram.json` configuration

## Project Files

```
firmware/
├── src/
│   ├── main_simulator.cpp     ✅ Code for simulator (USE THIS)
│   └── main.cpp               (Original - for real hardware)
├── diagram.json               ✅ Circuit diagram for WOKWI
├── wokwi.toml                 ✅ WOKWI configuration
└── platformio.ini             ✅ Build settings
```

## Using the Simulator

### 1. Understanding the Virtual Circuit

The `diagram.json` file contains:

```
Left Side (Sensors)          Right Side (Outputs)
┌──────────────┐            ┌──────────────┐
│ Light 1 (POT)│            │  Pump LED    │
│ Light 2 (POT)│            │              │
│ Temp (POT)   │  ESP32     │              │
│ Humidity(POT)│────────────│              │
│ Water (POT)  │            │              │
└──────────────┘            └──────────────┘
```

**POT = Potentiometer** - Simulates analog sensor input

### 2. Adjusting Sensor Values

In the simulator:
- **Drag the potentiometer sliders left/right** to simulate sensor readings
- **Left** = 0% (dry, dark, cold)
- **Right** = 100% (wet, bright, hot)

### 3. Serial Monitor

1. In the simulator, click the **Serial Monitor** tab
2. See real-time sensor readings
3. Send commands:
   - `pump on` - Turn pump ON
   - `pump off` - Turn pump OFF
   - `help` - Show available commands

### 4. Debugging Output

The simulator will display:
```
☀️  Light 1:      45.3 %
☀️  Light 2:      78.9 %
🌡️  Temperature:  24.5 °C
💧 Soil Humidity: 35.2 %
💦 Water Level:   60.5 %
💨 Pump:          OFF
```

## Key Features in Simulator Code

### Automatic Watering
The firmware automatically controls the pump based on soil humidity:

```cpp
if (soilHumidity < 40%) → Turn pump ON
if (soilHumidity > 70%) → Turn pump OFF
if (pumpOnTime > 5 sec) → Safety timeout
```

### Serial Commands
- **pump on** - Manually turn pump on
- **pump off** - Manually turn pump off
- **help** - Show command list

### Auto-calibration
Sensor values are automatically scaled:
- Light: 0-100%
- Temperature: 15-45°C
- Humidity: 0-100%
- Water Level: 0-100%

## Testing Scenarios

### Scenario 1: Dry Soil + Low Light
1. Set all humidity potentiometers to LEFT (low values)
2. Set light potentiometers to LEFT (dark)
3. Watch pump turn ON automatically
4. Gradually increase humidity potentiometer to RIGHT
5. Watch pump turn OFF when humidity reaches 70%

### Scenario 2: Manual Pump Control
1. Open Serial Monitor
2. Type `pump on` and press Enter
3. See "Pump: ON" in output
4. Type `pump off` and press Enter
5. See "Pump: OFF" in output

### Scenario 3: Temperature Monitoring
1. Move Temperature potentiometer
2. Watch temperature value change (15-45°C)
3. Can integrate temp-based controls later

## Troubleshooting

| Issue | Solution |
|-------|----------|
| "No firmware found" | Build first with `pio run -e heltec_wifi_lora_32_V2_sim` |
| "License Error: Invalid License" | In VS Code settings, clear or replace `Wokwi: License Key`. If you don't have a key, run the project on https://wokwi.com (Option 2 in this guide). |
| Simulator won't start | Reload VS Code, check WOKWI extension is installed |
| Potentiometers not responding | Click on the simulator window to focus it |
| Serial Monitor empty | Check that `Serial.begin(115200)` is called |
| Pump LED not lighting | Verify `diagram.json` connections are correct |

## Modifying the Simulator

### Edit Sensor Thresholds

In [firmware/src/main_simulator.cpp](src/main_simulator.cpp):

```cpp
const float HUMIDITY_THRESHOLD = 40.0;  // Change this value
const uint32_t PUMP_RUN_TIME = 5000;    // Max pump runtime (ms)
```

### Add More Sensors

Edit `diagram.json` to add new components:

```json
{
  "type": "wokwi-potentiometer",
  "id": "new_sensor",
  "top": 100,
  "left": 50,
  "label": "New Sensor"
}
```

### Change Pump Behavior

Modify the `checkAutoWatering()` function to implement different logic.

## Next Steps

1. ✅ Run the simulator and verify it works
2. ✅ Test pump control with serial commands
3. ✅ Adjust thresholds to your liking
4. ✅ Plan firmware improvements
5. When hardware arrives → Swap to `main.cpp` and add Firebase integration

## Resources

- **WOKWI Docs**: https://docs.wokwi.com/
- **WOKWI Simulator**: https://wokwi.com/
- **ESP32 Pinout**: https://randomnerdtutorials.com/esp32-pinout-reference-diagrams/
- **Arduino Reference**: https://www.arduino.cc/reference/en/

## Video Tutorial

Check WOKWI documentation for video walkthroughs on:
- Simulating analog sensors
- Using Serial Monitor
- Circuit connections
- Debugging with breakpoints
