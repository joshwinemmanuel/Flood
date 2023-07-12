
#if defined(ESP32)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif

#include <Firebase_ESP_Client.h>

// Provide the token generation process info.
#include <addons/TokenHelper.h>

// Provide the RTDB payload printing info and other helper functions.
#include <addons/RTDBHelper.h>

/* 1. Define the WiFi credentials */
#define WIFI_SSID "VATTAKKALAYIL HOME"
#define WIFI_PASSWORD "11111111"

// For the following credentials, see examples/Authentications/SignInAsUser/EmailPassword/EmailPassword.ino

/* 2. Define the API Key */
#define API_KEY "AIzaSyAJ0ZkMu2nybAYjTE9dIgfzZfN6WduOcdc"

/* 3. Define the RTDB URL */
#define DATABASE_URL "flood-detector-c9726-default-rtdb.firebaseio.com" //<databaseName>.firebaseio.com or <databaseName>.<region>.firebasedatabase.app

/* 4. Define the user Email and password that alreadey registerd or added in your project */
#define USER_EMAIL "joshwinejohnson@gmail.com"
#define USER_PASSWORD "Nopassword123#"

// Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;

unsigned long count = 0;
int Buzzer = 15;
int level1 = 15;
int level2 = 13;
int a;
int b;
int z = 1000; // Adjust this value from 100 to 1023 if your circuit do not show correct value.


void setup()
{
  pinMode(level1, INPUT);
  pinMode(level2, INPUT);
  Serial.begin(115200);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);

  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the user sign in credentials */
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; // see addons/TokenHelper.h


#if defined(ESP8266)
  // In ESP8266 required for BearSSL rx/tx buffer for large data handle, increase Rx size as needed.
  fbdo.setBSSLBufferSize(2048 /* Rx buffer size in bytes from 512 - 16384 */, 2048 /* Tx buffer size in bytes from 512 - 16384 */);
#endif

  // Limit the size of response payload to be collected in FirebaseData
  fbdo.setResponseSize(2048);

  Firebase.begin(&config, &auth);

  // Comment or pass false value when WiFi reconnection will control by your code or third party library
  Firebase.reconnectWiFi(true);

  Firebase.setDoubleDigits(5);

  config.timeout.serverResponse = 10 * 1000;

}

void loop()
{

  // Firebase.ready() should be called repeatedly to handle authentication tasks.

  if (Firebase.ready() && (millis() - sendDataPrevMillis > 500 || sendDataPrevMillis == 0))
  {
    sendDataPrevMillis = millis();

    a = analogRead(level1);
    b = analogRead(level2);
    Serial.print(a);
    Serial.print(",");
    Serial.println(b);
    
    if (analogRead(A0) < z )
    {
      Serial.println(", hanna found water at level 2");
      Firebase.RTDB.setInt(&fbdo, F("/test/int"), 2);
      digitalWrite (Buzzer, HIGH); //turn buzzer on
  delay(1000);
    }
    else
    {
      if (analogRead(level1) > z )
      {
        Serial.println(", hanna found water at level 1");
        Firebase.RTDB.setInt(&fbdo, F("/test/int"), 1);
      }
      else
      {
      Serial.println(", hanna found water at level 0");
      Firebase.RTDB.setInt(&fbdo, F("/test/int"), 0);
      }
    }
    


  }
}

\
