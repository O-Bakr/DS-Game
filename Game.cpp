#include <iostream>

using namespace std;
// Implementing nodes for the linked list
class node {
public:
	int data;
	class node* next;
};

// Creating pointers to save the base position which each player starts at
node* player1_base = NULL;
node* player2_base = NULL;

// Defining a class to contain all information regarding the player
class player {
public:
	int Static_Piece = 2;
	int Active_Piece = 0;
	int score1 = 0, score2 = 0;
	int pieces_won = 0;
	bool win = false;
	node* piece1 = NULL;
	node* piece2 = NULL;
};

player player1;
player player2;


// The used data staructure in our game is the circular linked list
// to implement it robustly we need to define a pointer pointing to the last node
// so that adding nodes at the end or the start would be O(1)

// 'addToEmpty' function is assigned to add a node to an empty initialized linked list
// we fill the node with '0' as a starting condition
void addToEmpty(node** last, int data = 0) {
	node *temp = new node;
	temp->data = data;
	*last = temp;
	(*last)->next = *last;
}

// 'append' funtion is used to add nodes at the end of the circular linked list
void append(node** last, int data = 0) {
	if (*last == NULL) {
		addToEmpty(last, data);
		return;
	}

	node* temp = new node;

	temp->data = data;
	temp->next = (*last)->next;
	(*last)->next = temp;
	*last = temp;
}

/*
Debugging purposes:

void traverse(node* last) {
	node* p;
	p = last->next;
	do {
		cout << p->data << " ";
		p = p->next;
	} while (p != last->next);

}
*/

// We initialize the game by first creating the playing board which consists of 52 tile
// and then pointing to the base or the starting position for each player to save it as a reference
void InitializeGame(node** last) {
	for (int i = 0; i < 52; i++) {
		append(last);
		if (i == 0)
			player1_base = *last;
		if (i == 26)
			player2_base = *last;
	}
}

// 'RollDice' function simulates throwing the dice by returning a random integer between 1 and 6
int RollDice() {
	return rand() % 6 + 1;
}
// 'Stats' function keep tracking the score of each player, thier pieces state
// and wheather any of them has won or not
// and then printing this data in a score board at the top of the game screen
void Stats() {
	// each piece will have to move 50 times to be considered a wining piece
	// so a total score of 100 would mean that both pieces have won and hence the player won
	int score1 = player1.score1 + player1.score2;
	int score2 = player2.score1 + player2.score2;

	// Condition for fixing the wining piece postion i.e. makes this piece unplayable
	if (player1.score1 >= 50) {
		player1.score1 = 50;
		if (player1.piece1 != player2.piece1 || player1.piece1 != player2.piece2)
			player1.piece1->data = 0;
		if (!player1.pieces_won)
			player1.pieces_won++;
	}

	if (player2.score1 >= 50) {
		player2.score1 = 50;
		if (player2.piece1 != player1.piece1 || player2.piece1 != player1.piece2)
		player2.piece1->data = 0;
		if (!player2.pieces_won)
			player2.pieces_won++;
	}

	// Setting the wining condition if there is a piece that already won and the other piece passed 50 tiles
	// i.e. a total score of 100 then set the player to won
	if (player1.pieces_won && player1.score2 >= 50)
		player1.win = true;
	if (player2.pieces_won && player2.score2 >= 50)
		player2.win = true;

	cout << "==================================================================\n";
	cout << "||\tPlayer1 Score: " << score1 << "\t\tPlayer2 Score: " << score2 << "\t||\n";
	cout << "||\tActive Pieces: " << player1.Active_Piece << "\t\tActive Pieces: " << player2.Active_Piece << "\t||\n";
	cout << "||\tPieces in Base: " << player1.Static_Piece << "\t\tPieces in Base: " << player2.Static_Piece << "\t||\n";
	cout << "||\tPieces Won: " << player1.pieces_won << "\t\t\tPieces Won: " << player2.pieces_won << "\t\t||\n";
	cout << "==================================================================\n";
}

// This function takes a pointer to a node and moves it by 'n' nodes
// this function is for a very specifc purpose regarding printing the playing board
void move(node** p, int n) {
	for (int i = 0; i < n; i++)
		*p = (*p)->next;
}

// This function is designed to print the playing board by visiting each node and printing the data inside it
// following the printing mechanism for any programming language (left to right then top to bottom)
void Board(node* last) {
	// to scan the playing board and print it properly we to need to keep track of a pointer and we need to be able
	// to easily move the pointer around the list

	node* p;
	p = last;

	// Player 2 will appear on the top of the board so we need to print their part first
	// and since the pointer 'last' now points to one node behind player 1 base we will move
	// a pointer 24 nodes to reach the first node to be printed

	/* first node to -> 0 0 0
		be printed		0	0 <- player 2 base
						0	0
						0	0
						0	0
					    0	0
			0 0 0 0 0 0		  0 0 0 0 0 0
			0							0
			0 0 0 0 0 0		  0 0 0 0 0 0
						0	0
						0	0
						0	0
						0	0
	  player 1 base  -> 0	0
				last -> 0 0 0
	*/


	// Top vertical part
	move(&p, 24);

	cout << "\n\n\t\t            ";
	for (int i = 0; i < 3; i++) {
		cout << p->data << " ";
		p = p->next;
	}
	cout << endl;
	cout << "\t\t            ";
	move(&p, 48); cout << p->data << "   "; move(&p, 4); cout << p->data << endl;
	cout << "\t\t            ";
	move(&p, 47); cout << p->data << "   "; move(&p, 6); cout << p->data << endl;
	cout << "\t\t            ";
	move(&p, 45); cout << p->data << "   "; move(&p, 8); cout << p->data << endl;
	cout << "\t\t            ";
	move(&p, 43); cout << p->data << "   "; move(&p, 10); cout << p->data << endl;
	cout << "\t\t            ";
	move(&p, 41); cout << p->data << "   "; move(&p, 12); cout << p->data << "\n\t\t";

	// Left horizontal part
	move(&p, 34);
	for (int i = 0; i < 6; i++) {
		cout << p->data << " ";
		p = p->next;
	}
	cout << "      "; move(&p, 13);

	// Right horizontal part
	for (int i = 0; i < 6; i++) {
		cout << p->data << " ";
		p = p->next;
	}
	move(&p, 26); cout << "\n\t\t" << p->data << "                           "; move(&p, 26); cout << p->data << "\n\t\t";
	move(&p, 25);
	for (int i = 0; i < 6; i++) {
		cout << p->data << " ";
		move(&p, 51);
	}
	cout << "      "; move(&p, 39);
	for (int i = 0; i < 6; i++) {
		cout << p->data << " ";
		move(&p, 51);
	}

	// Bottom vertical part
	cout << "\n\t\t            ";
	move(&p, 19); cout << p->data << "   "; move(&p, 40); cout << p->data << endl;
	cout << "\t\t            ";
	move(&p, 11); cout << p->data << "   "; move(&p, 42); cout << p->data << endl;
	cout << "\t\t            ";
	move(&p, 9); cout << p->data << "   "; move(&p, 44); cout << p->data << endl;
	cout << "\t\t            ";
	move(&p, 7); cout << p->data << "   "; move(&p, 46); cout << p->data << endl;
	cout << "\t\t            ";
	move(&p, 5); cout << p->data << "   "; move(&p, 48); cout << p->data << endl;
	cout << "\t\t            ";
	move(&p, 3);
	for (int i = 0; i < 3; i++) {
		cout << p->data << " ";
		move(&p, 51);
	}
	cout << endl;
}

// The function that keeps the game running and keeps switching turns between players
void Start(node** last) {
	// variable 'turns' to keep track whose turn is this
	// if even then player 1 turn, if odd then player 2 turn
	int turns = 0;
	while (!(player1.win || player2.win)) {
	start:
		system("pause");
		system("cls");
		int dice = RollDice();
		// Player1 turn
		if (turns % 2 == 0) {
			Stats();
			Board(*last);
			cout << "\n\tPlayer 1 turn!.\n\tDice: " << dice << endl;
			// Checking if we got 6 and if we got any pieces in base
			if (dice == 6 && player1.Static_Piece) {
				// If there is 2 pieces in base get out one without asking the player (only valid play)
				if (player1.Static_Piece == 2) {
					player1.Static_Piece--; player1.Active_Piece++;
					player1.piece1 = player1_base;
					player1.piece1->data = 1;
				}
				// If code excution reached this line it means that we got 1 active piece and a piece in base
				// so we ask the player what to do in this situation
				else {
					int choice;
					cout << "If you want to move the active piece enter 1.\n";
					cout << "If you want to activate a static piece enter 2.\n";
					cin >> choice;
					if (choice == 1) {
						// if player chooses to move the active piece then we move the piece pointer 'dice' times
						// moving mechanism is we set pointer data to 0 before moving then we move the pointer to
						// the desired tile then write 1 down
						player1.score1 += dice;
						player1.piece1->data = 0;
						move(&player1.piece1, dice);
						player1.piece1->data = 1;

						// after moving the piece if it landed on a piece from player2
						// if this piece isn't in wining position then return it back to its base
						if (player1.piece1 == player2.piece1 && player2.score1 != 50) {
							// to avoid any undesired errors and to keep the code simple
							// we will always keep 'player2.piece1' active (if player2 got any active pieces)

							// if player2 got a piece in base then it means the only active piece is piece1
							//  and then we can return it to its base easily
							if (player2.Static_Piece) {
								player2.score1 = 0;
								player2.piece1 = NULL;
								player2.Active_Piece--; player2.Static_Piece++;
							}
							// else player2 got 2 active pieces so we will do a simple handover by
							// switching piece1 position to piece2 position then return piece2 to base
							// (keeping piece1 the only active piece)
							else {
								player2.score1 = player1.score2;
								player2.score2 = 0;
								player2.piece1 = player2.piece2;
								player2.piece2 = NULL;
								player2.Active_Piece--; player2.Static_Piece++;
							}
						}
						// if that piece was piece2 then we will simply return it back to base
						// because piece2 will never be active if piece1 wasn't active
						if (player1.piece1 == player2.piece2) {
							player2.score2 = 0;
							player2.piece2 = NULL;
							player2.Active_Piece--; player2.Static_Piece++;
						}
					}
					// player chooses to get the other piece out of the base
					else if (choice == 2) {
						player1.Static_Piece--; player1.Active_Piece++;
						// if the piece in base is piece2
						if (!player1.piece2) {
							player1.piece2 = player1_base;
							player1.piece2->data = 1;
						}
						// if the piece in base is piece1
						else {
							player1.piece1 = player1_base;
							player1.piece1->data = 1;
						}
					}
				}
				// we return back to start without increamting turns because player1 got 6 so must play again
				goto start;
			}
			// Check if we got any active (playable) piece
			else if (player1.Active_Piece) {
				// if that piece is piece1 and piece2 is in base, move piece 1 automatically without asking player
				if (player1.piece1 && player1.score1 < 50 && !player1.piece2)
					goto move1;
				// if piece1 either not active or in wining position move piece2 (if active) without asking
				if ((player1.score1 >= 50 || !player1.piece1) && player1.piece2)
					goto move2;
				// if only one piece is active (piece1) and in wining position then do nothing
				if (player1.Active_Piece == 1 && player1.score1 >= 50)
					goto skip;
				int choice;
				cout << "If you want to move piece 1 enter 1\n";
				cout << "If you want to move piece 2 enter 2\n";
				cin >> choice;
				if (choice == 1) {
				move1:
					player1.score1 += dice;
					player1.piece1->data = 0;
					move(&player1.piece1, dice);
					player1.piece1->data = 1;

					if (player1.piece1 == player2.piece1 && player2.score1 != 50) {
						if (player2.Static_Piece) {
							player2.score1 = 0;
							player2.piece1 = NULL;
							player2.Active_Piece--; player2.Static_Piece++;
						}
						else {
							player2.score1 = player2.score2;
							player2.score2 = 0;
							player2.piece1 = player2.piece2;
							player2.piece2 = NULL;
							player2.Active_Piece--; player2.Static_Piece++;
						}
					}
					if (player1.piece1 == player2.piece2) {
						player2.score2 = 0;
						player2.piece2 = NULL;
						player2.Active_Piece--; player2.Static_Piece++;
					}
				}
				else if (choice == 2) {
				move2:
					player1.score2 += dice;
					player1.piece2->data = 0;
					move(&player1.piece2, dice);
					player1.piece2->data = 1;

					if (player1.piece2 == player2.piece1 && player2.score1 != 50) {
						if (player2.Static_Piece) {
							player2.score1 = 0;
							player2.piece1 = NULL;
							player2.Active_Piece--; player2.Static_Piece++;
						}
						else {
							player2.score1 = player2.score2;
							player2.score2 = 0;
							player2.piece1 = player2.piece2;
							player2.piece2 = NULL;
							player2.Active_Piece--; player2.Static_Piece++;
						}
					}
					if (player1.piece2 == player2.piece2) {
						player2.score2 = 0;
						player2.piece2 = NULL;
						player2.Active_Piece--; player2.Static_Piece++;
					}
				}
				// if the last dice throw got then player1 play again
				if (dice == 6)
					goto start;
			}
		}
		// Player2 turn
		else {
			Stats();
			Board(*last);
			cout << "\n\tPlayer 2 turn!.\n\tDice: " << dice << endl;
			// Player2 will be the Bot we play against
			// Moving mechanism will be the same as player1
			// and we made a simple playing technique for the Bot
			//		1- Bot will always favour getting a piece out of their base than moving the current active piece
			//		2- If the difference between the two pieces is more than 6 tiles then the Bot will move the piece behind

			if (dice == 6 && player2.Static_Piece) {
				// Getting a piece out of the base
				if (player2.Static_Piece == 2) {
					player2.piece1 = player2_base;
					player2.piece1->data = 2;
				}
				// if there is only one piece in the base get out
				else {
					player2.piece2 = player2_base;
					player2.piece2->data = 2;
				}
				player2.Static_Piece--; player2.Active_Piece++;
				// player get another turn
				goto start;
			}
			else if (player2.Active_Piece) {
				// Check if both pieces active and tile difference between them is 6 or less
				// and piece1 not in wining position then move piece1
				if ((player2.score1 - player2.score2 <= 6 || !player2.piece2) && player2.score1 < 50) {
					player2.score1 += dice;
					player2.piece1->data = 0;
					move(&player2.piece1, dice);
					player2.piece1->data = 2;

					//if landed on player1 piece return it to its base (if not in wining position)
					if (player2.piece1 == player1.piece1 && player1.score1 != 50) {
						player1.score1 = 0; player1.piece1 = NULL;
						player1.Active_Piece--; player1.Static_Piece++;
					}
					if (player2.piece1 == player1.piece2) {
						player1.score2 = 0; player1.piece2 = NULL;
						player1.Active_Piece--; player1.Static_Piece++;
					}
				}
				else if (!player2.Static_Piece) {
					player2.score2 += dice;
					player2.piece2->data = 0;
					move(&player2.piece2, dice);
					player2.piece2->data = 2;

					if (player2.piece2 == player1.piece1 && player1.score1 != 50) {
						player1.score1 = 0; player1.piece1 = NULL;
						player1.Active_Piece--; player1.Static_Piece++;
					}
					if (player2.piece2 == player1.piece2) {
						player1.score2 = 0; player1.piece2 = NULL;
						player1.Active_Piece--; player1.Static_Piece++;
					}
				}
				if (dice == 6)
					goto start;
			}
		}
	skip:
		turns++;
	}
}

// Display game instructions
void Instructions() {
	cout << "\n\n\n\t\t\t\t\tWelcome to Ludo Game\n\n\n";
	cout << "\t\tThis ludo game consists of 2 players each player got 2 pieces in base\n";
	cout << "\n\t\tEach player will throw the dice if it landed on 6 the player";
	cout << "\n\t\twill be able to get a piece out of his base and will throw the dice once more\n";
	cout << "\n\t\tIf a player piece landed on the other player piece it will return to its base\n";
	cout << "\n\t\tThe objective is to get out all pieces and make them reach the end of the board\n\n";

}

int main() {
	// This function is for choosing a random seed based on the current time of code execution
	// hence the 'rand' function can return actual random value every different game
	srand(time(0));

	// Initializing the board
	node* last = NULL;
	InitializeGame(&last);

	// Print game instructions
	Instructions();

	// Starting the game
	Start(&last);
	
	// If code execution reached this line that means a player must have won so we check which player won
	if (player1.win)
		cout << "\n\tPLAYER 1 WON CONGRATS!!!\n";
	else
		cout << "\n\tPLAYER 2 WON CONGRATS!!!\n";

	return 0;
}
