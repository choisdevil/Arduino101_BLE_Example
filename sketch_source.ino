/*
SparkFun Inventor's Kit 
Example sketch 21

BASIC BLE CONTROL

Turn an LED on and off using BLE and either a phone or tablet. Android and iOS devices only!

Based off of the BLE LED example written by Intel Corporation and included with the Curie BLE Arduino Library.

*/

 #include <CurieBLE.h>

BLEPeripheral blePeripheral;  // BLE Peripheral Device (the board you're programming)
BLEService ledService("19B10000-E8F2-537E-4F6C-D104768A1214"); // BLE LED Service


//set BLE characteristic
       BLEUnsignedCharCharacteristic switchCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);

const int ledPin = 13; // pin to use for the LED++++++++++++++------------------------------------------------------------------------------------------------

 void setup()
{
 // set LED pin to output mode
  pinMode(ledPin, OUTPUT);

  // set advertised local name and service UUID:
  blePeripheral.setLocalName("groupF");
  blePeripheral.setAdvertisedServiceUuid(ledService.uuid());

  // add service and characteristic:
   blePeripheral.addAttribute(ledService);
   blePeripheral.addAttribute(switchCharacteristic);

   // set the initial value for the characeristic:
    switchCharacteristic.setValue(0);

   // begin advertising BLE service:
   blePeripheral.begin();
 }

void loop() 
{
  // listen for BLE peripherals to connect:
 BLECentral central = blePeripheral.central();

 // if a central is connected to peripheral:
  if (central)
  {
   // while the central is still connected to peripheral:
    while (central.connected())
    {
      // if the remote device wrote to the characteristic,
      // use the value to control the LED:
      if (switchCharacteristic.written())
      {
          // any value other than 0, turn on the LED
         if (switchCharacteristic.value()) 
         {  
         digitalWrite(ledPin, HIGH);         
         } 
      //else turn the LED off
       else 
      {                              
      digitalWrite(ledPin, LOW);         
      }
      }
     }
    }
  }
