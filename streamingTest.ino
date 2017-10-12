#include <ESP8266WiFi.h>
const char* ssid     = "munichmakerlab";
const char* password = "h4ckingr00m";

const char* host = "10.10.10.70";
const int port = 8080;

WiFiClient client;
String payload;

void setup() {
  Serial.begin(115200);
  Serial.println("start");
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(200);
    Serial.print(".");
    ESP.wdtFeed();
  }

  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  // put your setup code here, to run once:

  Serial.print("connecting to ");
  Serial.println(host);
  
  if (! client.connect(host, port)) {
    Serial.println("connection failed");
    return;
  }

}

void loop() {
  // put your main code here, to run repeatedly:

  payload = "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\r";
  Serial.println("Sending:");
  // Serial.println(payload);
  client.print(payload);

  unsigned long timeout = millis();
  while (client.available() == 0) {
    ESP.wdtFeed();
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop(); 
      return;
    }
  }

  Serial.println("Recieved:");
  while(client.available()){
    String line = client.readStringUntil('\n');
    // Serial.print(line);
  }

  Serial.println("closing connection");
  
}
