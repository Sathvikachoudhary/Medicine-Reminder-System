# 💊 Medicine Reminder System ⏰

## 📌 Project Overview:
The Medicine Reminder System is a basic embedded system designed to alert users at a specific time to take their medicine. Built using the ARM7-based LPC2148 microcontroller, which comes with an inbuilt Real-Time Clock (RTC), this system helps individuals—especially the elderly or patients under medication—to maintain timely dosage schedules.

## 🛠️ Tools & Technologies Used:
- Keil µVision 4 – For coding and compilation  
- Proteus Design Suite – For simulating circuit behavior  
- Flash Magic – Helps in dumping the executable (.hex) file into the LPC2148 microcontroller.
- LPC2148 Microcontroller – ARM7 MCU with inbuilt RTC support

## 🧩 Hardware Components:
- 🧠 LPC2148 Microcontroller (ARM7)
- ⌚ Inbuilt RTC – Maintains accurate time
- 📺 20x4 LCD Display – Shows current time and alerts
- 🎛️ 4x4 Keypad – Used to set a reminder time
- 🔔 Buzzer – Sounds an alert when it's time for the medicine
- 🔌 Power Supply Unit – To power the setup

## ✨ Key Features:
✅ User can set one reminder time using the keypad  
✅ LCD continuously displays real-time clock and messages  
✅ A buzzer rings at the set time to remind the user  
✅ Simple and user-friendly keypad interface  
✅ Efficient use of RTC ensures precise time-based alerting

## ⚙️ How It Works:
1. At boot-up, the system initializes the RTC, LCD, buzzer, and keypad .
2. The real-time clock is shown on the LCD screen and after pressing switch 1 menu will displayed on LCD to do changes.
3. The user sets one fixed reminder time through the keypad.
4. The system continuously checks the RTC to keep track of the current time.
5. When current time matches the reminder:
   - 🔔 The buzzer activates.
   - 📢 LCD shows a message like  "Time to take medicine".
6. The user can interrupt the alert by pressing a switch2, which will then return the system to idle mode.

## 🚀 Steps to Compile & Run:
### 🔧 1. Compile Code  
   - Use Keil µVision 4 to write and compile the C program.  
   - Generate the `.hex` file after successful build.

### 🧪 2. Simulate (Optional)  
   - Open Proteus Design Suite.  
   - Load the `.hex` into LPC2148 in your circuit.  
   - Simulate the behavior and test alarm functionality.

### 💾 3. Flash to Hardware 
   - Connect your LPC2148 board to PC.  
   - Open Flash Magic.  
   -Select the appropriate device and COM port, followed by browsing to select the .hex file.
   - Click Start to flash code onto hardware.

### 🔌 4. Run on Hardware  
   - Connect LCD, keypad, and buzzer to LPC2148 as per circuit.  
   - Power the system — it will start showing time and accept reminder input.

## 📍 Applications:
🏠 Home use for single daily medication  
🏥 Small clinics and elderly care where a single alert is sufficient  
🔧 Can be extended to multi-reminder systems or automatic pill dispensers

# Happy Coding.......!
