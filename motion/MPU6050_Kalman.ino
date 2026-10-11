// Updated Adafruit MPU6050 Demo with Pitch and Roll Kalman Filters

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;

// --- Kalman Filter Structure ---
struct Kalman {
    float Q_angle = 0.001f;   
    float Q_bias  = 0.003f;   
    float R_measure = 0.03f;  

    float angle = 0.0f;       
    float bias  = 0.0f;       
    float rate  = 0.0f;       

    float P[2][2] = {{0.0f, 0.0f}, {0.0f, 0.0f}};

    float getAngle(float newAngle, float newRate, float dt) {
        // 1. Predict Step
        rate = newRate - bias;
        angle += dt * rate;

        P[0][0] += dt * (dt * P[1][1] - P[0][1] - P[1][0] + Q_angle);
        P[0][1] -= dt * P[1][1];
        P[1][0] -= dt * P[1][1];
        P[1][1] += Q_bias * dt;

        // 2. Update Step
        float y = newAngle - angle;
        float S = P[0][0] + R_measure;

        float K[2];
        K[0] = P[0][0] / S;
        K[1] = P[1][0] / S;

        angle += K[0] * y;
        bias  += K[1] * y;

        float P00_temp = P[0][0];
        float P01_temp = P[0][1];

        P[0][0] -= K[0] * P00_temp;
        P[0][1] -= K[0] * P01_temp;
        P[1][0] -= K[1] * P00_temp;
        P[1][1] -= K[1] * P01_temp;

        return angle;
    }
};

// Create instances for both axes
Kalman kalmanPitch;
Kalman kalmanRoll;

unsigned long lastTime;

void setup(void) {
  Serial.begin(115200);
  while (!Serial)
    delay(10); 

  Serial.println("Adafruit MPU6050 Kalman Filter Test!");

  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_2000_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  delay(100);
  lastTime = micros(); // Initialize timer
}

void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // 1. Calculate time delta (dt)
  unsigned long currentTime = micros();
  float dt = (float)(currentTime - lastTime) / 1000000.0f;
  lastTime = currentTime;

  // 2. Calculate Pitch & Roll from raw Accelerometer data (in Radians converted to Degrees)
  // Adafruit library gives data in m/s^2, which works perfectly with atan2
  float accRoll  = atan2(a.acceleration.y, a.acceleration.z) * 180.0 / M_PI;
  float accPitch = atan2(-a.acceleration.x, sqrt(a.acceleration.y * a.acceleration.y + a.acceleration.z * a.acceleration.z)) * 180.0 / M_PI;

  // 3. Convert Gyro rates from rad/s (Adafruit default) to deg/s
  float gyroRateRoll  = g.gyro.x * 180.0 / M_PI;
  float gyroRatePitch = g.gyro.y * 180.0 / M_PI;

  // 4. Process data through the Kalman filters
  float filteredRoll  = kalmanRoll.getAngle(accRoll, gyroRateRoll, dt);
  float filteredPitch = kalmanPitch.getAngle(accPitch, gyroRatePitch, dt);

  // 5. Print out the raw vs filtered values (Open Arduino Serial Plotter to see the difference!)
  Serial.print("AccPitch:");   Serial.print(accPitch);
  Serial.print(",KalmanPitch:"); Serial.print(filteredPitch);
  Serial.print(",AccRoll:");    Serial.print(accRoll);
  Serial.print(",KalmanRoll:");   Serial.println(filteredRoll);

  delay(10); // Changed from 500ms to 10ms for smooth filter tracking (~100Hz)
}
