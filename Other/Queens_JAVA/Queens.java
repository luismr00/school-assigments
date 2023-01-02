public class Queens {

    // Global variables
    // N can be changed to whichever board dimension one wants to test
	int N = 8;
    int totalBT = 0;

	void printBoard(int board[][]) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++)
				System.out.print(" " + board[i][j] + " ");
			System.out.println();
		}

	}


	boolean isSafe(int board[][], int row, int col) {
		int i, j;

		// Checking every spot within our row from the left side <---
		for (i = 0; i < col; i++)
			if (board[row][i] == 1)
				return false;

		// Checking every spot diagonally over the upper left side  \
		for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
			if (board[i][j] == 1)
				return false;

		// Checking every spot diagonally over the lower left side  /
		for (i = row, j = col; j >= 0 && i < N; i++, j--)
			if (board[i][j] == 1)
				return false;

        // Return true to indicate you didn't find any conflicts when placing the queen
		return true;
	}

	// Recursive function to solve N Queens
    // The algorithm starts from the top left and checks for every safe spot while backtracking by moving
    // through each column from left to right while checking every row from top to bottom
	boolean queensAlgorithm(int board[][], int currentcol)
	{
		// When all queens are placed safely then we found our solution and just return true to finish
		if (currentcol >= N)
			return true;

		// Checking for every row one by one while in the currentcol
		for (int currentrow = 0; currentrow < N; currentrow++) {
			
            // Check if queen can be placed safely within the currentcol and row(i)
			if (isSafe(board, currentrow, currentcol)) {
				
                // We mark our spot within our board as 1 to indicate that the queen has been placed safely
				board[currentrow][currentcol] = 1;

				// We call our algorithm recursively by moving to the next column to check new spots for our queens to be placed safely
				if (queensAlgorithm(board, currentcol + 1) == true)
					return true;

				// When the algorithm cannot place each queen safely up until the currentcol, then we backtrack by setting the last queen back to 0
				board[currentrow][currentcol] = 0;
                totalBT++;
			}
		}

		// We return false if the algorithm backtracks all possible spots and couldn't find a solution to place all queens safely
		return false;
	}

	boolean getSolution() {
		
        // Our 8 x 8 board
        // If you change N to something else than 8, then change this two dimensional array accordingly to meet your needs
        int board[][] = { { 0, 0, 0, 0, 0, 0, 0, 0 },
						{ 0, 0, 0, 0, 0, 0, 0, 0 },
						{ 0, 0, 0, 0, 0, 0, 0, 0 },
                        { 0, 0, 0, 0, 0, 0, 0, 0 },
						{ 0, 0, 0, 0, 0, 0, 0, 0 },
                        { 0, 0, 0, 0, 0, 0, 0, 0 },
						{ 0, 0, 0, 0, 0, 0, 0, 0 },
						{ 0, 0, 0, 0, 0, 0, 0, 0 } };

		if (queensAlgorithm(board, 0) == false) {
			System.out.print("Solution does not exist");
			return false;
		}

		printBoard(board);
        System.out.println("\nYou backtracked a total of " + totalBT + " times.");
		return true;
	}

	public static void main(String args[])
	{
		Queens Q = new Queens();
		Q.getSolution();

	}
}
