#include <string.h>
#include <omnetpp.h>
#include <iostream>
#include "customMessage.cc"


using namespace omnetpp;

/**
 * Derive the Txc1 class from cSimpleModule. In the Tictoc1 network,
 * both the `tic' and `toc' modules are Txc1 objects, created by OMNeT++
 * at the beginning of the simulation.
 */
class Client : public cSimpleModule
{
  public:
        int client_id;
  protected:
    // The following redefined virtual function holds the algorithm.
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

// The module class needs to be registered with OMNeT++
Define_Module(Client);

void Client::initialize()
{
    client_id = par("client_id");
    // Initialize is called at the beginning of the simulation.
    // To bootstrap the tic-toc-tic-toc process, one of the modules needs
    // to send the first message. Let this be `tic'.

    // Am I Tic or Toc?
//    if (strcmp("tic", getName()) == 0) {
        // create and send first message on gate "out". "tictocMsg" is an
        // arbitrary string which will be the name of the message object.

       CustomMessage *myMessage = new CustomMessage("MyCustomMessage", 0, client_id);

        // Set the client_id field
//       myMessage->setClientId(client_id);
       int clientId = myMessage->getClientId();
       EV << "Client id: " << client_id << ".\n";
       scheduleAt(0.0, myMessage);
//    }
}

void Client::handleMessage(cMessage *msg)
{
    if (msg->isSelfMessage()) {
                // Handle self-message
            EV << "[Client] Send request to server: " << msg->getName() << ".\n";
            send(msg, "clientGate$o");
    //        generateRequest();
        } else {
            EV << "[Client] Received message from server: " << msg->getName() << ".\n";
            delete msg;
        }
}
