/* Project : Fire Alarm
 * Hardware: ESP32, Flame Sensor
 * Penyusun: Fariz Husain Albar
 */

#define BLYNK_TEMPLATE_ID "TMPL6ccfM0LkC" 
#define BLYNK_TEMPLATE_NAME "Sistem Peringatan Kebakaran"
#define BLYNK_AUTH_TOKEN "_SRNbHVGll7zvuy41FN8f1CEqZIw0Hyg"

#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "lambor";
char pass[] = "gantengnyo";

// Disini Tulis Masing" PIN Dimanaa
const int pinFlame = 34;  // ke pin ADC (D34/D35/VP/VN)
const int pinBuzzer = 21; // Buzzer di D21

int flameValue = 0;       // Variabel menampung nilai (0 - 4095)
bool isNotified = false;
BlynkTimer timer;

void checkSensor() {
  // 1. BACA SENSOR (ANALOG)
  flameValue = analogRead(pinFlame);
  
  // 2. DEBUGGING
  Serial.print("Nilai Analog Api: ");
  Serial.println(flameValue);

  // Kirim nilai mentah ke Gauge di Blynk (Opsional, buat V1 di dashboard kalau mau lihat grafik)
  // Blynk.virtualWrite(V1, flameValue);

  // 3. LOGIKA ALARM ANALOG
  // Sensor Api Analog:
  // Nilai 4095 (Maksimal) = Gelap / Tidak Ada Api
  // Nilai mendekati 0 = Api Sangat Besar
  // Kita set "AMBANG BATAS" (Threshold). 
  // Contoh: Jika nilai DI BAWAH 1000, berarti ada api.
  
  if (flameValue < 100) {  // <--- ANGKA 1000 INI BISA DIUBAH SESUAI KONDISI
    
    // KONDISI BAHAYA
    digitalWrite(pinBuzzer, HIGH);
    Blynk.virtualWrite(V0, 1); // LED Nyala
    Serial.println(">>> API TERDETEKSI! <<<");

    if (!isNotified) {
      Blynk.logEvent("fire_alert", "AWAS! Api Terdeteksi!");
      isNotified = true;
    }

  } else {
    // KONDISI AMAN (Nilai di atas 1000)
    digitalWrite(pinBuzzer, LOW);
    Blynk.virtualWrite(V0, 0); // LED Mati
    isNotified = false;
  }
}

void setup() {
  Serial.begin(115200);
  
  // Analog pin tidak perlu pinMode INPUT, langsung baca saja owkaii??
  pinMode(pinBuzzer, OUTPUT);
  digitalWrite(pinBuzzer, LOW);

  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, checkSensor);
}

void loop() {
  Blynk.run();
  timer.run();
}
