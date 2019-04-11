/*
  EZExpander.cpp - EZExpander Library
  Copyright (C) 2010 Michael Krumpus  All rights reserved.
 
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  See file LICENSE.txt for further informations on licensing terms.
*/


#include "EZExpander.h"


EZExpander::EZExpander()
{
  init(DEFAULT_LATCH_PIN, DEFAULT_CLOCK_PIN, DEFAULT_DATA_PIN);
}

void EZExpander::init(int latchPin, int clockPin, int dataPin)
{
    this->latchPin = latchPin;
  this->clockPin = clockPin;
  this->dataPin = dataPin;
  data1 = 0;
  data2 = 0;

  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  digitalWrite(this->latchPin, LOW);
  shiftOut(this->dataPin, this->clockPin, MSBFIRST, data2);
  shiftOut(this->dataPin, this->clockPin, MSBFIRST, data1);
  digitalWrite(this->latchPin, HIGH);
}

EZExpander::EZExpander(int latchPin, int clockPin, int dataPin)
{
  init(latchPin, clockPin, dataPin);
}

void EZExpander::digitalWrite(int pin, uint8_t v) {
  digitalWrite(pin, v, true);
}

void EZExpander::digitalWrite(int pin, uint8_t v, bool doShift) {
  if ((pin < REGISTER1_FIRST_PIN) || (pin > REGISTER2_LAST_PIN)) {
    return;
  }
  int bit = pin - REGISTER1_FIRST_PIN;
  if (bit < 8) {
    if (v == HIGH) {
      data1 = data1 | (1 << bit);
    } else {
      if (v == LOW) {
        data1 = data1 & ~(1 << bit);
      }
    }
  }
  if (bit >= 8) {
    bit -= 8;
    if (v == HIGH) {
      data2 = data2 | (1 << bit);
    } else {
      if (v == LOW) {
        data2 = data2 & ~(1 << bit);
      }
    }
  }
  if (doShift) {
    doShiftOut();
  }
}


void EZExpander::doShiftOut() {
  if (this->latchPin == DEFAULT_LATCH_PIN) {
    // optimized for default latch pin
    PORTB &= B11101111;
  } else {
    digitalWrite(this->latchPin, LOW);
  }
  shiftOut(this->dataPin, this->clockPin, MSBFIRST, data2);
  shiftOut(this->dataPin, this->clockPin, MSBFIRST, data1);
  if (this->latchPin == DEFAULT_LATCH_PIN) {
    // optimized for default latch pin
    PORTB |= B00010000;
  } else {
    digitalWrite(this->latchPin, HIGH);
  }
}


