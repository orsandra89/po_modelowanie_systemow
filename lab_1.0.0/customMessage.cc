#include <omnetpp.h>

class CustomMessage : public omnetpp::cMessage {
  private:
    int client_id;

  public:
    CustomMessage(const char *name = nullptr, int kind = 0, int clientId = 0) : cMessage(name, kind) { client_id = clientId; }

    int getClientId() const { return client_id; }
    void setClientId(int id) { client_id = id; }
};


