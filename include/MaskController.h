#ifndef FACEMASK_H
#define FACEMASK_H

#include <vector>
#include "AesEcb.h"
#include "MaskConnector.h"

class MaskController
{
  public:
    MaskController(AesEcb* aes, MaskConnector* mask);
    void showImage(int id);

  private:
    std::vector<std::vector<uint8_t>> selectImageCmds;
    MaskConnector* mask = nullptr;
    AesEcb* aes = nullptr;

    void encryptSelectImageCommands();
};

#endif // FACEMASK_H