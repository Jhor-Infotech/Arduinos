/*
     CÓDIGO:  Q0600
     AUTOR:   BrincandoComIdeias
     LINK:    https://www.youtube.com/brincandocomideias ; https://cursodearduino.net/ ; https://cursoderobotica.net
     COMPRE:  https://www.arducore.com.br/
     SKETCH:  Carrinho Baja Team Arduino
     DATA:    27/12/2019
*/

// INCLUSÃO DE BIBLIOTECAS
#include "motor.h"
#include <SoftwareSerial.h>
#include "PiscaLed.h"

// NOVAS INCLUSÕES E DEFINIÇÕES
#include "Servo.h" // Inclui a Biblioteca Servo.h
// Variáveis com botões direita/esquerda
// int leituraBotaoAesquerda = 0; // Variável para uso de botão - pushbotton
// int leituraBotaoBdireita = 0; // Variável para uso de botão - pushbotton
// int angulo = 90; // Ajusta o ângulo inicial do Servo em 90º
  // FIM DAS NOVAS INCLUSÕES E DEFINIÇÕES

// DEFINIÇÕES DE PINOS
#define pinFarol 12
#define pinLanterna 3
#define pinBuzina 4
#define pinTx 14
#define pinRx 15

// DEFINIÇÕES
#define LIGADO HIGH
#define DESLIGADO LOW

// INSTANCIANDO OBJETOS
SoftwareSerial btSerial(pinRx, pinTx); // RX, TX
// Servo servoDirecao; // Cria o objeto servo para programação

// DECLARAÇÃO DE FUNÇÕES
PiscaLed farol(pinFarol, 350);
PiscaLed lanterna(pinLanterna, 350);

// DECLARAÇÃO DE VARIÁVEIS
char comando;
bool estadoFarol, estadoLanterna, estadoPisca;
// -----------------------------------------------------------------
void setup() {
  Serial.begin(9600);
  btSerial.begin(9600);
  // Portas digitais que controlam os motores - pin1 = motor1a etc
  pinMode(pin1, OUTPUT); // motor 1a porta digital 10
  pinMode(pin2, OUTPUT); // motor 1b porta digital 9
 // pinMode (botaoAesquerda, INPUT); // substituindo pinMode(pin4, OUTPUT) = motor 2b porta digital 7; MAS botaoAesquerda DEIXA DE EXISTIR AO SE USAR O BLUETOOTH
 // pinMode (botaoBdireita, INPUT); // substituindo pinMode(pin3, OUTPUT) = motor 2a porta digital 8 ; MAS botaoBdireita DEIXA DE EXISTIR AO SE USAR O BLUETOOTH
 // pinMode(setasEsquerda, OUTPUT);
 // pinMode(setasDireita, OUTPUT);
  servoDirecao.attach(7); // Declara o pino do servo - porta digital 7, NO LUGAR DO botaoAesquerda, q deixará de existir
  servoDirecao.write(angulo); // Inicia o servoDirecao em 90º
  pinMode(pinBuzina, OUTPUT);
  digitalWrite(pinFarol, LOW);
  digitalWrite(pinLanterna, LOW);
  digitalWrite(pinBuzina, LOW);

  pinMode(pinBuzina, OUTPUT);

  digitalWrite(pinFarol, LOW);
  digitalWrite(pinLanterna, LOW);
  digitalWrite(pinBuzina, LOW);

  estadoFarol = estadoLanterna = estadoPisca = DESLIGADO;

  Serial.println("Fim Setup");
  delay(2000);
}
//---------------------------------------------------------------------------------------------
void loop() {
  /*
  
  // Ação dos botões/funções viraAdireita/viraAesquerda
  // Na implementação real as leituras dos botões deixarão de existir,
  // pois as funções virtaAesquerda e viraAdireita serão invocadas nas funções do switch (comando)
     leituraBotaoAesquerda = digitalRead(botaoAesquerda);
  // Exibindo a leitura do botaoAesquerda no monitor serial
     Serial.println (leituraBotaoAesquerda);
     delay(250)
  if (leituraBotaoAesquerda == 1 && leituraBotaoBdireita == 0) {
    // Invoca a função viraAesquerda
    viraAesquerda(); 
  }  
  leituraBotaoBdireita = digitalRead(botaoBdireita);
     Exibindo a leitura do botaoAesquerda no monitor serial
     Serial.println (leituraBotaoBdireita);
     delay(250);
  if (leituraBotaoBdireita == 1 && leituraBotaoAesquerda == 0) {
    // Invoca a função viraAdireita
    viraAdireita(); 
  }  
  // FIM Ação dos botões/funções viraAdireita/viraAesquerda
  
  */

  if (estadoPisca) {
    farol.loop();
    lanterna.loop();
  }

  if (btSerial.available()) {
    comando = btSerial.read();
  }

  switch (comando) {
    case 'F': {
        moveFrente();
        break;
      }
    case 'I': {
        frenteDireita();
        break;
      }
    case 'G': {
        frenteEsquerda();
        break;
      }
    case 'R': {
        direita();
        break;
      }
    case 'L': {
        esquerda();
        break;
      }
    case 'B': {
        moveRe();
        break;
      }
    case 'H': {
        reEsquerda();
        break;
      }
    case 'J': {
        reDireita();
        break;
      }
    case 'W': {
      
        digitalWrite(pinFarol, HIGH);
        estadoFarol = LIGADO;
       
        break;
      }
    case 'w': {
      
        digitalWrite(pinFarol, LOW);
        estadoFarol = DESLIGADO;
       
        break;
      }
    case 'U': {
      
        digitalWrite(pinLanterna, HIGH);
        estadoLanterna = LIGADO;
  
        break;
      }
    case 'u': {
     
        digitalWrite(pinLanterna, LOW);
        estadoLanterna = DESLIGADO;
     
      Serial.println("Ola, Mundo!!");  
      break;
      }
    case 'V': {
        tone(pinBuzina, 380);
        break;
      }
    case 'v': {
        noTone(pinBuzina);
        break;
      }
    case 'X': {
      
        farol.play();
        lanterna.play();
        estadoPisca = LIGADO;
         
        break;
      }
    case 'x': {
        farol.stop();
        lanterna.stop();
        
        farol.loop();
        lanterna.loop();

        estadoPisca = DESLIGADO;

        if ( estadoLanterna) digitalWrite(pinLanterna, HIGH);
        else digitalWrite(pinLanterna, LOW);

        if ( estadoFarol) digitalWrite(pinFarol, HIGH);
        else digitalWrite(pinFarol, LOW);
     
      break;
      }
    default: {
        parar();
        break;
      }
  }
}



// IMPLEMENTO DE FUNÇÕES
