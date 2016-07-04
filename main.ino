#include <avr/io.h>
#include <avr/interrupt.h>

#define INVERSE_BITS 0b11000000

char output = 0b10000000;
volatile int counter = 0;
static char data = 0b00100010;

void setup() {
  int toggle_val = 49;
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  PORTD = 0b00000000; // initialize PORTD

  if(bitRead(data, 0) == 0){
    output ^= INVERSE_BITS;
  }

  delay(5000); // for clock being stable
  digitalWrite(8, HIGH);
  noInterrupts(); // prohibit interrupts


  /* Timer 2 setting */
  TCCR2A = bit(WGM21); // CTC (OCR2A)

  /*
    Timer_freq = 8MHz(clock) / (2 * division_ratio * [toggle_val + 1])
    Subcarrier_freq = Timer_freq
  */
  //TCCR2B = bit(CS20); // division_ratio = 1
  TCCR2B = bit(CS21); // division_ratio = 8
  //TCCR2B = bit(CS20) | bit(CS21); // division_ratio = 32
  //TCCR2B = bit(CS22); // division_ratio = 64
  //TCCR2B = bit(CS20) | bit(CS22); // division_ratio = 128
  //TCCR2B = bit(CS21) | bit(CS22); // division_ratio = 256
  //TCCR2B = bit(CS20) | bit(CS21) | bit(CS22); // division_ratio = 1024

  OCR2A = toggle_val; // The timer will be 0 next this value
  TIMSK2 = bit(OCIE2A);

  interrupts(); // allow interrupts
}

ISR(TIMER2_COMPA_vect) {
  int processing_unit_num = 8; // band_width = subcarrier_freq / (processing_unit_num / 2)
  static int index = 1;
  static boolean prev = bitRead(data, 0);

  PORTD = output; // output from 7pin & 8pin inversely
  output ^= INVERSE_BITS;

  if(counter == processing_unit_num - 1) {
    if(bitRead(data, index) != prev) {
      output ^= INVERSE_BITS;
    }
    prev = bitRead(data, index);
    counter = 0;
    index++;
    if(index == 8){ // when the index eqauls to data-bits-number, it restarts from first bit
      index = 0;
    }
  } else {
    counter++;
  }
}

void loop() {
}

/* reference
  - atmega328p datasheet: 18.11 Register Description
  - http://makers-with-myson.blog.so-net.ne.jp/2016-02-12
  - http://usicolog.nomaki.jp/engineering/avr/avrInterrupt.html
*/
