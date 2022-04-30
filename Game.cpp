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

int main() {
	return 0;
}
