#include "MaskController.h"
#include "crypto.h"


MaskController::MaskController(AesEcb* aes, MaskConnector* mask)
{
  this->aes = aes;
  this->mask = mask;
  encryptSelectImageCommands();
}

void MaskController::encryptSelectImageCommands()
{
  Serial.println("Creating encrypted image selection commands...");
  for (int i = 0; i < 20; ++i) {
    uint8_t rawData[16] = {0x06, 'P', 'L', 'A', 'Y', 0x01, static_cast<uint8_t>(i + 1), 0x3B, 0x97, 0xF2, 0xF3, 0x55, 0xA9, 0x72, 0x13, 0x8B};
    std::vector<uint8_t> encryptedImg(16);
    aes->encrypt(rawData, encryptedImg.data());
    selectImageCmds.push_back(encryptedImg);
  }
  Serial.println("Encrypted image selection commands created.");
}

void MaskController::showImage(int id)
{
    if (id < 1 || id > 20) {
        throw "Invalid image id.";
    }

  
    mask->sendCommand(selectImageCmds[id - 1]);
}

// void MaskController::initMaskService()
// {
//   if (client == nullptr) 
//     client = NimBLEDevice::createClient();

//   Serial.println("Hledám BLE zařízení...");
//   NimBLEScanResults results = NimBLEDevice::getScan()->start(5);

//   if(results.getCount() == 0) {
//     Serial.println("Nepodařilo se nalézt žádné BLE zařízení.");
//     return;
//   }

//   for (int i = 0; i < results.getCount(); i++) {
//     NimBLEAdvertisedDevice advertisedDevice = results.getDevice(i);
//     if (advertisedDevice.getName() == "MASK-1E7B54"){
//       Serial.println("Nalezeno zařízení s požadovanou službou, pokus o připojení...");
//       client->connect(&advertisedDevice);

//       if (client->isConnected()) {
//         Serial.println("Připojeno k BLE zařízení.");
//         NimBLERemoteService* pRemoteService = client->getService(NimBLEUUID("0000fff0-0000-1000-8000-00805f9b34fb"));

//         if (pRemoteService != nullptr) {
//             NimBLERemoteCharacteristic* pRemoteCharacteristic = pRemoteService->getCharacteristic(NimBLEUUID("d44bc439-abfd-45a2-b575-925416129600"));

//             if (pRemoteCharacteristic != nullptr) {
//                 Serial.println("Nalezena požadovaná charakteristika.");
       
//                 for (size_t i = 0; i < selectImageCmds.size(); ++i) {
//                     std::vector<uint8_t>& imgData = selectImageCmds[i];

//                     //print the image
//                     Serial.print("Image ");
//                     Serial.print(i + 1);
//                     Serial.print(": ");
//                     Serial.print(imgData.size());
//                     Serial.print(": ");
//                     for (size_t j = 0; j < imgData.size(); ++j) {
//                         Serial.print(imgData[j], HEX);
//                         Serial.print(" ");
//                     }
//                     bool writeStatus = pRemoteCharacteristic->writeValue(imgData.data(), imgData.size(), false); // Poslední parametr 'true' značí, že se jedná o zápis s odpovědí (Write with response)
                    
//                     if (writeStatus) {
//                         Serial.print("Data obrázku ");
//                         Serial.print(i + 1);
//                         Serial.println(" úspěšně zapsána do charakteristiky.");
//                     } else {
//                         Serial.print("Nepodařilo se zapsat data obrázku ");
//                         Serial.print(i + 1);
//                         Serial.println(" do charakteristiky.");
//                     }

//                     delay(1000); // Jednosekundové zpoždění před zápisem dalšího obrázku
//                 }
//             } else {
//                 Serial.println("Požadovaná charakteristika není dostupná.");
//             }
//         } else {
//             Serial.println("Požadovaná služba není dostupná.");
//         }

//         return; // Přerušení cyklu po úspěšném připojení a nalezení služby a charakteristiky
//       } 
//       else 
//       {
//         Serial.println("Nepodařilo se připojit k BLE zařízení.");
//       }
//     }
//   }

// }