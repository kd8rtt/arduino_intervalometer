
#include <Lewis.h>  // library to support text to Morse code
Lewis Morse;
#include <Key.h>
#include <Keypad.h>

const byte rows = 4; //four rows
const byte cols = 4; //four columns
char keys[rows][cols] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[rows] = {6, 7, 8, 9}; //connect to the row pinouts of the keypad
byte colPins[cols] = {2, 3, 4, 5}; //connect to the column pinouts of the keypad
Keypad customKeypad = Keypad( makeKeymap(keys), rowPins, colPins, rows, cols );

int i = 0;
int led = 10;
int opt = 11;

void setup() {
  pinMode(led, OUTPUT);
  pinMode(opt, OUTPUT);
  digitalWrite(led, HIGH);
  digitalWrite(opt, LOW);
  delay(3000);
  Morse.begin(led, led, 5, false);
}

void loop() {

  char key = customKeypad.waitForKey();
  char inputNum[5];
  char inputNum2[5];
  memset(inputNum2, 0, sizeof(inputNum2));
  memset(inputNum, 0, sizeof(inputNum));
  int index = 0;
  if (key == 'A') {
    // take one photo
    digitalWrite(opt, HIGH);
    delay(500);
    digitalWrite(opt, LOW);
    Morse.print('e'); //lets user know shutter is actuated
  }
  if (key == 'B') {
    // take one photo after 2 second delay
    Morse.print('i'); //lets user know mode acccepted
    delay(2000);
    digitalWrite(opt, HIGH);
    delay(500);
    digitalWrite(opt, LOW);
    Morse.print('e'); //lets user know shutter is actuated
  }

  if (key == 'C') {
    // take one photo after manually set delay
    Morse.print('s'); //lets user know mode acccepted
    memset(inputNum, 0, sizeof(inputNum)); // reset char array to blank
    while (true) {
      key = customKeypad.waitForKey(); //get key
      if (key == '#') { //if key is #, stop saving numbers
        break;
      } else {
        inputNum[index] = key; // else get another number
        index++;
      }
    }
    //Serial.println(inputNum);
    int NumPhotos = atoi(inputNum); // convert char array to integer
    //Serial.println(NumPhotos);
    for (int print_index = 0; print_index < index; print_index++) {
      //Serial.println(inputNum[print_index]);
      Morse.print(inputNum[print_index]);
      delay(NumPhotos * 1000);
      digitalWrite(opt, HIGH);
      delay(500);
      digitalWrite(opt, LOW);
      Morse.print('e'); //lets user know shutter is actuated
    }
  }
  if (key == 'D') { // enter timelapse mode
    Morse.print('h'); //lets user know mode acccepted

    memset(inputNum, 0, sizeof(inputNum)); // reset char array to blank
    while (true) {
      key = customKeypad.waitForKey(); //get key
      if (key == '#') { //if key is #, stop saving numbers
        break;
      } else {
        inputNum[index] = key; // else get another number
        index++;
      }
    }
    int NumPhotos = atoi(inputNum); // convert char array to integer
    for (int print_index = 0; print_index < index; print_index++) {
      //Serial.println(inputNum[print_index]);
      Morse.print(inputNum[print_index]);
    }
    int index2 = 0;
    while (true) {
      key = customKeypad.waitForKey(); //get key
      if (key == '#') { //if key is #, stop saving numbers
        break;
      } else {
        inputNum2[index2] = key; // else get another number
        index2++;
      }
    }
    int DelayTime = atoi(inputNum2); // convert char array to integer
    for (int print_index = 0; print_index < index2; print_index++) {
      Morse.print(inputNum2[print_index]);
    }
    for (int z = 0; z < NumPhotos; z++) {
      digitalWrite(opt, HIGH);
      delay(500);
      digitalWrite(opt, LOW);
      Morse.print('e'); //lets user know shutter is actuated
      if (z == NumPhotos) {
        break;
      } else {
        for (int zz = 0; zz < DelayTime; zz++) {
          delay(1000);
        }
      }
    }
    Morse.print('0'); //lets user know time lapse is complete
  }
}



