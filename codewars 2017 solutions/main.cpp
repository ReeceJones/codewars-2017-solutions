#include <cstdio>
#include <cmath>
#include <algorithm>
#include <string>
#include <iostream>
#include <vector>
#include <Windows.h>
#include <conio.h>
#include <iomanip>
#include <unordered_map>

/*
Codewars 2017 solutions: c++
	-Made by: Reece Jones
	-Arrays start at 0 edition
*/

void pause()
{
	while (!_kbhit()) { }
}

std::vector<std::string> getTokens(std::string str)
{
	std::vector<std::string> vecTok;
	char* cstr = new char[str.length() + 1];;
	strcpy(cstr, str.c_str());
	char* tok = strtok(cstr, " ");
	while (tok != NULL)
	{
		vecTok.push_back(tok);
		tok = strtok(NULL, " ");
	}
	delete[] cstr;
	delete[] tok;
	return vecTok;
}

std::vector<int> translateToInt(std::vector<std::string> vecStr, unsigned int start = 0)
{
	std::vector<int> vecInt;
	for (unsigned int i = start; i < vecStr.size(); i++)
	{
		vecInt.push_back(atoi(vecStr[i].c_str()));
	}
	return vecInt;
}

std::vector<float> translateToFloat(std::vector<std::string> vecStr, unsigned int start = 0)
{
	std::vector<float> vecInt;
	for (unsigned int i = start; i < vecStr.size(); i++)
	{
		vecInt.push_back(atof(vecStr[i].c_str()));
	}
	return vecInt;
}

std::string lineIn()
{
	std::string strIn;
	std::getline(std::cin, strIn);
	return strIn;
}

int stripToBase(int in)
{
	if (in > 9)
		while (in > 9)
			in -= 10;
	return in;
}

bool testBit(char data, unsigned int index/*from left to right*/)
{
	return data & (1 << index);
}

int getLargest(std::vector<int> vecInt)
{
	int largest = -0xFFFFF;
	for (int i : vecInt)
		if (i > largest)
			i = largest;
	return largest;
}

void addToPrintMatrix(char matrix[100][100], unsigned int x, unsigned int y, char inserted)
{
	matrix[y][x] = inserted;
}

struct coordinate
{
	unsigned int x, y;
	bool operator!=(coordinate& cmp)
	{
		return ((x != cmp.x) && (y != cmp.y));
	}
	bool operator==(coordinate& cmp)
	{
		return ((x == cmp.x) && (y == cmp.y));
	}
};

bool canGoDown(unsigned int y, unsigned int maxHeight)
{
	return y < maxHeight;
}

bool canGoRight(unsigned int x, unsigned int maxWidth)
{
	return x < maxWidth;
}

bool connectNode(coordinate node1, coordinate node2, std::vector<std::string> matrix)
{
	if (node1.x == node2.x)
	{
		std::string column;
		for (unsigned int i = (node1.y < node2.y) ? node2.y : node1.y; i > (node1.y > node2.y) ? node2.y : node1.y; i--)
		{
			column += matrix[i][node1.x];
		}
		return !(column.find('#') >= 0);
	}
	else if (node1.y == node2.y)
	{
		std::string row = matrix[node1.y];
		return !(row.find('#') >= 0);
	}
	
	return false;
}

std::vector<coordinate> findNodes(coordinate currentNode, std::vector<coordinate> nodes, std::vector<std::string> matrix)
{
	std::vector<coordinate> connectedNodes;
	for (auto node : nodes)
		if (connectNode(currentNode, node, matrix))
			connectedNodes.push_back(node);
	return connectedNodes;
}

std::vector<coordinate*> solveForPaths(std::vector<std::string> matrix)
{
	//my brain hurts right now
	//inspired by https://www.youtube.com/watch?v=rop0W4QDOUI

	//generate nodes
	std::vector<coordinate> nodes;
	char block = '#';
	
	for (unsigned int row = 0; row < matrix.size(); row++)
	{
		for (unsigned int x = 0; x < matrix[row].size(); x++)
		{
			//if you can go right or down there is a node
			if (canGoDown(row, matrix.size() - 1))
			{
				char downPos = matrix[row + 1].at(x);
				if (downPos != block)
					nodes.push_back({ x, row });
			}
			else if (canGoRight(x, matrix[row].size() - 1))
			{
				//we can else if just because nodes dont care about direction
				char rightPos = matrix[row].at(x + 1);
				bool exists = false;
				coordinate push = {row, x};
				for (auto coord : nodes)
					if (coord == push)
						exists = true;
				if (rightPos != block && exists == false)
					nodes.push_back(push);
			}
		}
	}

	//now we have to process the nodes
	std::vector<coordinate> traveledNodes;
	//we want to start with our top right node, i.e. node 0
	std::vector<coordinate> travelers;
	travelers.push_back({ 0, 0 });

	coordinate immediateNode = nodes[0];
	for (auto traveler : travelers)
	{
		std::vector<coordinate> possibleNodes = findNodes(immediateNode, nodes, matrix);
		for (auto extranode : possibleNodes)
		{
			for (auto traveled : traveledNodes)
				if (traveled == extranode)
					possibleNodes.erase
		}
	}

}

void problem0()
{
	std::cout << "Go Rams Go!" << std::endl;
}

void problem1()
{
	std::string strIn;
	std::getline(std::cin, strIn);
	std::cout << "What a wonderful judge " << strIn << " is!";
}

void problem2()
{
	std::string strIn;
	std::getline(std::cin, strIn);
	auto tok = getTokens(strIn);
	auto val = translateToInt(tok);
	std::cout << (val[0] * val[1]) << std::endl;
}

void problem3()
{
	std::vector<std::string> input;
	for (unsigned int i = 0; i < 3; i++)
		input.push_back(lineIn());

	for (unsigned int i = 0; i < 3; i++)
		std::cout << (atof(input[i].c_str()) * 0.299792) << std::endl;
}

void problem4()
{
	unsigned int lines = atoi(lineIn().c_str());
	std::vector<std::string> input;
	for (unsigned int i = 0; i < lines; i++)
	{
		input.push_back(lineIn());
	}
	for (unsigned int i = 0; i < lines; i++)
	{
		auto tok = getTokens(input[i]);
		auto val = translateToFloat(tok);
		std::cout << (val[0] / (val[1] / 60)) << std::endl;
	}
}

void problem5()
{
	unsigned int lines = atoi(lineIn().c_str());
	std::vector<std::string> input;
	for (unsigned int i = 0; i < lines; i++)
	{
		input.push_back(lineIn());
	}
	std::vector<double> times;
	for (unsigned int i = 0; i < lines; i++)
	{
		auto tok = getTokens(input[i]);
		auto val = translateToFloat(tok, 1);
		times.push_back((val[0] / val[1]));
	}
	unsigned int bestTime = 0xFFFFF;
	unsigned int bestIndex = times.size();
	for (unsigned int i = 0; i < times.size(); i++)
	{
		if (times[i] < bestTime)
		{
			bestTime = times[i];
			bestIndex = i;
		}
	}
	std::vector<std::string> names;
	for (std::string str : input)
	{
		auto tok = getTokens(str);
		std::string name = tok[0];
		names.push_back(name);
	}
	std::cout << names[bestIndex] << " " << times[bestIndex] << std::endl;
}

void problem6()
{
	//HAHAHAH
	//just realized i did this harder than it needed to be
	//the first digit of the line is ignored because the amount of integers in a sequence is determined dynamically
	//at least its dynamic, and i guess its a plus?
	unsigned int lines = atoi(lineIn().c_str());
	std::vector<std::string> input;
	for (unsigned int i = 0; i < lines; i++)
	{
		input.push_back(lineIn());
	}
	//woah a vector in a vector mind blown
	std::vector<std::vector<int>> vals;
	for (unsigned int i = 0; i < lines; i++)
	{
		auto tok = getTokens(input[i]);
		vals.push_back(translateToInt(tok));
	}
	//get deltas
	std::vector<std::vector<int>> deltas;
	for (unsigned int i = 0; i < lines; i++)
	{
		std::vector<int> pre = vals[i];
		std::vector<int> delta;
		for (unsigned int x = 1; x < pre.size(); x++)
			delta.push_back(pre[x] - pre[x - 1]);
		//for (int a : delta)
		//	std::cout << a << " ";
		//std::cout << std::endl;
		deltas.push_back(delta);
	}
	//invert the deltas
	std::vector<std::vector<int>> inverts;
	for (unsigned int i = 0; i < lines; i++)
	{
		std::vector<int> pre = deltas[i];
		std::vector<int> inverted;
		for (unsigned int x = 0; x < pre.size(); x++)
			inverted.push_back(-pre[x]);
		//for (int a : inverted)
		//	std::cout << a << " ";
		//std::cout << std::endl;
		inverts.push_back(inverted);
	}
	//apply the deltas
	std::vector<std::vector<int>> applied;
	for (unsigned int i = 0; i < lines; i++)
	{
		std::vector<int> pre = inverts[i];
		std::vector<int> res;
		int num = vals[i][1];
		res.push_back(num);
		for (unsigned int x = 1; x < pre.size(); x++)
		{
			num += pre[x];
			res.push_back(num);
		}
		//for (int a : res)
		//	std::cout << a << " ";
		//std::cout << std::endl;
		applied.push_back(res);
	}
	//finally convert all of the vectors to strings
	std::vector<std::string> result;
	for (unsigned int i = 0; i < lines; i++)
	{
		std::vector<int> pre = applied[i];
		std::string post = "";
		for (int a : pre)
			post += std::to_string(a) + " ";;
		//std::cout << post << std::endl;
		result.push_back(post);
	}

	for (std::string str : result)
		std::cout << str << std::endl;
}

void problem7()
{
	unsigned int lines = atoi(lineIn().c_str());
	std::vector<std::string> input;
	for (unsigned int i = 0; i < lines; i++)
	{
		input.push_back(lineIn());
	}
	for (unsigned int i = 0; i < lines; i++)
	{
		auto tok = getTokens(input[i]);
		std::vector<float> param = translateToFloat(tok);
		double x0 = param[0];
		double A = param[1];
		double B = param[2];
		double C = param[3];
		double M = param[4];
		double N = param[5];
		double e = param[6];
		double prev = x0;
		for (unsigned int t = 0; t < 100; t++)
		{
			x0 = C + (A * x0 + M) / (B * x0 + N);
			e = x0 - prev;
		}
		std::cout << x0 << std::endl;
	}
}

void problem8()
{
	std::vector<std::string> input;
	std::string line = lineIn();
	while (strcmp(line.c_str(), "0 0") != 0)
	{
		//loop all of the numbers
		auto tok = getTokens(line);
		auto val = translateToInt(tok);
		unsigned int num = 0;
		for (unsigned int i = val[0]; i <= val[1]; i++)
		{
			unsigned int numOn = 0;
			for (unsigned int bitIndex = 0; bitIndex < (sizeof(int) * 8); bitIndex++)
				if (testBit(i, bitIndex))
					numOn++;
			if (numOn % 2 == 0)
				num++;
		}
		std::cout << "\t\t" << num << std::endl;
		line = lineIn();
	}
}

void problem9()
{
	std::vector<std::string> input;
	std::string line = lineIn();
	std::vector<std::vector<int>> coordinates;
	while (strcmp(line.c_str(), "0 0") != 0)
	{
		//loop all of the numbers
		auto tok = getTokens(line);
		auto val = translateToInt(tok);

		coordinates.push_back(val);

		line = lineIn();
	}
	//build the skyline
	//bottom row reserved for numbers
	char printMatrix[13][60];
	//fill matrix
	for (unsigned int y = 0; y < 12; y++)
		for (unsigned int x = 0; x < 60; x++)
			printMatrix[y][x] = ' ';

	//fill the bottom row
	for (unsigned int i = 0; i < 60; i++)
		printMatrix[12][i] = std::to_string(stripToBase(i)).c_str()[0];

	for (auto coord : coordinates)
	{
		int center = coord[0];
		int height = coord[1];


		for (unsigned int y = 11; y > (11 - height); y--)
		{
			if (height > 11 - y)
			{
				printMatrix[y][center - (11 - y)] = '/';
				//printMatrix[y][center + (11 - y)] = '/';
			}
	/*		for (unsigned int x = center - height; x <= center; x++)
			{

			}
			for (unsigned int x = center - height; x <= center; x++)
			{

			}*/
		}

		//for (unsigned int y = 10; y > (10-height); y--)
		//	for (unsigned int x = center - height; x <= center + height; x++)
		//		printMatrix[y][x] = 'c';
	}

	//print the matrix
	for (unsigned int x = 0; x < 13; x++)
	{
		for (unsigned int y = 0; y < 60; y++)
			std::cout << printMatrix[x][y];
		std::cout << std::endl;
	}
}

void problem10()
{
	unsigned int lines = atoi(lineIn().c_str());
	std::vector<std::string> input;
	for (unsigned int i = 0; i < lines; i++)
	{
		input.push_back(lineIn());
	}
	std::vector<std::string> palindromes;
	for (std::string str : input)
	{
		std::vector<std::string> longest;
		std::vector<std::string> nice;
		for (unsigned int b = 0; b <= str.size(); b++)
		{
			for (unsigned int i = 0; i <= str.size(); i++)
			{
				//remove puncuation and stuffz
				std::string tmp = str.substr(b, i);
				std::string n = tmp;
				if (tmp.size() == 1 || tmp.size() == 2)
					continue;
				const char chars[] = "!\\/\"\'?.;:-=+[]()  ";

				for (unsigned int i = 0; i < strlen(chars); ++i)
				{
					tmp.erase(std::remove(tmp.begin(), tmp.end(), chars[i]), tmp.end());
				}

				for (char c : tmp)
					c = (char)tolower(c);

				//std::cout << tmp << std::endl;

				std::string rev = tmp;
				std::reverse(rev.begin(), rev.end());
				if (strcmp(tmp.c_str(), rev.c_str()) == 0)
				{
					longest.push_back(tmp);
					nice.push_back(n);
				}
			}
		}
		std::string s = "";
		std::string n = "";
		unsigned int originalSize = s.size();
		for (unsigned int i = 0; i < longest.size(); i++)
		{
			std::string test = longest[i];
			if (test.size() > s.size())
			{
				s = test;
				n = nice[i];
			}
		}
		if (s.size() == originalSize)
			n = "NO PALINDROMES";
		palindromes.push_back(n);
	}
	for (std::string str : palindromes)
		std::cout << str << std::endl;
}

void problem11()
{
	auto lineinfo = getTokens(lineIn());
	auto wordinfo = getTokens(lineIn());

	auto trlninfo = translateToInt(lineinfo);
	auto wdinfo = translateToInt(wordinfo);

	unsigned int numRows = trlninfo[0];
	unsigned int numColumns = trlninfo[1];
	unsigned int noiseThreshold = trlninfo[2];

	unsigned int numWords = wdinfo[0];
	std::vector<unsigned int> wdLengths;
	for (unsigned int i = 1; i < wdinfo.size(); i++)
		wdLengths.push_back(wdinfo[i]);

	std::vector<std::string> rows;
	for (unsigned int i = 0; i < numRows; i++)
	{
		rows.push_back(lineIn());
	}
	std::string strParsed = "";
	for (auto row : rows)
		strParsed += row;

	std::unordered_map<char, unsigned int> count;
	for (char c : strParsed)
			count[c]++;

	std::unordered_map<char, bool> toDelete;
	for (auto it : count)
		toDelete[it.first] = it.second >= noiseThreshold;

	toDelete[' '] = true;

	for (auto it : toDelete)
	{
		if (it.second == true)
		{
			strParsed.erase(std::remove(strParsed.begin(), strParsed.end(), it.first), strParsed.end());
		}
	}

	//make the rows into one long string


	std::cout << strParsed << std::endl;

	unsigned int indicesTraveled = wdLengths[0]; 

	for (unsigned int i = 1; i < wdLengths.size(); i++)
	{
		strParsed.insert(indicesTraveled, 1, ' ');
		indicesTraveled += wdLengths[i] + 1;
	}

	std::cout << strParsed << std::endl;
	/*for (auto str : finalWords)
		std::cout << str << " ";
	std::cout << std::endl;*/


	/*
	3 15 4
	4 2 3 3 9
	F L Y W B E G A L K R U B E T
	L H G E C K Y U B H L U G A F
	K Y F M P U B K F I G O N S Y
	*/
}

void problem12()
{
	//FIRST TRY OMG
	unsigned int lines = atoi(lineIn().c_str()) * 2;
	std::vector<std::string> input;
	for (unsigned int i = 0; i < lines; i++)
	{
		input.push_back(lineIn());
	}
	std::vector<std::vector<int>> tutorLevel;
	std::vector<std::vector<int>> tuteeLevel;
	for (unsigned int i = 0; i < input.size(); i++)
	{
		auto tok = getTokens(input[i]);
		auto val = translateToInt(tok);
		if (i % 2 != 0)
			tuteeLevel.push_back(val);
		else
			tutorLevel.push_back(val);
	}
	std::vector<unsigned int> weight;
	for (unsigned int i = 0; i < tutorLevel.size(); i++)
	{
		std::vector<int> tutors = tutorLevel[i];
		std::vector<int> tutees = tuteeLevel[i];

		//go through every single tutor on one line
		unsigned int totalCombo = 0;
		//1 because i forgot to do what i was supposed to do.
		for (unsigned int c = 1; c < tutors.size(); c++)
		{
			//1 because i again forgot to do what i was supposed to do.
			for (unsigned int t = 1; t < tutees.size(); t++)
				if (tutees[t] < tutors[c])
					totalCombo++;
		}
		weight.push_back(totalCombo);
	}
	std::cout << std::endl;
	for (auto i : weight)
		std::cout << i << std::endl;

	/*
	1
	3 10 11 12
	3 7 8 9
	*/

	/*
	3  
	3 10 11 12  
	3 7 8 9  
	4 2 3 4 5  
	5 5 6 7 8 9  
	9 24 27 35 38 40 47 77 79 85  
	8 14 23 29 38 45 53 64 89  
	*/
}

void problem13()
{
	//why was this one so easy?
	//first try ftw
	std::string input = lineIn();

	char dir = 'r';
	char printMatrix[100][100];

	for (unsigned int y = 0; y < 100; y++)
		for (unsigned int x = 0; x < 100; x++)
			printMatrix[y][x] = ' ';

	unsigned int posx = 50;
	unsigned int posy = 50;
	for (unsigned int i = 0; i < input.size(); i++)
	{
		char c = input[i];
		if (tolower(c) == 'l' || tolower(c) == 'r' || tolower(c) == 'u' || tolower(c) == 'd')
			dir = tolower(c);
		switch (dir)
		{
			//assume right
		default:
		case 'r':
			posx += 1;
			break;
		case 'l':
			posx -= 1;
			break;
		case 'u':
			posy -= 1;
			break;
		case 'd':
			posy += 1;
			break;
		}
		addToPrintMatrix(printMatrix, posx, posy, c);
	}

	for (unsigned int y = 0; y < 100; y++)
	{
		for (unsigned int x = 0; x < 100; x++)
			std::cout << printMatrix[y][x];
		std::cout << std::endl;
	}
	/*
	It is my humble opinion that standard text is boring. Therefore I introduce a new writing standard, walking words!
	*/
}

void problem14()
{
	std::vector<std::string> input;
	std::string line = lineIn();
	std::vector<std::vector<int>> coordinates;
	while (strcmp(line.c_str(), "0 0") != 0)
	{
		auto tok = getTokens(line);
		auto val = translateToInt(tok);
		unsigned int rows = val[0];
		unsigned int columns = val[1];
		
		unsigned int startx = 0, stopx = columns - 1, currentx = 0;
		unsigned int starty = 0, stopy = rows - 1, currenty = 0;

		std::vector<std::string> field;
		for (unsigned int i = 0; i < rows; i++)
			field.push_back(lineIn().c_str());

		unsigned int numPaths = 2;
		//check start and end
		if (field[0][0] == '#' || field[rows - 1][columns - 1] == '#')
			numPaths = 0;
		else
		{
			solveForPaths();
		}

		std::cout << numPaths << std::endl;

		/*
		4 4
		...  
		....  
		....  
		....  
		*/

		line = lineIn();
	}
}

int main()
{
	//todo: 9
	//problem9();
	problem14();
	pause();
}