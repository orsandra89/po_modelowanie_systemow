//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
//
network Simulation
{
    @display("bgb=737,493");
    types:
        channel Channel extends ned.DelayChannel
        {
            delay = 100ms;
        }

    submodules:
        client1: Client {
            @display("p=59,38");
            client_id = 1;
        }
        client2: Client {
            @display("p=98,185");
            client_id = 2;
        }
        client3: Client {
            @display("p=59,335");
            client_id = 3;
        }
        serwer1: Serwer {
            @display("p=489,185");
        }
        switch: Switch {

            @display("p=307,185");
        }
    connections:
        client1.clientGate <--> Channel <--> switch.client1;
        client2.clientGate <--> Channel <--> switch.client2;
        client3.clientGate <--> Channel <--> switch.client3;
        switch.serwer1 <--> Channel <--> serwer1.serwer1Gate;
}
