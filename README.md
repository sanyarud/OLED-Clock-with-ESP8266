# OLED-Clock-with-ESP8266

![OLED-Clock-with-ESP8266](https://github.com/sanyarud/OLED-Clock-with-ESP8266/blob/main/photo_2024-05-31_17-10-53.jpg)
---
![OLED-Clock-with-ESP8266](https://github.com/sanyarud/OLED-Clock-with-ESP8266/blob/main/photo_2024-05-31_17-10-22.jpg)



This project implements a simple digital clock on an **OLED display** using an **ESP8266** microcontroller. The clock fetches time from an NTP server and displays it along with the date and day of the week.
## Getting Started
### Prerequisites
* Arduino IDE installed on your computer.
* ESP8266 board package installed in the Arduino IDE.
## Libraries required:
* ESP8266WiFi
* TimeLib
* Wire
* SSD1306Wire
* OLEDDisplayUi
* NTPClient
* WiFiUdp
* Timezone

## Installing

Open Arduino IDE.
Go to File > Preferences, and in the "Additional Board Manager URLs" field, add the following URL: [http://arduino.esp8266.com/stable/package_esp8266com_index.json](url).
Go to Tools > Board > Boards Manager, search for "**esp8266**" and install the package.
Go to **Sketch** > **Include Library** > **Manage Libraries**... and install the required libraries listed above.

## Hardware Setup

Connect your **ESP8266** board to your computer via USB.
Connect your OLED display to the ESP8266 board using the appropriate pins (refer to your display's datasheet).
Ensure your display has the correct address set (**usually 0x3C**).

## Usage

Open the oled_clock.ino file in Arduino IDE.
Set your **WiFi SSID** and password in the ssid and password variables.
Customize the timezone settings in the myDST and mySTD variables according to your location.
Upload the code to your **ESP8266** board.
Open the Serial Monitor to monitor the connection process (baud rate: 115200).
Once connected, the clock will automatically synchronize with the NTP server and display the time on the OLED display.

## Contributing

Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.
## License

This project is licensed under the MIT License - see the [LICENSE](https://github.com/sanyarud/OLED-Clock-with-ESP8266/blob/main/LICENSE) file for details.
