/*
 * ConstVar.h
 *
 *  Created on: May 27, 2016
 *      Author: kamil
 */

#ifndef CONSTANT_H_
#define CONSTANT_H_
#include <iostream>
#include <sstream>
#include <string>
using namespace std;
class Constant : public Token
{
private:
	/**
	 * it may be int or char. Either way it can be storage as a variable type int
	 */
	int value;
public:
	Constant( int line , SymbolType symType, int val)
	{
		this->value = val;
		this->symbolType = symType;
		this->lineInDocument = line;
	}

	void toWrite()
	{
		cout<<"<Constant: \""<<value<<"\">"<<endl;
	}
	string getPhrase()
	{
		stringstream stream;
		string ret;
		stream << value;
		stream >> ret;
		return ret;
	}
};

#endif /* CONSTANT_H_ */
