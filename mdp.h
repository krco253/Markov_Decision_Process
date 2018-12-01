/*===============================================
|    Markov Decision Processes: mdp.h
=================================================
| Author: 
| Purpose:
| Compile with:
===============================================*/
#include <vector>
#include <iostream> //std::cout
#include <string> 

/*----------CONSTANTS-----------*/
const float DISCOUNT = 0.96; //desired discount 
const int HORIZON = 10000; //desired horizon; set to 0 if V* is desired
const int TOTAL_STATES = 16; //number of states in the given grid

/*--------UTILITY ARRAYS-------*/
int util[TOTAL_STATES]; // array of utilities 
int util_prime[TOTAL_STATES]; // array of utilities prime

/*NOTE: The utility arrays are used to keep track of the utility values
throughout the algorithm. note that util[0] corresponds to utility
value of state 1, util[1] corresponds to utility value of state 2,etc*/

int epsilon; //max error allowed in the utility of any state

std::vector<int> REWARDS{0,0,6,80,0,2,0,5,45,12,1,0,8,0,0,4}; //rewards in the given grid

std::string direction[TOTAL_STATES]; //array of directions for policy
