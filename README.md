# Fire Alarm System with Blynk (ESP32)

**Author:** Fariz Husain Albar  
**Platform:** ESP32 & Blynk IoT  
**Bahasa:** C++ (Arduino IDE)

## Deskripsi Proyek
Proyek ini adalah sistem peringatan dini kebakaran berbasis IoT (Internet of Things). Sistem ini mendeteksi keberadaan api menggunakan **Flame Sensor** dan memberikan peringatan ganda:
1.  **Peringatan Lokal:** Suara alarm melalui Buzzer.
2.  **Peringatan Jarak Jauh:** Notifikasi ke smartphone melalui aplikasi Blynk.

## Fitur Utama
* **Real-time Monitoring:** Memantau status sensor api secara langsung via aplikasi Blynk.
* **Push Notification:** Mengirim notifikasi *"AWAS! Api Terdeteksi!"* ke HP saat sensor mendeteksi api.
* **Indikator Visual:** Widget LED pada dashboard Blynk menyala saat ada api.
* **Hardware Alert:** Buzzer berbunyi otomatis saat bahaya terdeteksi.

## Kebutuhan Hardware
1.  **Microcontroller:** ESP32 Development Board (DOIT DEVKIT V1).
2.  **Sensor:** Flame Sensor (Sensor Api) - Modul KY-026.
3.  **Output:** Active Buzzer (3.3V).
4.  **Koneksi:** Kabel Jumper & Breadboard.
5.  **Power:** Kabel Micro USB.

## Diagram Rangkaian (Wiring)

Berikut adalah konfigurasi pin yang digunakan dalam kode program:

| Komponen | Pin Komponen | Pin ESP32 | Keterangan |
| :--- | :--- | :--- | :--- |
| **Flame Sensor** | D0 (Digital Out) | **GPIO 23** | Input sinyal api |
| | VCC | 3.3V | Sumber daya |
| | GND | GND | Ground |
| **Buzzer** | Positif (+) | **GPIO 21** | Output suara |
| | Negatif (-) | GND | Ground |

> **Catatan:** Sensor Flame menggunakan logika **Active LOW** (0 = Ada Api, 1 = Aman).

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
        * Min/Max: `0/1` (0 = Aman, 1 = Bahaya/LED Nyala).

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
        char ssid[] = "NAMA_WIFI_ANDA"; // Contoh: uhuy
        char pass[] = "PASSWORD_WIFI_ANDA"; // Contoh: gantengnyo
        ```
    * Pastikan `BLYNK_TEMPLATE_ID` dan `BLYNK_AUTH_TOKEN` sesuai dengan Dashboard Anda.

3.  **Upload:**
    * Hubungkan ESP32 ke komputer.
    * Pilih Board dan Port yang sesuai di Arduino IDE.
    * Klik tombol **Upload**.

4.  **Pengujian:**
    * Buka Serial Monitor (Baud rate **115200**).
    * Dekatkan sumber api (korek api) ke sensor.
    * Pastikan Buzzer berbunyi dan Notifikasi muncul di HP.

## ⚠️ Catatan Logika Sensor
Program ini menggunakan logika **Active LOW** (umum pada modul sensor KY-026):
* **Nilai 1 (HIGH):** Tidak ada api (Kondisi Aman) -> Buzzer Mati.
* **Nilai 0 (LOW):** Api terdeteksi (Bahaya) -> Buzzer Nyala.

---
**Disclaimer:** Proyek ini dibuat untuk tujuan tugas Mata Kuliah Arsitektur Komputer.
