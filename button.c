#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define HIGH 1
#define LOW 0
#define INPUT 1
#define OUTPUT 0

// inputPin differ depending on the module
// Artik 5 - use 121 pin
// Artik 7 - use pin 8
// Find more info at:
// https://developer.artik.io/documentation/getting-started-artik/tutorials/read-a-button.html

int inputPin = 8;

bool digitalPinMode(int pin, int dir){
  FILE * fd;
  char fName[128];
  
  // Exporting the pin to be used
  if(( fd = fopen("/sys/class/gpio/export", "w")) == NULL) {
    printf("Error: unable to export pin\n");
    return false;
  }
  fprintf(fd, "%d\n", pin);
  fclose(fd);

  // Setting direction of the pin
  sprintf(fName, "/sys/class/gpio/gpio%d/direction", pin);
  if((fd = fopen(fName, "w")) == NULL) {
    printf("Error: can't open pin direction\n");
    return false;
  }
  if(dir == OUTPUT) {
    fprintf(fd, "out\n");
  } else {
    fprintf(fd, "in\n");
  }
  fclose(fd);

  return true;
}

int digitalRead(int pin) {
  FILE * fd;
  char fName[128];
  char val[2];

  // Open pin value file
  sprintf(fName, "/sys/class/gpio/gpio%d/value", pin);
  if((fd = fopen(fName, "r")) == NULL) {
    printf("Error: can't open pin value\n");
    return false;
  }
  fgets(val, 2, fd);
  fclose(fd);

  return atoi(val);
}

int setup() {
   if (!digitalPinMode(inputPin, INPUT))
     return -1;

   return 0;
}

int main(void) {
  if (setup() == -1)
  {
    exit(1);
  }
    
  while(1) {
    int sensorVal;
    sensorVal = digitalRead(inputPin);
    printf("sensorVal is %d\n", sensorVal);
    sleep(1);
  }

  return 0;
}
