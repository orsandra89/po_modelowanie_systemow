#include <string.h>
#include <omnetpp.h>

using namespace omnetpp;

/**
 * Derive the Txc1 class from cSimpleModule. In the Tictoc1 network,
 * both the `tic' and `toc' modules are Txc1 objects, created by OMNeT++
 * at the beginning of the simulation.
 */
class Client : public cSimpleModule
{
    private:
        cMessage *requestEvent;
        simtime_t interArrivalTime;
        simtime_t interArrivalTimeMean;
        double dataSizeMean;
        double dataSizeVariance;
        virtual void generateRequest();
  protected:
    // The following redefined virtual function holds the algorithm.
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

// The module class needs to be registered with OMNeT++
Define_Module(Client);

void Client::generateRequest(){
    simtime_t interArrivalTime = exponential(interArrivalTimeMean);
    scheduleAt(simTime() + interArrivalTime, new cMessage("Request"));

    // Generate data size with normal distribution
//    double dataSize = normal(dataSizeMean, sqrt(dataSizeVariance));
    double dataSize = 100;

    // Ensure the data size is not smaller than 200B
    dataSize = std::max(dataSize, 200.0);

    EV << "Generated request with data size: " << dataSize << "B\n";
}

void Client::initialize()
{
    interArrivalTime = exponential(0.2);
    dataSizeMean = 5000;
    dataSizeVariance = 333;

    generateRequest();
    // Schedule the first request
//    requestEvent = new cMessage("Request");
//    scheduleAt(simTime() + interArrivalTime, requestEvent);

    // Am I Tic or Toc?
//    if (strcmp("tic", getName()) == 0) {
        // create and send first message on gate "out". "tictocMsg" is an
        // arbitrary string which will be the name of the message object.
//       cMessage *msg = new cMessage("tictocMsg");
//       send(msg, "clientGate$o");
//       scheduleAt(0.0, msg);
//    }
}

void Client::handleMessage(cMessage *msg)
{
    // The handleMessage() method is called whenever a message arrives
    // at the module. Here, we just send it to the other module, through
    // gate `out'. Because both `tic' and `toc' does the same, the message
    // will bounce between the two.
//    send(msg, "out"); // send out the message
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
