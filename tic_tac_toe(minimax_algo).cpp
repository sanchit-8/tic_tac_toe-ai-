#include<bits/stdc++.h>
using namespace std;

#define COMPUTER 1
#define HUMAN 2
#define computer_HUMAN 2

#define SIDE 3

#define COMPUTERMOVE 'O'
#define HUMANMOVE 'X'
#define computer_HUMANMOVE 'X'

void showInstructions()
{
	printf("\t\t\t Tic-Tac-Toe\n\n");
	printf("Choose a cell numbered from 1 to 9 as below"
			" and play\n\n");

	printf("\t\t\t 1 | 2 | 3 \n");
	printf("\t\t\t-----------\n");
	printf("\t\t\t 4 | 5 | 6 \n");
	printf("\t\t\t-----------\n");
	printf("\t\t\t 7 | 8 | 9 \n\n");

	printf("-\t-\t-\t-\t-\t-\t-\t-\t-\t-\n\n");

	return;
}
void showBoard(char board[][SIDE])
{
    system("CLS");
    showInstructions();
	printf("\n\n");

	printf("\t\t\t %c | %c | %c \n", board[0][0],
							board[0][1], board[0][2]);
	printf("\t\t\t------------\n");
	printf("\t\t\t %c | %c | %c \n", board[1][0],
							board[1][1], board[1][2]);
	printf("\t\t\t------------\n");
	printf("\t\t\t %c | %c | %c \n\n", board[2][0],
							board[2][1], board[2][2]);

	return;
}

void initialise(char board[][SIDE])
{
	for (int i=0; i<SIDE; i++)
	{
		for (int j=0; j<SIDE; j++)
			board[i][j] = ' ';
	}
	return;
}

void declareWinner(int whoseTurn)
{
	if (whoseTurn == COMPUTER)
		printf("COMPUTER has won\n");
	else
		printf("HUMAN has won\n");
	return;
}
bool rowCrossed(char board[][SIDE])
{
	for (int i=0; i<SIDE; i++)
	{
		if (board[i][0] == board[i][1] &&
			board[i][1] == board[i][2] &&
			board[i][0] != ' ')
			return (true);
	}
	return(false);
}
bool columnCrossed(char board[][SIDE])
{
	for (int i=0; i<SIDE; i++)
	{
		if (board[0][i] == board[1][i] &&
			board[1][i] == board[2][i] &&
			board[0][i] != ' ')
			return (true);
	}
	return(false);
}

bool diagonalCrossed(char board[][SIDE])
{
	if (board[0][0] == board[1][1] &&
		board[1][1] == board[2][2] &&
		board[0][0] != ' ')
		return(true);

	if (board[0][2] == board[1][1] &&
		board[1][1] == board[2][0] &&
		board[0][2] != ' ')
		return(true);

	return(false);
}

bool gameOver(char board[][SIDE])
{
	return(rowCrossed(board) || columnCrossed(board)
			|| diagonalCrossed(board) );
}

int evalute(char board[][SIDE],int moveIndex,int whoseturn)
{
    if(gameOver(board) == true )
    {
        if(whoseturn==COMPUTER)
            return 10;
        else if(whoseturn==computer_HUMAN)
            return -10;
    }
    else if(moveIndex==SIDE*SIDE)
        return 0;

    if(whoseturn==COMPUTER)
    {
        whoseturn=computer_HUMAN;
    }
    else if(whoseturn==computer_HUMAN)
    {
        whoseturn=COMPUTER;
    }
    if(whoseturn==COMPUTER)     //maximize the score
    {
        int bestscore=-1000,score;
        for(int i=1;i<=SIDE*SIDE;i++)
        {
            int x=(i-1)/SIDE;
            int y=(i-1)%SIDE;
            if(board[x][y]==' ')
            {
                board[x][y]=COMPUTERMOVE;
                score=evalute(board,moveIndex+1,COMPUTER);
                bestscore= max(bestscore,score);
                board[x][y]=' ';
            }
        }
        return bestscore;
    }
    else if(whoseturn=computer_HUMAN)   //minimize the score
    {
        int bestscore=1000,score;
        for(int i=1;i<=SIDE*SIDE;i++)
        {
            int x=(i-1)/SIDE;
            int y=(i-1)%SIDE;
            if(board[x][y]==' ')
            {
                board[x][y]=computer_HUMANMOVE;
                score=evalute(board,moveIndex+1,computer_HUMAN);
                bestscore= min(bestscore,score);
                board[x][y]=' ';
            }
        }
        return bestscore;
    }
}

int comput(char board[][SIDE],int moveIndex,int whoseturn)
{
	int bestmove=-1,bestscore=-1000,score=0;
	for(int i=1;i<=SIDE*SIDE;i++)
    {
        int x=(i-1)/SIDE;
        int y=(i-1)%SIDE;
        if(board[x][y]==' ')
        {
            board[x][y]=COMPUTERMOVE;
            score=evalute(board,moveIndex+1,whoseturn);
            cout<<score;
            if(score>bestscore)
            {
                cout<<"hello";
                bestmove=i;
                bestscore=score;
            }
            board[x][y]=' ';
        }
    }
    return (bestmove);
}


void playTicTacToe(int whoseTurn)
{

	char board[SIDE][SIDE];
	initialise(board);
	showInstructions();

	int moveIndex = 0, x, y;
	while (gameOver(board) == false && moveIndex != SIDE*SIDE)
	{
		if (whoseTurn == COMPUTER)
		{
		    int moves;
		    moves=comput(board,moveIndex,COMPUTER);
		   // cout<<"enter your choice";
		   // cin>>moves;
			x = (moves-1) / SIDE;
			y = (moves-1) % SIDE;
			board[x][y] = COMPUTERMOVE;

			showBoard(board);
			printf("COMPUTER has put a %c in cell %d\n",
					COMPUTERMOVE, moves);
			moveIndex ++;
			whoseTurn = HUMAN;
		}

		else if (whoseTurn == HUMAN)
		{
            int moves;
            while(true)
            {
                cout<<"Enter your choice";
                cin>>moves;
                x = (moves-1) / SIDE;
                y = (moves-1) % SIDE;
                if(board[x][y]==' ')
                {
                    break;
                }
                cout<<"Wrong Input  ";
            }
			board[x][y] = HUMANMOVE;
			showBoard(board);
			printf ("HUMAN has put a %c in cell %d\n",HUMANMOVE, moves);
			moveIndex ++;
			whoseTurn = COMPUTER;
		}
	}

	if (gameOver(board) == false &&
			moveIndex == SIDE * SIDE)
		printf("It's a draw\n");
	else
	{
		if (whoseTurn == COMPUTER)
			whoseTurn = HUMAN;
		else if (whoseTurn == HUMAN)
			whoseTurn = COMPUTER;

		declareWinner(whoseTurn);
	}
	return;
}

int main()
{
	playTicTacToe(HUMAN);

	return (0);
}
