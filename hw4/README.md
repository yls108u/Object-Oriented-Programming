Input:

Number of nodes; X_max, Y_max

Nodes with non-negative coordinates (x, y) 
 (the input graph is connected after adding links)

Each node broadcasts “hello message” at different time

Each node publishes its coordination at different time 

Source-destination pairs with start time

Simulation duration



Procedure:

Add a link between any two nodes u, v if dist(u,v) ≤ 1

Send and receive hello message and add the sender to the nb list

Publish the coordination (modify the add_initial_event)

Retrieve the dst’s coordination before computing the next hop

Reply the message directly if the dead end has the information

Compute the next hop by greedy routing for each node



Output:

All packets transmitted in the network 