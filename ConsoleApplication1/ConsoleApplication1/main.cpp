#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<vector<int>> readFromFile(string file_path);
vector<vector<int>> readFromInputFile(vector< vector<int>> grid, string file_path);
vector<vector<int>> loadVectorArrayMovesFromArray(vector< vector<int>> v, string arr);
void start(string gridFile, string movesFile, string* inMoves);
void checkArguments(int argc, char** argv);
vector<vector<int>> readFromInputArray(vector< vector<int>> grid, string* array);
vector<vector<int>> createVectorArrayGrid(string line);
vector<vector<int>> createVectorArrayMoves(unsigned int rows);
vector<vector<int>> loadVectorArrayMoves(vector< vector<int>> v, string line);
vector<vector<int>> loadVectorArrayGrid(vector< vector<int>> v, string line, int currentLine);
bool isInside(int currPosX, int currPosY, int gridPosX, int gridPosY);
bool pathExists(vector<vector<int>> grid, vector<vector<int>> moves, int gridPositionX, int gridPositionY);
void getCurrentPosition(vector< vector<int>> v, int row, int col);
void printVectorArray(vector< vector<int>> v, int k);
unsigned int integerCharAt(string line, int i);
bool isPath(vector<vector<int>> grid, int currPosX, int currPosY);
bool left(vector<vector<int>> grid, int currPosX, int currPosY, int gridPosX, int gridPosY);
bool right(vector<vector<int>> grid, int currPosX, int currPosY, int gridPosX, int gridPosY); 
bool up(vector<vector<int>> grid, int currPosX, int currPosY, int gridPosX, int gridPosY); 
bool down(vector<vector<int>> grid, int currPosX, int currPosY, int gridPosX, int gridPosY); 
void userInput();
void writeTofile();



 string input;
 vector<int> result;
 bool isInputFile = false;
 bool isOutputFile = false;
 const int arr_size = 10;
 //max arr_size user inputs
 string inputMoves[arr_size];
 int gridPositionX;
 int gridPositionY;
 string OutputFile = "c:\\tmp\\out.txt";
 //string GridFile = "c://data/School/2.Rocnik/1.Semester/APC/ConsoleApplication1/ConsoleApplication1/mazeTest.pbm";
 //string MovesFile = "c://data/School/2.Rocnik/1.Semester/APC/ConsoleApplication1/ConsoleApplication1/mazeMoves.txt";
 string GridFile = "c:\\tmp\\test.pbm";
 string MovesFile = "c:\\tmp\\in.txt";
 //================================================================
//	MAIN()
//================================================================
int main(int argc, char** argv) //int argc, char** argv
{
	checkArguments(argc, argv);
	start(GridFile, MovesFile, inputMoves);
	if (isOutputFile == false)
	{
		cout << "-------------------" << endl;
		cout << "RESULTS: " << endl;
		for (size_t i = 0; i < result.size(); i++)
		{
			cout << result[i] << '\n';
		}
		cout << "-------------------" << endl;
		cout << "Finished program... " << endl;
	}
	return 0;
}

//================================================================

//****************************************************************
//	START
//****************************************************************

void start(string gridFile, string movesFile, string * inMoves)
{
	vector<vector<int>> grid = readFromFile(gridFile);
	cout << "-------------------" << endl;
	printVectorArray(grid, 0);
	cout << "-------------------" << endl;
	//vector<vector<int>> moves = readFromInputFile(grid, movesFile);
	vector<vector<int>> moves;
	if (isInputFile == true)
	{
		/*cout << "readFromInputFile" << '\n';*/
		moves = readFromInputFile(grid, movesFile);
	}
	else 
	{
		/*cout << "readFromInputArray" << '\n';*/
		moves = readFromInputArray(grid, inMoves);
	}
		
	if (isOutputFile == true)
	{
		cout << "write to file" << '\n';
		writeTofile();
	}

}
//****************************************************************

//================================================================
//	FIND PATH
//================================================================
bool pathExists(vector<vector<int>> grid, vector<vector<int>> moves, int gridPosX, int gridPosY)
{
	 int currentPositionX = moves[0][0];
	 int currentPositionY = moves[0][1];
	 cout << "-------------------" << endl;
	 cout << "moves: ";
	 printVectorArray(moves, 1);
	 cout << "-------------------" << endl;
	if (!(isInside(currentPositionX, currentPositionY, gridPosX, gridPosY)))
	{
		return false;
	}
	else if (!(isPath(grid, currentPositionX, currentPositionY)))
	{
		return false;
	}
	else if (moves[1].size() == 0)
	{
		if (isPath(grid, currentPositionX, currentPositionY))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	for (size_t i = 0; i < moves[1].size(); i++)
	{
		
		cout << "Move: " << moves[1][i] << '\n';
		switch (moves[1][i]) {
		case 0:	
			currentPositionY--;
			if (!left(grid, currentPositionX, currentPositionY, gridPosX, gridPosY))
			{
				
				return false;
			}
			break;
		case 1:
			currentPositionY++;
			if (!right(grid, currentPositionX, currentPositionY, gridPosX, gridPosY))
			{
				
				return false;
			}
			break;
		case 2:
			currentPositionX--;
			if (!up(grid, currentPositionX, currentPositionY, gridPosX, gridPosY))
			{
				
				return false;
			}
			break;
		case 3:
			currentPositionX++;
			if (!down(grid, currentPositionX, currentPositionY, gridPosX, gridPosY))
			{
				
				return false;
			}
			break;
		default:
			cout << "I can't recognize this move: " << moves[1][i] << '\n';
			return false;
			break;
		}
	}

	return true;
}

//================================================================

//================================================================
//	TRY TO OPEN FILE, CREATE AND LOAD VECTOR ARRAY
//================================================================
vector<vector<int>> readFromFile(string file_path)
{
	ifstream file(file_path);
	int currentLine = 0;
	string line;
	vector< vector<int>> v;


	if (file.is_open())
	{
		while (getline(file, line))
		{
			if (currentLine == 1)
			{
				v = createVectorArrayGrid(line);
			}
			else if (currentLine > 1)
			{
				v = loadVectorArrayGrid(v, line, currentLine);
			}
			currentLine++;
		}
		file.close();
	}
	else
	{
		cout << "Can't open file" << '\n';
	}
	return v;
}

//================================================================

vector<vector<int>> readFromInputFile(vector< vector<int>> grid, string file_path)
{
	ifstream file(file_path);
	/*int currentChar = 0;*/
	string line;
	vector< vector<int>> v;
	v = createVectorArrayMoves(2);
	if (file.is_open())
	{
		while (getline(file, line))
		{
			v = loadVectorArrayMoves(v, line);
			if (pathExists(grid, v, gridPositionX, gridPositionY))
			{
				result.push_back(1);
				cout << "-------------------" << endl;
				cout << "IS PATH : " << 1 << '\n';
				cout << "-------------------" << endl;
			}
			else
			{
				result.push_back(0);
				cout << "-------------------" << endl;
				cout << "IS PATH: " << 0 << '\n';
				cout << "-------------------" << endl;
			}
			v.clear();
			v = createVectorArrayMoves(2);
		}
	}
	else 
	{
		cout << "Can't open file" << '\n';
	}
	return v;
}

//================================================================

vector<vector<int>> readFromInputArray(vector< vector<int>> grid, string* arr)
{
	vector< vector<int>> v;
	string empty = "";
	v = createVectorArrayMoves(2);
	
		size_t i = 0;
		while (!arr[i].empty()) {
			
			if (arr[i] == empty)
				break;
			v = loadVectorArrayMovesFromArray(v, arr[i]);
			if (pathExists(grid, v, gridPositionX, gridPositionY))
			{
				cout << "-------------------" << endl;
				cout << "IS PATH : " << 1 << '\n';
				cout << "-------------------" << endl;
				result.push_back(1);
			}
			else
			{
				cout << "-------------------" << endl;
				cout << "IS PATH: " << 0 << '\n';
				cout << "-------------------" << endl;
				result.push_back(0);
			}
			i++;
			v.clear();
			v = createVectorArrayMoves(2);
		}
	
	
	return v;
}

//================================================================

//================================================================
//	VECTOR ARRAY HELPER FUNCTIONS
//================================================================

vector<vector<int>> createVectorArrayGrid(string line) 
{
	vector< vector<int>> v;
	unsigned int M = integerCharAt(line, 0);
	unsigned int N = integerCharAt(line, 2);
	gridPositionX = M;
	gridPositionY = N;
	v.resize(M);
	vector<int> col(N);
	v.push_back(col);
	
	return v;
}

//================================================================

vector<vector<int>> createVectorArrayMoves(unsigned int rows)
{
	vector< vector<int>> v;
	unsigned int M = rows;
	//unsigned int N = cols;
	v.resize(M);
	//vector<int> col(N);
	//v.push_back(col);

	return v;
}

//================================================================

vector<vector<int>> loadVectorArrayGrid(vector< vector<int>> v, string line, int currentLine)
{
	for (unsigned int i = 0; i < line.size(); i++) {
		if (line[i] != ' ')
		{
			v[currentLine - 2].push_back(integerCharAt(line, i));
		}
	}
	return v;
}

//================================================================

vector<vector<int>> loadVectorArrayMoves(vector< vector<int>> v, string line)
{
	
	for (unsigned int i = 0; i < line.size(); i++) {
		if (line[i] != ' ')
		{
			if (i == 0 || i == 2)
			{
				v[0].push_back(integerCharAt(line, i));
			}
			else 
			{
				v[1].push_back(integerCharAt(line, i));
			}
		}
	}
	return v;
}

//================================================================

vector<vector<int>> loadVectorArrayMovesFromArray(vector< vector<int>> v, string arr)
{

	for (unsigned int i = 0; i < arr.size(); i++) {
		
		
			if (i == 0 || i == 1)
			{
				v[0].push_back(integerCharAt(arr, i));
			}
			else
			{
				v[1].push_back(integerCharAt(arr, i));
			}
		
	}
	return v;
}

//================================================================

void printVectorArray(vector< vector<int>> v, int k)
{
	if (!(v.empty())) 
	{
		for (size_t i = k; i < v.size(); i++)
		{
			for (size_t j = 0; j < v[i].size(); j++)
			{
				cout << int(v[i][j]);
			}
			cout << "\n";
		}
	}
	else 
	{
		cout << "Vector is empty";
	}
}

//================================================================

void getCurrentPosition(vector< vector<int>> v, int row, int col)
{
	cout << '\n' << "current position" << int(v[row][col]) << '\n';
}

//================================================================

//================================================================
//	GET INTEGER VALUE OF STRING'S SPECIFIC CHARACTER
//================================================================

unsigned int integerCharAt(string line,int i)
{
	return line[i] - '0';
}

//================================================================

//================================================================
//	CHECK IF CURRENT IS INSIDE OR IF IT IS PATH
//================================================================

bool isInside(int currPosX, int currPosY, int gridPosX, int gridPosY)
{
	return ((currPosX >= 0 && currPosX <= gridPosX) && (currPosY >= 0 && currPosY <= gridPosY));
}

//================================================================

bool isPath(vector<vector<int>> grid, int currPosX, int currPosY)
{
	if (grid[currPosX][currPosY] == 1)
	{
		return true;
	}
	else if (grid[currPosX][currPosY] == 0)
	{
		return false;
	}
	else 
	{
		return false;
	}
}

//================================================================

//================================================================
//	||   checkLEFT	||	checkRIGHT	||	checkUP	 ||	 checkDOWN ||
//================================================================

bool left(vector<vector<int>> grid, int currPosX, int currPosY, int gridPosX, int gridPosY) 
{
	if (!(isInside(currPosX, currPosY, gridPosX, gridPosY)))
	{
		return false;
	}
	else if (!(isPath(grid, currPosX, currPosY)))
	{
		return false;
	}
	else 
	{
		return true;
	}
}

//================================================================

bool right(vector<vector<int>> grid, int currPosX, int currPosY, int gridPosX, int gridPosY) 
{
	if (!(isInside(currPosX, currPosY, gridPosX, gridPosY)))
	{
		return false;
	}
	else if (!(isPath(grid, currPosX, currPosY)))
	{
		return false;
	}
	else
	{
		return true;
	}
}

//================================================================

bool up(vector<vector<int>> grid, int currPosX, int currPosY, int gridPosX, int gridPosY) 
{
	if (!(isInside(currPosX, currPosY, gridPosX, gridPosY)))
	{
		return false;
	}
	else if (!(isPath(grid, currPosX, currPosY)))
	{
		return false;
	}
	else
	{
		return true;
	}
}

//================================================================

bool down(vector<vector<int>> grid, int currPosX, int currPosY, int gridPosX, int gridPosY) 
{
	if (!(isInside(currPosX, currPosY, gridPosX, gridPosY)))
	{
		return false;
	}
	else if (!(isPath(grid, currPosX, currPosY)))
	{
		return false;
	}
	else
	{
		return true;
	}
}

//================================================================

//================================================================
//	CHECK COMMAND LINE ARGUMENTS
//================================================================

void checkArguments(int argc, char** argv)
{
	int vIndex =  0;
	int inIndex = 0;
	int outIndex = 0;
	for (int i = 0; i < argc; ++i)
	{
		if (string(argv[i]) == "--distance")
		{
			cout << "Error" << '\n';
			exit(1);
		}
		if (string(argv[i]) == "--verify")
		{
			vIndex = i;
			if (vIndex < 2)
			{
				cout << "Error" << '\n';
				exit(1);
			}
			GridFile = argv[1];
			//cout << "GridFile: " << GridFile << '\n';
		}
		if (string(argv[i]) == "--input-file")
		{
			inIndex = i;
			if (inIndex < 2)
			{
				cout << "Error" << '\n';
				exit(1);
			}
			isInputFile = true;
			MovesFile = argv[i + 1];
			//cout << "MovesFile: " << MovesFile<< '\n';
		}
		if (string(argv[i]) == "--output-file")
		{
			outIndex = i;
			if (outIndex < 2)
			{
				cout << "Error" << '\n';
				exit(1);
			}
			isOutputFile = true;
			OutputFile = argv[i + 1];
			//cout << "OutputFile: " << OutputFile << '\n';
		}
	}
	if (vIndex == 0)
	{
		cout << "Error" << '\n';
		exit(1);
	}
	if (inIndex == 0)
	{
		userInput();
	}
	cout << "GridFile: " << GridFile << '\n';
	cout << "OutputFile: " << OutputFile << '\n';
	cout << "MovesFile: " << MovesFile << '\n';
}
//================================================================

void userInput()
{
	for (int i = 0; i < arr_size; i++) {
		cout << ": write nums or write k to end: ";
		cin >> input;
		if (input.size() <= 1 && input != "k")
		{
			cout << "ERROR: Wrong Input" << '\n';
			exit(1);
		}
		if (input == "k")
		{
			break;
		}
		inputMoves[i] = input;
	}
	
}

//================================================================

void writeTofile()
{
	ofstream file(OutputFile);
	for (size_t i = 0; i < result.size(); i++)	
	{
		if (i + 1 == result.size())
		{
			file << result[i];
		}
		else
		{
			file << result[i] << endl;
		}
		
	}
}

//================================================================