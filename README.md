# Gaze Behavior Monitoring System Design

Code is written in System C.


Mobile.h is the header file for the mobile device.
Server.h is the header file for the server.
Gaze.txt is the simulated gaze behavior data(region of interst).

Performed data compression and packetization in each network end with handshaking and acknowledgement. Mobile side will obtain the user gaze data, compress them into packet and waiting for the network to be free to send data to server. Server side will acknoeledge and receive new data from mobiles and give them new images for differnt gaze behavior. The target of this project was to evaluated the Trade-off of between building a centralized vs distributed system in hardware storage and bandwidth aspect.


Outcome: From analysis, the case where image counter is larger will have larger storage. If we increase the bandwidth, it can shorter the transmission time while the image storage still dominates. It’s hard to say which one is better. Yet, high bandwidth requires more storage while low bandwidth requires longer fighting time for the network.






