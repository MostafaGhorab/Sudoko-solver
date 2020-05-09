// A Backtracking program in C to solve Sudoku problem
#include <stdio.h>

// UNASSIGNED is used for empty cells in sudoku grid
#define UNASSIGNED 0

// N is used for the size of Sudoku grid. Size will be NxN
#define N 9
#define false 0
#define true 1
#include <time.h>   	// for clock_t, clock(), CLOCKS_PER_SEC
#include <unistd.h> 	// for sleep()
  int grid[N][N]; //= {
//	{0,0,0,0,0,0,0,6,0 },
//	{2,0,4,0,0,3,0,1,0 },
//	{0,0,7,0,0,0,0,0,0 },
//	{7,0,9,0,1,0,0,0,0 },
//	{1,0,3,8,0,0,5,0,9 },
//	{4,0,0,9,3,0,1,0,0 },
//	{5,0,0,2,0,0,0,0,0 },
//	{0,0,0,3,0,0,0,0,0 },
//	{3,4,0,0,0,0,2,9,1 },
//
//	};

	 int ToBeinitalized_grid[N][N]  ;

	 int Play_grid[N][N]  ;



unsigned int FindUnassignedLocation(int grid[N][N], int *global_row, int *global_col);

unsigned int isSafe(int grid[N][N], int row, int col, int num);

//clock_t begin = clock();

double time_elapsed (double begin )
{

    // to store execution time of code
	double time_spent = 0.0;



	// do some stuff here


	clock_t end = clock();

	// calculate elapsed time by finding difference (end - begin) and
	// dividing the difference by CLOCKS_PER_SEC to convert to seconds
	time_spent += (int)(end - begin) / CLOCKS_PER_SEC;

	return time_spent ;

}


void init (int grid_1[N][N],int grid_2[N][N] ,int grid_3 [N][N])
{

   int i, j,x;
   for(i=0; i<N; i++) {
      for(j=0;j<N;j++) {
         printf("Enter value for row[%d]col[%d]:", i, j);
         scanf("%d",&x);
         grid_1[i][j] =x;
       //  printf("a");
           grid_2[i][j]=grid_1[i][j];
           grid_3[i][j]=grid_1[i][j];
         //  printf("de2");
      }
   }

}
void ClearSodko (void) //initialize play array
{
    int i ,j ;
     for(i=0; i<N; i++) {
      for(j=0;j<N;j++) {
      Play_grid[i][j]=ToBeinitalized_grid[i][j];
      }
     }
    // printGrid( grid);

}

unsigned int SolveSudoku(int grid[N][N])
{
	int row, col,num;
	int prev_row,prev_col;
	int skip_value;
	int back_flag=0;


	// If there is no unassigned location, we are done
	if (!FindUnassignedLocation(grid, &row, &col)) //true means all the soduko is solved
    {
	return true; // success!
    }


	// consider digits 1 to 9
	for ( num = 1; num <= 9; num++) //not used nw

	{
	    if (back_flag ==1 )
        {
            if (num<=skip_value)
            {
            continue ;
            }
            else
            {
            back_flag =0;
            }

        }
		// if looks promising
		if (isSafe(grid, row, col, num))
		{
			// make tentative assignment
			grid[row][col] = num;


			//prevrow = row;
			//prevcol = col;
			//printf ("%d row",row);
			//printf ("%d prevrow\n",prevrow);


			// return, if success, yay!
			if (SolveSudoku(grid))
            {
				return true;
            }

			// failure, unmake & try again
			grid[row][col] = UNASSIGNED;
		}
	}

   return false; // this triggers backtracking


}


unsigned int FindUnassignedLocation(int grid[N][N], int *global_row, int *global_col)
{
    int row ;
    int col;
	for (row = 0; row < N; row++)
    {
		for (col = 0; col < N; col++)
        {
			if (grid[row][col] == UNASSIGNED)
			{
                *global_row = row;
                *global_col = col;
				return true;
			}
        }
    }
	return false;
}

/* Returns a unsigned intean which indicates whether an assigned entry
in the specified row matches the given number. */
unsigned int UsedInRow(int grid[N][N], int row, int num)
{
    int col;
	for ( col = 0; col < N; col++)
    {
		if (grid[row][col] == num)
			return true;
    }
	return false;
}

/* Returns a unsigned intean which indicates whether an assigned entry
in the specified column matches the given number. */
unsigned int UsedInCol(int grid[N][N], int col, int num)
{
    int row;
	for ( row = 0; row < N; row++)
    {
		if (grid[row][col] == num)
			return true;
    }
	return false;
}

/* Returns a unsigned intean which indicates whether an assigned entry
within the specified 3x3 box matches the given number. */
unsigned int UsedInBox(int grid[N][N], int boxStartRow, int boxStartCol, int num)
{
    int row;
    int col;
	for ( row = 0; row < 3; row++)
    {
		for ( col = 0; col < 3; col++)
        {
			if (grid[row+boxStartRow][col+boxStartCol] == num)
				return true;
        }
    }
	return false;
}

/* Returns a unsigned intean which indicates whether it will be legal to assign
num to the given row,col location. */
unsigned int isSafe(int grid[N][N], int row, int col, int num)
{
	/* Check if 'num' is not already placed in current row,
	current column and current 3x3 box */
	return !UsedInRow(grid, row, num) &&
		!UsedInCol(grid, col, num) &&
		!UsedInBox(grid, row - row%3 , col - col%3, num)&&
			grid[row][col]==UNASSIGNED;
}

/* A utility function to print grid */
void printGrid(int grid[N][N])
{
    int row,col;
	for ( row = 0; row < N; row++)
	{
	for ( col = 0; col < N; col++)
    {
			printf("%d ", grid[row][col]);
    }
		printf("\n");
	}
}
int IsSolved (void)
{
      int i ,j ;
     for(i=0; i<N; i++) {
      for(j=0;j<N;j++) {
      if (Play_grid[i][j]!=ToBeinitalized_grid[i][j])
        return 0;
      }
     }
     return 1;

}

void play (void )
{
    int skip =0;
    int i,j,value;
    printf ("\n\nYou have 3 minutes to finish this, GOOD LOUCK\n\n");


//     if (SolveSudoku(grid) == true)
//        {
//
//        }
//        else
//        {
//
//		printf("\n\nNo solution exists");
//		return 0;
//
//        }

		printf("\n\nIN PROGRESS MATRIX: \n");
		printGrid(Play_grid);
    clock_t begin = clock();
do
    {

    printf ("Enter the row and coloumn and value of cell you want to edit with space between: ");
    scanf("%d %d %d",&i,&j,&value);
    Play_grid[i][j]  = value;
    printf ("\n\n\n\n");
    printGrid(Play_grid);
    printf ("\nto return back press 1 to continue  press 0\n");
    scanf("%d",&skip);
   // printf("is solved %d",IsSolved() );
    }
    while (! ( ( (int) time_elapsed(begin) ) >= 20 || IsSolved() || (skip ==1 ))) ; //120 for 2 minutes
    if (IsSolved())
    {
        printf("\nCongrats");
    }
    else if (skip ==1 )
    {
        printf("SKIPPED!");
    }
    else
    {
        printf("\nTIME OUT");
    }
    return 0;

}


int main()
{
	// 0{configurable) means unassigned cells
	//Configure N
	//double x;




//clock_t begin = clock();
 //while (! ( ( (int) time_elapsed(begin) ) == 1 )  );
 printf ("***********************WELCOME TO SODUKO GAME*****************************\n");
 int choice =0 ;


 do
 {
     putchar('\n');
     printf("\nPlease enter your choice: \na-Enter Sodoko      b-clearSodoko\nc-solve             d-play\ne-print             f-exit\n");
     putchar('\n');

do{
     scanf("%c",&choice);
     //printf ("\nchar%d",choice) ;
}while (choice == 10); //asci of enter



     putchar('\n');





 switch (choice )
 {
     case 'a':
         init (grid,ToBeinitalized_grid,Play_grid);
         break ;

     case 'b' :
        ClearSodko ();
        break;

     case 'c' :
        if (SolveSudoku(grid) == true)
		printGrid(grid);
        else
		printf("No solution exists");
		break;

		case 'd' :
        play();
        break;

		case 'e' :

        printf("\n\nINITIAL MATRIX: \n");
        printGrid(ToBeinitalized_grid);

        if (SolveSudoku(grid) == true)
        {
        printf("\n\nSOLVED MATRIX: \n");
		printGrid(grid);
        }
        else
		printf("\n\nNo solution exists");

		printf("\n\nIN PROGRESS MATRIX: \n");
		printGrid(Play_grid);





        default: {printf("ERROR!");} //: printf ("\n error!\n");

 }

 } while (choice != 'f');

                return 0 ;

}
