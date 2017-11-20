#include "grammar.h"
#include <iostream>
#include <algorithm>

using namespace std;




vector<bool> nullablesVec;
vector< set<tokens> > firstVec;


/*
******************************* FIND NULLABES ALGORITHM ****************************
*/
bool checkIfNullable(nonterminal nonTerminal) {
	
	//checking if this non terminal derives epsilon directly.
	if (nonTerminal >= 10)
		return false;

	for (int i = 0; i < grammar.size(); ++i)
		if (grammar[i].lhs == nonTerminal)
			if (grammar[i].rhs.size() == 0)
				return true;
			
	//checking if this non terminal derives epsilon un-directly; means all its rhs nonterminal should 
	//derive epsilon.
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
/*
*******************************FIRST FUNCTION ALGORITHM*****************************
*/
void initNonTerminals(){
	set<tokens> s;
	for (int i = 0;i < NONTERMINAL_ENUM_SIZE ; i++)
		firstVec.push_back(s);
}

void getFirstTerminalsFor(nonterminal nonTerminal){
	
	
	for (int i = 0; i < grammar.size(); ++i)
		if (grammar[i].lhs == nonTerminal)
			// here we find the current nonterminal at the left side of rule
			for (int j = 0; j < grammar[i].rhs.size(); ++j){
				int token = grammar[i].rhs[j];
				
				if(token == nonTerminal){ // if the same and nullabe so continue
					if(nullablesVec[token] == true)
						continue;
				}
				//checking if token is terminal
				if(token >= NONTERMINAL_ENUM_SIZE) {
					firstVec[nonTerminal].insert((tokens)token);
					break;
					
				}else{
					//token is non-terminal, so unify nonterminal firsts with current token firsts.
					firstVec[(int)nonTerminal].insert(firstVec[token].begin(),firstVec[token].end());
					//check if token isn't nullable , if so break ; else continue
					if(nullablesVec[token] == false)
						break;
					
				}
			}
}

bool vectorsAreEqual(vector< set<tokens> > prevFirstVec){
	
	
	for (int i = 0; i < NONTERMINAL_ENUM_SIZE; ++i){
		    
		set<tokens> diff;

		set_symmetric_difference(prevFirstVec[i].begin(), prevFirstVec[i].end(), firstVec[i].begin(), firstVec[i].end(),inserter(diff, diff.begin()));
		
		if(!diff.empty())
			return false;
	}
	
	return true;
}


/*
************************************ MAIN FUNCTION *********************************
*/
int main() {

	//filling nullablesVec values.
	for (int i = 0; i < NONTERMINAL_ENUM_SIZE; ++i) {
		nullablesVec.push_back(checkIfNullable((nonterminal)i));
	}

	// now we implement the algorithm of which we calc first function foreach non-terminal
	//step 0 : already done above ; calculating nullable non-terminals.
	
	//algorithm step 1 : 
		//induction basis: Init all non-terminals with an empty set of terminals.
	initNonTerminals();
	
		//inductive step: calculate new terminals as long as we find new terminals.
	
	bool areEqual = false;
	do{
		vector< set<tokens> > prevFirstVec(firstVec);
		
		for (int i = 0; i < NONTERMINAL_ENUM_SIZE; ++i)
			getFirstTerminalsFor((nonterminal)i);

		areEqual = vectorsAreEqual(prevFirstVec);
		
	}while(areEqual == false);
	

	
	
	print_nullable(nullablesVec);
	print_first(firstVec);
	

	return 0;
}