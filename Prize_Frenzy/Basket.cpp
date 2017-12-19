#include "Basket.h"
#include "Images.h"
#include "GameObject.h"
#include "GameState.h"

Basket::Basket(Arduboy2 *_arduboy) {
  arduboy = _arduboy;
  xPosition = 56;
}

bool Basket::isCollideWith(int x, int y) {
  int currentX = xPosition;
  int currentY = 52;
  int wide = 16;

  if (x < currentX - 2)
    return false;
  if (x > currentX + wide - 5)
    return false;
  if (y < currentY - 5)
    return false;
  if (y > currentY)
    return false;

  return true;
}

void Basket::Update(GameObject *gameObject[], int *availableItem, int *score, int *timeLimit, GameState *gameState) {

  if (arduboy->justPressed(LEFT_BUTTON))
    xPosition -= 8;
  if (arduboy->justPressed(RIGHT_BUTTON))
    xPosition += 8;

  xPosition = max(xPosition, 0);
  xPosition = min(xPosition, 112);

  arduboy->drawBitmap(xPosition, 52, basket_image, 16, 9, WHITE);

  for (int i = 0; i < 8; i++) {
    if (!gameObject[i]->enabled)
      continue;
    
    if (isCollideWith(gameObject[i]->x, gameObject[i]->y)) {
      if (gameObject[i]->itemType == 0)
        *score += 1;
      if (gameObject[i]->itemType == 1)
        gameState->currentState = STATE_PRE_GAME_OVER;
      if (gameObject[i]->itemType == 2) {
        *timeLimit += 7;
        *timeLimit = min(*timeLimit, 115);
      }
      gameObject[i]->Catch(availableItem);
    }
  }
}

