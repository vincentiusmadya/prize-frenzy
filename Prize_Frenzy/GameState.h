#ifndef GAME_STATE_H
#define GAME_STATE_H

const static int STATE_MAIN_MENU = 0;
const static int STATE_HELP = 1;
const static int STATE_CREDIT = 2;
const static int STATE_PRE_GAME_PLAYING = 3;
const static int STATE_GAME_PLAYING = 4;
const static int STATE_PRE_GAME_OVER = 5;
const static int STATE_GAME_OVER = 6;

class GameState {
  public:
    GameState() {
      currentState = STATE_MAIN_MENU;
    }

    int currentState;
};

#endif
