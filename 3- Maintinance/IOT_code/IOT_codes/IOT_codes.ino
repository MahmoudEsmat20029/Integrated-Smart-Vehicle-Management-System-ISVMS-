#include <WiFi.h>               // Include WiFi library
#include <PubSubClient.h>       // Include PubSubClient library for MQTT
#include <TinyGPSPlus.h>        // Include TinyGPS++ library for GPS
#include <Wire.h>               // Include Wire library for I2C communication
#include <Adafruit_Sensor.h>    // Include Adafruit Sensor library
#include <Adafruit_BMP085_U.h>  // Include Adafruit BMP085 library

// WiFi credentials
const char* ssid = "TP-LINK";            // WiFi network name
const char* password = "hello wirld 133";          // WiFi password

// MQTT Broker settings
const char* mqtt_server = "Test.mosquitto.org"; // MQTT Broker IP address
const char* outTopic = "/kdi/inTopic";        // Topic to publish messages
const char* inTopic = "/kdi/outTopic";        // Topic to subscribe to
const char* sensorTopic = "esp32/Sensors/Graduation_Project"; // Topic to publish sensor data
const int mqtt_port = 1883;                   // MQTT Broker port

// GPS settings
const int RXPin = 16, TXPin = 17;             // GPS module RX and TX pins
const uint32_t GPSBaud = 9600;                // GPS module baud rate

// LM35 sensor pin
const int lm35Pin = 34;     // Analog input pin for LM35 sensor

WiFiClient espClient;                // Create WiFi client
PubSubClient client(espClient);      // Create MQTT client
TinyGPSPlus gps;                     // Create TinyGPS++ object
Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085);     // Create BMP085 sensor object

char clientName[50];                 // Buffer for MQTT client name
char msg[100];                       // Buffer for MQTT messages
float lat, lon;                      // Variables for latitude and longitude
unsigned long previousMillis = 0;    // Store last time GPS data was published
const long interval = 10000;         // Interval at which to publish GPS data (10 seconds)

void setup() {
  Serial.begin(9600); // Start Serial Monitor at 9600 baud rate

  // Initialize GPS hardware serial
  Serial1.begin(GPSBaud, SERIAL_8N1, RXPin, TXPin);

  setup_wifi(); // Connect to WiFi

  // Auto-generate a unique client name based on ESP32 MAC address
  uint64_t chipid = ESP.getEfuseMac(); // Get unique chip ID
  String sChipID = String((uint16_t)(chipid >> 32), HEX) + String((uint32_t)chipid, HEX);
  sChipID.toCharArray(clientName, sChipID.length() + 1);
  Serial.println(clientName);

  client.setServer(mqtt_server, mqtt_port); // Set MQTT server and port
  client.setCallback(callback);        // Set callback function for incoming messages

  // Initialize BMP085 sensor
  if (!bmp.begin()) {
    Serial.print("Could not find a valid BMP085 sensor, check wiring!");
    while (1); // Stay here if sensor initialization fails
  }

  // Connect to MQTT Broker
  while (!client.connected()) {
    if (client.connect(clientName)) { // Unique MQTT client ID
      Serial.println("Connected to MQTT Broker");
      client.subscribe(inTopic); // Subscribe to topic
    } else {
      Serial.println("Retrying MQTT connection...");
      delay(2000); // Wait 2 seconds before retrying
    }
  }
}

void setup_wifi() {
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password); // Start WiFi connection

  while (WiFi.status() != WL_CONNECTED) { // Wait until connected
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

// Handle incoming MQTT messages
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);   // Print message payload
  }
  Serial.println();
}

// Reconnect to MQTT broker if disconnected
void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect(clientName)) { // Try to connect
      Serial.println("connected");
      client.publish(outTopic, "Reconnected"); // Publish reconnect message
      client.subscribe(inTopic);               // Subscribe to topic
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000); // Wait before retrying
    }
  }
}

// Function to process GPS data
void displayInfo() {
  if (gps.location.isValid()) { // Check if GPS location is valid
    lat = gps.location.lat();
    lon = gps.location.lng();
    Serial.print("Latitude: ");
    Serial.print(lat, 6);
    Serial.print(", Longitude: ");
    Serial.println(lon, 6);
  } else {
    Serial.println("Invalid GPS data.");
  }
}

void loop() {
  if (!client.connected()) {
    reconnect(); // Ensure MQTT connection
  }
  client.loop(); // Handle MQTT communication

  while (Serial1.available() > 0) {
    gps.encode(Serial1.read()); // Feed GPS data to TinyGPS++
  }

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    displayInfo(); // Update latitude and longitude
    if (gps.location.isValid() && client.connected()) {
      sprintf(msg, "{\"lat\":%.5f,\"lon\":%.5f}", lat, lon);
      Serial.println(msg); // Print GPS data
      client.publish(outTopic, msg); // Publish GPS data to MQTT broker
    }
  }

  // Read temperature from LM35 sensor
  int adcValue = analogRead(lm35Pin);          // Read analog value from LM35
  float voltage = adcValue * 3.3 / 4095.0;    // Convert analog value to voltage
  float lm35Temperature = voltage * 100.0;       // Convert voltage to temperature

  sensors_event_t event; // Create sensor event object

  // Read pressure from BMP085 sensor
  bmp.getEvent(&event);
  if (event.pressure) {
    float bmpTemperature;
    bmp.getTemperature(&bmpTemperature); // Get temperature from BMP085 sensor

    // Create payload with both temperature and pressure data
    String payload = "Pressure: " + String(event.pressure) + " Pa\n";
    payload += "LM35 Temperature: " + String(lm35Temperature) + " °C\n";
    payload += "BMP085 Temperature: " + String(bmpTemperature) + " °C";

    // Publish combined data to MQTT topic
    client.publish(sensorTopic, payload.c_str());
    Serial.println(payload); // Print combined data to Serial Monitor
  }

  delay(1000); // Wait 1 second before next reading
}