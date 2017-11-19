#include "grammar.h"
using namespace std;

bool checkIfNullable(grammar_rule nonTerminal){
	
	
	//checking if this non terminal derives null directly.
	vector<int> _rhs = nonTerminal->rhs;
	
	
	for(
	
	return true;
	
	
	
	
	
}







int main(){
	
	vector<bool> nullablesVec;
	
	for(int i = 0; i < NONTERMINAL_ENUM_SIZE; ++i) {
		
		nullablesVec.push_back(nullablesVec[grammar[i]] || checkIfNullable(grammar[i]));
	}
	
	print_nullable(nullablesVec);
	
	
	
	return 0;
}