#include <Servo.h>

#define trig_pin 13
#define echo_pin 12
#define motor_channel_1a 5
#define motor_channel_1b 6
#define motor_channel_2a 10
#define motor_channel_2b 11
#define servo_pin 3

Servo servo;

long get_distance() {
  digitalWrite(trig_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin, LOW);
  return 0.01725 * pulseIn(echo_pin, HIGH);
}

void servo_control(int angle) {
  servo.write(angle);
}

void move_forward(int speed) {
  analogWrite(motor_channel_1a, 0);
  analogWrite(motor_channel_1b, speed);

  analogWrite(motor_channel_2a, 0);
  analogWrite(motor_channel_2b, speed);
}

void setup() {
  Serial.begin(9600);
  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
  servo.attach(servo_pin);
}

void loop() {
  // put your main code here, to run repeatedly:
  long cur_dist = get_distance();
  Serial.println(cur_dist);
  if (cur_dist <= 5) {
    move_forward(0);
    servo_control(0);
  } else {
    move_forward(127);
    servo_control(90);
  }
  delayMicroseconds(1000);

}