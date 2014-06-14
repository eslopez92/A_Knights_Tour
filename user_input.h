#ifndef user_input
#define user_input


struct USER_INPUT
{
	int first_x; //x coordinate of this move
	int first_y; //y coordinate of this move
	USER_INPUT* next_initial_condition;
	STACK* first_move;
};

#endif