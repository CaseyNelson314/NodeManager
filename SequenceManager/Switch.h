/**
       @file   Switch.h
       @author CaseyNelson
       @date   2022/05/03
*/

#pragma once

class Switch {

    uint8_t pin;
    bool click_, press_, lastPress;

  public:

    Switch(uint8_t pin): pin(pin) {
      pinMode(pin, INPUT_PULLUP);
    }

    void update() {
      press_ = !digitalRead(pin);
      click_ = (lastPress == false && press_);
      lastPress = press_;
    }
    
    bool click() {
      return click_;
    }
    bool press() {
      return press_;
    }

};
