Input:
Number of nodes
Nodes with non-negative coordinates (x, y) 
 (the input graph is connected after adding links)
Each node broadcast “hello message” at different time 
Source-destination pairs with start time
Simulation duration



Procedure:
Add a link between any two nodes u, v if dist(u,v) ≤ 1
Receive hello message and add the sender to the nb list
Compute the next hop by greedy routing for each node



Output:
All packets transmitted in the network