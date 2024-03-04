// Definisikan pin yang akan digunakan
const int latchPin = 8; // Pin ST_CP pada register shift
const int clockPin = 12; // Pin SH_CP pada register shift
const int dataPin = 11; // Pin DS pada register shift



// Jumlah LED yang akan digunakan
const int numLEDs = 16;

// Kecepatan berjalan (ms)
const int delayTime = 100;

void setup() {
  // Set pin-mode untuk pin shift register
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void loop() {
  // 1. Bergerak dari tengah ke luar dan kembali
  runPattern(centerToOutside, 3);

  // 2. Pola LED berkedip
  runPattern(blinkPattern, 3);

  // 3. Pola LED spiral
  runPattern(spiralPattern, 3);

  // 4. Bergerak dari kiri ke kanan dan kembali
  runPattern(leftToRight, 3);

  // 5. Pola LED random
  runPattern(randomPattern, 3);
}

// Fungsi untuk menjalankan suatu pola sejumlah kali
void runPattern(void (*pattern)(), int repeatCount) {
  for (int i = 0; i < repeatCount; i++) {
    pattern();
  }
  delay(delayTime * 3);  // Tunggu sejenak sebelum pindah ke pola berikutnya
  twoLEDsWalking();      // Pindah ke pola dua LED yang saling berjalan maju
  threeLEDsWalking();    // Pindah ke pola tiga LED yang bergerak bersama
}

// Fungsi untuk menggerakkan LED dari tengah ke luar dan kembali
void centerToOutside() {
  for (int i = 0; i < numLEDs / 2; i++) {
    byte ledValue = (1 << i) | (1 << (numLEDs - 1 - i));
    updateLEDs(ledValue);
    delay(delayTime);
  }
  for (int i = numLEDs / 2 - 2; i >= 0; i--) {
    byte ledValue = (1 << i) | (1 << (numLEDs - 1 - i));
    updateLEDs(ledValue);
    delay(delayTime);
  }
}

// Fungsi untuk pola berkedip
void blinkPattern() {
  for (int i = 0; i < 2; i++) {
    byte ledValue = B11111111;
    updateLEDs(ledValue);
    delay(delayTime);
    ledValue = B00000000;
    updateLEDs(ledValue);
    delay(delayTime);
  }
}


// Fungsi untuk pola spiral
void spiralPattern() {
  int spiralPos = 0;
  for (int i = 0; i < numLEDs; i++) {
    byte ledValue = 1 << spiralPos;
    updateLEDs(ledValue);
    spiralPos = (spiralPos + 1) % numLEDs;
    delay(delayTime);
  }
  for (int i = numLEDs - 2; i > 0; i--) {
    byte ledValue = 1 << i;
    updateLEDs(ledValue);
    delay(delayTime);
  }
}

// Fungsi untuk menggerakkan LED dari kiri ke kanan dan kembali
void leftToRight() {
  for (int i = 0; i < numLEDs; i++) {
    byte ledValue = 1 << i;
    updateLEDs(ledValue);
    delay(delayTime);
  }
  for (int i = numLEDs - 1; i >= 0; i--) {
    byte ledValue = 1 << i;
    updateLEDs(ledValue);
    delay(delayTime);
  }
}

// Fungsi untuk pola LED random
void randomPattern() {
  for (int i = 0; i < 10; i++) {
    byte ledValue = random(256);
    updateLEDs(ledValue);
    delay(delayTime);
  }
}

// Fungsi untuk menggerakkan dua LED maju
void twoLEDsWalking() {
  for (int i = 0; i < numLEDs - 1; i++) {
    byte ledValue = (1 << i) | (1 << (i + 1));
    updateLEDs(ledValue);
    delay(delayTime);
  }
  for (int i = numLEDs - 2; i >= 0; i--) {
    byte ledValue = (1 << i) | (1 << (i + 1));
    updateLEDs(ledValue);
    delay(delayTime);
  }
}

// Fungsi untuk menggerakkan tiga LED bersamaan
void threeLEDsWalking() {
  for (int i = 0; i < numLEDs - 2; i++) {
    byte ledValue = (1 << i) | (1 << (i + 1)) | (1 << (i + 2));
    updateLEDs(ledValue);
    delay(delayTime);
  }
  for (int i = numLEDs - 3; i >= 0; i--) {
    byte ledValue = (1 << i) | (1 << (i + 1)) | (1 << (i + 2));
    updateLEDs(ledValue);
    delay(delayTime);
  }
}

// Fungsi untuk mengirim data ke shift register dan update LED
void updateLEDs(byte ledValue) {
  shiftOut(dataPin, clockPin, MSBFIRST, ledValue);
  digitalWrite(latchPin, HIGH);
  digitalWrite(latchPin, LOW);
}
