#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <stack>
#include <vector>

using namespace std;

void compile(string& val)
{
	for (size_t i = 0; i < val.size(); i++)
	{
		switch (val[i])
		{
		case '>':
		case '<':
		case '+':
		case '-':
		case '.':
		case ',':
		case '[':
		case ']':
			break;

		default:
			val.replace(val.cbegin() + i, val.cbegin() + i + 1, "");
			i--;
			break;
		}
	}
}

string arrToString(vector<string> vect)
{
	string temp;
	for each (string s in vect)
	{
		temp += s;
	}
	return temp;
}

void readInput(string& out)
{
	cin >> out;
	compile(out);
}


void readFile(string& commands, string file_name = "Hello.bf")
{
	vector<string> all;
	ifstream rfile;

	rfile.open("../" + file_name);

	if (rfile.is_open()) {
		int i = 0;
		while (getline(rfile, commands)) {
			compile(commands);
			all.push_back(commands);
		}
		rfile.close();
	}
	commands = arrToString(all);
}

void debug(vector<uint8_t>* SelfmemCell, vector<uint8_t>* othermemCell, size_t pointer)
{
	size_t i = 0;
	cout << endl;
	for (i = 0; i < SelfmemCell->size(); i++)
	{
		cout << (int)(*SelfmemCell)[i] << '\t';
	}
	cout << "Self" << endl;
	for (i = 0; i < SelfmemCell->size(); i++)
	{
		if (i == pointer)
		{
			cout << "|";
		}
		cout << '\t';
	}
	cout << endl;
	for (i = 0; i < othermemCell->size(); i++)
	{
		cout << (int)(*othermemCell)[i] << '\t';
	}
	cout << "Other";
	cin.get();
}

void vanilla_compiler(string* commands, stack<int>* stack, vector<unsigned char>* memCell);

enum player
{
	self = 0,
	other = 1,
};

void step_simulation()
{

}

void scaling_rgba_compiler(const int INIT_INDEX, string* commands, stack<int>* stack, vector<unsigned char>* selfMemCell, vector<unsigned char>* otherMemCell);

int main()
{
	srand(time(0));
	
	//file read and setup
	string commands;
	string othercommands;
	for (size_t i = 0; i < 5; i++)
	{
		othercommands = "";
		
		int tempLen = rand() % 5;
		switch (rand() % 6)
		{
			case 0:
				othercommands.append(">");
				break;
			case 1:
				othercommands.append("<");
				break;
			case 2:
				othercommands.append("+");
				break;
			case 3:
				othercommands.append("-");
				break;
			case 4:
				othercommands.append(".");
				break;
			case 5:
				othercommands.append(",");
				break;
			default:
				// if a player create a Canvas that excceds the agreed apon loop limit. The Canvas will be discarded for the current duel.
				// When either one of the players has unreachable Canvases, or the turn Count Execceds the Max allowed, resulting in a draw
			break;
		}
	}
	
	
	stack<int> stack;
	
	//readInput(commands);
	//readFile(commands, "duel.bf");

	//compile
	int selfPointer = 0;
	vector<unsigned char> SelfMemCell(8); //common memory size: 8

	//vanilla_compiler(&commands, &stack, &memCell);



	int otherPointer = 0;
	vector<unsigned char> otherMemCell(8);

	// turn based duel
	int turn = 0;
	while(turn < 1000)
	{
		turn++;
		// commands should be loaded from a directory of Canvases
		int selfTurnCharge = 0, otherTurnCharge = 0;

		if (turn >= commands.size())
		{
			if (turn % 2)
			{
				// load the Canvas commands

				switch ((int)SelfMemCell[selfPointer])
				{
					case 0:
						readFile(commands, "0.bf");
						
						break;
					case 1:
						readFile(commands, "1.bf");
						
						break;
					case 2:
						readFile(commands, "2.bf");
						
						break;
					case 3:
						readFile(commands, "3.bf");
						
						break;
					case 4:
						readFile(commands, "4.bf");
						
						break;
					default:
						
						break;
				}

				cout << endl << "turn #" << turn << endl;
				for (; selfPointer < commands.size(); selfPointer++)
				{
					if (selfTurnCharge >= commands.size())
					{
						cout << "slot " << selfPointer;
						scaling_rgba_compiler(selfPointer, &commands, &stack, &SelfMemCell, &otherMemCell);
						cout << ", compiled: " << commands << endl;
					}
					else
					{
						cout << "turnCharge is to low for this canvas and will remain dormant for " << commands.size() - selfTurnCharge <<
							(commands.size() - selfTurnCharge > 1) ? "turns." : "turn.";
					}
				}
				
				selfTurnCharge = turn + 1;
			}
			else
			{
				for (; otherPointer < commands.size(); otherPointer++)
				{
					cout << endl << "turn #" << turn << endl;
					if (otherTurnCharge >= commands.size())
					{
						scaling_rgba_compiler(otherPointer, &commands, &stack, &otherMemCell, &SelfMemCell);
						otherPointer++;
					}
					else
					{
						cout << "turnCharge is to low for this canvas and will remain dormant for " << commands.size() - otherTurnCharge <<
							(commands.size() - otherTurnCharge > 1) ? "turns." : "turn.";
					}
				}
					
				otherTurnCharge = turn + 1;
			}
		}
		cin.get();
	}
}

void vanilla_compiler(string* commands, stack<int>* stack, vector<unsigned char>* memCell)
{
	long long pointer = 0;
	bool greenLight = true;
	for (size_t runtimePos = 0; runtimePos < commands->size(); runtimePos++)
	{
		if (greenLight)
		{
			switch ((*commands)[runtimePos])
			{
			case '>':
				pointer = (pointer < memCell->size()) ? pointer + 1 : 0;
				break;

			case '<':
				pointer = pointer > 0 ?
					pointer - 1 : memCell->size() - 1;
				break;

			case '+':
				(*memCell)[pointer]++;
				break;

			case '-':
				(*memCell)[pointer]--;
				break;

			case '.':
				cout << (*memCell)[pointer];
				break;

			case ',':
				cin >> (*memCell)[pointer];
				break;

			case '[':
				stack->push(runtimePos);
				greenLight = (*memCell)[pointer];
				break;
			}

		}
		if ((*commands)[runtimePos] == ']')
		{
			if ((*memCell)[pointer])
				runtimePos = stack->top();
			else
				stack->pop();
			greenLight = true;
		}
		//debug(memCell, nullptr, pointer);
	}
}

void scaling_rgba_compiler(const int INIT_INDEX, string* commands, stack<int>* stack, vector<unsigned char>* selfMemCell, vector<unsigned char>* otherMemCell)
{
	const int MAX_LAP = 256;
	long long pointer = INIT_INDEX;

	bool greenLight = true;
	int runningLoopCountRaw = 0; // ignores scope depth

	for (size_t runtimePos = 0; runtimePos < commands->size(); runtimePos++)
	{
		if (greenLight)
		{
			switch ((*commands)[runtimePos])
			{
			case '>':
				pointer = (pointer < selfMemCell->size()) ? pointer + 1 : 0;
				break;

			case '<':
				pointer = pointer > 0 ?
					pointer - 1 : selfMemCell->size() - 1;
				break;

			case '+':
				(*selfMemCell)[pointer]++;
				break;

			case '-':
				(*selfMemCell)[pointer]--;
				break;

			case '.':
				//read from opponent buffer instead
				(*selfMemCell)[pointer] = (*otherMemCell)[pointer];
				break;

			case ',':
				// write to oppenent buffer instead
				(*otherMemCell)[pointer] = (*selfMemCell)[pointer];
				break;

			case '[':
				stack->push(runtimePos);
				greenLight = (*selfMemCell)[pointer];
				break;
			}

		}
		if ((*commands)[runtimePos] == ']')
		{
			if ((*selfMemCell)[pointer] && runningLoopCountRaw < MAX_LAP)
			{
				runtimePos = stack->top();
				runningLoopCountRaw++;
			}
			else
			{
				stack->pop();
				runningLoopCountRaw = 0;
			}
			greenLight = true;
		}
	} // end of command loop

	debug(selfMemCell, otherMemCell, pointer);
}
