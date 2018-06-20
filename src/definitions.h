#ifndef _definitions_h
#define _definitions_h

#include <Arduino.h>

/*
  Constants and other global stuff that you should probably never need to touch.
*/

namespace Definitions {
    extern const char* const APP_NAME;
    extern const char* const APP_VERSION;

    enum class MOWER_STATES {
                              DOCKED,     // mower is docked in its charging station and is fully charged
                              LAUNCHING,  // mower is leaving its charging station to head out for mowing
                              MOWING,     // mower is currently mowing
                              DOCKING,    // mower has stopped mowing and is heading back to its charging station (battery may be running low)
                              CHARGING,   // mower is docked in its charging station and is currently charging
                              STUCK,      // mower is stuck somewhere and have shutdown (it may be stuck in a hole, the cutter may be stuck, or some other hardware issue...)
                              FLIPPED,    // mower is flipped upside down or tiled too much, stopp mowing and wait to be unflipped.
                              MANUAL,     // mower is in manual drive mode and controlled by user from REST-API.
                              STOP,       // mower is stopped from it's normal operation, this happens when user press the physical stopbutton or UI button.
                              TEST        // mower is in test mode.
                            };
};

#endif
