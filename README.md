# Fire Alarm System with Blynk (ESP32)

**Author:** Fariz Husain Albar  
**Platform:** ESP32 & Blynk IoT  
**Bahasa:** C++ (Arduino IDE)

## Deskripsi Proyek
Proyek ini adalah sebuah sistem peringatan dini kebakaran berbasis IoT (Internet of Things). Berbeda dengan sistem digital biasa, proyek ini menggunakan **Flame Sensor Analog** untuk mendeteksi intensitas api dengan lebih presisi. Sistem memberikan peringatan ganda:
1.  **Peringatan Lokal:** Suara alarm melalui Buzzer saat intensitas api melewati ambang batas.
2.  **Peringatan Jarak Jauh:** Notifikasi ke smartphone melalui aplikasi Blynk.

## Fitur Utama
* **Analog Monitoring:** Memantau intensitas api secara spesifik (Range nilai 0 - 4095).
* **Push Notification:** Mengirim notifikasi *"AWAS! Api Terdeteksi!"* ke HP saat sensor mendeteksi api berbahaya.
* **Indikator Visual:** Widget LED pada dashboard Blynk menyala saat ada api.
* **Hardware Alert:** Buzzer berbunyi otomatis saat nilai analog sensor di bawah batas aman (threshold).

## Kebutuhan Hardware
1.  **Microcontroller:** ESP32 Development Board (DOIT DEVKIT V1 atau sejenisnya).
2.  **Sensor:** Flame Sensor (Sensor Api) - Menggunakan Pin Analog (A0).
3.  **Output:** Active Buzzer (3.3V).
4.  **Koneksi:** Kabel Jumper & Breadboard.
5.  **Power:** Kabel Micro USB.

## Diagram Rangkaian (Wiring)

Berikut adalah konfigurasi pin yang digunakan dalam kode program:

| Komponen | Pin Komponen | Pin ESP32 | Keterangan |
| :--- | :--- | :--- | :--- |
| **Flame Sensor** | A0 (Analog Out) | **GPIO 34** | Input sinyal analog (ADC 1) |
| | VCC | 3.3V / VIN | Sumber daya |
| | GND | GND | Ground |
| **Buzzer** | Positif (+) | **GPIO 21** | Output suara |
| | Negatif (-) | GND | Ground |

> **Catatan Penting:** Pastikan kabel sensor terhubung ke pin **A0 (Analog)**, bukan D0. Pin GPIO 34 pada ESP32 adalah pin *Input Only* yang khusus untuk membaca nilai analog.

## Konfigurasi Blynk

Untuk menjalankan proyek ini, atur Dashboard Blynk sebagai berikut:

1.  **Template Setup:**
    * **Name:** `Sistem Peringatan Kebakaran`
    * **Hardware:** ESP32
    * **Connection Type:** WiFi

2.  **Datastreams:**
    * **Virtual Pin V0:**
        * Name: `Status Api`
        * Data Type: `Integer`
        * Min/Max: `0/1` (0 = Aman, 1 = Bahaya).
    * *(Opsional)* **Virtual Pin V1:**
        * Name: `Intensitas Api`
        * Data Type: `Integer`
        * Min/Max: `0/4095` (Untuk melihat grafik).

3.  **Events (Penting untuk Notifikasi):**
    * Buat Event baru dengan kode: `fire_alert`
    * Nama Event: `Fire Detection`
    * Type: `Critical`
    * Aktifkan opsi **"Send Loop to Notifications"** agar notifikasi masuk ke tab Notifications di HP.

## Cara Instalasi & Penggunaan

1.  **Persiapan Software:**
    * Install [Arduino IDE](https://www.arduino.cc/en/software).
    * Install Library Blynk: `Sketch` -> `Include Library` -> `Manage Libraries` -> Cari **Blynk** by Volodymyr Shymanskyy.
    * Install Driver ESP32 Board pada Arduino IDE.

2.  **Konfigurasi Kode:**
    * Buka file `.ino`.
    * Sesuaikan bagian kredensial WiFi pada baris berikut:
        ```cpp
        char ssid[] = "NAMA_WIFI_ANDA"; // Masukkan nama WiFi
        char pass[] = "PASSWORD_WIFI_ANDA"; // Masukkan password WiFi
        ```
    * Pastikan `BLYNK_TEMPLATE_ID` dan `BLYNK_AUTH_TOKEN` sesuai dengan Dashboard Anda.

3.  **Upload:**
    * Hubungkan ESP32 ke komputer.
    * Pilih Board dan Port yang sesuai di Arduino IDE.
    * Klik tombol **Upload**.

4.  **Pengujian & Kalibrasi:**
    * Buka Serial Monitor (Baud rate **115200**).
    * Lihat nilai yang muncul ("Nilai Analog Api: ...").
    * Dekatkan api. Nilai akan turun drastis (misal dari 4000 menjadi 50).
    * Jika Buzzer tidak bunyi, naikkan angka threshold di kodingan (default: 100).

## Catatan Logika Sensor (Analog)
Program ini menggunakan pembacaan ADC dengan logika kebalikan (Inverse):
* **Nilai Tinggi (4095):** Gelap / Tidak ada api (Aman).
* **Nilai Rendah (< 100):** Terang / Ada api (Bahaya).

Kode logika yang digunakan:
```cpp
if (flameValue < 100) { // Jika nilai di bawah 100
   // Nyalakan Alarm & Kirim Notifikasi
}
```

Disclaimer: Proyek ini dibuat untuk tugas Mata Kuliah Arsitektur Komputer.
