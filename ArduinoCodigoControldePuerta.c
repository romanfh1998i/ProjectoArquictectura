#include <NewPing.h> // https://github.com/microflo/NewPing
#include <Servo.h>   // https://www.arduino.cc/en/Reference/Servo

// Pins for the ultrasonic sensor
#define TRIGGER_PIN 11
#define ECHO_PIN 10
//boolean booleanclose = true;
// Pins for the servo motors
#define SERVO_LEFT_PIN 13
#define SERVO_RIGHT_PIN 12

// Pins for the LEDs
#define LED_OPEN_PIN 6 // Cambia el número del pin según tu configuración
#define LED_CLOSE_PIN 7 // Cambia el número del pin según tu configuración

// Threshold distance for opening and closing the door
#define OPEN_DISTANCE 10 // Adjust this value as needed
#define CLOSE_DISTANCE 20 // Adjust this value as needed

// Create objects for the ultrasonic sensor and servos
NewPing sonar(TRIGGER_PIN, ECHO_PIN);
Servo servoLeft;
Servo servoRight;

void setup() {
  servoLeft.attach(SERVO_LEFT_PIN);
  servoRight.attach(SERVO_RIGHT_PIN);
  servoLeft.write(90); // Initial servo position
  servoRight.write(90); // Initial servo position
  delay(1000);
  
  pinMode(LED_OPEN_PIN, OUTPUT);
  pinMode(LED_CLOSE_PIN, OUTPUT);
  digitalWrite(LED_CLOSE_PIN, HIGH);
  Serial.begin(9600); // Inicia la comunicación serial para el Monitor Serial
}

void loop() {
  if (Serial.available() > 0) {
    char receivedChar = Serial.read(); // Lee el carácter recibido
    Serial.print("Caracter recibido: ");
    Serial.println(receivedChar);
    
    // Opcional: Enciende o apaga el LED incorporado en el pin 13
    if (receivedChar == 'O') {
      openDoor(); // Abre la puerta
      delay(1000);
    } else if (receivedChar == 'C') {
      closeDoor(); // Cierra la puerta
    }
  }
  delay(50); // Small delay for stability

  int distance = sonar.ping_cm();

  if (distance <= OPEN_DISTANCE) {
    openDoor();
  } else if (distance >= CLOSE_DISTANCE) {
    closeDoor();
  }
}

void openDoor() {
  digitalWrite(LED_OPEN_PIN, HIGH);
  digitalWrite(LED_CLOSE_PIN, LOW);
   //booleanclose=false;
    servoLeft.write(180); // Return to the closed position
  servoRight.write(0); // Return to the closed position
delay(2000);
}

void closeDoor() {
 
      digitalWrite(LED_OPEN_PIN, LOW);
      digitalWrite(LED_CLOSE_PIN, HIGH);
    servoLeft.write(90); // Regresa a la posición cerrada
    servoRight.write(90);
 // Regresa a la posición cerrada
  // booleanclose=true;
  //} 
  
}