#ifndef VARIABLE_H_
#define VARIABLE_H_
#include "Token.h"
#include <string>
#include <iostream>
using namespace std;
class Variable : public Token
{
private:
	string ident;
	/**
	 * Store the current value of variable
	 */
	int currentValue;
	/**
	 * this value determine if we can trust the currentValue or it was impossible to predict
	 */
	bool dirty;
public:
	Variable( int line , SymbolType symType, string sym)
	{
		this->ident = sym;
		this->symbolType = symType;
		this->lineInDocument = line;
		this->currentValue = 0;
		this->dirty = false;
	}

	void toWrite()
	{
		cout<<"<Variable: \""<<ident<<"\">"<<endl;
	}
	string getPhrase()
	{
		return ident;
	}
};
#endif /* VARIABLE_H_ */
