#include <Arduino.h>

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Max6675.h>
// variables


LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

int ktcSO = A3;                     
int ktcCS = A2;
int ktcCLK = A1;

MAX6675 ktc(ktcCLK, ktcCS, ktcSO); // set the  CLK pin, CS pin and SO pin
double tempC;                       // Almacenar la teperatura
bool Lleno;                        // Bandera para saber si esta  llena o no el contenedor de agua
bool vacio;                        // Bandera para  saber si esta vacia o no el contenedor de agua
//Funciones
void GetTemp();
void Llenar();
void print(int x, int y, String text);
void ceol(int x, int  y);


//Pines

const int FlotadorVacio = 11;
const int FlotadorLleno = 10;

void setup() {
 Serial.begin(9600);              // PREPARAR LA INTERFAZ SERIAL
  lcd.init();                      // initialize the lcd 
  // Print a message to the LCD.
  lcd.backlight();                 //Se enciende la luz de fondo de lcd
  print(5,0,"El Trebol");
  print(6,1,"Caldera");
  print(4,2,"Arduino 2024");
  print(0,3,"By Martin Llamas E.");
  // pines de entrada
  pinMode(FlotadorVacio,INPUT);    // Definir los flotadorVacio como  el flotador inferior
  pinMode(FlotadorLleno,INPUT);   // Definir los flotadorLleno como el flotador superior

  delay(1000);
   ceol(0,2);
   ceol(0,1);
}


void loop()
{
 
  GetTemp();
  
  Llenar();
 
  // ESPERAR UN SEGUNDO ENTRE LAS LECTURAS
  delay(500);
}

void GetTemp(){
  // LEER EL TERMOPAR Y ALMACENAR EL VALOR EN UNA VARIABLE
  tempC = ktc.readCelsius();
 
  // PRIMERO LIMPIAMOS LA PANTALLA Y LUEGO IMPRIMIMOS LA TEMPERATURA
  String str = "Tempertura = " + String(tempC) + " C";
  print(0,2,str); 
 
  // IMPRIMIR LA TEMPERATURA EN LA TERMINAL SERIAL
  Serial.println(tempC);
}

void Llenar(){
  Lleno = digitalRead(FlotadorLleno) == LOW;     // Leer el estado del Flotador Lleno
  lcd.setCursor(6,1);
  String estado =  (Lleno ? F("LLeno") : F("Vacio"));
  lcd.print(estado);
}
void print(int x, int y, String text){
  lcd.setCursor(x,y);
  lcd.print(text);
}
void ceol(int x, int  y) {
  lcd.setCursor(x,y);
  lcd.print("                    ");
}
