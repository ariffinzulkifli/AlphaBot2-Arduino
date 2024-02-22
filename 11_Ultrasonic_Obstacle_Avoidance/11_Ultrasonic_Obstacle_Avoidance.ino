#define PWMA 6   //Left Motor Speed pin (ENA)
#define AIN2 A0  //Motor-L forward (IN2).
#define AIN1 A1  //Motor-L backward (IN1)
#define PWMB 5   //Right Motor Speed pin (ENB)
#define BIN1 A2  //Motor-R forward (IN3)
#define BIN2 A3  //Motor-R backward (IN4)
#define ECHO 2
#define TRIG 3

int distance = 0;
int speed = 120;

void setup() {
  Serial.begin(115200);
  Serial.println("Ultrasonic Obstacle Avoidance");
  pinMode(ECHO, INPUT);   // Define the ultrasonic echo input pin
  pinMode(TRIG, OUTPUT);  // Define the ultrasonic trigger input pin
  pinMode(PWMA, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  analogWrite(PWMA, speed);
  analogWrite(PWMB, speed);
  stop();
}

void loop() {
  distance = distance_measure();                            //display distance
  Serial.println("Distance: " + String(distance) + " CM");  //print distance
  if (distance < 25)                                        //Ultrasonic range ranging 2cm to 400cm
  {
    right();
    //left();
    delay(500);
    stop();
  } else {
    forward();
  }
  delay(250);
}

// Measure the Distance
int distance_measure() {

  digitalWrite(TRIG, LOW);  // set trig pin low 2μs
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);  // set trig pin 10μs , at last 10us
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);                // set trig pin low
  float fDistance = pulseIn(ECHO, HIGH);  // Read echo pin high level time(us)
  fDistance = fDistance / 58;             //Y m=（X s*344）/2
  // X s=（ 2*Y m）/344 ==》X s=0.0058*Y m ==》cm = us /58
  return (int)fDistance;
}

void forward() {
  analogWrite(PWMA, speed);
  analogWrite(PWMB, speed);
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, HIGH);
}

void backward() {
  analogWrite(PWMA, speed);
  analogWrite(PWMB, speed);
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
}

void right() {
  analogWrite(PWMA, 50);
  analogWrite(PWMB, 50);
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
}

void left() {
  analogWrite(PWMA, 50);
  analogWrite(PWMB, 50);
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, HIGH);
}

void stop() {
  analogWrite(PWMA, 0);
  analogWrite(PWMB, 0);
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, LOW);
}
