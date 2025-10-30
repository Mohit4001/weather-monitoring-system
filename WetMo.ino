#include <ESP8266WiFi.h>
#include <DHT.h>
#include <OakOLED.h>

// WiFi Credentials
const char* ssid = "vivo 1820";
const char* password = "12345678";

// Pin Definitions
#define DHTPIN D4
#define DHTTYPE DHT11
const int mq135Pin = A0;

DHT dht(DHTPIN, DHTTYPE);
OakOLED oled;
WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  dht.begin();
  oled.begin();

  // Connect to WiFi
  WiFi.begin(ssid, password);
  oled.clearDisplay();
  oled.setCursor(0, 0);
  oled.setTextSize(1);
  oled.setTextColor(1);
  oled.println("Connecting...");
  oled.display();

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Print IP on Serial & OLED
  Serial.println("\nWiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  oled.clearDisplay();
  oled.setCursor(0, 0);
  oled.println("WiFi Connected");
  oled.println(WiFi.localIP());
  oled.display();

  server.begin();
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  int airRaw = analogRead(mq135Pin);

  // Check for invalid values
  if (isnan(h) || isnan(t)) {
    Serial.println("❌ DHT Reading Failed");
    return;
  }

  // Print to Serial Monitor
  Serial.print("Temp: "); Serial.print(t); Serial.print(" °C, ");
  Serial.print("Humid: "); Serial.print(h); Serial.print(" %, ");
  Serial.print("Air (raw): "); Serial.println(airRaw);

  // Display on OLED
  oled.clearDisplay();
  oled.setCursor(0, 0);
  oled.setTextSize(1);
  oled.println("WEATHER MONITOR");
  oled.print("Temprature: "); oled.println(t);
  oled.print("Humidity: "); oled.println(h);
  oled.print("Air Quality: "); oled.println(airRaw);
  oled.display();

  WiFiClient client = server.available();
  if (client) {
    String html = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
    html += "<!DOCTYPE html><html><head><meta charset='UTF-8'>";
    html += "<title>Weather Monitoring Dashboard</title>";
    html += "<style>";
    html += "body { font-family: Arial, sans-serif; background: #eaf2f8; margin: 0; padding: 0; display: flex; justify-content: center; align-items: center; height: 100vh; }";
    html += ".card { background: #ffffff; padding: 40px; width: 50vw; max-width: 600px;";
    html += "box-shadow: 0 10px 30px rgba(0,0,0,0.2); border-radius: 20px; }";
    html += "h2 { font-size: 32px; color: #2e86c1; margin-bottom: 30px; }";
    html += "p { font-size: 24px; margin: 20px 0; color: #333333; }";
    html += "b { color: #000000; }";
    html += "</style></head><body>";


  html += "<div class='card'>";
  html += "<h2>📡 Weather Monitoring Dashboard</h2>";
  html += "<p><b>🌡️ Temperature:</b> " + String(t) + " °C</p>";
  html += "<p><b>💧 Humidity:</b> " + String(h) + " %</p>";
  html += "<p><b>🌫️ Air Quality:</b> " + String(airRaw) + " (PPM)</p>";
  html += "</div></body></html>";

  client.print(html);
  delay(1);
  client.stop();
}


  delay(5000); // Wait 5 sec before next reading
}
