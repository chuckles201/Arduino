// first esp32 sketch!

// Communicating with ESP over wifi
#include <WiFi.h>
#define WIFI_NAME "Brfox"
#define WIFI_PASSWORD "Papa0761"

// port to communicate
const int port = 5001;

// for socket connections!
WiFiServer wifiServer(port);


void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  Serial.println("Setup...");
  // second serial
  Serial2.begin(9600, SERIAL_8N1, 16,17); // Baud rate, config, RX, TX
  

  // setting up wifi mode: connect to wifi
  WiFi.mode(WIFI_STA);
  // disconnect if alr connected
  WiFi.disconnect();
  delay(100);

  // connecting to wifi
  Serial.print("Connecting to ");
  Serial.print(WIFI_NAME);
  WiFi.begin(WIFI_NAME,WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("");
  Serial.print("Setup done | Ip: ");
  Serial.println(WiFi.localIP());

  // beginning server!
  wifiServer.begin();


}

void loop() {
  // Listen for info on socket...
  WiFiClient client = wifiServer.available();
  if (client){
    // checking if connected
    while (client.connected()) {

      // while info available
      if (client.available()) {
        String data = client.readString();
        Serial2.println(data);
        Serial.println(data);
      }
    }

  }


  


}
