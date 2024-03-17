#include <omnetpp/clog.h>
#include <omnetpp/cobjectfactory.h>
#include <omnetpp/csimplemodule.h>
#include <omnetpp/regmacros.h>
#include <cstdlib>
#include <iostream>
#include <omnetpp.h>

using namespace omnetpp;

/**
 * Derive the Txc1 class from cSimpleModule. In the Tictoc1 network,
 * both the `tic' and `toc' modules are Txc1 objects, created by OMNeT++
 * at the beginning of the simulation.
 */
class Cache : public cSimpleModule
{
    private:
        double findProbability = 0.7;
        double drivePathBarier = 0.3;
        virtual void searchOnDrive(cMessage *msg);
        virtual void searchInCache(cMessage *msg);

  protected:
    // The following redefined virtual function holds the algorithm.
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

// The module class needs to be registered with OMNeT++
Define_Module(Cache);

void Cache::initialize()
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
void Cache::searchOnDrive(cMessage *msg){
    // File not found in cache/ search on drive
    double findPathToDrive = static_cast<double>(rand()) / RAND_MAX;
    EV << "number for path to drive is: " << findPathToDrive << endl;
    if (findPathToDrive < drivePathBarier) {
        // Send request to Disk 1 (30% probability)
        EV << "File not found in cache. Sending request to Disk 1.\n";
        send(msg, "cacheGateToDrive$o", 0);
    } else {
        // Send request to Disk 2 (70% probability)
        EV << "File not found in cache. Sending request to Disk 2.\n";
        send(msg, "cacheGateToDrive$o", 1);
    }
}

void Cache::searchInCache(cMessage *msg){
    double calculatedFindProbability = static_cast<double>(rand()) / RAND_MAX;
    EV << "find probability is: " << calculatedFindProbability << endl;
    if (calculatedFindProbability < findProbability) {
        // File found in cache (70% probability)
        EV << "File found in cache. Handling the request locally.\n";
        // Handle the request locally (add your logic here)
        send(msg, "cacheGateToCpu$o");
    } else {
        searchOnDrive(msg);
    }
}
void Cache::handleMessage(cMessage *msg)
{
    cGate *arrivalGate = msg->getArrivalGate();
    if(arrivalGate){
        const char *gateName = arrivalGate->getName();
        EV << "Received message from gate: " << gateName << "\n";
        if (strcmp(gateName, "cacheGateToCpu$i") == 0) {
            // Message received from the "inGate" gate
            searchInCache(msg);
        } else {
            // Message received from the "outGate" gate
            send(msg, "cacheGateToCpu$o");
        }

    } else {
        EV << "Error: Message received without an arrival gate.\n";
    }

}

