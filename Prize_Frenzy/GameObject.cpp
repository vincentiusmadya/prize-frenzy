#include "GameObject.h"
#include "Images.h"

GameObject::GameObject(Arduboy2 *_arduboy) {
  arduboy = _arduboy;
  
  enabled = false;
}

void GameObject::Update(int *availableItem) {
  if (!enabled)
    return;

  y++;

  switch(itemType) {
    case (0):
      arduboy->drawBitmap(x, y, time_item, 9, 9, WHITE);
      break;
    case (1):
      arduboy->drawBitmap(x, y, bomb_item, 7, 9, WHITE);
      break;
    case (2):
      arduboy->drawBitmap(x, y, tick_item, 9, 5, WHITE);
      break;
  }

  if (y >= 64) {
    y = -8;
    enabled = false;
    *availableItem += 1;
  }
}

void GameObject::Catch(int *availableItem) {
  enabled = false;
  *availableItem += 1;
}

void GameObject::Trigger(int *availableItem) {
  enabled = true;

  int xPosition = random(1, 16) * 8;
  x = xPosition;
  y = -8;
  *availableItem -= 1;
  itemType = random(0, 3);
}

