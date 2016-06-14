
#ifndef AACIISIGN_H_
#define AACIISIGN_H_
#include <iostream>
#include <string>
#include <sstream>
using namespace std;
class AsciiSign : public Token
{
private:
	/**
	 * Only one sign it is enough to tell everything about this kind of token
	 */
	char asciiSign;
public:
	AsciiSign( int line , SymbolType symType, char asciiSign)
	{
		this->asciiSign = asciiSign;
		this->symbolType = symType;
		this->lineInDocument = line;
	}
	void toWrite()
	{
		cout<<"<ASCIISign: \""<<asciiSign<<"\">"<<endl;
	}
	string getPhrase()
	{
		stringstream stream;
		string ret;
		stream << asciiSign;
		stream >> ret;
		return ret;
	}
};

#endif /* AACIISIGN_H_ */
