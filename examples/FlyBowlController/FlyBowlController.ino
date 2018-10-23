#include <FlyBowlController.h>


FlyBowlController dev;

void setup()
{
  dev.setup();
  dev.startServer();
}

void loop()
{
  dev.update();
}
