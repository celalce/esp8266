# ESP8266 Infrared (IR) Remote Controller

A lightweight smart home project that allows you to control infrared-enabled devices—such as televisions, air conditioners, and robotic/vacuum cleaners—remotely using an ESP8266 microcontroller and a mobile application.

---

## 📌 Project Overview

This project turns an **ESP8266** board into a universal IR remote controller. By capturing the IR signals of your existing target devices and loading them onto the microcontroller, you can trigger IR commands over Wi-Fi via a custom mobile application.

---

## 🛠️ Hardware Requirements

* **ESP8266 Board** (e.g., NodeMCU V2/V3, WeMos D1 Mini)
* **IR Transmitter LED** (940nm IR LED)
* *(Optional)* NPN Transistor (e.g., 2N2222) or MOSFET module to boost IR LED range
* Resistor (100Ω - 220Ω depending on setup)
* Breadboard and Jumper Wires

---

## 🔌 Circuit & Wiring

Connect the IR transmitter LED to your ESP8266 as follows:

| IR LED Pin | ESP8266 Pin | Notes |
| :--- | :--- | :--- |
| **Short Leg (Cathode)** | **GND** | Ground connection |
| **Long Leg (Anode)** | **D2 (GPIO4)** | Data/Signal output pin |

> **Tip:** If you need a longer range for your remote control signal, consider using a transistor circuit to drive higher current through the IR LED.

---

## 🚀 Setup & Installation

### Step 1: Capture IR Remote Codes
Before flashing the main code onto your ESP8266, you must capture the specific IR codes for your target device (TV, AC, vacuum, etc.):
1. Use an **IR Receiver Module** (e.g., VS1838B) connected to your ESP8266.
2. Load an IR receiver/decoder sketch in the **Arduino IDE** (using libraries like `IRremoteESP8266`).
3. Press the buttons on your original remote control while monitoring the Serial Monitor to record the HEX/Protocol codes.
4. *Numerous tutorials and guides on capturing IR codes are available on YouTube and electronic forums.*

### Step 2: Configure Arduino IDE
1. Open a new sketch in **Arduino IDE**.
2. Install the **IRremoteESP8266** library via *Tools > Manage Libraries...*
3. Insert your recorded IR codes into the project sketch.
4. Select your ESP8266 board model and COM port under *Tools*.
5. Upload the code to your ESP8266.

---

## 📱 Mobile Application Integration
**📱 Mobil Uygulama Entegrasyonu**

To control the IR transmitter remotely from your smartphone:
**IR vericiyi akıllı telefonunuzdan uzaktan kontrol etmek için:**

 If you are going to start using the application, send a request to [celalce25@hotmail.com](mailto:celalce25@hotmail.com).
  **Eğer uygulamaya başlayacaksanız celalce25@hotmail.com adresinden istekte bulunun.**
 The application file (APK) will be sent to your email address.
  **Uygulama (APK) mail adresinize gönderilecektir.**


## 📧 Contact & Support

If you have questions, feedback, or need help creating the mobile application, please get in touch:

* **Email:** [celalce25@hotmail.com )
* **GitHub:** [@your-username](https://github.com/celalce)

---


This project is open-source and available under.



