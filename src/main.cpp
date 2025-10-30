#include <Arduino.h>
#include "ClubPlayCode.h"

// === CONFIGURACIÓN DE PINES ===
// Pines del sensor ultrasónico
#define TRIG_PIN  5
#define ECHO_PIN  18

// Pines del driver de motor MX1508
#define IN1 26   // Motor izquierdo
#define IN2 27
#define IN3 32   // Motor derecho
#define IN4 33

// Crear objeto principal
ClubPlayCode robot(TRIG_PIN, ECHO_PIN, IN1, IN2, IN3, IN4);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("=== Iniciando el robot ===");

  robot.iniciar();  // Inicializa sensores y motores
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
    float distancia = robot.leerDistancia();

    Serial.print("Distancia medida: ");
    if (distancia < 0) {
        Serial.println("Fuera de rango");
        robot.detener();
    } else {
        Serial.print(distancia);
        Serial.println(" cm");

        if (distancia > 20) {
            Serial.println("→ Avanzando");
            robot.avanzar(200);
        } else if (distancia > 10) {
            Serial.println("→ Girando izquierda");
            robot.girarIzquierda(180);
        } else {
            Serial.println("→ Obstáculo cerca, retrocediendo");
            robot.retroceder(180);
            delay(500);
            robot.girarDerecha(180);
        }
    }

    delay(500);
}