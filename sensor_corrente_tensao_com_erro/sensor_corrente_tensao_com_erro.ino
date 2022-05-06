// #### UNIVESP 

// #### ENG. DA COMPUTAÇÃO 

// #### PROJETO INTEGRADOR V 

// #### POLO JUQUITIBA

// #### SENSOR DE TENSÃO E CORRENTE EM CIRCUITO AC

// #### (APERFEIÇOAMENTO DO PI5)



#include <LiquidCrystal_I2C.h>        // Incluindo a biblioteca do módulo I2C para conexao e "reconhecimento" do display pelo arduino
#include <Wire.h>                     // Incluindo a biblioteca "Wire", a qual estabelece a comunicação entre o display e arduino
LiquidCrystal_I2C lcd (0X27, 20 ,4);  // Identificando a porta, quantidades de colunas e linhas do display

int sensorTensao = A0;                  // Variável que receberá o sinal analógico da porta A0 do Arduino com a tensão do circuito
float valorTensao;                      // Variável que receberá o valor lido na porta analógica A0 do Arduino
int tensaoFinal = 0;                    // Variável que receberá a tensão final convertida em volts AC

//int sensorCorrente = A1;                // variável que receberá o sinal analógico da porta A1 do Arduino com a CORRENTE do circuito
int sensorCorrente = 0;                // variável que receberá o sinal analógico da porta A1 do Arduino com a CORRENTE do circuito           
int sensorValue_aux = 0;                //
float valorSensor = 0;                  //
float valorCorrente = 0;                //
float voltsporUnidade = 0.004887586;    // 5%1023
float sensibilidade = 0.185;            // Para ACS712 de 5A, use 0.185; para ACS712 de 10A, 0.100; para ACS712 de 30A, 0.066
                                        
                                        //int tensao = sensorTensao;  // Declarando a tensão do circuito elétrico AC  
float energia = 0;                   

void setup() {
  pinMode(sensorTensao, INPUT);    // Definindo o pino A0 (sensorTensao) como entrada
  pinMode(sensorCorrente, INPUT);  // Definindo o pino A1 (sensorCorrente) como entrada
  lcd.init();                      // inicializando o display lcd de 20 colunas e 4 linhas
  lcd.backlight();                 // Mantendo acesa a luz de fundo do display, ao invés do blink abaixo comentado
}
void loop() {
  calculos();                 // Invocando a função dos cálculos da corrente
  lcd.clear();                // Limpando o display lcd
  delay(1500);                // Aguardando 1,1/2 segundo antes da tela de apresentação
  // tela_apresentacao();        // Invocando a função de apresentação da Faculdade, Graduação, Disciplina e polo
  exibir_tensao_corrente();   // Invocando a função de exibição da tensão e da corrente no display
  // exibir_potencia_consumo();  // Invocando a função de exibição da potência e consumo da carga do circuito no display
}

long calculos(){
  tensaoFinal = 0;                        //REINICIA O VALOR ATUAL E ATUALIZA NA PRÓXIMA LEITURA 
  valorTensao = 0;                        //REINICIA O VALOR ATUAL E ATUALIZA NA PRÓXIMA LEITURA 
  valorTensao = analogRead(sensorTensao); //LEITURA DO VALOR NA PORTA ANALÓGICA(VARIA DE 0 ATÉ 1023)
              
              
              //BLOCO REFERNETE A TENSÃO DE 127V 
        //SE VARIÁVEL FOR MAIOR QUE 100 E MENOR QUE 483 FAZ
        if ((valorTensao > 127) & (valorTensao < 483)) { 
        // ORIGINALMENTE, O PARÂMETRO "valorTensao" é multiplicado por 5. Mas multipliquei por 10 para chegar à tensão medida pelo multímetro
        tensaoFinal = ((valorTensao*10)/1023)77.3;       // VARIÁVEL RECEBE O VALOR GERADO PELA CONTA
                                                           // (O VALOR 77.3 PODE/DEVE SER ALTERADO PARA FINS DE AJUSTE DO VALOR DE TENSÃO)
                                                         
        }
              //BLOCO REFERENTE A TENSÃO DE 220V
        //SE VARIÁVEL FOR MAIOR QUE 665 E MENOR QUE 1023 FAZ 
        if ((valorTensao > 665) & (valorTensao < 1023)) { tensaoFinal = ((valorTensao*5)/1023)57;          /* VARIÁVEL RECEBE O VALOR GERADO PELA CONTA(O VALOR 57 PODE/DEVE SER ALTERADO PARA FINS DE AJUSTE DO VALOR DE TENSÃO) */}
    
        //BLOCO REFERENTE AOS CÁLCULOS DA MEDIÇÃO DA CORRENTE DO CIRCUITO  
  for(int i=10000; i>0; i--){    
    sensorValue_aux = (analogRead(sensorCorrente) -510); // le o sensor na pino analogico A1 e ajusta o valor lido 
                                                         // já que a saída do sensor é (1023)vcc/2 para corrente =0
                                                           
    valorSensor += pow(sensorValue_aux,2);               // somam os quadrados das leituras.
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
  energia +=(tensaoFinal*valorCorrente*1.2/1000); //calculando e imprimindo a energia consumida num ciclo de 1,2s
    
}

                          //  FUNÇÕES PARA EXIBIÇÕES DAS INFORMAÇÕES NO DISPLAY
                          
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
                        delay(500);                         // Determinando o tempo de exibição da apresnetação em milissegundos  
                      }
    
                      long exibir_tensao_corrente(){
                        lcd.clear();  
                        lcd.setCursor(2,0);
                        lcd.print("Tensao_circuito:");
                        lcd.setCursor(7,1);
                        lcd.print(tensaoFinal
                        );
                        lcd.print(" V");
                        lcd.setCursor(1,2);
                        lcd.print ("Corrente_circuito:");
                        lcd.setCursor(6,3);
                        lcd.print(valorCorrente, 3);
                        lcd.print("A");
                        delay(3000);                      
                      }
    
                      long exibir_potencia_consumo(){                         
                        lcd.clear();
                        lcd.setCursor(1,0);
                        lcd.print("Potencia da carga:");
                        lcd.setCursor(3,1);
                        lcd.print (tensaoFinal*valorCorrente);
                        lcd.print(" Watts");
                        lcd.setCursor(2,2);        
                        lcd.print("Consumo_energia");
                        lcd.setCursor(3,3);
                        lcd.print(energia, 3); // "3" é a quantidade de casa decimais
                        lcd.print (" kj");
                        delay(1000);                        
                      }
