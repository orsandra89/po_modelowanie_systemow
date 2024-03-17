network Simulation
{
    submodules:
        client1: Client {
            @display("p=23,140");
        }
        serwer: Serwer {
            @display("p=102,140");
        }
    connections:
        client1.clientGate <--> serwer.serwerGate;
}
