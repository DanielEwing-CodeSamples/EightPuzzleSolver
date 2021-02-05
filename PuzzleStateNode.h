/*
Daniel Ewing
*/
#ifndef Puzzle_State_Node_h
#define Puzzle_State_Node_h



#include<queue>
#include<iostream>
#include<fstream>
#include<cstdlib>
#include<string>

using namespace std;

class PuzzleStateNode
{
public:
	PuzzleStateNode(string tempArray[3][3]);
	PuzzleStateNode(const PuzzleStateNode& other);
	~PuzzleStateNode();

	int getEmptyXArrayPos();
	int getEmptyYArrayPos();
	int getMoveCounter();
	string getPuzzleID();

	void setEmptyXArrayPos(int x);
	void setEmptyYArrayPos(int y);
	void setPuzzleID();

	bool parityCheck(ofstream& outFile);
	bool checkForSolve();


	void pushToMoveQueue(string move);
	void moveEmptySquareDown(int xEmptyPos, int yEmptyPos);
	void moveEmptySquareUp(int xEmptyPos, int yEmptyPos);
	void moveEmptySquareRight(int xEmptyPos, int yEmptyPos);
	void moveEmptySquareLeft(int xEmptyPos, int yEmptyPos);

	void printState(ofstream& outFile);
	void printMoves(ofstream& outFile);


private:
	string puzzleStateArray[3][3];
	int moveCounter;
	queue<string> moveQueue;
	int emptyXArrayPos;
	int emptyYArrayPos;
	string puzzleID;
};



#endif Puzzle_State_Node_h