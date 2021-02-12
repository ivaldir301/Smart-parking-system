/*
 
/ Trabalho de grupo da disciplina de Inteligencia Artificial
/ O projecto é de código aberto e se encontrará disponibilizado publicamente após apresentação e avaliação
/ do docente da disciplina, para fins educativos.
/ Toda a parte eletrónica e a programação foi feita pelos elementos do grupo

*/


#include <Servo.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(0,1,4,6,7,10);

#define ldr A1
#define led 3

#define ldr1 A0
#define led1 2

int vldr = 0;
int vldr1 = 0;

Servo servo;

int vagas = 5;

int abertura = 90;
int fecha = 0;
int espera_porta = 5000;
int tempo_espera = 3500;

int buzzerPin = 5;

void setup () {
   pinMode(ldr, INPUT);
   pinMode(led, OUTPUT);
   
   pinMode(ldr1, INPUT);
   pinMode(led1, OUTPUT);

   Serial.begin(9600);
   // Código do servo motor
   servo.attach(4); 
   servo.write(0);
   delay(2000);

   pinMode(buzzerPin, OUTPUT);
   lcd.begin(16, 2);
   
}

// Funcao que controla e faz o buzzer apitar quando chamado
void buzzer(){
  
  tone(buzzerPin, 1000); 
  delay(1000);        
  noTone(buzzerPin);     
  delay(1000);       
}

// Funcao que exibe alguns textos iniciais na tela e imprime resultados passados por parametro
// Utilizando o display de LCD do arduino
void lcD(String texto){
  lcd.clear();
  lcd.print("Projecto de ...");
  delay(3000);

  lcd.setCursor(2,1);
  lcd.print("Inteligencia artificial");
  delay(3000);

  lcd.clear();
  lcd.print("Smart parking");
  delay(3000);

  lcd.setCursor(2,1);
  lcd.print("System");
  delay(3000);

  lcd.blink();
  delay(4000);
  lcd.setCursor(7,1);
  delay(3000);
  lcd.noBlink();

  lcd.cursor();
  delay(4000);
  lcd.noCursor();

  lcd.clear();
  lcd.print(texto);
}

// Controla quando um veicula vir na entrada do estacionamento
void entradas(){
  
  delay(3000);
  servo.write(abertura);  
  
  
  delay(espera_porta);
  servo.write(fecha);
  
  vagas--;
  
  Serial.println(vagas);  
}

// Controla quando um veiculo esta no processo de saida do estacionamento
void saidas(){
  
  servo.write(abertura);
   
  delay(espera_porta);
  servo.write(fecha);
  
  vagas++;
  
  Serial.println(vagas);  
}

void loop(){

  vldr = analogRead(ldr);

  if(vldr < 200  && vagas > 0){
    digitalWrite(led, HIGH);
    entradas();
  }else{
    digitalWrite(led, LOW);
  }

  Serial.println(vldr);
  delay(100);

 vldr1 = analogRead(ldr1);

  if(vldr1 < 200){
    digitalWrite(led1, HIGH);
    delay(1000);
    entradas();
    digitalWrite(led1, HIGH);
  }else{
    digitalWrite(led1, LOW);
  }

  Serial.println(vldr1);
  delay(100);
  
}
