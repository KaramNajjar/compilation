#include "grammar.h"
#include <iostream>
using namespace std;

bool checkIfNullable(nonterminal nonTerminal) {
	
	//checking if this non terminal derives null directly.
	cout << (int)nonTerminal << endl;
	if (nonTerminal >= 10)
		return false;

	for (int i = 0; i < grammar.size(); ++i)
		if (grammar[i].lhs == nonTerminal)
			if (grammar[i].rhs.size() == 0)
				return true;
			

	for (int i = 0; i < grammar.size(); ++i)
	{
		if (grammar[i].lhs == nonTerminal)
		{
			bool flag = true;

			for (int j = 0; j < grammar[i].rhs.size(); ++j)
			{
				if (grammar[i].rhs[j] != (int)nonTerminal)
					flag = flag && checkIfNullable((nonterminal)(grammar[i].rhs[j]));
			}
			if (flag)
				return true;		
		}
	}

	return false;
}


int main() {
	vector<bool> nullablesVec;

	for (int i = 0; i < NONTERMINAL_ENUM_SIZE; ++i) {
		nullablesVec.push_back(checkIfNullable((nonterminal)i));
	}

	print_nullable(nullablesVec);

	return 0;
}