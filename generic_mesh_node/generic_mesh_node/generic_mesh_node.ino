// rf22_mesh_client.pde
// -*- mode: C++ -*-
// Example sketch showing how to create a simple addressed, routed reliable messaging client
// with the RHMesh class.
// It is designed to work with the other examples rf22_mesh_server*
// Hint: you can simulate other network topologies by setting the 
// RH_TEST_NETWORK define in RHRouter.h

// Mesh has much greater memory requirements, and you may need to limit the
// max message length to prevent wierd crashes
//#define RH_MESH_MAX_MESSAGE_LEN 50

#include <SPI.h>

//Radio Head Library:
#include <RH_RF95.h> 
#include <RHMesh.h>

// In this small artifical network of 4 nodes,
#define CLIENT_ADDRESS 1
#define SERVER1_ADDRESS 2
#define SERVER2_ADDRESS 3
#define SERVER3_ADDRESS 4

// Singleton instance of the radio driver
RH_RF95 rf95(12, 6);
RHMesh manager(rf95, 2);


void setup() 
{
  SerialUSB.begin(115200);
  if (!manager.init())
    SerialUSB.println("init failed");
  // Defaults after init are 434.0MHz, 0.05MHz AFC pull-in, modulation FSK_Rb2_4Fd36
}

uint8_t data[] = "Hello World!";
// Dont put this on the stack:
uint8_t buf[RH_MESH_MAX_MESSAGE_LEN];

void loop()
{
  SerialUSB.println("Sending to manager_mesh_server3");
    
  // Send a message to a rf22_mesh_server
  // A route to the destination will be automatically discovered.
  if (manager.sendtoWait(data, sizeof(data), 1) == RH_ROUTER_ERROR_NONE)
  {
    // It has been reliably delivered to the next node.
    // Now wait for a reply from the ultimate server
    uint8_t len = sizeof(buf);
    uint8_t from;    
    if (manager.recvfromAckTimeout(buf, &len, 3000, &from))
    {
      SerialUSB.print("got reply from : 0x");
      SerialUSB.print(from, HEX);
      SerialUSB.print(": ");
      SerialUSB.println((char*)buf);
    }
    else
    {
      SerialUSB.println("No reply, is rf22_mesh_server1, rf22_mesh_server2 and rf22_mesh_server3 running?");
    }
  }
  else
     SerialUSB.println("sendtoWait failed. Are the intermediate mesh servers running?");
}

