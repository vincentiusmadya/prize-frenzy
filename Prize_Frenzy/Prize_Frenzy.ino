#include <Arduboy2.h>
#include <ArduboyTones.h>

// make an instance of arduboy used for many functions
Arduboy2 arduboy;
ArduboyTones sound(arduboy.audio.enabled);

#include "GameState.h"

#include "MainMenuScene.h"
#include "GameScene.h"

GameState *gameState;

void setup() {
  arduboy.begin();
  arduboy.setFrameRate(30);
  arduboy.initRandomSeed();
  
  gameState = new GameState();
}

void loop() {
  if (!(arduboy.nextFrame()))
    return;

  arduboy.clear();
  arduboy.pollButtons();

  switch (gameState->currentState) {
    case (STATE_MAIN_MENU):
      MainMenuScene(gameState);
      break;
    case (STATE_CREDIT):
      stateCredit(gameState);
      break;
    case (STATE_PRE_GAME_PLAYING):
      PreGame(gameState);
      break;
    case (STATE_GAME_PLAYING):
      GameScene(gameState);
      break;
    case (STATE_PRE_GAME_OVER):
      statePreGameOver(gameState);
      break;
    case (STATE_GAME_OVER):
      stateGameOver(gameState);
      break;
    case (STATE_HELP):
      stateHelp(gameState);
      break;
  }

  arduboy.display();
}
