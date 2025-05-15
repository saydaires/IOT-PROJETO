// Habilita os módulos personalizados do Dabble
#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <Dabble.h> // Biblioteca para comunicação com app Dabble via Bluetooth
// Biblioteca de controle direto dos pinos no ESP32
#include "driver/gpio.h"
// Define os pinos conectados à ponte H para os motores
#define INT1 2
#define INT2 3
#define INT3 4
#define INT4 5
// Define máscaras de bits para controle rápido desses pinos
#define INT1_MASK (1ULL << INT1)
#define INT2_MASK (1ULL << INT2)
#define INT3_MASK (1ULL << INT3)
#define INT4_MASK (1ULL << INT4)
// Configuração inicial
void setup() {
 Serial.begin(250000); // Inicializa comunicação serial (velocidade alta para test Dabble.begin(9600, 7, 6); // Inicia comunicação Bluetooth via Dabble nos pinos 7 (RX) // Cria estrutura para configurar os pinos de saída
 gpio_config_t io_conf = {
 .pin_bit_mask = INT1_MASK | INT2_MASK | INT3_MASK | INT4_MASK, // Define os 4 pinos
 .mode = GPIO_MODE_OUTPUT, // Define como saída
 .pull_up_en = GPIO_PULLUP_DISABLE, // Sem resistor de pull-up
 .pull_down_en = GPIO_PULLDOWN_DISABLE, // Sem resistor de pull-down
 .intr_type = GPIO_INTR_DISABLE // Sem interrupção
 };
 gpio_config(&io_conf); // Aplica a configuração
 // Define todos os pinos como LOW (parado)
 GPIO.out_w1tc = INT1_MASK | INT2_MASK | INT3_MASK | INT4_MASK;
}
// Loop principal
void loop() {
 Dabble.processInput(); // Processa os comandos do aplicativo Dabble
 if (GamePad.isUpPressed()) {
 // Movimento para frente
 // INT1 e INT4 = LOW; INT2 e INT3 = HIGH
 GPIO.out_w1tc = INT1_MASK | INT4_MASK; // Limpa (LOW) INT1 e INT4
 GPIO.out_w1ts = INT2_MASK | INT3_MASK; // Seta (HIGH) INT2 e INT3
 } else if (GamePad.isDownPressed()) {
 // Movimento para trás
 // INT2 e INT3 = LOW; INT1 e INT4 = HIGH
 GPIO.out_w1tc = INT2_MASK | INT3_MASK;
 GPIO.out_w1ts = INT1_MASK | INT4_MASK;
 } else if (GamePad.isLeftPressed()) {
 // Gira para esquerda
 // INT2 e INT4 = LOW; INT1 e INT3 = HIGH
 GPIO.out_w1tc = INT2_MASK | INT4_MASK;
 GPIO.out_w1ts = INT1_MASK | INT3_MASK;
 } else if (GamePad.isRightPressed()) {
 // Gira para direita
 // INT1 e INT3 = LOW; INT2 e INT4 = HIGH
 GPIO.out_w1tc = INT1_MASK | INT3_MASK;
 GPIO.out_w1ts = INT2_MASK | INT4_MASK;
 } else {
 // Parado: todos os pinos em LOW
 GPIO.out_w1tc = INT1_MASK | INT2_MASK | INT3_MASK | INT4_MASK;
 }
}
