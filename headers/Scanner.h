#ifndef SCANNER_H_
#define SCANNER_H_
#include "structures/Token.h"
#include "structures/SymbolType.h"
#include "vector"
#include "string"
using namespace std;

class Scanner
{
private:
	/**
	 * It contains current analyzing sign
	 */
	char currentSign;
	/**
	 *	It contains all tokens that will be presented to parser
	 */
	vector<Token*>  tokenTable;
	/**
	 * Use to keep last n signs f.i. when we are analyzing some variable
	 */
	string buffer;
	/**
	 *	It makes possible to take next letters form the file
	 */
	Source& src;
public:
	/**
	 *	We have to use initializing list to pass Source's reference
	 */
	Scanner (Source *s):src(*s)
	{
		currentSign = '0';
	}
	/**
	 * 	Defined to avid the memory leaking problem.
	 */
	~Scanner ();
	/**
	 * 	main of this object, analyzing input stream sign after sign
	 */
	bool run();
	/**
	 *	Use some Source's method to take next sign to analyze
	 */
	char takeNextChar();
	/**
	 *	Skips all white signs
	 */
	bool skipSpace();
	/**
	 *	Add token ASCIISign
	 */
	bool addAsciiSign();
	/**
	 *	Add token Constant
	 */
	bool addConstant();
	/**
	 *	Add token Keyword
	 */
	bool addKeyword();
	/**
	 *	Add token Variable
	 */
	bool addVariable();
	/**
	 *	Add token TableReference
	 */
	bool addReferenceToTable();
	/**
	 *	It is unused because every PainText is treated as a lexical error
	 *	It may be use in future
	 */
	bool addPlainText();
	/**
	 *	It is method which use polimorfizm to write all present tokens in tokenTable
	 */
	void ShowTokens();

	void saveTokens();
};

#endif /* SCANNER_H_ */
