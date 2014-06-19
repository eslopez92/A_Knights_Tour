#include<iostream>
#include<fstream>
#include <stack>
#include <time.h>
#include "stack.h"
#include "user_input.h"



using namespace std;

//function definitions
struct STACK * Warnsdoff_method(int chessboard[8][8],struct STACK *move);
struct STACK * brute_force_method(int chessboard[8][8],struct STACK *move);
struct STACK * previous_move(int chessboard[8][8],struct STACK *move);
void printboard(int chessboard[8][8]);
void displayList(struct STACK *pHead);
int num_of_choices(int chessboard[][8], struct STACK *head);//counts the number of choices available
void clearscreen();
void sleep(int time);
void set_flags_false(struct STACK *pHead);

static int move_choice[8][3] = {
								{0,-2,1},//option 0
							    {1,-1,2},
							    {2,1,2},
							    {3,2,1},
							    {4,2,-1},//option 4
							    {5,1,-2},
							    {6,-1,-2},
							    {7,-2,-1},//option 7
							   };//8 possible different moves //array of possible moves
static int move_num = 0;
static int num_available_choices = 0;//counts the number of available coices
static bool back_tracked = false; //static variables


int main()
{
	char quit = 'n';
	struct USER_INPUT *first_input, *last_input;
	int starting_x,starting_y;
	int num_of_inputs=0;

	first_input = (struct USER_INPUT*) malloc(sizeof(struct USER_INPUT));

	cout<<"\t\t\t Knight's Tour"<<endl<<endl<<"Please enter all of the initial coordinates for each round."<<endl;
	last_input = first_input;//creating the tail node
	while (quit !=	'q')
	{
		
		cout<<"Please enter the coordiantes in which to place the Rook."<<endl;
		cout<<"(0-7) x = "; cin>>starting_x;
		cout<<"(0-7) y = "; cin>>starting_y;
		cout<<"To quit enter q, otherwise enter n: ";
		cin>>quit;
		num_of_inputs++;

		last_input->first_x = starting_x;
		last_input->first_y = starting_y;

		last_input ->next_initial_condition= (struct USER_INPUT*) malloc(sizeof(struct USER_INPUT));
		last_input = last_input ->next_initial_condition;

	}

for(int i_rounds = 0;i_rounds<num_of_inputs;i_rounds++)
{
	
	cout<<"\t\t\tRound "<<i_rounds + 1<<endl<<endl;
	system("pause");
	struct STACK *head, *move;
	head = (struct STACK*) malloc(sizeof(struct STACK));
	first_input->first_move=head;//points to the first move of the round
	if(head == NULL)
	{
		cout<<"Allocation error!"<<endl;
		exit(1);
	}


	int chessboard[8][8];
	int i,j;
	int next_choice = 0;//for bruteforce, means go to next choice becuase the choice now leads to a dead end
	int previous_counter = 0;

	int take_away_choice = 0;//if a place has been visited where a dead end only, then the previous move goes to the next choice without ones
	for (i=0;i<8;i++)
	{
		for(j=0;j<8;j++)
			chessboard[i][j] = 0; //initializing the 2D array
	}

	

	head -> x = 0;
	head -> y = 0;
	move = (struct STACK*) malloc(sizeof(struct STACK));
	head -> next_move = move;
		set_flags_false(move);//sets all the flags false for the game max of 64 nodes
	move -> x = first_input ->first_x;//retrieve initial coordinates
	move -> y = first_input ->first_y;

	chessboard[move -> x][move->y] = 1;//setting the first move to be 1

	cout<<"Current cordinate: ("<<move -> x<<","<<move -> y<<")"<<endl;
	cout<<"Move #: "<<move_num<<endl;
	printboard(chessboard);


	for(i=0;i<32;i++)//first 32 moves
	{		
		sleep(0);
		move = Warnsdoff_method(chessboard,move);//the next move should be returned as a structure
		move_num++;
		cout<<"Current cordinate: ("<<move -> x<<","<<move -> y<<")"<<endl;
		cout<<"Move #: "<<move_num<<endl;
		printboard(chessboard);
		//move -> choice_num = 0;
	}

	while(move_num !=63)
	{


		move = brute_force_method(chessboard,move);		
		move ->num_of_choices = num_of_choices(chessboard,move);
			

		
		if(move ->num_of_choices - move ->choice_num == 0)
		{
			/*cout<<"Current coordinate: ("<<move -> x<<","<<move -> y<<")"<<endl;
			cout<<"choice_num = "<<move->choice_num<<" num_of_choices = "<<move->num_of_choices<<"flag: "<<move ->choice_flag<<endl;
			cout<<"Move # : "<<move_num<<"FAIL"<<endl;
			printboard(chessboard);*/
			//system("pause");

			if(move ->choice_num > move ->num_of_choices)
				move ->choice_num = 0;

			move = previous_move(chessboard,head);
			move_num--;
			move ->choice_num++;//trys the next choice
			move ->choice_flag = true;

			/*cout<<"Current coordinate: ("<<move -> x<<","<<move -> y<<")"<<endl;
			cout<<"choice_num = "<<move->choice_num<<" num_of_choices = "<<move->num_of_choices<<"flag: "<<move ->choice_flag<<endl;
			cout<<"Move # : "<<move_num<<"try again"<<endl;
			printboard(chessboard);*/
			//system("pause");
			
			back_tracked = true;//okay we back tracked
		}

		if(back_tracked == false)//means you havent backtracked to this particular spot
		{


			move ->choice_num = 0;
		    cout<<"Current coordinate: ("<<move -> x<<","<<move -> y<<")"<<endl;
			cout<<"Move #: "<<move_num<<" success"<<endl;
			cout<<"choice_num = "<<move->choice_num<<" num_of_choices = "<<move->num_of_choices<<"flag: "<<move ->choice_flag<<endl;
			printboard(chessboard);
			

			//system("pause");
		}
	}	
	
	cout<<endl<<endl<<endl<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!SUCCESS!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
	system("pause");

	//displayList(head);
	first_input = first_input ->next_initial_condition;//next round
	move_num = 0;
    num_available_choices = 0;//counts the number of available coices
    back_tracked = false; //static variables
			//reseting all the conditions
}
	return 0;	
}

void printboard(int chessboard[][8])
{
	int i,j;
	for (i=0;i<8;i++)
	{
		cout<<7-i<<"  |  ";

		for(j=0;j<8;j++)
		cout<<chessboard[j][7-i]<<"   ";//appears so that the origin is at the bottom
										//left side instead of top right
		
		cout<<endl<<"   |"<<endl;
	}

		cout<<"------------------------------------";
	cout<<endl<<"      ";
	for (j=0;j<8;j++)
		cout<<j<<"   ";



	clearscreen();
}

struct STACK * Warnsdoff_method(int chessboard[][8], struct STACK *move) //first 32 m
{
		

	int x_outter, x_inner;
	int y_outter, y_inner;


	int x_bound_1,x_bound_2;//to make sure x is within the bounds of the chess board
	int y_bound_1,y_bound_2;//to make sure y is within the bounds of the chess board

	int cursor_x = move->x;//cursor points where the knight is
	int cursor_y = move->y;
	int min_value = 9,min_index = -1;

	int temp_counter;//temporary counter for the loop
	
											//for every possible different move
	


		
	for (int i = 0; i<8; i++)
	{
		x_outter = move_choice[i][1]; //x next
		y_outter = move_choice[i][2]; //y next
		temp_counter = 0;//resets the temporary counter
		

		x_bound_1 = cursor_x + x_outter;
		y_bound_1 = cursor_y + y_outter;

		if(chessboard[x_bound_1][y_bound_1] == 0
			&& chessboard[x_bound_1][y_bound_1] != 1
			&& x_bound_1 >= 0 && x_bound_1 <=7
			&& y_bound_1 >= 0 && y_bound_1 <=7)//checks to see if that spot is available
										//and does not go out of bounds
		 {
			for(int k=0;k<8;k++)
			{
				x_inner = move_choice[k][1];//x next next
				y_inner = move_choice[k][2];//y next next
				
				x_bound_2 = x_bound_1 + x_inner;
				y_bound_2 = y_bound_1 + y_inner;

				if (chessboard[x_bound_2][y_bound_2] == 0 && chessboard[x_bound_2][y_bound_2] != 1
					&& x_bound_2 >= 0 && x_bound_2 <=7
					&& y_bound_2 >= 0 && y_bound_2 <=7)
							temp_counter++;

			}

		 }

		if(temp_counter < min_value && temp_counter > 0)
		{
			min_value = temp_counter;//min value is now temp counter
			min_index = i;//min index is at i
			//cout<<"test"<<" i = "<<i;
			//cout<<", min_value = "<<min_value<<endl;
		}
	}
	if (min_index >= 0 && min_index < 8)
	{
	//cout<<"min_index = "<<min_index<<" min_value = "<<min_value<<endl;

	cursor_x = cursor_x + move_choice[min_index][1];//sets the cursor
	cursor_y = cursor_y + move_choice[min_index][2];//sets the cursor
	//cout<<"moved: x = "<<move_choice[min_index][1]<<" moved: y = "<<move_choice[min_index][2]<<endl;

	//move->next_move = (struct STACK*) malloc(sizeof(struct STACK));//allocates memory for the next move
	move -> next_move -> x = cursor_x;//records where the knight is x
	move -> next_move -> y = cursor_y;//records where the knight is y

	chessboard[cursor_x][cursor_y] += 1;//places move on chessboard
	
	return move -> next_move;
	}

	else
	{
		cout<<"!!!!!!!!!!!!!!!!!!SOMETHING WENT WRONG!!!!!!!!!!!!!!!!!!!!!"<<endl;
		return move;
	}
}

void clearscreen()
{
	for(int i= 0;i<25;i++)
		cout<<endl;
}

void sleep(int time)
{
	for(int i = 0; i<time*3.1*7530000;i++)
	{}
	
}

struct STACK * brute_force_method(int chessboard[][8], struct STACK *move) //first 32 m
{
	if (move ->num_of_choices - move ->choice_num == 0)	//makes sure that it doesnt do this whole process
		return move;

	int x_next, y_next;
	int x_bound,y_bound;//to make sure x is within the bounds of the chess board

	int cursor_x = move->x;//cursor points where the knight is
	int cursor_y = move->y;
	int index = -1;

	int temp_counter = 0;//temporary counter for the loop
											//for every possible different move
	for (int i = 0; i<8; i++)
	{
		x_next = move_choice[i][1]; //x next
		y_next = move_choice[i][2]; //y next		

		x_bound = cursor_x + x_next;
		y_bound = cursor_y + y_next;

		if(	chessboard[x_bound][y_bound] == 0 && chessboard[x_bound][y_bound] != 1
					&& x_bound >= 0 && x_bound <=7
					&& y_bound >= 0 && y_bound <=7)//checks to see if that spot is available and does not go out of bounds
		 {
			 if (temp_counter == move ->choice_num)//keeps going
			 {
				index = i;
				break;
			 }
			 else
				 temp_counter++;
		 }
		
	}

	if (index >= 0 && index < 8)
	{
		
		cursor_x = cursor_x + move_choice[index][1];//sets the cursor
		cursor_y = cursor_y + move_choice[index][2];//sets the cursor
	
		//move->next_move = (struct STACK*) malloc(sizeof(struct STACK));//allocates memory for the next move
		move -> next_move -> x = cursor_x;//records where the knight is x
		move -> next_move -> y = cursor_y;//records where the knight is y

		chessboard[cursor_x][cursor_y] += 1;//places move on chessboard

		if(chessboard[cursor_x][cursor_y] == 1)
			back_tracked = false;//means you have found a spot and can proceed;

		move_num++;//next move
		//move ->choice_num = 0;
		return move -> next_move;
		
	}

	else
	{
		cout<<"!!!!!!!!!!!!!!!!!!SOMETHING WENT WRONG!!!!!!!!!!!!!!!!!!!!!"<<endl;
		return move;
	}
}

struct STACK * previous_move( int chessboard[][8], struct STACK *head)
{
	struct STACK *pMove, *temp;
	pMove = head;
	int num_moves =move_num;//there are move_num + 2 total nodes
	while(num_moves > 0)
	{
		pMove = pMove -> next_move;	
		num_moves--;
	}

	int x = pMove -> next_move -> x;
	int y = pMove -> next_move -> y;
	//temp = pMove -> next_move;

	chessboard[x][y] --;
	//free(pMove->next_move);//deletes that move
	
	
	cout<<"Went back one move"<<endl;
	return pMove;	
}

void displayList(struct STACK *pHead)
{
	struct STACK *pMove;
	pMove = pHead;
	int num_moves =move_num + 2;//there are move_num + 2 total nodes
	while(num_moves > 0)
	{
		cout<<"x = "<<pMove -> x<<" y = "<<pMove ->y<<endl; 
		pMove = pMove -> next_move;	
		num_moves--;
	}

}

int num_of_choices(int chessboard[][8], struct STACK *head)
{
	int x_bound,y_bound;
	int choice_counter=0;
	for (int i=0;i<8;i++)
	{
		x_bound = head -> x + move_choice[i][1];
		y_bound = head -> y + move_choice[i][2];

		if(chessboard[x_bound][y_bound] == 0
			&& chessboard[x_bound][y_bound] != 1
			&& x_bound >= 0 && x_bound <=7
			&& y_bound >= 0 && y_bound <=7)//checks to see if that spot is available
										//and does not go out of bounds
		 {
			 choice_counter++;
		 }
	

	
	}
	return choice_counter;
}

void set_flags_false(struct STACK *pHead)
{
	struct STACK *pMove;
	pMove = pHead;
	int num_moves = 64;//there are move_num + 2 total nodes
	while(num_moves > 0)
	{
		pMove -> next_move = (struct STACK*) malloc(sizeof(struct STACK));//allocates memory for the next move
		pMove ->choice_flag= false;
		pMove -> choice_num = 0;
		pMove = pMove -> next_move;	

		num_moves --;
		
	}

}
