#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <Arduboy2.h>

class GameObject {
  public:
    GameObject(Arduboy2 *arduboy);
    void Update(int *availableItem);
    void Trigger(int *availableItem);
    void Catch(int *availableItem);

    bool enabled;
    int x, y;
    int itemType;

  private:
    Arduboy2 *arduboy;
};

#endif
