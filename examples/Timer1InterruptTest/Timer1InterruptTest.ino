/****************************************************************************************************************************
  Timer1InterruptTest.ino
  For Arduino and Adadruit AVR 328(P) and 32u4 boards
  
  Created by: RTEK1000 (08-2025) based in TimerInterruptTest.ino (Written by Khoi Hoang)
  - Shortened version of TimerInterruptTest.ino

  Built by Khoi Hoang https://github.com/khoih-prog/TimerInterrupt
  Licensed under MIT license

  Now we can use these new 16 ISR-based timers, while consuming only 1 hardware Timer.
  Their independently-selected, maximum interval is practically unlimited (limited only by unsigned long miliseconds)
  The accuracy is nearly perfect compared to software timers. The most important feature is they're ISR-based timers
  Therefore, their executions are not blocked by bad-behaving functions / tasks.
  This important feature is absolutely necessary for mission-critical tasks.

  Notes:
  Special design is necessary to share data between interrupt code and the rest of your program.
  Variables usually need to be "volatile" types. Volatile tells the compiler to avoid optimizations that assume
  variable can not spontaneously change. Because your function may change variables while your program is using them,
  the compiler needs this hint. But volatile alone is often not enough.
  When accessing shared variables, usually interrupts must be disabled. Even with volatile,
  if the interrupt changes a multi-byte variable between a sequence of instructions, it can be read incorrectly.
  If your data is multiple variables, such as an array and a count, usually interrupts need to be disabled
  or the entire sequence of your code which accesses the data.
 *****************************************************************************************************************************/

#define USE_TIMER_1     true

#include "TimerInterrupt.h"

unsigned int outputPin1 = 13;  // UNO LED_BUILTIN: 13

#define TIMER1_INTERVAL_MS 500
#define TIMER1_FREQUENCY (float)(1000.0f / TIMER1_INTERVAL_MS)
#define TIMER1_DURATION_MS    (10UL * TIMER1_INTERVAL_MS)

void TimerHandler1(unsigned int outputPin = LED_BUILTIN) {
  static bool toggle1 = false;

  //timer interrupt toggles pin LED_BUILTIN
  digitalWrite(outputPin, toggle1);
  toggle1 = !toggle1;
}

void setup() {
  // put your setup code here, to run once:
  pinMode(outputPin1, OUTPUT);

  ITimer1.init();
  ITimer1.attachInterruptInterval(TIMER1_INTERVAL_MS, TimerHandler1, outputPin1, TIMER1_DURATION_MS);
}

void loop() {
  // put your main code here, to run repeatedly:
}