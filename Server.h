#include "systemc.h"


SC_MODULE(Server){

sc_out<bool> network_free1, network_free2, network_free3 ;
sc_in<bool> m1_request, m2_request, m3_request;
sc_in<bool> m1_packet, m2_packet, m3_packet;
sc_out<bool> m1_response, m2_response, m3_response;
sc_out<int> m1_status, m2_status, m3_status;

 

SC_CTOR(Server){
SC_THREAD(prc_rx);
}

void prc_rx(){

network_free1 = false;
network_free2 = false;
network_free3 = false;
wait(SC_ZERO_TIME);

while(true){

network_free1 = true;
network_free2 = true;
network_free3 = true;
wait(SC_ZERO_TIME);

wait(m1_request.posedge_event() |m2_request.posedge_event() |m3_request.posedge_event());
if(m1_request){

cout << " @ " << sc_time_stamp() << " mobile 1 requests send data" << endl;
network_free1 = true;
network_free2 = false;
network_free3 = false;
m1_response = true;
m2_response = true;
m3_response = true;
m1_status = 1;
m2_status = 0;
m3_status = 0;
wait(SC_ZERO_TIME);

cout << "@ " << sc_time_stamp() << " mobile 1 starts sending data " << endl;
wait(m1_packet.posedge_event());
cout << "@  " << sc_time_stamp()  << " the mobile 1 tx_packet starts" << endl;
wait(m1_packet.negedge_event());
cout << "@  " << sc_time_stamp() << " the mobile 1 tx_packet is over" << endl;
}

else if(m2_request){
cout << " @ " << sc_time_stamp() << " mobile 2 requests send data" << endl;
network_free2 = true;
network_free1 = false;
network_free3 = false;
m2_response = true;
m1_response = true;
m3_response = true;
m2_status = 1;
m1_status = 0;
m3_status = 0;
wait(SC_ZERO_TIME);

cout << "@ " << sc_time_stamp() << " mobile 2 starts sending data " << endl;
wait(m2_packet.posedge_event());
cout << "@  " << sc_time_stamp()  << " the mobile 2 tx_packet starts" << endl;
wait(m2_packet.negedge_event());
cout << "@  " << sc_time_stamp() << " the mobile 2 tx_packet is over" << endl;

}

else if(m3_request){
cout <<  " @ " << sc_time_stamp() << " mobile 3 requests send data" << endl;
network_free3 = true;
network_free2 = false;
network_free1 = false;
m3_response = true;
m2_response = true;
m1_response = true;
m3_status = 1;
m1_status = 0;
m2_status = 0;
wait(SC_ZERO_TIME);
cout << "@ " << sc_time_stamp() << " mobile 3 starts sending data " << endl;
wait(m3_packet.posedge_event());
cout << "@  ns" << sc_time_stamp()  << " the mobile 3 packet starts" << endl;
wait(m3_packet.negedge_event());
cout << "@  ns" << sc_time_stamp() << " the mobile 3 packet is over" << endl;

}

m1_response = false;
m2_response = false;
m3_response = false;
}

}


};
