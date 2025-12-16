/* * Project : Fire Alarm
 * Hardware: ESP32, Flame Sensor, dan Buzzer
 * Penyusun: Fariz Husain Albar
 */

#define BLYNK_TEMPLATE_ID "TMPL6ccfM0LkC" 
#define BLYNK_TEMPLATE_NAME "Sistem Peringatan Kebakaran"
#define BLYNK_AUTH_TOKEN "_SRNbHVGll7zvuy41FN8f1CEqZIw0Hyg"

#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "fariz";
char pass[] = "anakyuin";

const int pinFlame = 34; 
const int pinBuzzer = 21; 

int flameValue = 0;      
bool isNotified = false;
BlynkTimer timer;

// KONFIGURASI SENSITIVITAS
// Nilai Analog: 4095 (Gelap/Jauh) -> 0 (Terang/Api Dekat)

// Batas 1: Zona Bahaya (Api < 15cm)
int BATAS_BAHAYA = 100; 

// Batas 2: Zona Waspada (Matahari / Api Jauh)
int BATAS_WASPADA = 2000; 

// Jumlah sampel untuk rata-rata
const int NUM_SAMPLES = 20; 

void checkSensor() {
  // ALGORITMA RATA-RATA (SMOOTHING)
  long totalValue = 0;
  
  // Ambil data 20 kali berturut-turut
  for (int i = 0; i < NUM_SAMPLES; i++) {
    totalValue += analogRead(pinFlame);
    delay(5); // Jeda dikit biar stabil
  }
  
  // Hitung rata-ratanya
  flameValue = totalValue / NUM_SAMPLES;
  
  // HITUNG PERSENTASE
  // Map: 4095=0% (Aman), 0=100% (Bahaya)
  int persentaseApi = map(flameValue, 4095, 0, 0, 100);
  if (persentaseApi < 0) persentaseApi = 0;

  // Kirim Nilai Gauge ke Blynk (V1)
  Blynk.virtualWrite(V1, persentaseApi);

  // Debugging
  Serial.print("Rata-rata Sensor: ");
  Serial.print(flameValue);
  Serial.print(" | Persen: ");
  Serial.println(persentaseApi);
  
  // KONDISI 1: BAHAYA (MERAH)
  if (flameValue < BATAS_BAHAYA) { 
    
    // Aksi Hardware: BUNYI
    digitalWrite(pinBuzzer, HIGH); 
    
    // Aksi Blynk
    Blynk.virtualWrite(V0, 1);                  // LED Nyala
    Blynk.virtualWrite(V2, "KEBAKARAN!!");      // Teks Status
    
    // UBAH WARNA JADI MERAH (Teks & Gauge)
    Blynk.setProperty(V2, "color", "#D3435C");  
    Blynk.setProperty(V1, "color", "#D3435C");  

    // Kirim Notifikasi
    if (!isNotified) {
      Blynk.logEvent("fire_alert", "AWAS! Api Terdeteksi Sangat Dekat!");
      isNotified = true;
    }

  } 
  // KONDISI 2: WASPADA (KUNING) - SOLUSI MATAHARI
  else if (flameValue < BATAS_WASPADA) {
    
    // Aksi Hardware: DIAM
    digitalWrite(pinBuzzer, LOW); 
    
    // Aksi Blynk
    Blynk.virtualWrite(V0, 0);                       // LED Mati
    Blynk.virtualWrite(V2, "Waspada / Cahaya Terang"); // Teks Status
    
    // UBAH WARNA JADI KUNING (Teks & Gauge)
    Blynk.setProperty(V2, "color", "#ED9D00");       
    Blynk.setProperty(V1, "color", "#ED9D00");  

    isNotified = false; // Reset notifikasi
  } 
  // KONDISI 3: AMAN (HIJAU)
  else {
    
    // Aksi Hardware: DIAM
    digitalWrite(pinBuzzer, LOW); 
    
    // Aksi Blynk
    Blynk.virtualWrite(V0, 0);                  // LED Mati
    Blynk.virtualWrite(V2, "Ruangan Aman");     // Teks Status
    
    // UBAH WARNA JADI HIJAU (Teks & Gauge)
    Blynk.setProperty(V2, "color", "#23C48E");  
    Blynk.setProperty(V1, "color", "#23C48E");
    
    isNotified = false; 
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(pinBuzzer, OUTPUT);
  digitalWrite(pinBuzzer, LOW); 

  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, checkSensor); 
}

void loop() {
  Blynk.run();
  timer.run();
}
