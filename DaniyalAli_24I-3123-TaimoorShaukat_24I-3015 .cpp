#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <conio.h>
#include <fstream>
using namespace std;
// DANIYAL ALI STUDENT 1 24I-3123 BSE-1B, TAIMOOR SHAUKAT STUDENT 2 24I-3015 BSE-1B, PROJECT
// Constants our uno gqme
const int NUM_COLORS = 4; // Red, Blue, Green, Yellow
const int NUM_CARDS_PER_COLOR = 15; // Includes number and action cards
const int TOTAL_CARDS = 108; // Total cards in UNO deck
int HAND_SIZE = 7; // Initial hand size
int size = HAND_SIZE;
// Global variables
int gameDirection = 1;
int nextPlayer = -1;
int currentPlayer = 1;
int deck[NUM_COLORS][NUM_CARDS_PER_COLOR];
int discardSize = 0;
int player1[TOTAL_CARDS] = {0};
int player2[TOTAL_CARDS] = {0};
static string moves;
static int P1SCORE = 0;
static int P2SCORE = 0;

int randomIndex;
int randomNumber;
int randValue;
int topColor;
int player1Color;
int player2Color;


int player1Colors[TOTAL_CARDS];  
int player2Colors[TOTAL_CARDS];  
int p1totalcolor;
int p2totalcolor;
int topCard = deck[0][0];

// Function prototypes
void handleSpecialCard(int specialCardType);
void UpdateDiscardPile(int playerHand[],int &topCard,int discardPile[],int choice,int &discardSize,int playercolor);
void setColor(int textColor, int bgColor);
void clearScreen();
void initializeDeck(int deck[][NUM_CARDS_PER_COLOR]);
void shuffleDeck(int deck[][NUM_CARDS_PER_COLOR]);
void dealCards(int deck[][NUM_CARDS_PER_COLOR], int player1[], int player2[]);
bool isValidPlay(int playerCard, int topCard);
void printBoard(int topCard, int player1[], int player2[], int player1Colors[], int player2Colors[], int player1Size, int player2Size);
bool checkWinner(int playerHand[], int handSize);
void playTurn(int ptotalcolor,int deck[][NUM_CARDS_PER_COLOR], int playerHand[], int &handSize, int &topCard, int discardPile[], int &discardSize,int &currentplayer,int &nextPlayer,int &gamedirection,int playercolor[]);
bool callUno(int playerHand[], int handSize);
// Function definitions
bool callUno(int playerHand[],int handsize) {
    int cardsLeft = 0;
    for (int i = 0; i < handsize ; ++i) 
	{
        if (playerHand[i] != -1) 
		{ 
            cardsLeft = cardsLeft + 1;
        }// checking how many cards left
    }
    if (cardsLeft == 2) {
        return true;// if two left and this function was called the returns true else false
    }
    else
    {
    	return false;
	}
}
void clearScreen() {
    system("CLS");
}


void handleSpecialCard(int specialCardType)
{
	
	int digit2 = (specialCardType / 10) % 10;


	if(digit2 == 10 || digit2 == 11 || digit2 == 12 || digit2 == 14)
	{
		gameDirection = -gameDirection;
	}
	
	if(digit2 == 12 && currentPlayer == 0)
	{
		  for (int i = 0; i < 2; i++) {
        	player1[i] = rand() % NUM_CARDS_PER_COLOR;
        	player1Colors[i] = rand() % NUM_COLORS + 1; 
        	deck[NUM_COLORS][NUM_CARDS_PER_COLOR]++;
    		}
	}
	
	else if(digit2 == 12 && currentPlayer == 1)
	{
		for (int i = 0; i < 2; i++) {
        	player2[i] = rand() % NUM_CARDS_PER_COLOR;
        	player2Colors[i] = rand() % NUM_COLORS + 1; 
        	deck[NUM_COLORS][NUM_CARDS_PER_COLOR]++;
    		}
	}
	
	if(digit2 == 14 && currentPlayer == 0)
	{
		for (int i = 0; i < 4; i++) {
        	player1[i] = rand() % NUM_CARDS_PER_COLOR;
        	player1Colors[i] = rand() % NUM_COLORS + 1; 
        	deck[NUM_COLORS][NUM_CARDS_PER_COLOR]++;
    		}
	}
	else if(digit2 == 14 && currentPlayer == 1)
	{
		for (int i = 0; i < 4; i++) {
        	player2[i] = rand() % NUM_CARDS_PER_COLOR;
        	player2Colors[i] = rand() % NUM_COLORS + 1; 
        	deck[NUM_COLORS][NUM_CARDS_PER_COLOR]++;
    		}
	}
}

// Function to initialize a deck of cards
void initializeDeck(int deck[][NUM_CARDS_PER_COLOR]) {
    // Loop through each color (0 to NUM_COLORS-1)
    for (int color = 0; color < NUM_COLORS; color++) {
        // Set the '0' card for the current color (only 1 card per color)
        deck[color][0] = 1;

        // Loop through numbers 1 to 9 for the current color (each has 2 cards)
        for (int type = 1; type <= 9; type++) {
            deck[color][type] = 2;  // Two cards for numbers 1-9 per color
        }

        // Set 2 Skip, 2 Reverse, and 2 Draw Two cards per color
        deck[color][10] = 2; // Two Skip cards
        deck[color][11] = 2; // Two Reverse cards
        deck[color][12] = 2; // Two Draw Two cards
    }

    // Set the number of Wild cards and Wild Draw Four cards
    deck[0][13] = 4; // Four Wild cards
    deck[0][14] = 4; // Four Wild Draw Four cards
}

// Shuffle the deck
void shuffleDeck(int deck[][NUM_CARDS_PER_COLOR]) {
    srand(time(0));
    for (int color = 0; color < NUM_COLORS; color++) {
        for (int i = 0; i < NUM_CARDS_PER_COLOR; i++) {
            int randomColor = rand() % NUM_COLORS;
            int randomIndex = rand() % NUM_CARDS_PER_COLOR;
            int temp = deck[color][i];
            deck[color][i] = deck[randomColor][randomIndex];
            deck[randomColor][randomIndex] = temp;//random pos swapping shuffle
        }
    }
}

void dealCards(int deck[4][NUM_CARDS_PER_COLOR], int player1[], int player2[]) {
    int dealt = 0;
    srand(time(0));
    for (int i = 0; i < HAND_SIZE; i++) {
        player1[i] = rand() % NUM_CARDS_PER_COLOR;
        player2[i] = rand() % NUM_CARDS_PER_COLOR;
        player1Colors[i] = rand() % NUM_COLORS + 1; // Random color assignment
		player2Colors[i] = rand() % NUM_COLORS + 1; // Random color assignment
    }
}
// Check if a card is a valid play
bool isValidPlay(int playerCard, int topCard) {// returns true for wild card or same number or same color
	bool valid = false;
   if(topCard==playerCard)
   {
   		valid=true;
   }
   else if(playerCard>=10)
   {
   		valid=true;
   }
   else if(playerCard == topColor)
   {
   		valid=true;
   }
   return valid;
}
void UpdateDiscardPile(int playerHand[],int &topCard,int discardPile[],int choice,int &discardSize,int playercolor)
{
	topCard = playerHand[choice];
	topColor = playercolor;
    discardPile[discardSize++] = playerHand[choice];
}
void playTurn(int ptotalcolor, int deck[][NUM_CARDS_PER_COLOR], int playerHand[], int &handSize, int &topCard, int discardPile[], int &discardSize, int currentplayer,int nextplayer,int gamedirection,int playercolor[]) 
{
	wow:
    cout << "Your Turn! Select a card to play or draw (-1 to draw): ";
    int choice;
    cin >> choice;
	if(choice < -1)
	{
		cout<<"invalid";
		goto wow;
	}
    if (choice == -1) 
	{
		
		moves += "Player " + to_string(currentplayer + 1) + " drew a card.\n";// chose random color and num indexs drawes them checks them and adds them to players hands
		int colorchoice,numchoice;
		while(true)
		{
			int randomColor = rand() % NUM_COLORS;
        	int randomIndex = rand() % NUM_CARDS_PER_COLOR;	
        	if(deck[randomColor][randomIndex]>-1)
        	{
        		colorchoice = randomColor;
        		numchoice = randomIndex;
        		break;
			}			
		}
        playerHand[handSize++] = numchoice;
        playercolor[ptotalcolor++] = colorchoice;
        deck[colorchoice][numchoice]=-1;
        discardSize++;
    }
    else if(choice>-1)
    {
    	moves += "Player " + to_string(currentplayer + 1) + " played card " + to_string(playerHand[choice]) + ".\n";
    	if (isValidPlay(playerHand[choice], topCard))// checks if num matches w top card
		{
		
        	UpdateDiscardPile(playerHand,topCard,discardPile,choice,discardSize,playercolor[choice]);//updates cards and decks accordingly
        	if(playerHand[choice]>=10){
        	handleSpecialCard(playerHand[choice]);
			}
        	playerHand[choice] = -1;
        	playercolor[choice] = -1;
        	handSize--;
        	
		}
		else if(isValidPlay(playercolor[choice], topCard)) // checks if color matches w top card
		{
			UpdateDiscardPile(playerHand,topCard,discardPile,choice,discardSize,playercolor[choice]);//updates cards and decks accordingly
        	if(playerHand[choice]>=10){
        	handleSpecialCard(playerHand[choice]);
			}
        	playerHand[choice] = -1;
        	playercolor[choice] =-1;
        	handSize--;
		}
		else 
		{
        	cout << "Invalid play. Try again." << endl;
        	goto wow;
    	}
	}
}

// Function to set console text color
void setColor(int background, int text) {
    int color = (background << 4) | text;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// Function to calculate the number of digits in an integer
int length(int num) {
    int count = 0;
    while (num != 0) {
        num /= 10;
        count++;
    }
    if(count > 0){
        return count;
    } else {
        return 1;
    }   
}

// Function to get the size of a player's hand
int HandSize(int playerHand[]) {
    int handSize = 0;
    for (int i = 0; i < HAND_SIZE; i++) {
        if (playerHand[i] >= 0) {  // Check if the card is not empty
            handSize++;
        }
    }
    return handSize;
}


// Function to print the board
void printBoard(int topCard, int player1[], int player2[], int player1Colors[], int player2Colors[], int player1Size, int player2Size) {
    // Display the top card
    cout << "Top Card:" << endl;
    setColor(topColor, 0); // Set the top card color
    cout << "+-------+" << endl;
    cout << "|       |" << endl;
    if (length(topCard) != 1 || length(topCard)==-1) {
        cout << "|  " << topCard << "   |" << endl;
    } else {
        cout << "|   " << topCard << "   |" << endl;
    }
    cout << "|       |" << endl;
    cout << "+-------+" << endl;
    setColor(0, 7); // Reset color
    cout << endl;

    // Display Player 1's Hand
    cout << "Player 1's Hand:" << endl;
    for (int i = 0; i < player1Size; i++) {
    	if(player1Colors[i]==3)	
    		player1Colors[i] = 6;
        setColor(player1Colors[i], 0);
        cout << "+-------+";
        setColor(0, 7);
        cout << "    ";
    }
    cout << endl;

    for (int i = 0; i < player1Size; i++) {
    	if(player1Colors[i]==3)	
    		player1Colors[i] = 6;
        setColor(player1Colors[i], 0);
        cout << "|       |";
        setColor(0, 7);
        cout << "    ";
    }
    cout << endl;

    for (int i = 0; i < player1Size; i++) {
    	if(player1Colors[i]==3)	
    		player1Colors[i] = 6;
        setColor(player1Colors[i], 0);
        if (length(player1[i]) != 1) {
            cout << "|  " << player1[i] << "   |";
        } else {
            cout << "|   " << player1[i] << "   |";
        }
        setColor(0, 7);
        cout << "    ";
    }
    cout << endl;

    for (int i = 0; i < player1Size; i++) {
    	if(player1Colors[i]==3)	
    		player1Colors[i] = 6;
        setColor(player1Colors[i], 0);
        cout << "|       |";
        setColor(0, 7);
        cout << "    ";
    }
    cout << endl;

    for (int i = 0; i < player1Size; i++) {
    	if(player1Colors[i]==3)	
    		player1Colors[i] = 6;
        setColor(player1Colors[i], 0);
        cout << "+-------+";
        setColor(0, 7);
        cout << "    ";
    }
    cout << endl;
    
    // Display Player 2's Hand
    cout << "Player 2's Hand:" << endl;
    for (int i = 0; i < player2Size; i++) {
    	if(player2Colors[i]==3)	
    		player2Colors[i] = 6;
        setColor(player2Colors[i], 0);
        cout << "+-------+";
        setColor(0,7);
        cout<<"    ";
    }
    cout << endl;

    for (int i = 0; i < player2Size; i++) {
    	if(player2Colors[i]==3)	
    		player2Colors[i] = 6;
        setColor(player2Colors[i], 0);
        cout << "|       |";
        setColor(0,7);
        cout<<"    ";
    }
    cout << endl;

    for (int i = 0; i < player2Size; i++) {
    	if(player2Colors[i]==3)	
    		player2Colors[i] = 6;
        setColor(player2Colors[i], 0);
        if (length(player2[i]) != 1) {
            cout << "|  " << player2[i] << "   |";
        } else {
            cout << "|   " << player2[i] << "   |";
        }
        setColor(0,7);
        cout<<"    ";
    }
    cout << endl;

    for (int i = 0; i < player2Size; i++) {
    	if(player2Colors[i]==3)	
    		player2Colors[i] = 6;
        setColor(player2Colors[i], 0);
        cout << "|       |";
        setColor(0,7);
        cout<<"    ";
    }
    cout << endl;

    for (int i = 0; i < player2Size; i++) {
    	if(player2Colors[i]==3)	
    		player2Colors[i] = 6;
        setColor(player2Colors[i],0);
        cout << "+-------+";
        setColor(0,7);
        cout<<"    ";
    }
    cout << endl;

    // Reset to default color
    setColor(0, 7);
}
//save results
void saveLoadGameResult(int player1Wins, int player2Wins,int turns,string moves,int p1score,int p2score) {
    ofstream outFile("game_results.txt");
    outFile << "Player 1 Wins: " << player1Wins << endl;
    outFile << "Player 2 Wins: " << player2Wins << endl;
    outFile << "Score of Player 1 : " << p1score << endl;
    outFile << "Score of player 2 : " << p2score << endl;
    outFile << "Total Turns: " << turns << endl;
    outFile << moves;
    outFile.close();
}
bool checkWinner(int playerHand[], int handSize) {
    return handSize == 0;  // Player wins if they have no cards left
}

// playgame Function
int playgame() {
	clearScreen();
	static int turns = 0;
    int deck[NUM_COLORS][NUM_CARDS_PER_COLOR];
    int player1Size = HAND_SIZE;
    int player2Size = HAND_SIZE;
    int player1[player1Size], player2[player2Size];
    int discardPile[TOTAL_CARDS];
    int discardSize = 0;
    int gamedirection =1;
    static int player1Wins = 0;
    static int player2Wins = 0;
    char uno;
    
    int options[] = {2,4,1, 6}; 
	topColor = options[rand() % 4]; 
	player1Color = options[rand() % 4];
	player2Color = options[rand() % 4];
	
    

    initializeDeck(deck);
    shuffleDeck(deck);
    dealCards(deck, player1, player2);

    int topCard = deck[0][0];
    discardPile[discardSize++] = topCard;
	char exit;
	char sure;
    
	int currentPlayer = 0;
while (true) {
	clearScreen();
    printBoard(topCard, player1, player2, player1Colors, player2Colors, player1Size, player2Size);
    
    cout << "Do you want to exit the game? Press E or any other key to continue: ";
    cin >> exit;
    if (exit == 'e' || exit == 'E') {
        cout << "Are you sure? Press Y to confirm or any other key to continue: ";
        cin >> sure;
        if (sure == 'y' || sure == 'Y') {
            saveLoadGameResult(player1Wins, player2Wins,turns,moves,P1SCORE,P2SCORE);
            break;
        }
    }
    
    if (currentPlayer == 0) {
    	cout<<"Player 1 turns    ";
        // Player 1's turn
        int p1cardsLeft = 0;
        for (int i = 0; i < player1Size ; ++i) 
			{
        		if (player1[i] != -1) 
				{ 
            		p1cardsLeft = p1cardsLeft + 1;// CHECKS CARDSLEFT SAME FOR P2
        		}
    		}
        cout<<"do u want to call UNO enter U";
        cin>>uno;
        if((uno!= 'u' || uno!='U') && p1cardsLeft==2)// APPPLYING PEN FOR NOT CALLING UNO AT 2 CARDSLEFT SAME FOR P2
        	{
        		cout<<"penalty applied"<<endl;
        		for(int i=0;i<2;i++)
        		{	
        			int colorchoice,numchoice;
					while(true)
					{
						int randomColor = rand() % NUM_COLORS;
        				int randomIndex = rand() % NUM_CARDS_PER_COLOR;	
        			if(deck[randomColor][randomIndex]>-1)
        			{
        				colorchoice = randomColor;
        				numchoice = randomIndex;
        				break;
					}			
					}
        			player1[player1Size++] = numchoice;
        			player1Colors[p1totalcolor++] = colorchoice;
        			deck[colorchoice][numchoice]=-1;
        			discardSize++;
				}
			}
			else if(uno == 'u' || uno== 'U')
			{
				if(callUno(player1,player1Size))// CORRECT UNO CALL SAME FOR P2
				{
					cout<<"PLAYER 1 CALLED UNO"<<endl;
				}
				else
				{
					cout<<"penalty applied"<<endl;
        			for(int i=0;i<2;i++)
        			{	
        				int colorchoice,numchoice;
						while(true)
						{
							int randomColor = rand() % NUM_COLORS;
        					int randomIndex = rand() % NUM_CARDS_PER_COLOR;	
        				if(deck[randomColor][randomIndex]>-1)
        				{
        					colorchoice = randomColor;
        					numchoice = randomIndex;
        					break;
						}			
						}
        				player1[player1Size++] = numchoice;
        				player1Colors[p1totalcolor++] = colorchoice;
        				deck[colorchoice][numchoice]=-1;
        				discardSize++;
					}
				}
			}
        playTurn(p1totalcolor,deck,  player1, player1Size,topCard,  discardPile, discardSize,currentPlayer,currentPlayer+1,gamedirection,player1Colors);;
        if (checkWinner(player1, player1Size)) {
            cout << "Player 1 Wins!" << endl;
            player1Wins++;
            P1SCORE += 50;
            P2SCORE += 0;
            saveLoadGameResult(player1Wins, player2Wins,turns,moves,P1SCORE,P2SCORE);
            break;
        }
    } else {
    	int p2cardsLeft = 0;
    		for (int i = 0; i < player2Size ; ++i) 
			{
        		if (player2[i] != -1) 
				{ 
            		p2cardsLeft = p2cardsLeft + 1;
        		}
    		}
    	cout<<"Player 2 turns     ";
    		cout<<"do u want to call uno enter U else enter any char"<<endl;
        	cin>>uno;
        	if((uno!= 'u' || uno!='U') && p2cardsLeft==2)
        	{
        		cout<<"penalty applied"<<endl;
        			for(int i=0;i<2;i++)
        			{	
        				int colorchoice,numchoice;
						while(true)
						{
							int randomColor = rand() % NUM_COLORS;
        					int randomIndex = rand() % NUM_CARDS_PER_COLOR;	
        				if(deck[randomColor][randomIndex]>-1)
        				{
        					colorchoice = randomColor;
        					numchoice = randomIndex;
        					break;
						}			
						}
        				player2[player2Size++] = numchoice;
        				player2Colors[p2totalcolor++] = colorchoice;
        				deck[colorchoice][numchoice]=-1;
        				discardSize++;
					}
			}
			else if(uno == 'u' || uno== 'U')
			{
				if(callUno(player2,player2Size))
				{
					cout<<"PLAYER 2 CALLED UNO"<<endl;
				}
				else
				{
					cout<<"penalty applied"<<endl;
        			for(int i=0;i<2;i++)
        			{	
        				int colorchoice,numchoice;
						while(true)
						{
							int randomColor = rand() % NUM_COLORS;
        					int randomIndex = rand() % NUM_CARDS_PER_COLOR;	
        				if(deck[randomColor][randomIndex]>-1)
        				{
        					colorchoice = randomColor;
        					numchoice = randomIndex;
        					break;
						}			
						}
        				player2[player2Size++] = numchoice;
        				player2Colors[p2totalcolor++] = colorchoice;
        				deck[colorchoice][numchoice]=-1;
        				discardSize++;
					}
				}
			}
        // Player 2's turn
         playTurn(p1totalcolor,deck, player2, player2Size, topCard, discardPile, discardSize,currentPlayer,currentPlayer+1,gamedirection,player2Colors);
        if (checkWinner(player2, player2Size)) {
            cout << "Player 2 Wins!" << endl;
            player2Wins++;
            P2SCORE += 50;
            P1SCORE += 0;
            saveLoadGameResult(player1Wins, player2Wins,turns,moves,P1SCORE,P2SCORE);
            break;
        }
    }
	turns++;
    // Switch players
    currentPlayer = 1 - currentPlayer;
}
return 0;
}

int main() {
	clearScreen();
    char option;
    while (true) {
        cout << "====================" << endl;
        cout << "   Welcome to UNO" << endl;
        cout << "Enter P to play game" << endl;
        cout << "Enter S to see scores" << endl;
        cout << "Enter E to exit" << endl;
        cout << "====================" << endl;
        cin >> option;

        if (option == 'p' || option == 'P') {
            playgame();
        } else if (option == 's' || option == 'S') {
        	clearScreen();
            ifstream inFile("game_results.txt");
            string line;
            while (getline(inFile, line)) {
                cout << line << endl;
            }
            inFile.close();
        } else if (option == 'e' || option == 'E') {
            cout << "Exiting the game. Goodbye!" << endl;
            break;
        } else {
            cout << "Invalid option. Try again!" << endl;
        }
    }
    
}
