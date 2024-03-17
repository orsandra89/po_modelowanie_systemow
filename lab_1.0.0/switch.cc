#include <string.h>
#include <omnetpp.h>
#include "customMessage.cc"

using namespace omnetpp;

/**
 * Derive the Txc1 class from cSimpleModule. In the Tictoc1 network,
 * both the `tic' and `toc' modules are Txc1 objects, created by OMNeT++
 * at the beginning of the simulation.
 */
class Switch : public cSimpleModule
{
  protected:
    // The following redefined virtual function holds the algorithm.
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

// The module class needs to be registered with OMNeT++
Define_Module(Switch);

void Switch::initialize()
{
    // Initialize is called at the beginning of the simulation.
    // To bootstrap the tic-toc-tic-toc process, one of the modules needs
    // to send the first message. Let this be `tic'.

    // Am I Tic or Toc?
//    if (strcmp("tic", getName()) == 0) {
        // create and send first message on gate "out". "tictocMsg" is an
        // arbitrary string which will be the name of the message object.
//        cMessage *msg = new cMessage("tictocMsg");
//        send(msg, "out");
//    }
}

void Switch::handleMessage(cMessage *msg){

    cGate *arrivalGate = msg->getArrivalGate();
    CustomMessage *myCustomMessage = dynamic_cast<CustomMessage *>(msg);
    if(arrivalGate){
        const char *gateName = arrivalGate->getName();
        if (strcmp(gateName, "serwer1$i") == 0) {
            int clientId = myCustomMessage->getClientId();
            EV << "Client id: " << clientId << ".\n";
            // Message received from the "inGate" gate
            if (clientId == 1){
                send(msg, "client1$o");
            } else if (clientId == 2){
                send(msg, "client2$o");
            } else{
                send(msg, "client3$o");
            }
        } else {
            // Message received from the "outGate" gate
            int clientId = myCustomMessage->getClientId();
            EV << "Client id: " << clientId << ".\n";
            send(msg, "serwer1$o");
        }

    }
}


