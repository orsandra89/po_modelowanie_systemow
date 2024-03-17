network Network
{
    parameters:
        int numClients;
        int numSerwers;
//        int numPorts = 2* (numClients + numSerwers);
        @display("bgb=514,379");
    submodules:
        switch: Switch;

        client[numClients]: Client {
            xCoord = uniform(0, 100);
            yCoord = uniform(0, 100);
        }
        serwer[numSerwers]: Serwer{
            xCoord = uniform(200, 300);
            yCoord = uniform(200, 300);
        }
    connections:
        for i=0..numClients-1 {
            switch.portToClient++ <--> client[i].clientsGate;
        }
        for i=0..numSerwers-1{
        	switch.portToSerwer++ <--> serwer[i].serwersGate;
        }
}