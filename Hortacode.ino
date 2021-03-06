#include <Arduino.h>
//Inclui a biblioteca LiquidCrystal.h para o LCD
#include <LiquidCrystal.h>

//definição dos pinos digitais e analógicos
#define pin_analog A0
#define pin2_analog A1
#define relay 8
#define p5va0 7
#define p5va1 6
#define ledred 10
#define ledgreen 9
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

//variavel tipo int para conversão dos valores dos sensores
int ValAnalogIn;
void setup(){
//configuração do lcd com as definições de 16 caracteres por 2 linhas
  lcd.begin(16, 2);
//configuração do bound rate por segundos
  Serial.begin(9600);

//set dos pinos em modo OUTPUT
  pinMode(relay, OUTPUT);  
  pinMode(p5va0, OUTPUT);
  pinMode(p5va1, OUTPUT);
  pinMode(ledgreen, OUTPUT);
  pinMode(ledred, OUTPUT);
  digitalWrite(p5va0, HIGH);
  digitalWrite(p5va1, HIGH);

}
void loop(){
//limpa o lcd para receber novos dados
  lcd.clear();
  
//configuração dos valores dos sensores dentro da variavel ValAnalogIN
  ValAnalogIn = analogRead(pin_analog);
//converção dos valores dos sensores para porcentagem
  int Porcento = map(ValAnalogIn, 1023, 0, 0, 100);
// configuração do segundo sensor
  ValAnalogIn = analogRead(pin2_analog);
  int Porcento2 = map(ValAnalogIn, 1023, 0, 0, 100);
  
// configuração do display lcd
/* modelo de print dos sensores com a seguinte palavra "S1: XXX% S2: XXX%"
obs: XXX remetem aos valores dos sensores de 0% a 100%*/
  lcd.setCursor(0, 0);
  lcd.print("S1:");
  lcd.setCursor(4, 0);
  lcd.print(Porcento);
  lcd.setCursor(7, 0);
  lcd.print("%");
  lcd.setCursor(8, 0);
  lcd.print("S2:");
  lcd.setCursor(12, 0);
  lcd.print(Porcento2);
  lcd.setCursor(15, 0);
  lcd.print("%");

/*Caso os sensores forem igualmente iguais ou menores de 45% 
o módulo relê aciona a válvula solenóide*/
    if(Porcento <= 45 || Porcento2 <= 45){
          digitalWrite(ledred, HIGH);
          digitalWrite(relay, LOW);
          lcd.setCursor(3, 1);
          lcd.print("Irrigando...");
      }

/*Caso os valores dos dois sensores ou somente um deles possuir 
o valor maior que 45% ele mantem o relê desligado*/
    else{
          digitalWrite(ledgreen, HIGH);
          digitalWrite(relay, HIGH);
          lcd.setCursor(3, 1);
          lcd.print("Irrigado...");
      }

delay(1000);
}