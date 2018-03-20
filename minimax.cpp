#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;

void printboard(int board[3][3]) {
	cout << endl;
	for(int i=0;i<3;i++) {
		for(int j=0;j<3;j++) {
			if(board[i][j]==1) cout << "O ";
			else if(board[i][j]==2) cout << "X ";
			else cout << "_ ";
		}
		cout << endl;
	}
}

void printInstructions() {
	cout << "Instructions: Enter the number written on the cell to put a cross there. The AI is circles." << endl << endl;
	for(int i=0;i<3;i++) {
		for(int j=0;j<3;j++) {
			cout << i*3 + j + 1<< " ";
		}
		cout << endl;
	}
}

bool wins(int board[3][3], int p) {
	if(board[0][0]==p) {
		if(board[0][1]==p && board[0][2]==p) return true;
		else if(board[1][0]==p && board[2][0]==p) return true;
		else if(board[1][1]==p && board[2][2]==p) return true;
	}
	else if(board[0][2]==p) {
		if(board[1][1]==p && board[2][0]==p) return true;
		else if(board[1][2]==p && board[2][2]==p) return true;
	}
	else if(board[1][1]==p) {
		if(board[1][0]==p && board[1][2]==p) return true;
		else if(board[0][1]==p && board[2][1]==p) return true;
	}
	else if(board[2][0]==p && board[2][1]==p && board[2][2]==p) return true;
	return false;
}

bool movesLeft(int board[3][3]) {
	for(int i=0;i<3;i++) {
		for(int j=0;j<3;j++) {
			if(board[i][j]==0) return true;
		}
	}
	return false;
}
int iter=0;
int minimax(int board[3][3], bool isP) {
	if(wins(board, 1)) {
		return 10;
	}
	else if(wins(board, 2)) {
		return -10;
	}
	else if(!movesLeft(board)) {
		return 0;
	}
	if(isP){
		int bestVal = INT_MIN;
		for(int i=0;i<3;i++) {
			for(int j=0;j<3;j++) {
				if(board[i][j]==0) {
					board[i][j] = 1;
					int curVal = minimax(board, false);
					bestVal = max(bestVal, curVal);
					board[i][j] = 0;
				}
			}
		}
		return bestVal;
	}
	else if(!isP) {
		int bestVal = INT_MAX;
		for(int i=0;i<3;i++) {
			for(int j=0;j<3;j++) {
				if(board[i][j]==0) {
					board[i][j] = 2;
					int curVal = minimax(board, true);
					bestVal = min(bestVal, curVal);
					board[i][j] = 0;
				}
			}
		}
		//if(bestVal==10) printf("%d\n", iter++);
		return bestVal;
	}
}

struct move{
	int row, col;
};

struct move bestMove(int board[3][3]) {
	int bestVal = INT_MIN;
	struct move bestMove;
	bestMove.row = -1;
	bestMove.col = -1;
	for(int i=0;i<3;i++) {
		for(int j=0;j<3;j++) {
			if(board[i][j]==0) {
				board[i][j] = 1;
				int val = minimax(board, false);
				//if(val == 10) printf("asche to\n");
				board[i][j] = 0;
				if(val>bestVal) {
					//printf("%d %d is a good move %d\n", i, j, val);
					bestMove.row = i;
					bestMove.col = j;
					bestVal = val;
				}
			}
		}
	}
	return bestMove;
}

void loadingAnimation() {
	cout << "Thinking:  " << flush;
	sleep(1);
    cout << "\b\\" << flush;
    sleep(1);
    cout << "\b|" << flush;
    sleep(1);
    cout << "\b/" << flush;
    sleep(1);
    cout << "\b-" << flush;
    sleep(1);
    cout << "\b\b\b\b\b\b\b\b\b\b\b           " << flush;
    
    
}

int main() {
	int board[3][3] = {{0,0,0},{0,0,0},{0,0,0}};
	printInstructions();
	printf("\nDo you want to go first? (y/n) ");
	char choice;
	scanf("%c", &choice);
	if(choice == 'y') {
		printf("\nYour turn: ");
		int r=0,c=0, inp;
		scanf("%d", &inp);
		r = (inp-1)/3;
		c = (inp-1)%3;
		while(board[r][c]!=0 || inp < 1 || inp > 9) {
			printf("\nThat's not a valid move, try again: ");
			scanf("%d", &inp);
			r = (inp-1)/3;
			c = (inp-1)%3;
		}
		board[r][c]=2;
		printboard(board);
		
	}
	while(movesLeft(board)) {
		printf("\nAI's turn: \n");
		loadingAnimation();
        
        struct move nextMove = bestMove(board);
		board[nextMove.row][nextMove.col]=1;
		printboard(board);
		if(wins(board, 1)) {
			printf("\nAI Wins\n");
			break;
		}
		else if(!movesLeft(board)) {
			printf("\nIt's a draw!\n");
			break;
		}
		printf("\nYour turn: "); 
		int r=0,c=0, inp;
		scanf("%d", &inp);
		r = (inp-1)/3;
		c = (inp-1)%3;
		while(board[r][c]!=0 || inp < 1 || inp > 9) {
			printf("\nThat's not a valid move, try again: ");
			scanf("%d", &inp);
			r = (inp-1)/3;
			c = (inp-1)%3;
		}
		board[r][c]=2;
		printboard(board);
		if(wins(board, 2)) {
			printf("\nYou win\n");
			break;
		}
		else if(!movesLeft(board)) {
			printf("\nIt's a draw!\n");
			break;
		}
	}
	return 0;
}