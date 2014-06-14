#ifndef stack
#define stack

struct STACK 
{
	int x; //x coordinate of this move
	int y; //y coordinate of this move
	int num_of_choices;
	int choice_num;
	bool choice_flag;//flags if choice has been made in the past
	STACK* next_move;
};

#endif