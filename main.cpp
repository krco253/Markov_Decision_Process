/*===============================================
|    Markov Decision Processes: main.cpp
=================================================
| Author: 
| Purpose:
| Compile with:
===============================================*/
#include "mdp.h"

/*=============================
           moving
===============================
The following functions calculate
the utility of going in any 
direction given a state_num.
This is used by max_util
-----------------------------*/

/*------------go_up-----------*/
double go_up(int state_num)
{
	int up = state_num; 
	if (state_num+1 > 4) //if you can go up without bouncing back
		up = state_num - 4; //set up to the state_num-4
	double utility = util[up];
	return utility; 
}

/*---------go_down--------------*/
double go_down(int state_num)
{
	int down = state_num;
	if(state_num+1 > 13) //if you can go down without bouncing back
		down = state_num +4; //set down to the state_num+4
	double utility = util[down];
	return utility; 
}

/*----------go_right------------*/
double go_right(int state_num)
{
	int right = state_num;
	if((state_num+1)%4 != 0) //if you can go right without hitting a wall
		right = state_num+1; //right is the state_num+1
	double utility = util[right];
	return utility; 
} 

/*------------go_left------------*/
double go_left(int state_num)
{
	int left = state_num;
	int adj_num = state_num+1; //adjust state number to correspond with num it represents on given grid
	if((adj_num != 1) && (adj_num+1 != 5) && (adj_num+1 != 9) 
	&& (adj_num+1 != 13))
		left = state_num-1;
	double utility = util[left];
	return utility; 
}

/*=============================
           max_util
===============================
calculate the max action to take
given a state number, update the
direction array appropriately,
and return value of max action
-----------------------------*/
double max_util(int state_num)
{
	//calculate the utility of going in each direction from state_num
	double right = go_right(state_num);
	double left = go_left(state_num);
	double up = go_up(state_num);
	double down = go_down(state_num);	

	//consider probabilities
	double tot_up = 0.7 * up + 0.2 * down + 0.1 * util[state_num];
	double tot_down = 0.7 * down + 0.2 * up + 0.1 * util[state_num];
	double tot_right = 0.7 * right + 0.2 * left + 0.1 * util[state_num];
	double tot_left = 0.7 * left + 0.2 * right + 0.1 * util[state_num];

	//choose the max value as the policy 
	double max = util[state_num];		
	if((tot_right >= tot_left) && (tot_right >= tot_up) && (tot_right >= tot_down))
	{
		max = tot_right;
		direction[state_num] = "right";
	}
	if((tot_left >= tot_right) && (tot_left >= tot_up) && (tot_left >= tot_down))
	{
		max = tot_left;
		direction[state_num] = "left";
	}
	if((tot_up >= tot_left) && (tot_up >= tot_right) && (tot_right >= tot_down))
	{
		max = tot_up;
		direction[state_num] = "up";
	}
	if((tot_down >= tot_left) && (tot_down >= tot_up) && (tot_right >= tot_down))
	{
		max = tot_down;
		direction[state_num] = "down";
	}
	return max;
}

/*=============================
           util_calc
===============================
calculate the utlility prime 
of state state_num and return it 
-----------------------------*/
double util_calc(int state_num)
{
	double reward = REWARDS[state_num-1]; //determine reward for just being in this state
	double util_prime_s = 0; //intialize utility prime
	if(DISCOUNT ==0) //if there is no discount
		util_prime_s = reward + max_util(state_num);
	else
		util_prime_s = reward + DISCOUNT * max_util(state_num);

	return util_prime_s;
}


/*=============================
           update_util()
===============================
sets utility values equal to 
    utility prime values
-----------------------------*/
void update_util()
{
	for(int i = 0; i < TOTAL_STATES; i++)
		util[i] = util_prime[i];
}


/*=============================
           main.cpp
===============================
implements the value iteration
algorithm and prints out grids
-----------------------------*/
int main()
{
	//initialize the utility and direction arrays
	for(int i = 0; i < TOTAL_STATES; i++)
	{
		util[i] = 0;
		direction[i] = "";
	}

	int max_change = 0; //max change in the utility of any state in an iteration

	int iter = 0; //accumulator to keep track of the loop
	while(iter < HORIZON) //while less than the horizon
	{
		update_util(); //set utility array equal to the utility prime array 
		for(int i =0; i < TOTAL_STATES; i++) //for each state in S
		{
			util_prime[i] = util_calc(i); //calculate new utility prime
		}		
	
		iter++;	//add one to the accumulator
	}


	std::cout << std::endl << "----------------Utilities--------------------------" << std::endl;
	
	//print out utility grid
	for(int i =0; i < TOTAL_STATES; i++)
	{
		std::cout << " | " << util_prime[i] << " | ";
		if((i+1)%4 == 0)
				std::cout << std::endl << "---------------------------------------------------" << std::endl;
	}

	std::cout << std::endl << "---------Policies-------------" << std::endl;

	for (int i = 0; i < TOTAL_STATES; i++)
	{
		if (direction[i] == "up")
			std::cout << " | ^ | ";
		else if (direction[i] == "left")
			std::cout << " | < | ";
		else if (direction[i] == "right")
			std::cout << " | > | ";
		else
			std::cout << " | v | ";
		if ((i+1)%4 ==0)
			std::cout << std::endl << "------------------------------" << std::endl;
	
	}

	return 0;
}
