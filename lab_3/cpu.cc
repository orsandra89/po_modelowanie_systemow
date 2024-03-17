#include <string.h>
#include <omnetpp.h>

using namespace omnetpp;

/**
 * Derive the Txc1 class from cSimpleModule. In the Tictoc1 network,
 * both the `tic' and `toc' modules are Txc1 objects, created by OMNeT++
 * at the beginning of the simulation.
 */
class Cpu : public cSimpleModule
{
  protected:
    // The following redefined virtual function holds the algorithm.
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

// The module class needs to be registered with OMNeT++
Define_Module(Cpu);

void Cpu::initialize()
{
    // Initialize is called at the beginning of the simulation.
    // To bootstrap the tic-toc-tic-toc process, one of the modules needs
    // to send the first message. Let this be `tic'.

    // Am I Tic or Toc?
//    if (strcmp("tic", getName()) == 0) {
        // create and send first message on gate "out". "tictocMsg" is an
        // arbitrary string which will be the name of the message object.
//       cMessage *msg = new cMessage("tictocMsg");
//       send(msg, "clientGate$o");
//       scheduleAt(0.0, msg);
//    }
}

void Cpu::handleMessage(cMessage *msg)
{
    // The handleMessage() method is called whenever a message arrives
    // at the module. Here, we just send it to the other module, through
    // gate `out'. Because both `tic' and `toc' does the same, the message
    // will bounce between the two.
//    send(msg, "out"); // send out the message
//    send(msg, "clientGate$o");

    cGate *arrivalGate = msg->getArrivalGate();
    if(arrivalGate){
        const char *gateName = arrivalGate->getName();
        EV << "[Cpu] Received message from gate: " << gateName << "\n";
        if (strcmp(gateName, "cpuGate$i") == 0) {
            // Message received from the "inGate" gate
            send(msg, "cpuGateToCache$o");
        } else {
            // Message received from the "outGate" gate
            send(msg, "cpuGate$o");
        }

    } else {
        EV << "[CPU] Error: Message received without an arrival gate.\n";
    }
}
