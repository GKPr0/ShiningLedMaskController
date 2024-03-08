#include "MaskConnector.h"

MaskConnector::MaskConnector()
{
    NimBLEDevice::init("");
}

bool MaskConnector::connect()
{
  if (connectedClient == nullptr) {
    connectedClient = NimBLEDevice::createClient();
  }

  Serial.println("Looking for bluetooth devices...");
  NimBLEScanResults results = NimBLEDevice::getScan()->start(5);

  if(results.getCount() == 0) {
    Serial.println("Failed to find any BLE devices.");
    return false;
  }

  NimBLEAdvertisedDevice* mask;
  for (int i = 0; i < results.getCount(); i++) {
    NimBLEAdvertisedDevice advertisedDevice = results.getDevice(i);
    if (advertisedDevice.getName() == maskName)
    {
      mask = &advertisedDevice;
      break;
    }
  }

  if (mask == nullptr) {
    Serial.println("Failed to find the mask.");
    return false;
  }

  connectedClient->connect(mask);
  if (!connectedClient->isConnected()) 
  {
    Serial.println("Failed to connect to the mask.");
    return false;
  }

  Serial.println("Connected to the mask.");
  isConnected = true;

  targetService = connectedClient->getService(targetServiceUUID);
  if(targetService == nullptr) 
  {
    Serial.println("Failed to find the target service");
    return false;
  }
  
  targetCharacteristic = targetService->getCharacteristic(targetCharacteristicUUID);
  if(targetCharacteristic == nullptr) 
  {
    Serial.println("Failed to find the target characteristic");
    return false;
  }

  Serial.println("Successfully connected to the mask.");
  return true;
}

void MaskConnector::disconnect()
{
  if (connectedClient != nullptr) {
    NimBLEDevice::deleteClient(connectedClient);
    isConnected = false;
  }
}

bool MaskConnector::sendCommand(std::vector<uint8_t>& command)
{
  if (!isConnected)
  {
    Serial.println("Failed to send command, not connected to the mask.");
    return false;
  }
  
  if(targetCharacteristic == nullptr) 
  {
    Serial.println("Failed to send command, target characteristic is null.");
    return false;
  }

  // print the image
  Serial.print("Command: ");
  Serial.print(command.size());
  Serial.print(": ");
  for (size_t j = 0; j < command.size(); ++j) {
      Serial.print(command[j], HEX);
      Serial.print(" ");
  }
  Serial.println();

  targetCharacteristic->writeValue(command.data(), command.size(), false);
  return true;
}

MaskConnector::~MaskConnector()
{
    disconnect();
}