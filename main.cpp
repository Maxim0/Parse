#include <iostream>
#include <math.h>
#include <fstream>
#include <string>
#include <map>
#include <vector>
using namespace std;

class Parse
{
	map<char,int> variables;
	vector<string> text;
	int count = 0;
	char* str;

public:
	Parse(char* s):str(s){}

	int stringToNumber(string& str);
	void signEqual(string& str);
	void signPlus(string& str);
	void signMinus(string& str);
	void signMul(string& str);
	void signDiv(string& str);
	void makeMark(string& str);
	void parse(string& str);
	void ifCondition(string& str);
	void signSqrt(string& str);
	void print();

	void start();
};

int Parse::stringToNumber(string& str)
{
	int num = 0;
	for(size_t i = 0; i < str.size(); i++)
	{
		if(str[i] >= '0' && str[i] <= '9')
		{
			num += (str[i] - 48);
			num *= 10;
		}
	} num /= 10;
	if(str[4] == '-') num = -num;
	return num;
}

void Parse::signEqual(string& str)
{
	char name = str[2];
	int num = stringToNumber(str);

	variables[name] = num;
	cout << "Variable (" << name << ") = " << variables[name] << endl;
}

void Parse::signPlus(string& str)
{
	char res = str[str.size()-1];
	char left = str[2], right = str[4];
	variables[res] = variables[left] + variables[right];
	cout << "+: " << left << "+" << right << "=" << res << " => " << variables[res] << endl;
}

void Parse::signMinus(string& str)
{
	char res = str[str.size()-1];
	char left = str[2], right = str[4];
	variables[res] = variables[left] - variables[right];
	cout << "-: " << left << "-" << right << "=" << res << " => " << variables[res] << endl;
}

void Parse::signMul(string& str)
{
	char res = str[str.size()-1];
	char left = str[2], right = str[4];
	variables[res] = variables[left] * variables[right];
	cout << "*: " << left << "*" << right << "=" << res << " => " << variables[res] << endl;
}

void Parse::signDiv(string& str)
{
	char res = str[str.size()-1];
	char left = str[2], right = str[4];
	variables[res] = variables[left] / variables[right];
	cout << "/: " << left << "*" << right << "=" << res << " => " << variables[res] << endl;
}

void Parse::makeMark(string& str)
{
	char name = str[1];
	variables[name] = count;
	cout << ":" << name << " => " << variables['1'] << endl;
}

void Parse::ifCondition(string& str)
{
	if(variables[str[3]])
	{
		int start = variables[str[str.size()-1]] + 1;
		for(; start <= count; start++)
		{
			parse(text[start]);
		}
	}
}

void Parse::signSqrt(string& str)
{
	char res = str[str.size()-1];
	char left = str[5];
	variables[res] = sqrt(variables[left]);
	cout << "sqrt: " << left << "=" << res << " => " << variables[res] << endl;
}

void Parse::parse(string& str)
{
	switch(str[0])
	{
		case '=': signEqual(str); break;
		case '+': signPlus(str); break;
		case '-': signMinus(str); break;
		case '*': signMul(str); break;
		case ':': makeMark(str); break;
		case '/': signDiv(str); break;
	}

	if(str[0] == 'I' && str[1] == 'f')
		ifCondition(str);
	if(str[0] == 's' && str[1] == 'q' && str[2] == 'r' && str[3] == 't')
		signSqrt(str);
}

void Parse::print()
{
	cout << endl;
	for(map<char,int>::iterator i = variables.begin(); i != variables.end(); i++)
		cout << i->first << " = " << i->second << endl;
	cout << endl;
	for(size_t i = 0; i < text.size(); i++)
		cout << text[i] << endl;
}

void Parse::start()
{
	ifstream fin(str);
	char tmp[50];

	while(!fin.eof())
	{
		fin.getline(tmp, 10);
		string str = tmp;
		text.push_back(str);
		parse(str);
		++count;
	}

	print();

	fin.close();
}

int main()
{
	Parse p1("discriminant.txt");
	p1.start();
}
