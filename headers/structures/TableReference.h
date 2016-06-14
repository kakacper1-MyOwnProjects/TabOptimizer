#ifndef TABLEREFERENCE_H_
#define TABLEREFERENCE_H_
#include "Token.h"
#include <string>
#include <iostream>
using namespace std;

class TableReference : public Token
{
private:
	/**
	 * Store the name of variable
	 */
	string ident;
	/**
	 * this value determine if we may to optimize this object or we should leave it as it is
	 */
	bool ableToOptimize;
public:
	TableReference( int line , SymbolType symType, string sym)
	{
		this->ident = sym;
		this->symbolType = symType;
		this->lineInDocument = line;
		this->ableToOptimize = true;
	}

	void toWrite()
	{
		cout<<"<TableReference: \""<<ident<<"\">"<<endl;
	}
	string getPhrase()
	{
		return ident;
	}
};
#endif /* TABLEREFERENCE_H_ */
