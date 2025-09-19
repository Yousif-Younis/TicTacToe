#pragma once
#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <string>

// TreeNode struct for game tree
struct TreeNode {
    char board[3][3];         // Board configuration
    TreeNode* children[9];    // Possible moves (up to 9)
    int numChildren;          // Number of children nodes
    int score;                // Score for the current game state

    TreeNode() {
        numChildren = 0;
        score = 0;
        for (int i = 0; i < 9; ++i) {
            children[i] = nullptr;
        }
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                board[i][j] = '-';
    }
};

class TicTacToe {
public:
    TicTacToe();  
    ~TicTacToe();   
    void playGame();

private:
    char ttt[3][3];
    std::string player1Name; 
    std::string player2Name; // Name of player 2 or AI
    char player1Symbol; // Symbol for player 1
    char player2Symbol; // Symbol for player 2 or AI
    bool playerTurn; // Boolean to keep track of turns
    bool gameOver; // Boolean to check if the game is over
    char difficulty; // Difficulty level (E for Easy, H for Hard)

    void displayBoard(); // Function to display the board
    bool isWinner(char symbol); // Function to check if there is a winner
    bool isDraw(); // Function to check if the game is a draw
    bool isValidMove(int move); // Function to check if a move is valid
    void getPlayerMove(char symbol, const std::string& playerName); // Function to get player's move
    int getAIMove(); // Function to get AI's move
    int getEasyAIMove(); // Function to get AI's move for easy difficulty
    int getHardAIMove(); // Function to get AI's move for hard difficulty using the game tree
    int minimax(TreeNode* node, bool isMaximizingPlayer); // Minimax algorithm for AI
    void getOpponent(char& opponent); // Function to get opponent choice
    void getDifficulty(); // Function to get difficulty level
    void initializeBoard(); // Function to initialize the board
    void buildGameTree(TreeNode* node, char currentPlayer, char player1Symbol, char player2Symbol); // Function to build game tree
    void deleteGameTree(TreeNode* node); // Function to delete game tree
    void copyBoard(char dest[3][3], const char src[3][3]); // Function to copy board state

    TreeNode* gameTreeRoot; // Root of the game tree
};

#endif // TICTACTOE_H
