#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>

#define WIFI_SSID "NOMBRE DE WIFI"
#define WIFI_PASSWORD "CLAVE DE WIFI"

#define FIREBASE_HOST "proyectobia-default-rtdb.firebaseio.com" // NO CAMBIA
#define FIREBASE_AUTH "eE1GOXD70X9b1z2a5AVUDawrfUYWyqcxE3DmqYQP" // NO CAMBIAR

int NUMERO_DE_SERVO_MOTOR = 0; // NO CAMBIAR - OPCIONES: 1, 2, 3, 4
 
FirebaseData ServoMotores;

void setup() {
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.println();
  Serial.print("Conectado");
  while (WiFi.status() != WL_CONNECTED)
  {
      Serial.print(".");
      delay(300);
  }

  Serial.println();
  Serial.print("IP de conexion: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

}
  // LUEGO DE ACTIVAR SERVOMOTOR
  Firebase.setInt(ServoMotores, "/bia/ServoMotorActivo", NUMERO_DE_SERVO_MOTOR);

  // LUEGO DE APAGAR SERVOMOTOR
  Firebase.setInt(ServoMotores, "/bia/ServoMotorActivo", 0);

void loop() {
    int sma = Firebase.getInt(ServoMotores, F("/bia/ActivarServoMotor"));
    if (sma > 0)
    {       
            // ACTIVAR SERVOMOTOR Y LUEGO
            Firebase.setInt(ServoMotores, "/bia/ServoMotorActivo", sma);
            Serial.println(sma);

    }

}