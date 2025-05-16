/* 

O que falta para o code abaixo compilar em outras máquinas:

0. Em um dispositivo móvel ANDROID/IOS, instale o aplicativo "Arduino ESP Bluetooth - Dabble"

1. em Tools > Board > Board Manager instale a board "esp32 by Espressif Systems" na VERSÃO 2.0.14;

2. Após a instalação, em Tools > Board, selecione a board "ESP WROOM";

3. No menu lateral esquerdo, selecione a opção "libraries" e baixe a biblioteca "DabbleESP32";

4. Compile o código.

 */

#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <DabbleESP32.h>

// Definição dos pinos conectados à ponte-H
#define IN1 13
#define IN2 12
#define IN3 14
#define IN4 27

void setup() {
  Serial.begin(115200);           // Inicializa a comunicação serial
  Dabble.begin("SumoESP32");      // Inicializa o Dabble com o nome Bluetooth

  // Configura os pinos como saída
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  Stop(); // Garante que o robô inicie parado
}

void loop() {
  Dabble.processInput(); // Processa as entradas do Dabble

  if (GamePad.isUpPressed()) {
    forward();
  } else if (GamePad.isDownPressed()) {
    backward();
  } else {
    Stop();
  }
}

// Função para mover o robô para frente
void forward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

// Função para mover o robô para trás
void backward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

// Função para parar o robô
void Stop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
