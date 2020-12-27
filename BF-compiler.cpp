#include <iostream>
#include <fstream>
#include <string>
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
}

void readFile(string& commands)
{
	vector<string> all;
	ifstream rfile;
	rfile.open("../Hello.bf");
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

void debug(const vector<uint8_t> memCell, const size_t pointer, const size_t totalmemlen)
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

	readInput(commands);
	//readFile(commands);

	//compile
	vector<unsigned char> memCell(8); //common memory size: 8

	long long pointer = 0;
	bool greenLight = true;
	for (size_t runtimePos = 0; runtimePos < commands.size(); runtimePos++)
	{
		if (greenLight)
		{
			switch (commands[runtimePos])
			{
			case '>':
				pointer = (pointer < memCell.size()) ? pointer + 1 : 0;
				break;

			case '<':
				pointer = pointer > 0 ?
					pointer - 1 : memCell.size() - 1;
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
		debug(memCell, pointer, memCell.size());
	}
}
