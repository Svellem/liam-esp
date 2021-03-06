#ifndef _log_store_h
#define _log_store_h

#include <Arduino.h>
#include <deque>
#include "HardwareSerial.h"
#include "definitions.h"

struct logmessage {
  uint16_t id;  
  String message;
};

struct logmessage_response {
  const uint16_t total;
  const std::deque<logmessage>& messages;
};

class LogStore : public HardwareSerial {
  public:
    LogStore();
    size_t write(uint8_t) override;
    size_t write(const uint8_t* buffer, size_t size) override;
    logmessage_response getLogMessages();

  private:
    std::deque<logmessage> log_messages;
    String current_line;
    uint16_t current_lastnr = 0;
    void writeInternal(uint8_t c);
};

extern LogStore LoggingSerial;

#endif