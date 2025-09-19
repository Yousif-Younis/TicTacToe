#include "tictactoe.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <cstdlib>
#include <ctime>
using namespace std;


TicTacToe::TicTacToe() {
    gameTreeRoot = new TreeNode;
    initializeBoard();
    playerTurn = true;
    gameOver = false;
    difficulty = 'E'; 
}

// Destructor 
TicTacToe::~TicTacToe() {
    deleteGameTree(gameTreeRoot);
}

// empty cells
void TicTacToe::initializeBoard() {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            ttt[i][j] = '-';
        }
    }
}

// Main game 
void TicTacToe::playGame() {
  
    cout << setw(40) << "Welcome to Tic Tac Toe!\n\n";

    
    cout << "Enter player 1's name: ";
    cin >> player1Name;

   
    char opponent;
    getOpponent(opponent);

   
    if (opponent == 'A') {
        player2Name = "AI";
        cout << player1Name << ", choose your symbol (X or O): ";
        cin >> player1Symbol;
        player1Symbol = toupper(player1Symbol);
        player2Symbol = (player1Symbol == 'X') ? 'O' : 'X';

        getDifficulty();
    }
    else {
        cout << "Enter player 2's name: ";
        cin.ignore(); 
        getline(cin, player2Name);
        cout << player1Name << ", choose your symbol (X or O): ";
        cin >> player1Symbol;
        player1Symbol = toupper(player1Symbol);
        player2Symbol = (player1Symbol == 'X') ? 'O' : 'X';
    }

 
    if (opponent == 'A' && difficulty == 'H') {
        buildGameTree(gameTreeRoot, player1Symbol, player1Symbol, player2Symbol);
    }

    while (!gameOver) {
        system("cls"); 
        displayBoard();

        
        if (playerTurn) {
            getPlayerMove(player1Symbol, player1Name);
        }
        else {
            if (opponent == 'A') {
                int move = getAIMove();
                cout << "AI's move: " << move + 1 << endl;
                ttt[move / 3][move % 3] = player2Symbol;
            }
            else {
                getPlayerMove(player2Symbol, player2Name);
            }
        }

        
        if (isWinner(playerTurn ? player1Symbol : player2Symbol)) {
            system("cls"); 
            displayBoard();
            cout << (playerTurn ? player1Name : player2Name) << " wins!\n";
            gameOver = true;
        }
        else if (isDraw()) {
            system("cls");
            displayBoard();
            cout << "It's a draw!\n";
            gameOver = true;
        }

        playerTurn = !playerTurn;
    }
}


void TicTacToe::displayBoard() {
    cout << "\n";
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            cout << ttt[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}


bool TicTacToe::isWinner(char symbol) {
    for (int i = 0; i < 3; ++i) {
        if ((ttt[i][0] == symbol && ttt[i][1] == symbol && ttt[i][2] == symbol) ||
            (ttt[0][i] == symbol && ttt[1][i] == symbol && ttt[2][i] == symbol)) {
            return true;
        }
    }
    if ((ttt[0][0] == symbol && ttt[1][1] == symbol && ttt[2][2] == symbol) ||
        (ttt[0][2] == symbol && ttt[1][1] == symbol && ttt[2][0] == symbol)) {
        return true;
    }
    return false;
}


bool TicTacToe::isDraw() {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (ttt[i][j] == '-') {
                return false;
            }
        }
    }
    return true;
}

bool TicTacToe::isValidMove(int move) {
    return (ttt[move / 3][move % 3] == '-');
}


void TicTacToe::getPlayerMove(char symbol, const string& playerName) {
    int move;
    while (true) {
        cout << playerName << ", choose a cell (1-9): ";
        cin >> move;
        move--; 
        if (move >= 0 && move < 9 && isValidMove(move)) {
            ttt[move / 3][move % 3] = symbol;
            break;
        }
        else {
            cout << "Invalid move. Please enter a number between 1 and 9 for an empty cell.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // btfokha men el invalid input
        }
    }
}


int TicTacToe::getAIMove() {
    return (difficulty == 'E') ? getEasyAIMove() : getHardAIMove();
}

// Easy
int TicTacToe::getEasyAIMove() {
    srand(static_cast<unsigned int>(time(0)));
    int move;
    do {
        move = rand() % 9;
    } while (!isValidMove(move));
    return move;
}

// Hard
int TicTacToe::getHardAIMove() {
    int bestScore = -1000;
    int bestMove = -1;
    for (int i = 0; i < 9; ++i) {
        if (isValidMove(i)) {
            ttt[i / 3][i % 3] = player2Symbol;
            int score = minimax(gameTreeRoot, false); // all possible moves 
            ttt[i / 3][i % 3] = '-';
            if (score > bestScore) {
                bestScore = score;
                bestMove = i;
            }
        }
    }
    return bestMove;
}


int TicTacToe::minimax(TreeNode* node, bool isMaximizingPlayer) {
    if (isWinner(player1Symbol)) return -10;
    if (isWinner(player2Symbol)) return 10;
    if (isDraw()) return 0;

    if (isMaximizingPlayer) {
        int bestScore = -1000;
        for (int i = 0; i < 9; ++i) {
            if (node->children[i] != nullptr) {
                int score = minimax(node->children[i], false);
                bestScore = max(bestScore, score);
            }
        }
        return bestScore;
    }
    else {
        int bestScore = 1000;
        for (int i = 0; i < 9; ++i) {
            if (node->children[i] != nullptr) {
                int score = minimax(node->children[i], true);
                bestScore = min(bestScore, score);
            }
        }
        return bestScore;
    }
}

// choose ai or player
void TicTacToe::getOpponent(char& opponent) {
    cout << "Choose your opponent:\n";
    cout << "A. Play against AI\n";
    cout << "P. Play against another player\n";
    cout << "Enter your choice (A/P): ";
    cin >> opponent;
    opponent = toupper(opponent);
    while (opponent != 'A' && opponent != 'P') {
        cout << "Invalid choice. Please enter A or P: ";
        cin >> opponent;
        opponent = toupper(opponent);
    }
}

// H or E
void TicTacToe::getDifficulty() {
    cout << "Choose AI difficulty level:\n";
    cout << "E. Easy\n";
    cout << "H. Hard\n";
    cout << "Enter your choice (E/H): ";
    cin >> difficulty;
    difficulty = toupper(difficulty);
    while (difficulty != 'E' && difficulty != 'H') {
        cout << "Invalid choice. Please enter E or H: ";
        cin >> difficulty;
        difficulty = toupper(difficulty);
    }
}


void TicTacToe::buildGameTree(TreeNode* node, char currentPlayer, char player1Symbol, char player2Symbol) {

    if (isWinner(player1Symbol) || isWinner(player2Symbol) || isDraw()) {
        return;
    }

    for (int i = 0; i < 9; ++i) {
        if (isValidMove(i)) {
            TreeNode* child = new TreeNode;
            copyBoard(child->board, node->board);
            child->board[i / 3][i % 3] = currentPlayer;
            node->children[node->numChildren++] = child;
            buildGameTree(child, (currentPlayer == player1Symbol) ? player2Symbol : player1Symbol, player1Symbol, player2Symbol);
        }
    }
}


void TicTacToe::deleteGameTree(TreeNode* node) {
    if (node != nullptr) {
        for (int i = 0; i < node->numChildren; ++i) {
            deleteGameTree(node->children[i]);
        }
        delete node;
    }
}


void TicTacToe::copyBoard(char dest[3][3], const char src[3][3]) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            dest[i][j] = src[i][j];
        }
    }
}

int main() {
    TicTacToe game;
    game.playGame(); 
    return 0; 
}
