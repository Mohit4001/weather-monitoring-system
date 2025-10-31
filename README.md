# weather-monitoring-system
AIM: To be updated with Temperature, Humidity and Air quality of the
surrounding. Also display this data on both the OLED and in a web browser.
HARDWARE:
1. NodeMCU board
2. ESP8266 module
3. DHT sensor (if not present in the board)
4. Air Quality sensor (MQ135)
5. OLED
6. USB cable
7. Jumper wire
SOFTWARE: Arduino IDE,
(Proper Wi-fi Connection is required in this experiment.)
CONNECTIONS:
OLED-ESP8266
GND-GND
VCC-3.3V
SCL-D1
SDA-D2
DHT sensor-ESP8266
GND-GND
DATA-D4
3V3-3V3
MQ135 sensor-ESP8266
GND-GND
A0 -A0
PWR-3V3
PROCEDURE:
1. Take NodeMCU board, mount the OLED screen and Air quality sensor at
their respective place in the board (DHT sensor is already mounted).
2. Connect the OLED, DHT sensor, Air quality sensor (MQ135) and ESP8266
according to above table. (Note: These connections must also be defined in
the code.)
3. Open Arduino IDE.
4. Connect NodeMCU board with your laptop using USB cable.
5. Go to Board manager tab and connect NodeMCU board with Arduino IDE
by selecting the board (NodeMCU 12E module).
6. Write the program for weather monitoring system in the IDE and installed
the required library mentioned in the program from library manager.
7. In the program write your own wi-fi credentials in the line where wi-fi
credentials is mentioned.
8. Once the program is ready to upload, upload it by clicking on the arrow
present in the top left corner.
9. Once the program is successfully uploaded, open serial monitor, set the
baud rate as 115200 (as written in code) and note the IP address.
10.Enter the IP address in the web browser to see the result.
Result:
Result on the web browser
Result on OLED
