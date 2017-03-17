#include "Util.hpp"
#include <fstream>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <cstdlib>
using namespace std;

int stringToInt(string str) {
	stringstream ss;
	int i;
	ss << str;
	ss >> i;
	return i;
}

string intToString(int i) {
	stringstream ss;
	ss << i;
	return ss.str();
}

map<string,string> loadXML(string file) {
	ifstream input(file.c_str());
	map<string,string> ret;
	vector<string> nameStack;
	string temp;
	unsigned int i = 0;

	enum {
		WaitingTag,
		ReadingOpenTag,
		ReadingCloseTag,
		ReadingData
	}state = WaitingTag;

	while (input.good()) {
		char c = input.get();

		switch (state) {
		case WaitingTag:
			if (c=='<') {
				c = input.peek();
				if (c=='/') {
					input.get();
					state = ReadingCloseTag;
				}
				else
					state = ReadingOpenTag;
			}
			break;

		case ReadingOpenTag:
			if (c=='>') {
				nameStack.push_back(temp);
				temp.clear();
				c = input.peek();
				if (isalnum(c))
					state = ReadingData;
				else
					state = WaitingTag;
			}
			else
				temp.push_back(c);
			break;

		case ReadingCloseTag:
			if (c=='>') {
                for (i = 0; i<nameStack.size(); ++i) {
					if (nameStack[i]==temp) {
						nameStack.erase(nameStack.begin()+i);
						i--;
					}
                }
                temp.clear();
                if (isalnum(c))
					state = ReadingData;
				else
					state = WaitingTag;
			}
			else
				temp.push_back(c);
			break;

		case ReadingData:
            if (c!='<')
				temp.push_back(c);
			else {
				file.clear();
				for (i = 0; i<nameStack.size(); ++i)
					file += nameStack[i]+".";
				file.erase(file.size()-1); //erase last '.'
				ret.insert(make_pair(file,temp));
				temp.clear();
				c = input.peek();
				if (c=='/') {
					input.get();
					state = ReadingCloseTag;
				}
				else
					state = ReadingOpenTag;
			}
			break;

		default:
			cout << "Error in loadXML\n";
			break;
		}
	}

	return ret;
}

void loadTerritoryCSV(vector<Territory>& territoryVec, string file) {
	ifstream input(file.c_str());
	Territory ter;
	string temp;

	getline(input,temp); //ignore line with labels
	while (input.good()) {
		getline(input,temp,','); //id
		ter.GameData.id = stringToInt(temp);

		getline(input,ter.GameData.name,','); //name
		if (!input.good())
			break;

		getline(input,temp,','); //continent
		ter.GameData.continentId = stringToInt(temp);

		getline(input,temp,','); //x
		ter.GameData.x = stringToInt(temp);

		getline(input,temp,','); //y
		ter.GameData.y = stringToInt(temp);

		getline(input,temp,','); //crop production
		ter.ConstData.baseCropProduction = stringToInt(temp);

		getline(input,temp,','); //industry production
		ter.ConstData.baseIndustrialProduction = stringToInt(temp);

		//neighbors
        ter.GameData.neighbors.clear();
		for (int i = 0; i<5; ++i) {
			getline(input,temp,',');
			if (temp.size()==0)
				continue;
			ter.GameData.neighbors.push_back(stringToInt(temp));
		}
		getline(input,temp);
		if (temp.size()!=0)
			ter.GameData.neighbors.push_back(stringToInt(temp));

		territoryVec.push_back(ter);
	}
}

void loadContinentCSV(vector<Continent>& conVec, string file) {
	ifstream input(file.c_str());
	Continent temp;
	string s;

	getline(input,s); //ignore line with labels
	while (input.good()) {
		getline(input,s,','); //id
		temp.id = stringToInt(s);

		getline(input,temp.name,','); //name
		if (!input.good())
			break;

		getline(input,s,','); //troop bonus
		temp.troopBonus = stringToInt(s);

		getline(input,s,','); //moral boost
		temp.moralBoost = stringToInt(s);

		getline(input,s); //moral hurt
		temp.moralDamage = stringToInt(s);

		conVec.push_back(temp);
	}
}

int getRandom(int mn, int mx) {
	return (rand()%(mx-mn)+mn);
}
