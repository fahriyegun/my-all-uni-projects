 /*********************************************************************************
 * 							     HOMEWORK3                                       *
 *                                                                               *
 *                         FAHRÝYE GÜN-150112025                                 *
 *                                 &&                                            *
 *                      ÞEBNEM KARAKILIÇ-150112058                               *
 *                                                                               *
 * ********************************************************************************/	
//We implement code that coin collecting robot code.
//Each cell has integer numbers between -5 and 5 and barrier "X"
//if cell has positive integer, robot gains that amount of coins when it visits that cell.
//if the value of the cell is negative, then the robot pays that amount of coins if it visits that cell and if it has enough coin.
//But if it has not collected that amount of coins in the previous cells, then the robot cannot visit a cell with negative value
//Also there are some cells on the board that are always inaccessible for the robot. These are barriers "X".
//Let us examine code.

	import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Calendar;


	public class CoinCollectingRobot {

		public static void main(String[] args) {
			long millisStart = Calendar.getInstance().getTimeInMillis();
			//definitions variables
			int i,j,row,col;
			String filename="C:\\Users\\Fahriye\\Documents\\Eclipse\\algorithmHW\\src\\Problem1\\test4.dat";//path of input file
			String output_filename="C:\\Users\\Fahriye\\Documents\\Eclipse\\algorithmHW\\src\\Problem1\\output.dat";
			FileReader file;
			BufferedReader reader ;
			PrintWriter output;
			String line;
			int[][] coins;
			String[][] last_coins ;
			
			try {
				//Before we read file with FileReader and BufferedReader library.
				file = new FileReader(filename);
				reader = new BufferedReader(file);
				//readLine() function makes that read line from file.
				//And we take first line. it contains row and column values of our matrix.
				line =reader.readLine();
				//Separate line two: row and column. keep in ret[] array.
				String[] ret = line.split("\t");
				row = Integer.parseInt(ret[0]);//ret[0] is row value. 
				col = Integer.parseInt(ret[1]);//ret[1] is column value
				System.out.println(row +" " +col);//show that.
				coins = new int[row][col];//create 2D array (row*column or n*m size)
				
				//again read file line by line and keep in array all of values
				for( i=0; i<row; i++){
				line =reader.readLine();
				System.out.println(line);
				String delims = "\t"; //separate line until \t
				String[] tokens = line.split(delims);// and keep value in token[] array 
				for (j = 0; j < tokens.length; j++){
				    if((tokens[j].equals("X"))){
						coins[i][j]=-999;//if we see "X" barrier, its value is so small,like -infinite
				    }else{
					coins[i][j]=Integer.parseInt(tokens[j]);// else, convert string in file to integer value into array.
				    }
					//System.out.print(coins[i][j]+"		");
				    }
				//System.out.println();
				}
				System.out.println();
				
				//close file for reading
				reader.close();
				file.close();
				
				//create new 2D array for route, n*m size
				int[][] F = new int[row][col];
				F[0][0] = coins[0][0];//First element is 0. Because this is robot's starting point. 0 coin.
				for(j=1;j<col;j++){
						//if we go following first row,how many coins gain or pay? Keeping in array all values.
						F[0][j]= F[0][j-1]+ coins[0][j];
					
				}
				for(i=1;i<row;i++){
					//if we go with following other cells,how many coins gain or pay? Keeping in array all values.
					F[i][0]=F[i-1][0]+coins[i][0];
					for(j=1;j<col;j++){
						//we go just right or down. For this reason, compare right and down cells and choose including max coin and keeping in array 
						F[i][j]=Math.max(F[i-1][j], F[i][j-1]) +coins[i][j];
					}
				}
				//show on console that total coins: 
				System.out.println(F[row-1][col-1]);
				//this step's aim is  that show visited cells.
				//start with end of matrix
				i = row-1;
				j = col - 1;
				//create an 2D array for showing visited cells n*m sizes
				last_coins = new String[row][col];
				//starting and ending points are also visited.For this reason they represent with "P"
				last_coins[0][0]="P";
				last_coins[i][j]="P";
				while(i >=0 && j >= 0)
				{
					//if cell is not in first row and column;
					if(j==0 && i != 0){
						//and if following cell is following up cell coins plus and original cell,
						if( F[i][j] == (F[i-1][j] + coins[i][j])){
							//this cell is visited and go up row
							last_coins[i-1][j]="P";
							i--;
						}
					}//if cell is in first row and not in first column
					else if(i==0 && j!=0){
						//and if following cell is following left cell coins plus and original cell,
						if( F[i][j] == (F[i][j-1] + coins[i][j])){
							//this cell is visited and go left column
							last_coins[i][j-1]="P";
							j--;
						}
					}//if cell is first row or column break loop
					else if(i==0 && j==0){
						j--;
					}else{//if inside in array
						//and if following cell is following up cell coins plus and original cell,
						if( F[i][j] == (F[i-1][j] + coins[i][j])){
							//this cell is visited and go left row
							last_coins[i-1][j]="P";
							i--;
						}
						//and if following cell is following left cell coins plus and original cell,
						if( F[i][j] == (F[i][j-1] + coins[i][j])){
							//this cell is visited and go left column
							last_coins[i][j-1]="P";
							j--;
						}
					}
				}
				
				//this step's aim is that write output on file.
				output = new PrintWriter(new BufferedWriter(new FileWriter(output_filename, true)));
				//print total coins in file.
				output.println(F[row-1][col-1]);
				//print all matrix with visited cells "P" and barriers "X"
				for(i=0;i<row;i++){
					for(j=0;j<col;j++){
						if(last_coins[i][j]!="P"){
							if(coins[i][j]==-999){
								last_coins[i][j]="X";
								
							}else{
								//for writing operations, we use string array. For this reason,we convert all integer value to string into array
								last_coins[i][j]=Integer.toString(coins[i][j]);
							}
							
						}else{
							last_coins[i][j]="P";
						}
						//and print in file.
						output.print(last_coins[i][j]+"\t");
						//show output on console
					   System.out.print(last_coins[i][j]+"\t");
				}
					//print new line
					output.println("\n");
				System.out.println();
				}
				//if you want that print path in file, delete comment mark 
				//output.println("the path is:");
				
				//show path on console
				System.out.println("\nthe path is:");
				for(i=0;i<row;i++){
					for(j=0;j<col;j++){
						if(last_coins[i][j]=="P"){
							//output.print("["+i+","+j+"] ");
							System.out.print("["+i+","+j+"] ");
						}
					}
				}
				
				//close writing file.
				output.close();
			} catch (IOException e) {
				e.printStackTrace();
			}
			
			System.out.println("\n\n***MISSION COMPLETED***");
			long milliEnd = Calendar.getInstance().getTimeInMillis();
			System.out.println((milliEnd-millisStart)/1000.00 +"sec.");
	}
	}

			


