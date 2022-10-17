// definir o número dos pinos
const int buttonPin = 12; 
const int greenLedPin =  9; 
const int yellowLedPin = 10;
const int redLedPin = 11;
const int blueLedPin = 13;

//tempo minimo de semaforo aberto
const long openedTime = 20000;

const long regressiveCount = 10000;

//matriz para contagem de tempo
byte seven_seg_digits[10][7] = {
{ 1,1,1,1,1,1,0 },  // = 0
{ 0,1,1,0,0,0,0 },  // = 1
{ 1,1,0,1,1,0,1 },  // = 2
{ 1,1,1,1,0,0,1 },  // = 3
{ 0,1,1,0,0,1,1 },  // = 4
{ 1,0,1,1,0,1,1 },  // = 5
{ 1,0,1,1,1,1,1 },  // = 6
{ 1,1,1,0,0,0,0 },  // = 7
{ 1,1,1,1,1,1,1 },  // = 8
{ 1,1,1,1,0,1,1 }   // = 9
};

int buttonState; 
unsigned long previousMillis; 
bool isOpenForCars;
void setup() {
  //Leds
  pinMode(greenLedPin, OUTPUT);
  pinMode(yellowLedPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);
  pinMode(blueLedPin, OUTPUT);

  //Botao
  pinMode(buttonPin, INPUT);

  //Display
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);

  //Sempre inicia com sinais verdes abertos
  digitalWrite(greenLedPin, HIGH);

  buttonState = 0; // variável para ler o status do botão
  previousMillis = 0; 
  isOpenForCars = true;
  
}
void loop(){

  buttonState = digitalRead(buttonPin);

  unsigned long currentMillis = millis();
  if (buttonState == HIGH && isOpenForCars == true) {
    if (currentMillis - previousMillis >= openedTime) {
      allowPedestriansAndStopCars();
    } else {
      delay(openedTime - (currentMillis - previousMillis));
      allowPedestriansAndStopCars();
    }
    
  }
}

void allowPedestriansAndStopCars(){
  closeForCars();
  delay(1000);
  openForPedestrians();
  closeForPedestrians();
  delay(1000);
  openForCars();
  previousMillis = millis();  
}

void closeForCars(){
  isOpenForCars = false;
  digitalWrite(greenLedPin, LOW);
  digitalWrite(yellowLedPin, HIGH);
  delay(1500);
  digitalWrite(yellowLedPin, LOW);
  digitalWrite(redLedPin, HIGH);
}

void openForPedestrians(){
  digitalWrite(blueLedPin, HIGH);
  displayRegressiveCounting();
  lowDisplay();
}

void displayRegressiveCounting(){
  int secondsOpen = (openedTime - regressiveCount) / 1000;
  
  for (byte count = secondsOpen; count > 0; count = count-2) {
    digitalWrite(8, HIGH);
    delay(1000);
    digitalWrite(8, LOW);
    delay(1000);
    }
  
  for (byte count = 9; count < 255; --count) {
    byte pin = 2;
    for (byte displayPin = 0; displayPin < 7; ++displayPin) {
      digitalWrite(pin, seven_seg_digits[count][displayPin]);
      ++pin;
    }

    delay(1000);
  }    
}

void lowDisplay(){
    for (byte pin = 0; pin < 9; ++pin) {
      digitalWrite(pin, 0);
    }  
}

void closeForPedestrians(){
  digitalWrite(blueLedPin, LOW);
}

void openForCars(){
  isOpenForCars = true;
  digitalWrite(redLedPin, LOW);
  digitalWrite(greenLedPin, HIGH);
}

