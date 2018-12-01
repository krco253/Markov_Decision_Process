##Markov Decision Processes 

###Structure
- Parameters can be changed in mdp.h. Most "running" source code is in main.

###To run:
- Compile with:
g++ -std=c++11 -o MDP main.cpp
	-make sure mdp.h is in the same folder
- To change the horizon:
	-go to mdp.h
	-change HORIZON constant to desired value
- To change discount:
	-go to mdp.h
	-change DISCOUNT to desired value

###Interpreting output:
- First grid is grid of utilities. 
- Second gtid is grid of policies. 

###Acknowledgements
- Implemented value iteration algorithm as described in "Artificial 
Intelligence, A Modern Approach" by Russell and Norvig.
