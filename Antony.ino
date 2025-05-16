#include "BluetoothSerial.h"
#include "driver/gpio.h"

BluetoothSerial SerialBT;

// Pinos dos motores
#define IN1 GPIO_NUM_26
#define IN2 GPIO_NUM_27
#define IN3 GPIO_NUM_14
#define IN4 GPIO_NUM_12

// Enum para os comandos
enum Comando {
  FRENTE = 'F',
  TRAS   = 'T',
  DIREITA= 'D',
  ESQUERDA='E',
  PARAR  = 'P',
  INVALIDO = '?'
};

void setup() {
  Serial.begin(115200);
  Serial.println("Iniciando Robo_Sumo...");

  SerialBT.begin("Robo_Sumo");
  Serial.println("Bluetooth pronto. Aguardando comandos...");

  gpio_set_direction(IN1, GPIO_MODE_OUTPUT);
  gpio_set_direction(IN2, GPIO_MODE_OUTPUT);
  gpio_set_direction(IN3, GPIO_MODE_OUTPUT);
  gpio_set_direction(IN4, GPIO_MODE_OUTPUT);

  parar();
}

void loop() {
  if (SerialBT.available()) {
    char entrada = SerialBT.read();
    Serial.print("Comando recebido: ");
    Serial.println(entrada);

    Comando comando = interpretarComando(entrada);
    executarComando(comando);
  }
}

// Traduz char para Comando (enum)
Comando interpretarComando(char c) {
  switch (c) {
    case 'F': return FRENTE;
    case 'T': return TRAS;
    case 'D': return DIREITA;
    case 'E': return ESQUERDA;
    case 'P': return PARAR;
    default:  return INVALIDO;
  }
}

// Executa comando com verificação
void executarComando(Comando cmd) {
  switch (cmd) {
    case FRENTE: frente(); break;
    case TRAS: tras(); break;
    case DIREITA: direita(); break;
    case ESQUERDA: esquerda(); break;
    case PARAR: parar(); break;
    case INVALIDO:
      SerialBT.println("Comando inválido.");
      Serial.println("Comando inválido recebido.");
      break;
  }
}

// Funções de movimento
inline void frente() {
  gpio_set_level(IN1, 1); gpio_set_level(IN2, 0);
  gpio_set_level(IN3, 1); gpio_set_level(IN4, 0);
  Serial.println("Movendo para frente");
}

inline void tras() {
  gpio_set_level(IN1, 0); gpio_set_level(IN2, 1);
  gpio_set_level(IN3, 0); gpio_set_level(IN4, 1);
  Serial.println("Movendo para trás");
}

inline void direita() {
  gpio_set_level(IN1, 1); gpio_set_level(IN2, 0);
  gpio_set_level(IN3, 0); gpio_set_level(IN4, 1);
  Serial.println("Virando à direita");
}

inline void esquerda() {
  gpio_set_level(IN1, 0); gpio_set_level(IN2, 1);
  gpio_set_level(IN3, 1); gpio_set_level(IN4, 0);
  Serial.println("Virando à esquerda");
}

inline void parar() {
  gpio_set_level(IN1, 0); gpio_set_level(IN2, 0);
  gpio_set_level(IN3, 0); gpio_set_level(IN4, 0);
  Serial.println("Parando");
}
