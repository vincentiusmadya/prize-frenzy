#ifndef MAIN_MENU_SCENE_H
#define MAIN_MENU_SCENE_H

#include "Images.h"

int mainMenuIndex = 0;

const int MAIN_MENU_TOTAL = 3;

void MainMenuScene(GameState *gameState) {
  arduboy.drawBitmap(0, 0, main_menu_image, 128, 64, WHITE);

  arduboy.drawBitmap(36, 50, left_indicator, 8, 8, WHITE);
  arduboy.drawBitmap(84, 50, right_indicator, 8, 8, WHITE);

  if (arduboy.justPressed(LEFT_BUTTON))
    mainMenuIndex = ((mainMenuIndex - 1) + MAIN_MENU_TOTAL) % MAIN_MENU_TOTAL;
  if (arduboy.justPressed(RIGHT_BUTTON))
    mainMenuIndex = (mainMenuIndex + 1) % MAIN_MENU_TOTAL;

  if (mainMenuIndex == 0) {
    arduboy.setCursor(50, 50);
    arduboy.print("START");
  } else if (mainMenuIndex == 1) {
    arduboy.setCursor(52, 50);
    arduboy.print("HELP");
  } else if (mainMenuIndex == 2) {
    arduboy.setCursor(46, 50);
    arduboy.print("CREDIT");
  }
  
  if (arduboy.justPressed(A_BUTTON)) {
    if (mainMenuIndex == 0)
      gameState->currentState = STATE_PRE_GAME_PLAYING;
    if (mainMenuIndex == 1)
      gameState->currentState = STATE_HELP;
    if (mainMenuIndex == 2)
      gameState->currentState = STATE_CREDIT;
  }
}

void stateCredit(GameState *gameState) {
  arduboy.drawBitmap(0, 10, credit_image, 128, 64, WHITE);
  
  if (arduboy.justPressed(B_BUTTON))
    gameState->currentState = STATE_MAIN_MENU;
}

void stateHelp(GameState *gameState) {
  arduboy.drawRect(33, 1, 61, 61, WHITE);
  arduboy.drawBitmap(34, 2, qr_code, 59, 59, WHITE);

  if (arduboy.justPressed(B_BUTTON))
    gameState->currentState = STATE_MAIN_MENU;
}

#endif  
