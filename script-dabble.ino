/* CONFIGS
esp32 by Espressif Systems version 2.0.4
board: esp32 WROOM
*/

#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <DabbleESP32.h>

// Definição dos pinos conectados à ponte-H
#define MOTOR_DIR_F 13 // Direita Frente
#define MOTOR_DIR_R 12 // Direita Ré (Trás)
#define MOTOR_ESQ_F 27 // Esquerda Frente
#define MOTOR_ESQ_R 26 // Esquerda Ré (Trás)

void setup() {
  Serial.begin(115200);              // Inicializa a comunicação serial
  Dabble.begin("SumoESP32");         // Inicializa o Bluetooth com nome "SumoESP32"

  // Configura os pinos como saída
  pinMode(MOTOR_DIR_F, OUTPUT);
  pinMode(MOTOR_DIR_R, OUTPUT);
  pinMode(MOTOR_ESQ_F, OUTPUT);
  pinMode(MOTOR_ESQ_R, OUTPUT);

  stopMotors(); // Garante que o robô inicie parado
}

void loop() {
  Dabble.processInput(); // Processa comandos do app Dabble

  if (GamePad.isUpPressed()) {
    Serial.println("Comando: Frente");
    moverFrente();
  } 
  else if (GamePad.isDownPressed()) {
    Serial.println("Comando: Trás");
    moverTras();
  } 
  else if (GamePad.isLeftPressed()) {
    Serial.println("Comando: Esquerda");
    virarEsquerda();
  } 
  else if (GamePad.isRightPressed()) {
    Serial.println("Comando: Direita");
    virarDireita();
  } 
  else {
    Serial.println("Comando: Parar");
    stopMotors();
  }
}

// Função para mover o robô para frente
void moverFrente() {
  digitalWrite(MOTOR_DIR_F, HIGH);
  digitalWrite(MOTOR_DIR_R, LOW);
  digitalWrite(MOTOR_ESQ_F, HIGH);
  digitalWrite(MOTOR_ESQ_R, LOW);
}

// Função para mover o robô para trás
void moverTras() {
  digitalWrite(MOTOR_DIR_F, LOW);
  digitalWrite(MOTOR_DIR_R, HIGH);
  digitalWrite(MOTOR_ESQ_F, LOW);
  digitalWrite(MOTOR_ESQ_R, HIGH);
}

// Função para virar para a esquerda (parar motor esquerdo, girar direito para frente)
void virarEsquerda() {
  digitalWrite(MOTOR_DIR_F, HIGH);
  digitalWrite(MOTOR_DIR_R, LOW);
  digitalWrite(MOTOR_ESQ_F, LOW);
  digitalWrite(MOTOR_ESQ_R, LOW);
}

// Função para virar para a direita (parar motor direito, girar esquerdo para frente)
void virarDireita() {
  digitalWrite(MOTOR_DIR_F, LOW);
  digitalWrite(MOTOR_DIR_R, LOW);
  digitalWrite(MOTOR_ESQ_F, HIGH);
  digitalWrite(MOTOR_ESQ_R, LOW);
}

// Função para parar o robô
void stopMotors() {
  digitalWrite(MOTOR_DIR_F, LOW);
  digitalWrite(MOTOR_DIR_R, LOW);
  digitalWrite(MOTOR_ESQ_F, LOW);
  digitalWrite(MOTOR_ESQ_R, LOW);
}
