network Network
{
    parameters:
        int numClients;
        int numSerwers;
//        int numPorts = 2* (numClients + numSerwers);
        @display("bgb=514,379");
    submodules:
        switch: Switch{
            serverGates = parent.numSerwers;
            clientGates = parent.numClients;
        };

        client[numClients]: Client {
            xCoord = uniform(0, 100);
            yCoord = uniform(0, 100);
        }
        serwer[numSerwers]: Serwer{
            xCoord = uniform(200, 300);
            yCoord = uniform(200, 300);
        }
    connections:
        for j=0..numClients-1{
            client[j].clientsGate<--> switch.portToClient[j];
        }
        for i=0..numSerwers-1{
        	switch.portToSerwer[i] <--> serwer[i].serwersGate;
        }

}