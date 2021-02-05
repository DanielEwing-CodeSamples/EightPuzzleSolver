Project Requirements: 
	Solve an eight puzzle, a 3x3 square composed of nine 1x1 squares labeled 1-8 and an empty square, by moving the empty square until the puzzle is in the
 order of row 1: 1,2,3, row 2: 4,5,6, row 3: 7,8,Empty. Populate the puzzle from a text file and if solveable list the moves necessary to solve it in the fewest
 moves possible. If it is not solveable then say so. The highest number of minimum movements to solve from any given puzzle state is 31 movements. 

Personal improvements not specified in project requirements:
	Checks parity - bubble sort the array by row then column. If the number of movements to sort, not counting movements of the empty space is odd, then
the puzzle is impossible to solve, and we can move to the next puzzle. 
	Stores visited puzzle states in a hash map for instantaneous lookup of states already added to the move queue, so theyre not added to the BFS search tree. 
This reduces our search tree to a maximum of 9!, or 362,880 nodes, a reduction of almost 21 fold for those who only excluded a reversal of the previous move
(i.e. dont move down if you just moved up), and a reduction of more than 44 million fold for those who added any possible move at any time to the BFS search tree.
	 
	