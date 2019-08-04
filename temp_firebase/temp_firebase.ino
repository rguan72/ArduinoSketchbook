#include <Firebase_Arduino_WiFiNINA.h>
#include <Firebase_Arduino_WiFiNINA_HTTPClient.h>
#include <dht.h>
#include <WiFiNINA.h>

#define FIREBASE_HOST "urbanbee-8b6d6.firebaseio.com"
#define FIREBASE_AUTH "nBOkkUD9aqlJ4flYdSOy1Nnm5Xoy81A4IlJdMR2K"
#define WIFI_SSID "ATT6ypc8Pk"
#define WIFI_PASSWORD "4sqx4xka9682"

//Define Firebase data object
FirebaseData firebaseData;
int status = WL_IDLE_STATUS;

dht DHT;
#define DHT11_PIN A0

void setup() {
  // put your setup code here, to run once:
    pinMode(LED_BUILTIN, OUTPUT);
     //Initialize serial and wait for port to open:
    Serial.begin(9600);
    while (!Serial) {
      ; // wait for serial port to connect. Needed for native USB port only
    }
  
    // check for the WiFi module:
    if (WiFi.status() == WL_NO_MODULE) {
      Serial.println("Communication with WiFi module failed!");
      // don't continue
      while (true);
    }
  
    String fv = WiFi.firmwareVersion();
    if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
      Serial.println("Please upgrade the firmware");
    }
  
    // attempt to connect to Wifi network:
    while (status != WL_CONNECTED) {
      Serial.print("Attempting to connect to WPA SSID: ");
      Serial.println(WIFI_SSID);
      // Connect to WPA/WPA2 network:
      status = WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  
      // wait 10 seconds for connection:
      delay(10000);
    }
  
    // you're connected now, so print out the data:
    Serial.print("You're connected to the network");
    Serial.println();
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH, WIFI_SSID, WIFI_PASSWORD);
    Serial.print("You've connected to Firebase");
    Serial.println();
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);

  int chk = DHT.read11(DHT11_PIN);
  Serial.print("Temperature = ");
  Serial.println(DHT.temperature);
  Serial.print("Humidity = ");
  Serial.println(DHT.humidity);
  if (Firebase.setFloat(firebaseData, "/hives/-LkwlsGCeRtgzJ5NJnx6/temp", DHT.temperature)){

      //Success, then read the payload value return from server
      //This confirmed that your data was set to database as float number
    
      if (firebaseData.dataType() == "float")
        Serial.println(firebaseData.floatData());
    
    } else {
      //Failed, then print out the error detail
        Serial.println("errored");
        Serial.println(firebaseData.errorReason());
    }
  if (Firebase.setFloat(firebaseData, "/hives/-LkwlsGCeRtgzJ5NJnx6/humidity", DHT.humidity)){

      //Success, then read the payload value return from server
      //This confirmed that your data was set to database as float number
    
      if (firebaseData.dataType() == "float")
        Serial.println(firebaseData.floatData());
    
    } else {
      //Failed, then print out the error detail
        Serial.println("errored");
        Serial.println(firebaseData.errorReason());
    }
  delay(1000);


}
