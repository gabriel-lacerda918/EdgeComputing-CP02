#include <LiquidCrystal.h>

// Definições de pinos
const int ldrPin = A0;          // Pino analógico para o LDR
const int tmpPin = A2;          // Pino analógico para o sensor de temperatura
const int potPin = A1;          // Pino analógico para o potenciômetro de umidade
const int greenLedPin = 8;      // Pino do LED verde
const int yellowLedPin = 9;     // Pino do LED amarelo
const int redLedPin = 10;       // Pino do LED vermelho
const int buzzerPin = 7;        // Pino do buzzer
const int numReadings = 5; // Número de leituras para calcular a média

// Definições de limites de luminosidade
const int luminosityThresholdOK = 600;      // Luminosidade considerada OK
const int luminosityThresholdAlert = 200;   // Luminosidade considerada em alerta

// Definições de limites de temperatura
const int tempThresholdHigh = 15;           // Limite superior de temperatura
const int tempThresholdLow = 10;            // Limite inferior de temperatura

// Definições de limites de umidade
const int humidityThresholdHigh = 715;       // Limite superior de umidade
const int humidityThresholdLow = 512;        // Limite inferior de umidade

// Variáveis globais
int luminosityReadings[5];     // Array para armazenar as últimas 5 leituras de luminosidade
int tempReadings[5];           // Array para armazenar as últimas 5 leituras de temperatura
int humidityReadings[5];       // Array para armazenar as últimas 5 leituras de umidade
int luminosityIndex = 0;       // Índice para rastrear a posição atual no array de leituras de luminosidade
int tempIndex = 0;             // Índice para rastrear a posição atual no array de leituras de temperatura
int humidityIndex = 0;         // Índice para rastrear a posição atual no array de leituras de umidade
unsigned long lastDisplayTime;  // Último momento em que o display foi atualizado
LiquidCrystal lcd(11, 12, 13, 5, 4, 3, 2); // Inicialização do display LCD

int avgLuminosity = 0;
int avgTemp = 0;
int avgHumidity = 0;

int tempReadTotal = 0;
int humidityReadTotal = 0;

void setup() {
  // Inicialização dos pinos
  pinMode(ldrPin, INPUT);
  pinMode(tmpPin, INPUT);
  pinMode(potPin, INPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(yellowLedPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  
  // Inicialização do monitoramento
  Serial.begin(9600); // Inicialização da comunicação serial
  lcd.begin(16, 2);   // Inicialização do display LCD
  
  for (int i = 0; i < 5; i++) {
    tempReadings[i] = 0; // Inicializa todas as leituras com 0
    humidityReadings[i] = 0;
  }
}

void loop() {
  // Leitura dos sensores
  int luminosityValue = analogRead(ldrPin);
  int humidityValue = analogRead(potPin);
  int rawTempValue = analogRead(tmpPin);
  double voltage = (rawTempValue / 1023.0) * 5000; // 5000 to get millivots.
  double tempValue = (voltage - 500) * 0.1; // 500 is the offset
  
  tempReadTotal = tempReadTotal - tempReadings[tempIndex];    // Subtrai o valor mais antigo	
  tempReadings[tempIndex] = tempValue;      // Armazena a leitura atual
  tempReadTotal = tempReadTotal + tempReadings[tempIndex];    // Adiciona o novo valor ao total
  tempIndex = (tempIndex + 1) % 5; // Avança para o próximo índice circularmente
  avgTemp = tempReadTotal / 5; // Calcula a média das últimas leituras
  
  humidityReadTotal = humidityReadTotal - humidityReadings[humidityIndex];    // Subtrai o valor mais antigo	
  humidityReadings[humidityIndex] = humidityValue;      // Armazena a leitura atual
  humidityReadTotal = humidityReadTotal + humidityReadings[humidityIndex];    // Adiciona o novo valor ao total
  humidityIndex = (humidityIndex + 1) % 5; // Avança para o próximo índice circularmente
  avgHumidity = humidityReadTotal / 5; // Calcula a média das últimas leituras
  
  // Leitura dos sensores a cada 1000ms
  if (millis() - lastDisplayTime >= 1000) {
    readSensors(); // Realiza a leitura dos sensores
    lastDisplayTime = millis(); // Atualiza o tempo da última leitura dos sensores
  }
  
   // Atualiza o display LCD a cada 5000ms
  if (millis() - lastDisplayTime >= 5000) {
    updateDisplay(); // Atualiza o display LCD
    lastDisplayTime = millis(); // Atualiza o tempo da última atualização do display
  }



  
  if (luminosityValue >= luminosityThresholdOK && tempValue >= tempThresholdLow && tempValue <= tempThresholdHigh && humidityValue >= humidityThresholdLow && humidityValue <= humidityThresholdHigh){
	digitalWrite(greenLedPin, HIGH);
    digitalWrite(yellowLedPin, LOW);
	digitalWrite(redLedPin, LOW);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Luminosidade OK");
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(" Temperatura OK ");
    lcd.setCursor(0, 1);
    lcd.print(" Temp: ");
    lcd.print(avgTemp);
    lcd.print(" C   ");
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Umidade OK");
    lcd.setCursor(0, 1);
    lcd.print("Umidade: ");
    lcd.print(map(avgHumidity, 0, 1023, 0, 100));
    lcd.print("%  ");
    noTone(buzzerPin);
  }
  else if (luminosityValue >= luminosityThresholdAlert && luminosityValue < luminosityThresholdOK) {
    digitalWrite(greenLedPin, LOW);
    digitalWrite(yellowLedPin, HIGH);
    digitalWrite(redLedPin, LOW);
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("Ambiente a");
    lcd.setCursor(4, 1);
    lcd.print("meia luz");
    //tone(buzzerPin, 1000);// // Frequência do buzzer
  }
  else if (luminosityValue < luminosityThresholdAlert)
  {
    digitalWrite(greenLedPin, LOW);
    digitalWrite(yellowLedPin, LOW);
    digitalWrite(redLedPin, HIGH);
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("Ambiente muito");
    lcd.setCursor(5, 1);
    lcd.print("claro");
    tone(buzzerPin, 291); // Frequência do buzzer
  }
  else if (tempValue > tempThresholdHigh) {
    digitalWrite(greenLedPin, LOW);
    digitalWrite(yellowLedPin, HIGH);
    digitalWrite(redLedPin, HIGH);
    tone(buzzerPin, 1000); // Frequência do buzzer
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temperatura Alta");
    lcd.setCursor(0, 1);
    lcd.print("Temp: ");
    lcd.print(avgTemp);
    lcd.print(" C   ");
    delay(5000);
  } 
  else if (tempValue < tempThresholdLow){
    digitalWrite(greenLedPin, LOW);
    digitalWrite(yellowLedPin, HIGH);
    digitalWrite(redLedPin, HIGH);
    tone(buzzerPin, 1000); // Frequência do buzzer
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temp. Baixa");
    lcd.setCursor(0, 1);
    lcd.print("Temp: ");
    lcd.print(avgTemp);
    lcd.print(" C   ");
  }
  else if (humidityValue > humidityThresholdHigh) {
    digitalWrite(greenLedPin, LOW);
    digitalWrite(redLedPin, HIGH);
    tone(buzzerPin, 1000); // Frequência do buzzer
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Umidade. Alta");
    lcd.setCursor(0, 1);
    lcd.print("Umidade: ");
    lcd.print(map(avgHumidity, 0, 1023, 0, 100));

    //lcd.print(avgHumidity);//
    lcd.print("%  ");
    delay(1000);
  } else {
    digitalWrite(greenLedPin, LOW);
    digitalWrite(redLedPin, HIGH);;
    tone(buzzerPin, 1000); // Frequência do buzzer
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Umidade. Baixa");
    lcd.setCursor(0, 1);
    lcd.print("Umidade: ");
    lcd.print(map(avgHumidity, 0, 1023, 0, 100));
    lcd.print("%  ");
  }  

  // Saída de depuração para monitoramento
  Serial.print("Luminosidade: ");
  Serial.println(luminosityValue);
  Serial.print("Temperatura: ");
  Serial.println(tempValue);
  Serial.print("Umidade: ");
  //Serial.println(humidityValue);//
  Serial.print(map(humidityValue, 0, 1023, 0, 100));
  Serial.println("%");
  Serial.println("---");
  delay(1000); // Aguarda 1 segundo entre as leituras
  
}
void readSensors() {
  // Leitura dos sensores
  int luminosityValue = analogRead(ldrPin);
  int rawTempValue = analogRead(tmpPin);
  int humidityValue = analogRead(potPin);}


void updateDisplay() {}