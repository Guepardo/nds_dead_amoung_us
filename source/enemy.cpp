#include <stdlib.h>
#include <time.h>

class Enemy
{
public:
  int x;
  int y;
  short screenId;
  int clock;
  int moveStep;
  int speed;
  short spriteId;

  void setY(int value)
  {
    y = value;
  };

  void setX(int value)
  {
    x = value;
  };

  void setScreenId(short value)
  {
    screenId = value;
  }

  void init(int value)
  {
    x = 32;
    y = 32;

    moveStep = 8;

    clock = 0;
    speed = 10;
  }

  void setSpriteId(int value)
  {
    spriteId = value;
  }

  void move()
  {
    clock++;

    if (clock <= speed)
    {
      return;
    }

    clock = 0;

    short number = rand() % 4 + 1;
    short offset = 16;

    switch (number)
    {
    case 1:
      x += moveStep;

      if (x > 256 - offset)
        x = 256 - offset;

      break;
    case 2:
      x -= moveStep;

      if (x < 0 + offset)
        x = 0 + offset;

      break;
    case 3:
      y -= moveStep;

      if (y < 0 + offset)
        y = 0 + offset;

      break;
    case 4:
      y += moveStep;

      if (y > 196 - offset)
        y = 196 - offset;
      break;

    default:
      break;
    }
  }
};