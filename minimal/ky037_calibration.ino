// Writes out the analog reading and its average for calibrating them.
// Format matches the Arduino IDE Serial Plotter.

// Define the pin connections.
// Assuming each sensor has a digital and an analog pin
// analog pins not used currently
int sensorPins[][2] = {{38, A1}, {3, A0}, {49, A2}, {48, A3}};
String sensorNames[] = {"N", "E", "S", "W"};

// Define arrays to store the last 100 analog readings for each sensor
const int numSamples = 30;
int analogReadings[4][numSamples];  // 4 sensors, each with 100 samples
int readIndex[4] = {0, 0, 0, 0};  // Current position in each sensor's readings array

void setup() {
  // Initialize serial communication
  Serial.begin(115200);

  // Initialize sensor pins and readings arrays
  for (int i = 0; i < 4; i++) {
    pinMode(sensorPins[i][0], INPUT);  // Digital pin as input
    // Fill the readings arrays with 0s
    for (int j = 0; j < numSamples; j++) {
      analogReadings[i][j] = 0;
    }
  }
}

void loop() {
  // Read from each sensor, update readings, and print values
  for (int i = 0; i < 4; i++) {
    int digitalValue = digitalRead(sensorPins[i][0]);
    int analogValue = analogRead(sensorPins[i][1]);
    String sensorName = sensorNames[i];

    // Update the readings array with the new value
    analogReadings[i][readIndex[i]] = analogValue;
    readIndex[i] = (readIndex[i] + 1) % numSamples;  // Move to the next position in the array

    // Calculate the average of the last 100 readings
    long sum = 0;
    for (int j = 0; j < numSamples; j++) {
      sum += analogReadings[i][j];
    }
    long average = sum / numSamples;

    // Print the sensor name, digital value, and average analog value
    Serial.print(sensorName + "Avg:");
    Serial.print(average);
    Serial.print(", " + sensorName + "A:");
    Serial.print(analogValue);

    if (i < 3) {
      Serial.print(", ");  // Separate the sensor readings
    }
  }
  Serial.println();  // End of a set of readings

  delay(200);  // Adjust delay as needed
}
