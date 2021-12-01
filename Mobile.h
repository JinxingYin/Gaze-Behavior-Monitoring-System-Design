#include "systemc.h"
#include "stdio.h"
#include <fstream>
#include <iostream>


SC_MODULE(Mobile){
  
  sc_in<bool> clock;
  sc_in<bool> network_free;
  sc_in<int> m_status;
  sc_in<bool> m_response;
  sc_out<bool> m_request;          // request to access network
  sc_out<bool> m_packet;           // send packet
  int image_index = 0;              // index of each image
  int counter = 0;                 // count 1000 times to switch an image
  int x , y ,  XendIndex;
  int pre_index = -1;              // compare with current index
  int index = -1;
  int transmit_package_counter = 0; //tpc counter similar to tx_counter like a register holding the tx_counter value from prc_update
  int tx_counter = 0 ;              // count # of packet sent
  int tuple_counter = 0;            // count # of tuple
  ifstream my_file;
  bool second_time = false;
  sc_event tx_event;
  //int gamma = rand()%25;
  
  
  int table[10][18] = {{1,0,5,50,400,50,450,470,600,670,950,680,1000,0,0,0,0,1},
                       {1,0,5,20,320,370,1000,20,900,40,550,700,1000,0,0,0,0,1},
                       {2,10,4,10,150,300,980,300,980,10,950,0,0,0,0,0,0,1},
                       {2,10,4,10,700,10,250,270,700,740,1000,0,0,0,0,0,0,1},
                       {3,20,4,10,260,270,520,570,700,730,950,0,0,0,0,0,0,1},
                       {3,20,4,10,900,10,1000,20,950,10,950,0,0,0,0,0,0,1},
                       {4,30,7,10,160,170,220,230,380,390,540,550,700,710,860,870,1010,1},
                       {4,30,7,10,1000,10,1000,10,1000,10,1000,10,1000,10,1000,10,1000,1},
                       {5,40,7,10,1000,10,1000,10,1000,100,1000,10,1000,10,1000,10,1000,1},
                       {5,40,7,10,160,170,220,230,380,390,540,550,700,710,860,870,1010,1}};
  
  
  SC_CTOR(Mobile){
   my_file.open("Gaze.txt");  
  SC_METHOD(prc_update);
  sensitive << clock.pos();
  SC_THREAD(prc_tx);
  }
  
  
  void prc_update(){   
      
     // cout << "gamma is :" << gamma << endl;
      //cout << "@ here is the time " << sc_time_stamp() << " s for counter value " << counter << endl; 
      my_file >> x >> y;
      XendIndex = table[image_index][2]*2+2;
      for(int i = 3; i<= XendIndex; i+=2){
      if(x>= table[image_index][i] && x<=table[image_index][i+1] && y>= table[image_index+1][i] && y<=table[image_index+1][i+1]){
                 index = (i-1)/2;
                 break;
      }
      else
                 index = -1;
      }
      
      if(((index != pre_index) && index != -1)){
       tuple_counter ++;
       //cout << "at time: " << sc_time_stamp() << " a tuple is created " << endl;
       }
       
       if(tuple_counter == 20){
             counter ++;
             tx_counter ++;
             tuple_counter = 0;
           //  cout << " at time " << sc_time_stamp() << " a packet is created " << endl ;
       }
       else if(!second_time && table[image_index][1]==0 && counter == 1000){
          tx_counter ++;
             tuple_counter = 0;
           //  cout << " at time " << sc_time_stamp() << " a packet is created " << endl ;
             counter = 0;
             image_index +=2;
             second_time = true;
       }
       else if(second_time && table[image_index][1] ==0 && counter == 999){
                tx_counter ++;
             tuple_counter = 0;
           //  cout << " at time " << sc_time_stamp() << " a packet is created " << endl ;
             counter = 0;
             image_index +=2;
       }
       else if(table[image_index][1] != 0 && counter == 999){
         tx_counter ++;
             tuple_counter = 0;
           //  cout << " at time " << sc_time_stamp() << " a packet is created " << endl ;
             counter = 0;
             if(table[image_index][1] == 40)
             image_index = 0;
             else
             image_index +=2;
       }
       else{
       counter++;
       }
       
      
      pre_index = index;
      
      //cout << "@ " << sc_time_stamp() << "the tx_counter is " << tx_counter << endl;
       if(transmit_package_counter==0 && tx_counter != 0){
       transmit_package_counter = tx_counter;
       tx_counter = 0;
       tx_event.notify(SC_ZERO_TIME);
       }
       
       
       
       if(my_file.eof()){
       my_file.close(); 
      // cout << "@ " << sc_time_stamp() << " finish reading " << endl;
       }           
      }
  
      void prc_tx(){
      
      m_request = false;
      m_packet = false;
      
      while(true){
        wait(tx_event);
        while(transmit_package_counter>0){
        //cout << "transmit_package_counter is: " << transmit_package_counter << endl;
        if(!network_free)
        wait(rand()%10,SC_MS);
        //wait(gamma,SC_MS);
        else{
            m_request = true;
            wait(m_response.posedge_event());
           // cout << "@ " << sc_time_stamp() << " mobile is waiting! " << endl;
           
            if(m_status == 0){
            wait(rand()%10,SC_MS);
            //wait(gamma,SC_MS);
         
            }
            else{
           // cout << "@ " << sc_time_stamp() << "mobile is sending! " << endl;
            m_packet = true;
            wait(7.32422,SC_MS);   
            m_packet = false;
            transmit_package_counter --;
            //cout << "@ " << sc_time_stamp() << " still have " << transmit_package_counter << " to send" << endl;
            }
            m_request = false;
        }
        }
      }
      }
  
};



