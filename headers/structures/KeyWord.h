#ifndef KEYWORD_H_
#define KEYWORD_H_
#include <string>
using namespace std;
class KeyWord : public Token
{
private:
	/**
	 * 	It contains specific keyword and sometime  some another chars connected to this keyword
	 */
	string stringPhrase;

public:

	KeyWord( int line , SymbolType symType, string strPhr )
	{
		this->stringPhrase = strPhr;
		this->symbolType = symType;
		this->lineInDocument = line;
	}

	void toWrite()
	{
		cout<<"<KeyWord: \""<<stringPhrase<<"\">"<<endl;
	}
	string getPhrase()
	{
		return stringPhrase;
	}
};
#endif /* KEYWORD_H_ */
