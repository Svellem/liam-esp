#include "abstract_state.h"

class Paused : public AbstractState {
  Paused(StateController& stateController) : AbstractState(stateController) {

  }

  void selected(Definitions::MOWER_STATES lastState) {

  }

  void run() {

  }
};
