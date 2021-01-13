#include<iostream>
#include<set>
using namespace std;
/*Function to check if a given row is valid.It will return:
 -1 if the row contains an invalid value
  0 if the row contains repeated values
  1 if the row is valid.*/
int valid_row(int row,int grid[][9])
{
  set<int>s;
  for(int i=0;i<9;i++)
  {
    /*Checking for values outside 0 and 9;
      0 is considered valid because it denotes an empty cell.*/
    if(grid[row][i]<0||grid[row][i]>9)
    {
      return -1;
    }
    else
    { //Checking for repeated values.
      if(grid[row][i]!=0)
      {
        if(s.insert(grid[row][i]).second==false)
        {
          return 0;
        }
      }
    }
  }
  return 1;
}
/*Function to check if a given column is valid. It will return:
 -1 if the column contains an invalid value
  0 if the column contains repeated values
  1 if the column is valid.*/
int valid_col(int col,int grid[][9])
{
  set<int>s;
  for(int i=0;i<9;i++)
  {
    /*Checking for values outside 0 and 9;
      0 is considered valid because it denotes an empty cell.*/
    if(grid[i][col]<0||grid[i][col]>9)
    {
      return -1;
    }
    else
    { // Checking for repeated values.
      if(grid[i][col]!=0)
      {
        if(s.insert(grid[i][col]).second==false)
        {
          return 0;
        }
      }
    }
  }
  return 1;
}
/*Function to check if the subgrid is valid. It will return:
 -1 if a subgrid contains an invalid value
  0 if a subgrid contains repeated values
  1 if the subgrid is valid.*/
int valid_subgrid(int grid[][9])
{
  for(int row=0;row<9;row=row+3)
  {
    for(int col=0;col<9;col=col+3)
    {
        set<int>s;
        for(int r=row;r<row+3;r++)
        {
          for(int c=col;c<col+3;c++)
          {
            /* Checking for values outside 0 and 9;
            // 0 is considered valid because it
            // denotes an empty cell.*/
            if(grid[r][c]<0||grid[r][c]>9)
            {
              return -1;
            }
            else
            {
              // Checking for repeated values
              if(grid[r][c]!=0)
              {
                if(s.insert(grid[r][c]).second==false)
                {
                  return 0;
                }
              }
            }
          }
        }
    }
  }
  return 1;
}
//Function to check if the board is valid or not.
bool valid_board(int grid[][9])
{
  for(int i=0;i<9;i++)
  {
    int res1=valid_row(i,grid);
    int res2=valid_col(i,grid);
    // If a row or a column is invalid, then the board is invalid.
    if(res1<1||res2<1)
    {
      return false;
    }
  }
  // if any one the subgrid is invalid, then the board is invalid.
  int res3=valid_subgrid(grid);
  if(res3<1)
  {
    return false;
  }
  else
  {
    return true;
  }
}
/*Checks whether it will be
  legal to assign num to the
  given row,col*/
bool isSafe(int grid[][9],int row,int col,int num)
{
    /*Check if we find the same num
      in the similar row,we
      return false*/
    for(int x=0;x<9;x++)
    {
        if(grid[row][x]==num)
            return false;
    }
    /*Check if we find the same num in
      the similar column , we
      return false*/
    for(int x=0;x<9;x++)
    {
        if(grid[x][col]==num)
            return false;
    }
    /*Check if we find the same num in
      the particular 3*3 matrix,
      we return false*/
    int startRow=row-row%3;
    int startCol=col-col%3;
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            if(grid[i+startRow][j+startCol]==num)
                return false;
        }
    }
    return true;
}
/*Takes a partially filled-in grid and attempts
  to assign values to all unassigned locations in
  such a way to meet the requirements for
  Sudoku solution (non-duplication across rows,
  columns, and boxes) */
bool solveSudoku(int grid[][9],int row,int col)
{
    /*Check if we have reached the 8th row and 9th column(0 indexed matrix),we are
      returning true to avoid further backtracking*/
      if(row==8&&col==9)
        return true;
    /*Check if column value becomes 9,we move to next row and
    column start from 0*/
    if(col==9)
    {
        row++;
        col=0;
    }
    /*Check if the current position of the grid already contains
      value>0,we iterate for next column*/
      if(grid[row][col]>0)
        return solveSudoku(grid,row,col+1);
      for(int num=1;num<=9;num++)
      {
        /*Check if it is safe to place the num(1-9) in the
          given row,col-> we move to next column*/
          if(isSafe(grid,row,col,num))
          {
            /*Assigning the num in the current (row,col)
              position of the grid and assuming our
              assigned num in the position is correct*/
              grid[row][col]=num;
              //Checking for next possibility with next column
              if(solveSudoku(grid,row,col+1))
                return true;
          }
          /*Removing the assigned num,since our assumption was wrong,
            and we go for next assumption with different num value*/
            grid[row][col]=0;
      }
      return false;
}
// Function to print the board.
void print_board(int grid[][9])
{
  cout<<"----------------------------------"<<endl;
  for(int row=0;row<9;row++)
  {
    for(int col=0;col<9;col++)
    {
      cout<<grid[row][col]<<" ";
    }
    cout<<endl;
  }
  cout<<"------------------------------------"<<endl;
}
int main()
{
    int board[9][9];
    cout<<"Enter Sudoku elements"<<endl;
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            cin>>board[i][j];
        }
    }
    if(valid_board(board)==true)
    {
        if(solveSudoku(board,0,0))
        {
            cout<<"Sudoku entered by the user is valid"<<endl;
            cout<<"Solved Sudoku is: "<<endl;
            print_board(board);
        }
    }
    else
    {
        cout<<"Sudoku entered by the user is Invalid";
    }
    return 0;
}
