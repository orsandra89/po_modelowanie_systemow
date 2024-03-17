#include <string.h>
#include <omnetpp.h>

using namespace omnetpp;

/**
 * Derive the Txc1 class from cSimpleModule. In the Tictoc1 network,
 * both the `tic' and `toc' modules are Txc1 objects, created by OMNeT++
 * at the beginning of the simulation.
 */
class Drive : public cSimpleModule
{
    private:
        cQueue messageQueue;
        simtime_t searchTime;  // Search time for the disk
            simtime_t transmissionTime;
        bool isBusy;
        virtual void processQueue();
  protected:
    // The following redefined virtual function holds the algorithm.
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

// The module class needs to be registered with OMNeT++
Define_Module(Drive);

void Drive::initialize()
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
    searchTime = 5.0;  // Search time for the disk in milliseconds
        transmissionTime = 410e-6;  // Time to transmit 4KB of data through the disk in seconds
        isBusy = false;
}

void Drive::processQueue()
{
    if (!isBusy && !messageQueue.isEmpty()) {
        // If the disk is not busy and the queue is not empty, process the next request
        cMessage *nextRequest = dynamic_cast<cMessage *>(messageQueue.pop());
        if (nextRequest) {
            EV << "Processing next request from the queue.\n";
            isBusy = true;
            simtime_t processingTime = searchTime + transmissionTime;
            scheduleAt(simTime() + processingTime, nextRequest);
        } else {
            EV << "Error: Received a non-cMessage object from the queue.\n";
        }
    }
}

void Drive::handleMessage(cMessage *msg)
{
    if (msg->isSelfMessage()) {
        // This block is executed when the received message is a self-message
        EV << "Found file! Send to cache.\n";
        isBusy = false;
        send(msg, "driveGate$o");
        processQueue();
    } else {
        // This block is executed when the received message is not a self-message
        EV << "Received message for processing: " << msg->getName() << ".\n";


        if (!isBusy) {
            // If the disk is not busy, process the request
            EV << "Processing request on the disk.\n";
            isBusy = true;
            simtime_t processingTime = searchTime + transmissionTime;
            scheduleAt(simTime() + processingTime, msg);
        } else {
            // If the disk is busy, enqueue the message
            EV << "Disk is busy. Enqueuing the request.\n";
            messageQueue.insert(msg);
        }
    }
}
