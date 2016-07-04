Subcarrier_Generater
===


This repository uses for generating a subcarrier.

---


## Environment

### Hardware
- Atmega328p-pu <http://www.atmel.com/images/Atmel-8271-8-bit-AVR-Microcontroller-ATmega48A-48PA-88A-88PA-168A-168PA-328-328P_datasheet_Complete.pdf>
- FT232RL <http://akizukidenshi.com/catalog/g/gK-01977/>
- USB cable(miniB-A)

### Software
- OS: Ubuntu-15.10
- Library: avrdude, arduino, arduino-core, arduino-mk


## Installation
```
yum install avrdude arduino arduino-core arduino-mk
```


## How to use
1. Check connection
```
sudo avrdude -p m328p -c diecimila -b 9600 -U lfuse:w:0xE2:m -D
```

2. Compile the program
```
make
```

3. write the program into atmega328p
```
cd build-atmega328
sudo avrdude -p -c diecimila -b 9600 -U flash:w:[target_file.hex]
sudo avrdude -p -c diecimila -b 9600 -U flash:w:[target_file.hex] -D
```


## Note

- Library install
  1. Install library into /usr/share/arduino/libraries
  2. Write "ARDUINO_LIBS=[library_name]" into Makefile


## Reference
- Arduino nanoのPWM機能使ってみた <http://makers-with-myson.blog.so-net.ne.jp/2016-02-12>
- Arduino pi配置 <http://wiki.onakasuita.org/pukiwiki/?Arduino%2F%E3%83%94%E3%83%B3%E9%85%8D%E7%BD%AE>
- Arduino 日本語レファレンス <http://www.musashinodenpa.com/arduino/ref/index.php>
- AVRでの割り込みの使い方 <http://usicolog.nomaki.jp/engineering/avr/avrInterrupt.html>
- Arduinoで遊ぶページ <http://garretlab.web.fc2.com/arduino/inside/arduino/wiring_analog.c/analogWrite.html>
