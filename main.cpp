#include "Mobile.h"
#include "Server.h"

int sc_main(int argc, char* argv[]) {

	sc_clock clk("clk", 10, SC_MS);
 

		sc_signal<int> m_status1s, m_status2s, m_status3s;

		  //Server:
		sc_signal<bool> m_request1s, m_request2s, m_request3s;
    sc_signal<bool> m_packet1s, m_packet2s, m_packet3s;						
		sc_signal<bool> m_network1s, m_network2s, m_network3s;
		sc_signal<bool> m_response1s, m_response2s, m_response3s;

	Mobile m1("m1");
	Mobile m2("m2");
	Mobile m3("m3");

	Server s1("server");


	s1.m1_request(m_request1s);
	s1.m2_request(m_request2s);
	s1.m3_request(m_request3s);
	s1.m1_status(m_status1s);
	s1.m2_status(m_status2s);
	s1.m3_status(m_status3s);
	s1.m1_packet(m_packet1s);
	s1.m2_packet(m_packet2s);
	s1.m3_packet(m_packet3s);
	s1.network_free1(m_network1s);
	s1.network_free2(m_network2s);
	s1.network_free3(m_network3s);
	s1.m1_response(m_response1s);
	s1.m2_response(m_response2s);
	s1.m3_response(m_response3s);



	m1.clock(clk);
 
	m1.network_free(m_network1s);
	m1.m_response(m_response1s);
	m1.m_status(m_status1s);
	m1.m_request(m_request1s);
	m1.m_packet(m_packet1s);

	m2.clock(clk);
 
	m2.network_free(m_network2s);
	m2.m_status(m_status2s);
	m2.m_response(m_response2s);
	m2.m_request(m_request2s);
	m2.m_packet(m_packet2s);
	
	m3.clock(clk);
 
	m3.network_free(m_network3s);
	m3.m_status(m_status3s);
	m3.m_response(m_response3s);
	m3.m_request(m_request3s);
	m3.m_packet(m_packet3s);

	sc_start(50,SC_SEC);

  return 0;
}