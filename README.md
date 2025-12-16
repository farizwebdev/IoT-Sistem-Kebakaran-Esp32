# Fire Alarm System with Blynk (ESP32)

**Penyusun:** Fariz Husain Albar    
**Jurusan:** Informatika - UIN Sunan Kalijaga Yogyakarta  
**Hardware:** ESP32, Flame Sensor, Buzzer  

## Deskripsi Proyek
Sistem peringatan dini kebakaran berbasis IoT yang dirancang untuk mendeteksi intensitas api menggunakan sensor analog. Sistem ini dilengkapi dengan **algoritma smoothing** (rata-rata sampel) untuk pembacaan data yang stabil dan mengurangi *noise*.

Sistem terintegrasi dengan **Blynk IoT** untuk monitoring jarak jauh, menampilkan status keamanan dalam 3 zona warna (Hijau, Kuning, Merah), serta mengirim notifikasi darurat ke smartphone.

## Fitur Utama
* **Smart Smoothing:** Mengambil 20 sampel data sensor sebelum dikirim untuk hasil yang akurat.
* **Real-time Monitoring:** Menampilkan intensitas api dalam persentase (0% - 100%).
* **Dynamic UI:** Warna dashboard berubah otomatis sesuai kondisi:
    * 🟢 **Hijau:** Aman.
    * 🟡 **Kuning:** Waspada (Cahaya terang/Api jauh).
    * 🔴 **Merah:** Bahaya (Api < 15cm).
* **Peringatan Ganda:** Alarm fisik (Buzzer) dan Notifikasi Push ke HP ("AWAS! Api Terdeteksi Sangat Dekat!").

## Kebutuhan Hardware
1.  **ESP32 Development Board** (DOIT DEVKIT V1).
2.  **Flame Sensor** (KY-026 atau sejenisnya) - Mode Analog.
3.  **Active Buzzer** 3.3V.
4.  Kabel Jumper & Breadboard.

## Konfigurasi Wiring (Pinout)
Sesuai dengan definisi kode `Fire_Alarm.ino`:

| Komponen | Pin Device | Pin ESP32 | Keterangan |
| :--- | :--- | :--- | :--- |
| **Flame Sensor** | A0 (Analog) | **GPIO 34** | Input data sensor |
| | VCC | 3V3 / VIN | Power |
| | GND | GND | Ground |
| **Buzzer** | Positif (+) | **GPIO 21** | Output suara |
| | Negatif (-) | GND | Ground |

> **Note:** Pin GPIO 34 adalah pin *Input Only* yang terhubung ke ADC1, optimal untuk pembacaan sensor analog.

## 📱 Konfigurasi Blynk Dashboard
Untuk sinkronisasi data, atur **Datastreams** sebagai berikut:

| Nama Stream | Virtual Pin | Tipe Data | Min/Max | Fungsi |
| :--- | :--- | :--- | :--- | :--- |
| **Status LED** | `V0` | Integer | 0 / 1 | Indikator visual alarm |
| **Persentase Api** | `V1` | Integer | 0 / 100 | Grafik gauge intensitas |
| **Status Teks** | `V2` | String | - | Menampilkan teks & warna dinamis |

**Pengaturan Event (Notifikasi):**
* Buat Event baru dengan kode: `fire_alert`
* Type: **Critical**
* Centang opsi: **Send Loop to Notifications**

## Logika Algoritma
Sistem menggunakan logika *Inverse Analog* (Nilai rendah = Terang/Api).

1.  **Zona Aman (Hijau)**
    * Nilai Sensor: `> 2000`
    * Aksi: Buzzer Mati, Status "Ruangan Aman".
2.  **Zona Waspada (Kuning)**
    * Nilai Sensor: `100 - 2000`
    * Aksi: Buzzer Mati, Status "Waspada / Cahaya Terang".
3.  **Zona Bahaya (Merah)**
    * Nilai Sensor: `< 100` (Threshold Bahaya)
    * Aksi: **Buzzer Bunyi**, LED Nyala, Notifikasi dikirim ke HP.

## Cara Instalasi
1.  Install **Arduino IDE** dan Library **Blynk** by Volodymyr Shymanskyy.
2.  Buka file `Fire_Alarm.ino`.
3.  Sesuaikan kredensial WiFi pada baris:
    ```cpp
    char ssid[] = "fariz"; 
    char pass[] = "anakyuin"; 
    ```
4.  Pastikan `BLYNK_TEMPLATE_ID` sesuai dengan akun Blynk Anda.
5.  Upload ke board ESP32.

---
*Dibuat untuk tugas Mata Kuliah Organisasi & Arsitektur Komputer.*
