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

int main() {
	return 0;
}
