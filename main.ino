PRODUCT_ID(7131);
PRODUCT_VERSION(1);

#include "application.h"

int led1 = WKP;  // Red
int led2 = A4;   // Green
int led3 = P1S1; // Blue
int led4 = D6;   // green diode

int high = 100;

String color       = "blue";
String targetColor = "green";

void setup() {
  RGB.control(true);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);

  Particle.function("setColor", setColor);

  Particle.publish("ILL_WAKE");
}

void loop() {
  if (color != targetColor) {
    commenceFade();
  }
}

void commenceFade() {
  int start_r, start_g, start_b;
  if (color == "green") {
    start_r = 0;
    start_g = high;
    start_b = 0;
  } else if (color == "red") {
    start_r = high;
    start_g = 0;
    start_b = 0;
  } else if (color == "yellow") {
    start_r = high;
    start_g = high;
    start_b = 0;
  } else if (color == "blue") {
    start_r = 0;
    start_g = 0;
    start_b = high;
  } else if (color == "blue_green") {
    start_r = 0;
    start_g = high;
    start_b = high;
  } else if (color == "white") {
    start_r = high;
    start_g = high;
    start_b = high;
  }

  int dest_r, dest_g, dest_b;
  if (targetColor == "green") {
    dest_r = 0;
    dest_g = high;
    dest_b = 0;
  } else if (targetColor == "red") {
    dest_r = high;
    dest_g = 0;
    dest_b = 0;
  } else if (targetColor == "yellow") {
    dest_r = high;
    dest_g = high;
    dest_b = 0;
  } else if (targetColor == "blue") {
    dest_r = 0;
    dest_g = 0;
    dest_b = high;
  } else if (targetColor == "blue_green") {
    dest_r = 0;
    dest_g = high;
    dest_b = high;
  } else if (targetColor == "white") {
    dest_r = high;
    dest_g = high;
    dest_b = high;
  }

  for (int i = 0; i < 100; i++) {
    int r = map(i, 0, 100, start_r, dest_r);
    int g = map(i, 0, 100, start_g, dest_g);
    int b = map(i, 0, 100, start_b, dest_b);

    analogWrite(led1, r);
    analogWrite(led2, g);
    analogWrite(led3, b);

    delay(10);
  }

  color = targetColor;
}

int setColor(String newColor) {
  if (
    newColor == "green"      ||
    newColor == "red"        ||
    newColor == "blue"       ||
    newColor == "blue_green" ||
    newColor == "yellow"     ||
    newColor == "white"
  ) {
    targetColor = newColor;
    return 1;
  } else {
    return 0;
  }
}
