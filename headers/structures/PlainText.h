
#ifndef PLAINTEXT_H_
#define PLAINTEXT_H_
#include "Token.h"
#include <string>
#include <iostream>
using namespace std;
class PlainText : public Token
{
private:
	/**
	 * If this will be use it will be just rewrite so string it is enough
	 */
	string plainText;
public:
	PlainText( int line , SymbolType symType, string sym)
	{
		this->plainText = sym;
		this->symbolType = symType;
		this->lineInDocument = line;
	}
	void toWrite()
	{
		cout<<"<PlainText: \""<<plainText<<"\">"<<endl;
	}
	string getPhrase()
	{
		return plainText;
	}
};
#endif /* PLAINTEXT_H_ */
