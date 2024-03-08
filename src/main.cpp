#include <Arduino.h>
#include "MaskController.h"
#include "MaskConnector.h"
#include "AesEcb.h"


byte keys[16] = {0x32, 0x67, 0x2f, 0x79, 0x74, 0xad, 0x43, 0x45, 0x1d, 0x9c, 0x6c, 0x89, 0x4a, 0x0e, 0x87, 0x64};

MaskConnector* maskConnector;
AesEcb* aes;
MaskController* maskController;

void setup() {
  Serial.begin(115200);

  maskConnector = new MaskConnector();
  if(!maskConnector->connect())
  {
    ESP.restart();
  }

  aes = new AesEcb(keys, 16);
  maskController = new MaskController(aes, maskConnector);
}


void loop() {
  maskController->showImage(1);
  delay(1000);
  maskController->showImage(2);
  delay(1000);
}
