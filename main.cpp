/*---------------------------------------------------------------------------------------------------

Autor: Adler
Título: Desafio Assobio
Placa utilizada: Arduino Uno

Funcionamento:
Este projeto tem por objetivo coletar valores aleatórios de temperatura e, a partir disso, 
tomar uma série de decisões.

Para evitar condições inesperadas, são coletados 100 valores de temperatura e é feita uma 
média com eles, fazendo com que, caso hajam erros de leitura, o sistema os ignora.

Já para a verificação, foi feita uma função responsável por conferir se o valor de temperatura 
está dentro ou não de um limite de temperatura agradável (10°C<T<40°C). Se estiver o dispositivo
segue o funcionamento normal, mas se estiver acima do limite (>40°C), deve ligar uma LED vermelha
e desligar um motor interno, em uma tentativa de diminuir a atividade. Caso estiver abaixo do limite
(<10°C), deve ligar uma LED azul e ligar um motor interno, em uma tentativa de aumentar a atividade.

Para facilitar o teste do funcionamento do programa, pode-se alterar os valores do limite da função
criadora de números aleatórios (linha 51), como nos exemplos a seguir:
random(-50,9)   -> Frio
random(41,110)  -> Quente
random(10,40)   -> Agradável
random(-50,110) -> Aleatório (mas provável de ser agradável)

---------------------------------------------------------------------------------------------------*/

#include <Arduino.h>

// Portas de saída
#define led_quente 13 // LED que indica se a temperatura está alta (ligada se sim, desligada se não)
#define led_frio 12   // LED que indica se a temperatura está baixa (ligada se sim, desligada se não)
#define motor 11      // Componente que englobaria todas as funcionalidades do dispositivo

// Variáveis auxiliares
int aux_temperatura = 0; // Armazena todas as temperaturas obtidas
int aux_i = 0;           // Índice da iteração
 
// Função para verificação da temperatura
void verifica_temperatura(float);

// Definições iniciais
void setup() {
  Serial.begin(9600); 
  pinMode(led_quente,OUTPUT);
  pinMode(led_frio,OUTPUT);
  pinMode(motor,OUTPUT);
}

// Laço principal
void loop() {
  // Coleta 100 números aleatórios de temperatura para manter uma constância dos valores
  if (aux_i < 100){
    aux_temperatura += random(-50,110);         
    aux_i += 1;                                  
  }
  else{
    float temperatura = aux_temperatura/aux_i;  // Calcula a média das temperaturas
    verifica_temperatura(temperatura);          // Aplica a média na função
    aux_temperatura = 0;                        // Reinicia as variáveis auxiliares
    aux_i = 0;
  }
}

// Função para verificar se a temperatura coleta está fora dos padrões desejados
void verifica_temperatura(float T) {
  if (T > 40){
    Serial.println("ALERTA QUENTE!!!");
    digitalWrite(led_quente, HIGH);      // Liga led vermelha
    digitalWrite(motor, LOW);            // Desliga o motor
  }
  else if (T< 10){
    Serial.println("ALERTA FRIO!!!");
    digitalWrite(led_frio, HIGH);        // Liga led azul
    digitalWrite(motor, HIGH);           // Liga o motor
  }
  else{
    Serial.println(T);
    digitalWrite(led_quente, LOW);       // Desliga led vermelha
    digitalWrite(led_frio, LOW);         // Desliga led vermelha
  }
}
