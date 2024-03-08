#ifndef MASKCONNECTOR_H
#define MASKCONNECTOR_H

#include <Arduino.h>
#include <NimBLEDevice.h>

class MaskConnector
{
  public:
    MaskConnector();
    ~MaskConnector();

    bool connect();
    void disconnect();
    bool sendCommand(std::vector<uint8_t>& command);
    
    bool isConnected = false;

  private:
    const std::string maskName = "MASK-1E7B54";
    const NimBLEUUID targetServiceUUID = NimBLEUUID("0000fff0-0000-1000-8000-00805f9b34fb");
    const NimBLEUUID targetCharacteristicUUID = NimBLEUUID("d44bc439-abfd-45a2-b575-925416129600");

    NimBLEClient* connectedClient = nullptr;
    NimBLERemoteService* targetService = nullptr;
    NimBLERemoteCharacteristic* targetCharacteristic = nullptr;
};

#endif // MASKCONNECTOR_H