/*
Daniel Ewing
*/
#include "PuzzleStateNode.h"

using namespace std;

PuzzleStateNode::PuzzleStateNode(string tempArray[3][3])
{
	puzzleID = "";
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			puzzleStateArray[i][j] = tempArray[i][j];
			puzzleID += tempArray[i][j];
			if (puzzleStateArray[i][j] == "E") {
				emptyXArrayPos = j;
				emptyYArrayPos = i;
			}
		}
	}
	moveCounter = 0;
}
PuzzleStateNode::PuzzleStateNode(const PuzzleStateNode& other) {
	{ puzzleID = "";
	moveCounter = other.moveCounter;
	moveQueue = other.moveQueue;
	emptyXArrayPos = other.emptyXArrayPos;
	emptyYArrayPos = other.emptyYArrayPos;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			puzzleStateArray[i][j] = other.puzzleStateArray[i][j];
			puzzleID += other.puzzleStateArray[i][j];
		}
	}
	}
}
PuzzleStateNode::~PuzzleStateNode()
{
}

int PuzzleStateNode::getEmptyXArrayPos() {
	return emptyXArrayPos;
}
int PuzzleStateNode::getEmptyYArrayPos() {
	return emptyYArrayPos;
}
int PuzzleStateNode::getMoveCounter() {
	return moveCounter;
}
string PuzzleStateNode::getPuzzleID() {
	return puzzleID;
}
void PuzzleStateNode::setPuzzleID() {
	puzzleID = "";
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			puzzleID += puzzleStateArray[i][j];
		}
	}
}
void PuzzleStateNode::setEmptyXArrayPos(int x) {
	emptyXArrayPos = x;
}
void PuzzleStateNode::setEmptyYArrayPos(int y) {
	emptyXArrayPos = y;
}
bool PuzzleStateNode::parityCheck(ofstream& outFile) {	// counts number of swaps for a bubble sort excluding swaps involving the empty space
	string parityCheckString = "";						// Puzzles with odd swaps have odd parity and are unsolvable. 
	char tempChar;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			parityCheckString += puzzleStateArray[i][j];
		}
	}
	int counter = 0;
	for (int j = 0; j < 8; j++) {
		for (int i = 0; i < 8; i++) {
			if (parityCheckString[i] > parityCheckString[i + 1]) {
				if (parityCheckString[i] == 'E') {
					tempChar = parityCheckString[i];
					parityCheckString[i] = parityCheckString[i + 1];
					parityCheckString[i + 1] = tempChar;
				}
				else {
					tempChar = parityCheckString[i];
					parityCheckString[i] = parityCheckString[i + 1];
					parityCheckString[i + 1] = tempChar;
					counter += 1;
				}
			}
		}
	}
	if (counter % 2 == 0) {
		outFile << "Puzzle with the following initial state is solvable: " << endl;
		printState(outFile);
		outFile << endl;
		return true;
	}
	outFile << "The following puzzle state is unsolvable. Skipping to next Puzzle. \n";
	printState(outFile);
	outFile << endl;
	return false;
}
bool PuzzleStateNode::checkForSolve() {
	if (puzzleStateArray[0][0] == "1" && puzzleStateArray[0][1] == "2" && puzzleStateArray[0][2] == "3" && puzzleStateArray[1][0] == "4" && puzzleStateArray[1][1] == "5" && puzzleStateArray[1][2] == "6" && puzzleStateArray[2][0] == "7" && puzzleStateArray[2][1] == "8" && puzzleStateArray[2][2] == "E") {
		return true;
	}
	return false;
}
void PuzzleStateNode::pushToMoveQueue(string move) {
	moveQueue.push(move);
}
void PuzzleStateNode::moveEmptySquareDown(int xEmptyPos, int yEmptyPos) {
	puzzleStateArray[yEmptyPos][xEmptyPos] = puzzleStateArray[yEmptyPos + 1][xEmptyPos];
	puzzleStateArray[yEmptyPos + 1][xEmptyPos] = "E";
	moveQueue.push("     Down");
	moveCounter++;
	emptyYArrayPos = yEmptyPos + 1;
}
void PuzzleStateNode::moveEmptySquareUp(int xEmptyPos, int yEmptyPos) {
	puzzleStateArray[yEmptyPos][xEmptyPos] = puzzleStateArray[yEmptyPos - 1][xEmptyPos];
	puzzleStateArray[yEmptyPos - 1][xEmptyPos] = "E";
	moveQueue.push("     Up");
	moveCounter++;
	emptyYArrayPos = yEmptyPos - 1;
}
void PuzzleStateNode::moveEmptySquareLeft(int xEmptyPos, int yEmptyPos) {
	puzzleStateArray[yEmptyPos][xEmptyPos] = puzzleStateArray[yEmptyPos][xEmptyPos - 1];
	puzzleStateArray[yEmptyPos][xEmptyPos - 1] = "E";
	moveQueue.push("     Left");
	moveCounter++;
	emptyXArrayPos = xEmptyPos - 1;
}
void PuzzleStateNode::moveEmptySquareRight(int xEmptyPos, int yEmptyPos) {
	puzzleStateArray[yEmptyPos][xEmptyPos] = puzzleStateArray[yEmptyPos][xEmptyPos + 1];
	puzzleStateArray[yEmptyPos][xEmptyPos + 1] = "E";
	moveQueue.push("     Right");
	moveCounter++;
	emptyXArrayPos = xEmptyPos + 1;
}
void PuzzleStateNode::printMoves(ofstream& outFile) {
	string tempString;
	for (int i = 0; i < moveQueue.size(); i++) {
		tempString = moveQueue.front();
		outFile << tempString << endl;
		moveQueue.push(moveQueue.front());
		moveQueue.pop();
	}
	outFile << endl;
}
void PuzzleStateNode::printState(ofstream& outFile) {
	for (int i = 0; i < 3; i++) {
		outFile << "     ";
		for (int j = 0; j < 3; j++) {
			string tempString = puzzleStateArray[i][j];
			outFile << tempString;
		}
		outFile << endl;
	}
}