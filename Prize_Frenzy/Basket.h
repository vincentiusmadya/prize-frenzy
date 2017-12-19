#ifndef BASKET_H
#define BASKET_H

#include <Arduboy2.h>
#include "GameObject.h"
#include "GameState.h"

class Basket {
  public:
    Basket(Arduboy2 *arduboy);

    void Update(GameObject *gameObject[], int *availableItem, int *score, int *timeLimit, GameState *gameState);

  private:
    Arduboy2 *arduboy;
    int xPosition;

    bool isCollideWith(int x, int y);
};

#endif
