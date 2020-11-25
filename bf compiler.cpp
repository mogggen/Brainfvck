#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <vector>

using namespace std;

void trim(string& val)
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
	for (size_t i = 0; i < vect.size(); i++)
	{
		temp += vect[i];
	}
	return temp;
}

void appendSymbols(string& commands)
{
	vector<string> all;
	ifstream rfile;
	rfile.open("../Hello.bf");
	if (rfile.is_open()) {
		int i = 0;
		while (getline(rfile, commands)) {
			trim(commands);
			all.push_back(commands);
		}
		rfile.close();
	}
	commands = arrToString(all);
}

void debug(const uint8_t* memCell, const size_t pointer, const size_t totalmemlen)
{
	size_t i = 0;
	cout << endl;
	for (; i < totalmemlen; i++)
	{
		cout << i << '\t';
	}
	cout << endl;
	for (i = 0; i < totalmemlen; i++)
	{
		cout << (int)memCell[i] << '\t';
	}
	cout << endl;
	for (i = 0; i < totalmemlen; i++)
	{
		if (i == pointer)
			cout << "|";
		cout << '\t';
	}

	cin.get();
}

int main()
{
	//file read and setup
	string commands;
	stack<int> stack;

	appendSymbols(commands);

	//compile
	unsigned char memCell[5]; for (char i = 0; i < sizeof(memCell) / sizeof(*memCell); i++) memCell[i] = 0;

	int pointer = 0;
	bool greenLight = true;
	for (size_t runtimePos = 0; runtimePos < commands.size(); runtimePos++)
	{
		if (greenLight)
		{
			switch (commands[runtimePos])
			{
			case '>':
				pointer = (pointer < sizeof(memCell) / sizeof(*memCell)) ? pointer + 1 : 0;
				break;

			case '<':
				pointer = pointer > 0 ?
					pointer - 1 : sizeof(memCell) / sizeof(*memCell) - 1;
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
				stack.push(runtimePos);
				greenLight = memCell[pointer];
				break;
			}

		}
		if (commands[runtimePos] == ']')
		{
			if (memCell[pointer])
				runtimePos = stack.top();
			else
				stack.pop();
			greenLight = true;
		}
	}
}
