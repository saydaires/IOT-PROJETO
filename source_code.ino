#include <BluetoothSerial.h>
BluetoothSerial SerialBT;

// Pinos dos motores
#define MOTOR_DIR_F 18
#define MOTOR_DIR_R 19
#define MOTOR_ESQ_F 22
#define MOTOR_ESQ_R 23

void setup() {
  Serial.begin(115200);                     // Monitor serial
  SerialBT.begin("Equipe02-SumoESP32");              // Nome do dispositivo Bluetooth

  // Pinos como saída
  pinMode(MOTOR_DIR_F, OUTPUT);
  pinMode(MOTOR_DIR_R, OUTPUT);
  pinMode(MOTOR_ESQ_F, OUTPUT);
  pinMode(MOTOR_ESQ_R, OUTPUT);

  stopMotors(); // Inicia parado
}

void loop() {
  if (SerialBT.available()) {
    char comando = SerialBT.read();          // Lê um caractere enviado
    Serial.print("Comando recebido: ");
    Serial.println(comando);

    // Interpreta comandos recebidos
    switch (comando) {
      case '1': moverFrente();     break;    // Frente
      case '3': moverTras();       break;    // Trás
      case '4': virarEsquerda();   break;    // Esquerda
      case '2': virarDireita();    break;    // Direita
      //case 'P': stopMotors();      break;    // Parar
      default:
        Serial.println("Comando inválido");
        stopMotors();
        break;
    }
  }
}

// Funções de movimento
void moverFrente() {
  Serial.println("FRENTE");
  digitalWrite(MOTOR_DIR_F, HIGH);
  digitalWrite(MOTOR_DIR_R, LOW);
  digitalWrite(MOTOR_ESQ_F, HIGH);
  digitalWrite(MOTOR_ESQ_R, LOW);
}

void moverTras() {
  Serial.println("TRÁS");
  digitalWrite(MOTOR_DIR_F, LOW);
  digitalWrite(MOTOR_DIR_R, HIGH);
  digitalWrite(MOTOR_ESQ_F, LOW);
  digitalWrite(MOTOR_ESQ_R, HIGH);
}

void virarEsquerda() {
  Serial.println("ESQUERDA");
  digitalWrite(MOTOR_DIR_F, HIGH);
  digitalWrite(MOTOR_DIR_R, LOW);
  digitalWrite(MOTOR_ESQ_F, LOW);
  digitalWrite(MOTOR_ESQ_R, LOW);
}

void virarDireita() {
  Serial.println("DIREITA");
  digitalWrite(MOTOR_DIR_F, LOW);
  digitalWrite(MOTOR_DIR_R, LOW);
  digitalWrite(MOTOR_ESQ_F, HIGH);
  digitalWrite(MOTOR_ESQ_R, LOW);
}

void stopMotors() {
  Serial.println("PARANDO");
  digitalWrite(MOTOR_DIR_F, LOW);
  digitalWrite(MOTOR_DIR_R, LOW);
  digitalWrite(MOTOR_ESQ_F, LOW);
  digitalWrite(MOTOR_ESQ_R, LOW);
}
