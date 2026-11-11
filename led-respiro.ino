/*
  LED que "respira" (efecto fade con PWM) para ESP32
  - Usa el LED integrado en GPIO2 (o conecta un LED + resistencia de 220 ohm)
  - La luz sube y baja suavemente
*/

const int PIN_LED = 2;
const int FRECUENCIA = 5000;   // Hz
const int RESOLUCION = 8;      // 8 bits = brillo de 0 a 255
const int VELOCIDAD_MS = 8;    // menor = mas rapido

void setup() {
  // Compatible con las versiones 2.x y 3.x del core de ESP32
  #if ESP_ARDUINO_VERSION_MAJOR >= 3
    ledcAttach(PIN_LED, FRECUENCIA, RESOLUCION);
  #else
    ledcSetup(0, FRECUENCIA, RESOLUCION);
    ledcAttachPin(PIN_LED, 0);
  #endif
}

void escribirBrillo(int brillo) {
  #if ESP_ARDUINO_VERSION_MAJOR >= 3
    ledcWrite(PIN_LED, brillo);
  #else
    ledcWrite(0, brillo);
  #endif
}

void loop() {
  // Subir brillo
  for (int b = 0; b <= 255; b++) {
    escribirBrillo(b);
    delay(VELOCIDAD_MS);
  }
  // Bajar brillo
  for (int b = 255; b >= 0; b--) {
    escribirBrillo(b);
    delay(VELOCIDAD_MS);
  }
}