#ifndef TOKEN_H_
#define TOKEN_H_
#include "SymbolType.h"
#include <string>
using namespace std;
/**
 * Virtual class that make convenient for us to use polymorphism
 */
class Token
{
protected:
	/**
	 * Each token has to have lineInDocument to generate code in proper way
	 * It may be use to handle multiple errors: Now we check only first one
	 */
	int lineInDocument;
	/**
	 * It is used by parser to determine if there is no semantic error and to keep symbol table always accurate.
	 */
	int range;
	/**
	 * It is used by parser to check semantic order.
	 */
	SymbolType symbolType;
public:
	/**
	 * Initializing default values
	 */
	Token()
	{
		lineInDocument = 0;
		symbolType  = plain_text;
		range = 0;
	};
	/**
	 * virtual method use to write all tokens to console [DEBUG/PRESENTATION]
	 */
	virtual void toWrite() = 0;
	/**
	 * virtual method use to generate all tokens to save it in new file;
	 */
	virtual string getPhrase() = 0;
	int getLineOfDocument()
	{
		return lineInDocument;
	}
	/**
	 * Virtual destructor is use to allow class to erase entirely
	 */
	virtual ~Token() {};
};

#endif /* TOKEN_H_ */
