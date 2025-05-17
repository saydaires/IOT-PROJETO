#include <BluetoothSerial.h>
BluetoothSerial SerialBT;

#define MOTOR_DIR_F 12
#define MOTOR_DIR_R 13
#define MOTOR_ESQ_F 32
#define MOTOR_ESQ_R 35

void setup() {
  Serial.begin(115200);                     
  SerialBT.begin("Equipe02-Sumo");              

  pinMode(MOTOR_DIR_F, OUTPUT);
  pinMode(MOTOR_DIR_R, OUTPUT);
  pinMode(MOTOR_ESQ_F, OUTPUT);
  pinMode(MOTOR_ESQ_R, OUTPUT);

  stopMotors(); 
}

void loop() {
  if (SerialBT.available()) {
    char comando = SerialBT.read();          
    Serial.print("Comando recebido: ");
    Serial.println(comando);

    switch (comando) {
      case '1': moverFrente();     break;    
      case '3': moverTras();       break;    
      case '4': virarEsquerda();   break;    
      case '2': virarDireita();    break;    
      default:
        Serial.println("Comando inválido");
        stopMotors();
        break;
    }
  }
}

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
