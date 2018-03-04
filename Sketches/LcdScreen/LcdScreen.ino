#include <LiquidCrystal.h>

#define FORWARD_BUTTON_PIN 5

#define BACKWARD_BUTTON_PIN 4

#define RECALC_BUTTON_PIN 3

#define MAX_VALUE 16

#define MIN_VALUE 3

LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

int arrayLength = MIN_VALUE;

int currentPosition = 0;

int* array = 0;

bool forwardButtonWasUp;

bool backwardButtonWasUp;

bool recalcArrayButtonWasUp;

void setup() {
    // если порт 0 неподключен, то генератор псевдослучайных чисел
    // будет инициализироваться функцией randomSeed() со случайного
    // значения при каждом запуске программы из-за "шума" на порту.
    randomSeed(analogRead(A0));

    pinMode(FORWARD_BUTTON_PIN, INPUT_PULLUP);
    pinMode(BACKWARD_BUTTON_PIN, INPUT_PULLUP);
    pinMode(RECALC_BUTTON_PIN, INPUT_PULLUP);

    lcd.begin(16, 2);
    createArray(arrayLength);
    desortArray();

    print("Ready!");
}

void loop() {
    forwardButtonWasUp = handleClick(forwardButtonWasUp, FORWARD_BUTTON_PIN);
    backwardButtonWasUp = handleClick(backwardButtonWasUp, BACKWARD_BUTTON_PIN);
    recalcArrayButtonWasUp = handleClick(recalcArrayButtonWasUp, RECALC_BUTTON_PIN);

    if (!forwardButtonWasUp) {
        showNext();
    }

    if (!backwardButtonWasUp) {
        showPrev();
    }

    if (!recalcArrayButtonWasUp) {
        recalcArray();
    }
}

void showNext() {
    lcd.clear();
    
    if (currentPosition == arrayLength) {
        currentPosition = 0;
    }

    print(array[currentPosition]);
    currentPosition++;
}

void showPrev() {
    if (currentPosition == 0) {
        print("No need to return");
        print(array[currentPosition]);

        return;
    }

    currentPosition--;
    print(array[currentPosition]);
}

void createArray(int length) {
    if (array != 0) {
        delete [] array;
    }

    array = new int [length];

    for (int i = 0; i < length; i++) {
        array[i] = i + 1;
    }
}

void desortArray() {
    for (int i = 0; i < arrayLength; i++) {
        int firstPosition = random(0, arrayLength);
        int secondPosition = random(0, arrayLength);
        int buffer = array[firstPosition];
        array[firstPosition] = array[secondPosition];
        array[secondPosition] = buffer;
    }
}

void recalcArray() {
    if (arrayLength == MAX_VALUE) {
        arrayLength = MIN_VALUE;
    } else {
        arrayLength++;
    }

    // Хак для корректного приведения типов, если писать одной строкой, то message не может проинициализироваться как String.
    String message = "Length: ";
    message = message  + arrayLength;
    print(message);

    createArray(arrayLength);
    desortArray();
}

bool handleClick(bool buttonWasUp, int buttonPin) {
    bool buttonPressed = !digitalRead(buttonPin);

    if (buttonWasUp && buttonPressed) {
      delay(10);
      buttonPressed = !digitalRead(buttonPin);
    }

    return !buttonPressed;
}

void print(int value) {
    print(String(value));
}

void print(char* value) {
    print(String(value));
}

void print(String value) {
    lcd.clear();
    lcd.print(value);
    delay(500);
}
