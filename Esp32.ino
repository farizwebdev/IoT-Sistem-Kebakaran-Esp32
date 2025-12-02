/* * Judul: Fire Alarm System with Blynk
 * Hardware: ESP32, Flame Sensor (D23), Buzzer (D21)
 * Author: Fariz Husain Albar
 */

// --- KREDENSIAL BLYNK ---
// (Salin dari Device Info di Dashboard Blynk)
#define BLYNK_TEMPLATE_ID "TMPL6ccfM0LkC" 
#define BLYNK_TEMPLATE_NAME "Sistem Peringatan Kebakaran"
#define BLYNK_AUTH_TOKEN "_SRNbHVGll7zvuy41FN8f1CEqZIw0Hyg"

// --- KONFIGURASI ---
#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

// Kredensial WiFi
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "uhuy";    // SSID WiFi Anda
char pass[] = "gantengnyo";   // Password WiFi Anda

// Definisi Pin
const int pinFlame = 23;  // Sensor Api di Pin D23
const int pinBuzzer = 21; // Buzzer di Pin D21

// Variabel
int flameState = 0;       
bool isNotified = false;  
BlynkTimer timer;

// Fungsi Pembacaan Sensor
void checkSensor() {
  // 1. BACA SENSOR
  flameState = digitalRead(pinFlame);
  
  // 2. DEBUGGING
  Serial.print("Nilai Sensor: ");
  Serial.println(flameState);

  // 3. KIRIM KE BLYNK
  // Kirim kebalikan (!flameState) agar:
  // Kalau Sensor 1 (Aman) -> Kirim 0 (LED Mati)
  // Kalau Sensor 0 (Api)  -> Kirim 1 (LED Nyala)
  Blynk.virtualWrite(V0, !flameState); 

  // 4. LOGIKA ALARM (Active LOW)
  // KITA KEMBALIKAN KE LOGIKA AWAL: 0 = BAHAYA
  if (flameState == LOW) { 
    
    // Nyalakan Buzzer
    digitalWrite(pinBuzzer, HIGH);
    Serial.println(">>> BAHAYA! API TERDETEKSI! (Logika 0) <<<");

    // Kirim Notifikasi
    if (!isNotified) {
      Blynk.logEvent("fire_alert", "AWAS! Api Terdeteksi!"); 
      isNotified = true;
    }

  } else {
    // KONDISI AMAN (Nilai 1 / HIGH)
    digitalWrite(pinBuzzer, LOW); 
    isNotified = false;
  }
}

void setup() {
  Serial.begin(115200); // Baud rate ESP32

  pinMode(pinFlame, INPUT);
  pinMode(pinBuzzer, OUTPUT);
  digitalWrite(pinBuzzer, LOW); 

  // Koneksi ke Blynk
  Blynk.begin(auth, ssid, pass);

  // Jalankan checkSensor setiap 1 detik
  timer.setInterval(1000L, checkSensor);
}

void loop() {
  Blynk.run();
  timer.run();
}
