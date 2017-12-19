#include "Images.h"

#include "Basket.h"
#include "GameObject.h"

Basket *basket;

int timeLimit = 115;
int timeBuffer = 0;

int availableItem = 8;
GameObject *gameObject[8];
int itemBuffer = 12;

int score = 0;

void PreGame(GameState *gameState) {
  timeLimit = 115;
  timeBuffer = 0;

  availableItem = 8;
  itemBuffer = 12;

  score = 0;
  
  delete basket;
  basket = new Basket(&arduboy);

  for (int i = 0; i < 8; i++) delete gameObject[i];
  for (int i = 0; i < 8; i++) gameObject[i] = new GameObject(&arduboy);
  
  gameState->currentState = STATE_GAME_PLAYING;
}

void drawBaseLayout();
void handleTime();
void maintainItem();

void GameScene(GameState *gameState) {
  basket->Update(gameObject, &availableItem, &score, &timeLimit, gameState);

  handleTime();
  drawBaseLayout();

  for (int i = 0; i < 8; i++) gameObject[i]->Update(&availableItem);
  maintainItem();

  if (timeLimit <= 0)
    gameState->currentState = STATE_PRE_GAME_OVER;
}

void maintainItem() {
  if (--itemBuffer > 0)
    return;
  
  for (int i = 0; i < 8; i++) {
    if (!gameObject[i]->enabled && availableItem > 0) {
      gameObject[i]->Trigger(&availableItem);
      break;
    }
  }

  itemBuffer = 12;
}

void drawBaseLayout() {
  arduboy.drawBitmap(2, 3, time_image, 5, 5, WHITE);

  arduboy.drawRect(10, 2, 115, 7, WHITE);
  arduboy.fillRect(10, 2, timeLimit, 7, WHITE);
}

void handleTime() {
  if (timeBuffer >= 7) {
    timeBuffer = 0;
    timeLimit--;
  }

  timeBuffer++;
  timeLimit = max(timeLimit, 0);
}

/**
 * GAME OVER
 */

int gameOverDelay = 30;

void statePreGameOver(GameState *gameState) {
  gameOverDelay = 30;
  gameState->currentState = STATE_GAME_OVER;
}

void stateGameOver(GameState *gameState) {
  if(gameOverDelay > 0)
    arduboy.digitalWriteRGB(RGB_ON, RGB_OFF, RGB_OFF);

  arduboy.drawBitmap(0, 0, game_over_image, 128, 64, WHITE);

  int charLength = 0;
  if (score < 10) charLength += 5;
  else if (score < 100) charLength += 10;
  else if (score < 1000) charLength += 15;
  else charLength += 20;

  arduboy.setCursor(64 - charLength, 47);
  arduboy.setTextSize(2);
  arduboy.print(score);
  arduboy.setTextSize(1);
  
  if (gameOverDelay-- > 0)
    return;

  arduboy.digitalWriteRGB(RGB_OFF, RGB_OFF, RGB_OFF);
  
  if (arduboy.justPressed(A_BUTTON))
    gameState->currentState = STATE_MAIN_MENU;
}

