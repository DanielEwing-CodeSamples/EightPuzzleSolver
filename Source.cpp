/*
Daniel Ewing
Approximate Runtime 7m 55s
*/
#include"PuzzleStateNode.h"
#include<string>
#include<fstream>
#include<iostream>
#include<unordered_set>

using namespace std;

int main() {
	void solvePuzzle(string stateArray[3][3], ofstream & outFile);
	ifstream inFile("input.txt");
	ofstream outFile("output.txt");
	string puzNum;
	int numberOfPuzzles;
	string junk; // gets junk from the input file
	getline(inFile, puzNum); // read number of puzzles
	numberOfPuzzles = stoi(puzNum); // convert value to int. 

	for (int i = 0; i < numberOfPuzzles; i++) {
		string stateArray[3][3];  // populates a temporary puzzle state. 
		string temp;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				while (temp != "1" && temp != "2" && temp != "3" && temp != "4" && temp != "5" && temp != "6" && temp != "7" && temp != "8" && temp != "E") {
					temp = inFile.get();
				}
				stateArray[i][j] = temp;
				temp = inFile.get();
			}
		}
		solvePuzzle(stateArray, outFile);
	}
	outFile.close();
	system("pause");
	return 0;
}

void solvePuzzle(string stateArray[3][3], ofstream& outFile) {
	bool isFinalState(PuzzleStateNode & tempState, queue<PuzzleStateNode> & puzzleQueue, ofstream & outFile);
	PuzzleStateNode pState(stateArray);
	queue<PuzzleStateNode> puzzleQueue;
	unordered_set<string> visitedPuzzleStateSet; //hashmap for instantaneous lookup of previously visited states.
	if (pState.parityCheck(outFile) == true) {
		puzzleQueue.push(pState);
		while (!puzzleQueue.empty()) {
			PuzzleStateNode myTempState(puzzleQueue.front());
			if (visitedPuzzleStateSet.find(myTempState.getPuzzleID()) == visitedPuzzleStateSet.end()) {  // is our value in the set? if not then do the following
				visitedPuzzleStateSet.emplace(myTempState.getPuzzleID()); // add to the list of visited states.				
				if (myTempState.getEmptyXArrayPos() == 0 || myTempState.getEmptyXArrayPos() == 1) { // if a move to the right is available
					PuzzleStateNode tempState(myTempState);
					tempState.moveEmptySquareRight(tempState.getEmptyXArrayPos(), tempState.getEmptyYArrayPos());
					tempState.setPuzzleID();
					if (isFinalState(tempState, puzzleQueue, outFile) == true) {
						return;
					}
				}
				if (myTempState.getEmptyXArrayPos() == 1 || myTempState.getEmptyXArrayPos() == 2) { // if a move to the left is available
					PuzzleStateNode tempState(myTempState);
					tempState.moveEmptySquareLeft(tempState.getEmptyXArrayPos(), tempState.getEmptyYArrayPos());
					tempState.setPuzzleID();
					if (isFinalState(tempState, puzzleQueue, outFile) == true) {
						return;
					}
				}
				if (myTempState.getEmptyYArrayPos() == 0 || myTempState.getEmptyYArrayPos() == 1) {// if a move down is available
					PuzzleStateNode tempState(myTempState);
					tempState.moveEmptySquareDown(tempState.getEmptyXArrayPos(), tempState.getEmptyYArrayPos());
					tempState.setPuzzleID();
					if (isFinalState(tempState, puzzleQueue, outFile) == true) {
						return;
					}
				}
				if (myTempState.getEmptyYArrayPos() == 1 || myTempState.getEmptyYArrayPos() == 2) {// if a move up is available
					PuzzleStateNode tempState(myTempState);
					tempState.moveEmptySquareUp(tempState.getEmptyXArrayPos(), tempState.getEmptyYArrayPos());
					tempState.setPuzzleID();
					if (isFinalState(tempState, puzzleQueue, outFile) == true) {
						return;
					}
				}
			}
			else
				puzzleQueue.pop();
		}
	}
	else
		return;
}

bool isFinalState(PuzzleStateNode& tempState, queue<PuzzleStateNode>& puzzleQueue, ofstream& outFile) {
	if (tempState.checkForSolve() == true) {
		outFile << "   Solved in " << tempState.getMoveCounter() << " movements of the emtpy tile which are listed below." << endl;
		tempState.printMoves(outFile);
		return true;
	}
	else {
		puzzleQueue.push(tempState);
		return false;
	}
}
