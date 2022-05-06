void setup() {

 // Iniciando a comunicação serial a uma velocidade de 9600 bits por segundo
 Serial.begin(9600);
 
 int i;
 for (i = 0; i<=3; i++){
  Serial.println("OLÀ, MUNDO!");
  delay(2000);
 }
}

void loop() {
  // put your main code here, to run repeatedly:

  //int i;
  //for (i = 0; i<=5; i++){
   // Serial.println("OLÀ, MUNDO!");
   // delay(2000);
  //}
// Serial.println("OLÀ, MUNDO!");
}
