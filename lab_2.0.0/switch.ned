simple Switch
{
    parameters:
        int serverGates;
        int clientGates;
    gates:
        inout portToSerwer[serverGates];
        inout portToClient[clientGates];
}