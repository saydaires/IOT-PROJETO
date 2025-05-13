 #include <DabbleESP32.h>

#define motor_esquer 9
#define motor_direi 10

void setup() {
  pinMode(motor_esquer, OUTPUT);
  pinMode(motor_direi, OUTPUT);

  Serial.begin(115200); // Comunicação com o PC (depuração)
  Dabble.begin("ESP32_Robot"); // Nome visível no app Dabble
}

void loop() {
  Dabble.processInput(); // Atualiza dados recebidos do app

  if (GamePad.isUpPressed()) {
    digitalWrite(motor_esquer, HIGH);
    digitalWrite(motor_direi, HIGH);
    Serial.println("Frente");
  }
  else if (GamePad.isDownPressed()) {
    digitalWrite(motor_esquer, HIGH);
    digitalWrite(motor_direi, HIGH); // ajustar se quiser direção real de ré
    Serial.println("Tras");
  }
  else if (GamePad.isLeftPressed()) {
    digitalWrite(motor_esquer, LOW);
    digitalWrite(motor_direi, HIGH);
    Serial.println("Esquerda");
  }
  else if (GamePad.isRightPressed()) {
    digitalWrite(motor_esquer, HIGH);
    digitalWrite(motor_direi, LOW);
    Serial.println("Direita");
  }
  else {
    digitalWrite(motor_esquer, LOW);
    digitalWrite(motor_direi, LOW);
    Serial.println("Parado");
  }

  delay(150);
}
