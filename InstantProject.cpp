#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <vector>

using namespace std;

vector<string> linesFromFile()
{
	vector<string> all;
	string temp;
	ifstream rfile;
	rfile.open("Hello.bf");
	if (rfile.is_open()) {
		int i = 0;
		while (getline(rfile, temp)) {
			all.push_back(temp);
		}
		rfile.close();
	}
	return all;
}

string arrToString(vector<string> vect)
{
	string temp;
	for (size_t i = 0; i < vect.size(); i++)
	{
		temp += vect[i];
	}
	return temp;
}

static bool isIterating(stack<char> pair)
{
	
}

int main()
{
	//file read and setup
	string commands;
	vector<string> lines;
	stack<int> start;

	lines = linesFromFile();
	commands = arrToString(lines);

	//compile
	char memCell[16]; for (char i = 0; i < sizeof(memCell) / sizeof(*memCell); i++) memCell[i] = 0;
	
	int pointer = 0;
	bool greenLight = true;
	for (char runtimePos = 0; runtimePos < commands.size(); runtimePos++)
	{
		if (greenLight)
		{
			switch (commands[runtimePos])
			{
			case '>':
				pointer = pointer < sizeof(memCell) / sizeof(*memCell) ?
					pointer++ : pointer = 0;
				break;

			case '<':
				pointer = pointer >= 0 ?
					pointer-- : pointer = sizeof(memCell) / sizeof(*memCell) - 1;
				break;

			case '+':
				memCell[pointer]++;
				break;

			case '-':
				memCell[pointer]--;
				break;

			case '.':
				cout << memCell[pointer];
				break;

			case ',':
				cin >> memCell[pointer];
				break;

			case '[':
				if (memCell[pointer] && runtimePos - 1 >= 0)
				{
					greenLight = true;
					
					start.push(runtimePos);
				}
				else
				{
					start.pop();
					greenLight = false;
				}
				break;

			default:
				break;
			}

		}
		if (commands[runtimePos] == ']')
			if (memCell[pointer])
			{
				runtimePos = start.top();
				greenLight = true;
			}
			else
			{
				greenLight = true;
			}
		cout << (int)runtimePos << ": " << commands[runtimePos] << endl;
		cout << "memCell[" << pointer << "]:" << (int)memCell[pointer];
		cin.get();
	}
}