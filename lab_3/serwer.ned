module Serwer
{
    gates:
        inout serwerGate;

    submodules:
        cpu: Cpu;
        cache: Cache {
            @display("p=378,154");
        }
        drive[2]: Drive;
        
    connections:
        serwerGate <--> cpu.cpuGate;
        cpu.cpuGateToCache <--> cache.cacheGateToCpu;
        cache.cacheGateToDrive[0] <--> drive[0].driveGate;
        cache.cacheGateToDrive[1] <--> drive[1].driveGate;
}
