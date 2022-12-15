
/*
#define botaoAesquerda 7 // Substitui pin4
#define botaoBdireita 8 // Substitui pin3
// #define pin3 8 // Substituido por botaoBdireita
// #define pin4 7 // Substituido por botaoAesquerda

#define setasEsquerda 6
#define setasDireita 5  
*/  

#define pin1 10
#define pin2 9
Servo servoDirecao; // Cria o objeto servo para programação
int angulo = 90; // Ajusta o ângulo inicial do Servo em 90º

// IMPLEMENTO DE FUNÇÕES CONTROLE DOS MOTORES

// MOVE PARA FRENTE
void moveFrente(){
  // MOTOR DA TRAÇÃO - frente/ré
  digitalWrite(pin1, HIGH); // motor1a ligado
  digitalWrite(pin2, LOW); // motor1b desligado
  // MOTOR DA DIREÇÃO - dir/esq
                                 /* digitalWrite(pin3, LOW); // motor2a desligado
                                    digitalWrite(pin4, LOW); // motor2b desligado
                                  */
}
// MOVE PARA TRÁS - RÉ
void moveRe(){
  digitalWrite(pin1, LOW); // motor1a desligado
  digitalWrite(pin2, HIGH);// motor1b ligado
  
                                      /*
                                      digitalWrite(pin3, LOW); // motor2a desligado
                                      digitalWrite(pin4, LOW); // motor2b desligado
                                      */
}

void frenteDireita(){
  digitalWrite(pin1, HIGH); // motor1a ligado
  digitalWrite(pin2, LOW); // motor1b desligado
  viraAdireita();
  
                                      //digitalWrite(pin3, HIGH); // motor2a ligado
                                      // digitalWrite(pin4, LOW); // motor2b desligado
}

void frenteEsquerda(){
  digitalWrite(pin1, HIGH); // motor1a ligado
  digitalWrite(pin2, LOW); // motor1b desligado
  viraAesquerda();
  
                                       //  digitalWrite(pin3, LOW); // motor2a desligado
                                       //   digitalWrite(pin4, HIGH); // motor2b ligado
}

void reDireita(){
  digitalWrite(pin1, LOW); // motor1a desligado
  digitalWrite(pin2, HIGH); // motor1b ligado
  viraAdireita();

                                        //   digitalWrite(pin3, HIGH); // motor2a ligado
                                        //  digitalWrite(pin4, LOW); // motor2b desligado
}

void reEsquerda(){
  digitalWrite(pin1, LOW); // motor1a desligado
  digitalWrite(pin2, HIGH); // motor1b ligado
  viraAesquerda();

                                        // digitalWrite(pin3, LOW); // motor2a desligado
                                        // digitalWrite(pin4, HIGH); // motor2b ligado
}
// CONTROLE DE DIREÇÃO (motor 2) sem a tração (motor 1)
void direita(){
  // piscaSetasDireita();
  // delay(500);
  viraAdireita();
                                        // digitalWrite(pin1, LOW); // motor1a desligado
                                        // digitalWrite(pin2, LOW); // motor1b desligado

                                        // digitalWrite(pin3, HIGH); // motor2a ligado
                                        // digitalWrite(pin4, LOW); // motor2b desligado
}

void esquerda(){
  // piscaSetasEsquerda();
  // delay(500);
  viraAesquerda(); 
                                         // digitalWrite(pin1, LOW); // motor1a desligado
                                         // digitalWrite(pin2, LOW); // motor1b desligado

                                          // digitalWrite(pin3, LOW); // motor2a desligado
                                          // digitalWrite(pin4, HIGH); // motor2b ligado
}

void parar(){
  digitalWrite(pin1, LOW); // motor1a desligado
  digitalWrite(pin2, LOW); // motor1b desligado

                                           // digitalWrite(pin3, LOW); // motor2a desligado
                                           // digitalWrite(pin4, LOW); // motor2b desligado
}

// Funções direção direita/esqueda
void viraAesquerda(){
  // piscaSetasEsquerda();
  if (angulo < 181) {
    angulo += 1;
    servoDirecao.write(angulo); // Comando para angulo específico
    Serial.println(angulo);
    delay(25);
  }
}

void viraAdireita(){
  // piscaSetasDireita();  
  if (angulo >= 1) {
    angulo -= 1;
    servoDirecao.write(angulo); // Comando para angulo específico
    Serial.println(angulo);
    delay(25);
  }
}

// -------     FUNÇÕES SETAS DIREITA/ESQUERDA   ---------------------------------------------------------

void piscaSetasDireita (){  
    digitalWrite(setasDireita, HIGH);
    delay(25);
    digitalWrite(setasDireita, LOW);
    delay(25);
  }


void piscaSetasEsquerda (){  
  digitalWrite(setasEsquerda, HIGH);
  delay(25);
  digitalWrite(setasEsquerda, LOW);
   delay(25);
}

// -------    FIM FUNÇÕES SETAS DIREITA/ESQUERDA   ---------------------------------------------------------
