# Quick Start: Getting Your Simulator Running

## ⚡ 5-Minute Setup

### Step 1: Install WOKWI Extension (1 min)
```
VS Code → Extensions (Ctrl+Shift+X) 
→ Search "WOKWI Simulator" 
→ Install
```

### Step 2: Build the Firmware (2 min)
```bash
cd /home/jfgalvao/GreenerDays/greener-days/firmware
pio run -e heltec_wifi_lora_32_V2_sim
```

**Expected output:**
```
Building in release mode
...
LDF: Library Dependency Finder -> http://bit.ly/configure-pio-ldf
...
======================== [SUCCESS] Took X.XX seconds ========================
```

### Step 3: Run Simulator (2 min)
1. Open `diagram.json` in VS Code
2. Press `Ctrl+Shift+P` (Command Palette)
3. Type `WOKWI: Run`
4. Click on the command

**Your simulator should open!** 🎉

## 📊 What You'll See

```
Left Panel              Middle         Right Panel
┌──────────┐           ┌─────────┐     ┌──────────┐
│ Light 1  │           │ ESP32   │     │ Pump LED │
│ Light 2  │───────────│ (Board) │─────│ Status   │
│ Temp     │           │         │     │          │
│ Humidity │───────────│         │     │          │
│ Water    │           │         │     │          │
└──────────┘           └─────────┘     └──────────┘
   (Sliders)           (Running)       (Indicator)
```

## 🎮 First Test: Manual Pump Control

1. **Click on Serial Monitor tab** in the simulator
2. **Type in the input field:**
   ```
   pump on
   ```
3. **Press Enter**
4. **Watch:**
   - Red LED turns ON (pump status)
   - Serial output shows `[PUMP] ✓ ON`

5. **Now turn it off:**
   ```
   pump off
   ```
6. **Watch LED turn OFF**

✅ **Congrats! Your simulator works!**

## 🌱 Second Test: Auto-Watering Logic

1. **Find "Soil Humidity" slider** on the left (labeled "humidity_pot")
2. **Drag it all the way LEFT** (represents dry soil)
3. **Watch:**
   - Humidity percentage drops
   - When it goes below 40% → LED turns ON automatically
   - Pump starts watering automatically

4. **Drag the slider RIGHT** (simulating watering)
5. **Watch:**
   - When humidity reaches 70% → LED turns OFF
   - Pump stops automatically

✅ **Auto-watering logic works!**

## 📈 Third Test: Monitor All Sensors

1. **Open Serial Monitor tab**
2. **Adjust each potentiometer slider:**
   - Light 1 slider → watch "Light 1" % change
   - Light 2 slider → watch "Light 2" % change  
   - Temp slider → watch temperature change (15-45°C)
   - Humidity slider → watch humidity change
   - Water Level slider → watch water level change

3. **Every 2 seconds**, you'll see fresh readings

✅ **All sensors working!**

## 🔧 Common Issues & Fixes

### Issue: "Error: No firmware found"
**Fix:**
```bash
cd firmware
pio run -e heltec_wifi_lora_32_V2_sim
```
Wait for `[SUCCESS]` message.

### Issue: WOKWI window won't open
**Fix:**
1. Close VS Code completely
2. Reopen VS Code
3. Install WOKWI extension again
4. Restart VS Code

### Issue: Serial Monitor shows nothing
**Fix:**
- Wait 2-3 seconds (first sensor read takes time)
- Check that `diagram.json` is open in editor
- Close and reopen the simulator

## 📝 Serial Commands Reference

| Command | Effect |
|---------|--------|
| `pump on` | Turn pump on |
| `pump off` | Turn pump off |
| `help` | Show available commands |

## 🎯 Your Next Steps

1. ✅ **Now:** Get simulator running (complete above steps)
2. ⏭️ **Next:** Modify firmware to add more features
3. ⏭️ **Then:** Test Firebase integration (when ready)
4. ⏭️ **Finally:** Deploy to real hardware when it arrives

## 📚 Full Documentation

For detailed setup guides, see:
- [SIMULATOR_SETUP.md](SIMULATOR_SETUP.md) - Complete simulator guide
- [FIRMWARE_DEVELOPMENT.md](FIRMWARE_DEVELOPMENT.md) - Firmware coding reference
- [HARDWARE_SETUP.md](HARDWARE_SETUP.md) - Real hardware wiring (for later)

## ❓ Need Help?

- **Simulator not working?** Check [docs/SIMULATOR_SETUP.md](SIMULATOR_SETUP.md#troubleshooting)
- **Want to modify code?** Edit `firmware/src/main_simulator.cpp`
- **Want to add sensors?** Edit `firmware/diagram.json`

---

**You're all set! 🚀 Now go test your plant monitoring system!**
