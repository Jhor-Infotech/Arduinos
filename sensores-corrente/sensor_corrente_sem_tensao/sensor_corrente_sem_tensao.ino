// UNIVESP
// ENG. DA COMPUTAÇÃO
// PROJETO INTEGRADOR V
// POLO JUQUITIBA
// SENSOR DE CORRENTE AC

#include <LiquidCrystal_I2C.h>        // Incluindo a biblioteca do módulo I2C para conexao e "reconhecimento" do display pelo arduino
#include <Wire.h>                     // Incluindo a biblioteca "Wire", a qual estabelece a comunicação entre o display e arduino
LiquidCrystal_I2C lcd(0x27, 20,4);    // Identificando a porta, quantidades de colunas e linhas do display
                                        /* Seta os pinos do I2C usado (padrao da biblioteca, caso se use protoboard
                                        addr, en,rw,rs,d4,d5,d6,d7,bl,blpol
                                        LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address
                                        */

int pinoSensor =A0;                     //

int sensorValue_aux = 0;                //
float valorSensor = 0;                  //
float valorCorrente = 0;                //
float voltsporUnidade = 0.004887586;    // 5%1023
// Para ACS712 de  5 Amperes use 0.185  //
// Para ACS712 de 10 Amperes use 0.100  // 
//  Para ACS712 de 30 Amperes use 0.066 //
float sensibilidade = 0.185;
int tensao = 127;                       //Declarando a tensão do circuito elétrico AC  
float energia = 0;                   

void setup() {
  pinMode(pinoSensor, INPUT);  
  lcd.init(); // inicializando o display lcd de 20 colunas e 4 linhas
  lcd.backlight(); // Mantendo acesa a luz de fundo do display, ao invés do blink abaixo comentado
}
void loop() {
calculos();      // Invocando a função dos cálculos da corrente
lcd.clear();
delay(1500);
tela_apresentacao(); // Invocando a função de apresentação da Faculdade, Graduação, Disciplina e polo
exibir_tensao_corrente();
exibir_potencia_consumo();
}

long calculos(){
  for(int i=10000; i>0; i--){    
    sensorValue_aux = (analogRead(pinoSensor) -510); /* le o sensor na pino analogico A0 e ajusta o valor lido 
                                                        já que a saída do sensor é (1023)vcc/2 para corrente =0
                                                     */    
    valorSensor += pow(sensorValue_aux,2); // somam os quadrados das leituras.
     // delay(1);
  }  
  valorSensor = (sqrt(valorSensor/ 10000)) * voltsporUnidade; // finaliza o calculo da média quadratica e ajusta o valor lido para volts
  valorCorrente = (valorSensor/sensibilidade);                // calcula a corrente considerando a sensibilidade do sernsor (185 mV por amper)
  //tratamento para possivel ruido
  //O ACS712 para 30 Amperes é projetado para fazer leitura de valores alto acima de 0.25 Amperes até 30.
  // por isso é normal ocorrer ruidos de até 0.20A e este deve ser tratado
    if(valorCorrente <= 0.095){
    valorCorrente = 0; 
  }
  valorSensor =0;
  energia +=(tensao*valorCorrente*1.2/1000); //calculando e imprimindo a energia consumida num ciclo de 1,2s


}
                      char tela_apresentacao(){
                        lcd.clear();                      // Limpando a tela antes da impressão da apresnetação
                        lcd.setCursor(6,0);               // Posicionando o cursor na 7ª coluna e na 1ª linha
                        lcd.print("UNIVESP");             // Imprindo na tela o nome da Faculdade("UNIVESP")
                        lcd.setCursor(1,1);               // Posicionando o cursor na 2ª coluna e na 2ª linha
                        lcd.print("Eng. da Computacao");  // Imprindo na tela o nome da Graduação("Eng. da Computação")
                        lcd.setCursor(0,2);               // Posicionando o cursor na 1ª coluna e na 3ª linha
                        lcd.print("Projeto Integrador V");// Imprindo na tela o nome da Disciplina("Projeto Integrador V")
                        lcd.setCursor(3,3);               // Posicionando o cursor na 4ª coluna e na 4ª linha
                        lcd.print("Polo Juquitiba");      // Imprindo na tela o nome do Polo da Faculdade("Polo Juquitiba")  
                        delay(2000);                         // Determinando o tempo de exibição da apresnetação em milissegundos  
                      }

                        long exibir_tensao_corrente(){
                    lcd.clear();  
                    lcd.setCursor(2,0);
                    lcd.print("Tensao_circuito:");
                    lcd.setCursor(7,1);
                    lcd.print(tensao);
                    lcd.print(" V");
                    lcd.setCursor(1,2);
                    lcd.print ("Corrente_circuito:");
                    lcd.setCursor(6,3);
                    lcd.print(valorCorrente, 3);
                    lcd.print("A");
                    delay(2000);                      
                  }

                  long exibir_potencia_consumo(){                         
                    lcd.clear();
                    lcd.setCursor(1,0);
                    lcd.print("Potencia da carga:");
                    lcd.setCursor(3,1);
                    lcd.print (tensao*valorCorrente);
                    lcd.print(" Watts");
                    lcd.setCursor(2,2);        
                    lcd.print("Consumo_energia");
                    lcd.setCursor(3,3);
                    lcd.print(energia, 3); // "3" é a quantidade de casa decimais
                    lcd.print (" kj");
                    delay(2000);                        
                  }
