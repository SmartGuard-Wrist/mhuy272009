#include <Wire.h>
#include <Adafruit_ADXL345_U.h>
#include "MAX30100_PulseOximeter.h"
#include "battery.h"
#include "BluetoothSerial.h"  // Bluetooth classic ESP32

// ===== ADXL345 SENSOR =====
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

// ===== MAX30100 SENSOR =====
PulseOximeter pox;

// ===== BLUETOOTH SERIAL =====
BluetoothSerial SerialBT;

unsigned long lastPrintTime = 0;

// Callback when a heartbeat is detected
void onBeatDetected() {
  Serial.println("💓 Beat detected!");
  SerialBT.println("💓 Beat detected!");
}

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32_HealthBand"); // Bluetooth device name

  Serial.println("🔵 Bluetooth started with name: ESP32_HealthBand");
  SerialBT.println("🔵 ESP32 Bluetooth started");

  delay(100);

  // === Initialize battery monitoring ===
  battery_begin();

  // === Initialize ADXL345 ===
  if (!accel.begin()) {
    Serial.println("❌ ADXL345 not working.");
    SerialBT.println("❌ ADXL345 not working.");
  } else {
    accel.setRange(ADXL345_RANGE_4_G);
    Serial.println("✅ ADXL345 is ready.");
    SerialBT.println("✅ ADXL345 is ready.");
  }

  // === Initialize MAX30100 ===
  if (!pox.begin()) {
    Serial.println("❌ MAX30100 not working.");
    SerialBT.println("❌ MAX30100 not working.");
  } else {
    pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);
    pox.setOnBeatDetectedCallback(onBeatDetected);
    Serial.println("✅ MAX30100 is ready.");
    SerialBT.println("✅ MAX30100 is ready.");
  }

  Serial.println("🚀 System initialization complete!");
  SerialBT.println("🚀 System initialization complete!");
}

void loop() {
  pox.update();  // Update MAX30100 sensor data

  if (millis() - lastPrintTime >= 1000) {
    lastPrintTime = millis();

    // === Read ADXL345 ===
    sensors_event_t event;
    accel.getEvent(&event);

    float x = event.acceleration.x;
    float y = event.acceleration.y;
    float z = event.acceleration.z;
    float totalG = sqrt(x * x + y * y + z * z);

    // === Read MAX30100 ===
    float bpm = pox.getHeartRate();
    float spo2 = pox.getSpO2();

    // === Read battery ===
    float voltage = battery_get_voltage();
    int percent = battery_get_level();

    // === Print to UART và Bluetooth ===
    String message = "Total G: " + String(totalG, 2) +
                     " | BPM: " + String(bpm, 1) +
                     " | SpO2: " + String(spo2, 1) +
                     "% | Battery: " + String(percent) + "% (" + String(voltage, 2) + " V)";

    Serial.println(message);
    SerialBT.println(message);
  }
}
