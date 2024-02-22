#define ECHO 2
#define TRIG 3

int distance = 0;

void setup() {
  Serial.begin(115200);
  pinMode(ECHO, INPUT);  // Define the ultrasonic echo input pin
  pinMode(TRIG, OUTPUT);
  Serial.println("Ultrasionc Testing");
}

void loop() {
  distance = distance_measure();                            //display distance
  Serial.println("Distance: " + String(distance) + " CM");  //print distance
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
