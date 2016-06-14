#include "../headers/Source.h"
#include "../headers/Scanner.h"
#include "../headers/structures/AsciiSign.h"
#include "../headers/structures/Constant.h"
#include "../headers/structures/SymbolType.h"
#include "../headers/structures/KeyWord.h"
#include "../headers/structures/Variable.h"
#include "../headers/structures/TableReference.h"
#include "../headers/structures/PlainText.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream>

using namespace std;

Scanner:: ~Scanner ()
{
	delete[] &tokenTable;
}
/**
 * As we can seethe only time when we are taking next char is at the start
 * Every another time we are taking them on demand in following function in other way
 * At the end of this method where there was no function which could recognize token we are reporting error
 */
bool Scanner:: run()
{
	takeNextChar();
	while(currentSign!=EOF)
	{
		if(skipSpace())
			continue;
		if(addAsciiSign())
			continue;
		if(addConstant())
		{
			if(buffer.empty())
				continue;
			else
			{
				src.writeError(buffer);
				return 0;
			}
		}
		if(addKeyword())
			continue;
		if(addVariable())
			continue;
		if(addReferenceToTable())
			continue;
		src.writeError(buffer);
		return 0;
	}
	return 1;
}
/**
 * This method takes another sign from the Source
 */
char Scanner:: takeNextChar()
{
	currentSign = src.getCharFromLine();
	cout<< currentSign;
	return currentSign;
}
/**
 * This method skips the white signs
 */
bool Scanner:: skipSpace()
{
	if(isspace(currentSign))
	{
		takeNextChar();
		return 1;
	}
	else
		return 0;
}
/**
 * 	This is the first method, which can create a token.
 * 	We start with the smallest ones. ( One sign )
 * 	It returns 1 if we created a token and 0 if not
 */
bool Scanner:: addAsciiSign()
{
	AsciiSign* tmp;
	switch(currentSign)
	{
	case '+':
		tmp  = new AsciiSign(src.getNumberOfLine(), plus_o , '+');
		tokenTable.push_back(tmp);
		break;
	case '-':
		tmp  = new AsciiSign(src.getNumberOfLine(), minus_o , '-');
		tokenTable.push_back(tmp);
		break;
	case '*':
		tmp  = new AsciiSign(src.getNumberOfLine(), star_o , '*');
		tokenTable.push_back(tmp);
		break;
	case '/':
		tmp  = new AsciiSign(src.getNumberOfLine(), div_o , '/');
		tokenTable.push_back(tmp);
		break;
	case ';':
		tmp  = new AsciiSign(src.getNumberOfLine(), semicolon , ';');
		tokenTable.push_back(tmp);
		break;
	case '=':
		tmp  = new AsciiSign(src.getNumberOfLine(), equal_o , '=');
		tokenTable.push_back(tmp);
		break;
	case '(':
		tmp  = new AsciiSign(src.getNumberOfLine(), l_parentheses , '(');
		tokenTable.push_back(tmp);
		break;
	case ')':
		tmp  = new AsciiSign(src.getNumberOfLine(), r_parentheses , ')');
		tokenTable.push_back(tmp);
		break;
	case '{':
		tmp  = new AsciiSign(src.getNumberOfLine(), l_braces , '{');
		tokenTable.push_back(tmp);
		break;
	case '}':
		tmp  = new AsciiSign(src.getNumberOfLine(), r_braces , '}');
		tokenTable.push_back(tmp);
		break;
	case '[':
		tmp  = new AsciiSign(src.getNumberOfLine(), l_bracket , '[');
		tokenTable.push_back(tmp);
		break;
	case ']':
		tmp  = new AsciiSign(src.getNumberOfLine(), r_bracket , ']');
		tokenTable.push_back(tmp);
		break;
	default:
		return 0;
	}
	takeNextChar();
	return 1;
}
/**
 * Second class of token represents all constant. We take the digits to a string and then we makes an int variable
 *  If the identifier will be like "111dsds" - it will report error. First it put the content to the buffer
 *  and then we will check if there is sth in this buffer Yes- Error No-Go ahead!
 */
bool Scanner:: addConstant()
{
	buffer.clear();
	Constant* tmp;
	string numStr;
	int value;
	if(isdigit(currentSign))
	{
		while(isdigit(currentSign) )
		{
			numStr += currentSign;
			takeNextChar();
		}
		if(!isalpha(currentSign))
		{
			value = strtol(numStr.c_str(), 0, 10);
			tmp = new Constant(src.getNumberOfLine(), int_const , value);
			tokenTable.push_back(tmp);
		}
		else
			buffer = numStr;
		return 1;
	}
	else
		return 0;
}
/**
 * Third class of token represents all keywords. That is why it is soo big.
 * First we check if this is a directive to the preprocessor. If not we take all alphanumeric
 * char and then we compare if it fits to some keyword. At the end we add it to a buffer.
 */
bool Scanner:: addKeyword()
{
	KeyWord *tmp;
	string keyPhrase;

	if(currentSign == '#')
	{
		buffer += currentSign;
		takeNextChar();
		if(currentSign == 'i') //
		{
			while(currentSign != '\n')
			{
				buffer += currentSign;
				takeNextChar();
			}
			keyPhrase = buffer;
			tmp = new KeyWord(src.getNumberOfLine(), include_s , keyPhrase);
			tokenTable.push_back(tmp);
			takeNextChar();
		}
		else // zakładam ze to define
		{
			while(currentSign != ' ')
			{
				buffer += currentSign;
				takeNextChar();
			}
			keyPhrase = buffer;
			tmp = new KeyWord(src.getNumberOfLine(), define_s , keyPhrase);
			tokenTable.push_back(tmp);
			takeNextChar();
		}
		return 1;
	}
	while(isalpha(currentSign))
	{
		buffer += currentSign;
		takeNextChar();
	}
	if(buffer == "else")
	{
		keyPhrase = buffer;
		tmp = new KeyWord(src.getNumberOfLine(), if_s , keyPhrase);
		tokenTable.push_back(tmp);
		takeNextChar();
		return 1;
	}
	if(buffer == "return")
	{
		keyPhrase = buffer;
		tmp = new KeyWord(src.getNumberOfLine(), return_s , keyPhrase);
		tokenTable.push_back(tmp);
		takeNextChar();
		return 1;
	}
	if(buffer == "using")
	{
		while(currentSign != '\n')
		{
			buffer += currentSign;
			takeNextChar();
		}
		keyPhrase = buffer;
		tmp = new KeyWord(src.getNumberOfLine(), using_s , keyPhrase);
		tokenTable.push_back(tmp);
		return 1;
	}
	if(buffer == "int")
	{
		keyPhrase = buffer;
		tmp = new KeyWord(src.getNumberOfLine(), int_s , keyPhrase);
		tokenTable.push_back(tmp);
		takeNextChar();
		return 1;
	}
	if( currentSign == '(' || currentSign == ' ')
	{
		if(buffer == "if")
		{
			while(currentSign != ')')
			{
				buffer += currentSign;
				takeNextChar();
			}
			buffer += currentSign;
			keyPhrase = buffer;
			tmp = new KeyWord(src.getNumberOfLine(), if_s , keyPhrase);
			tokenTable.push_back(tmp);
			takeNextChar();
			return 1;
		}
		if(buffer == "for")
		{
			while(currentSign != ')')
			{
				buffer += currentSign;
				takeNextChar();
			}
			buffer += currentSign;
			keyPhrase = buffer;
			tmp = new KeyWord(src.getNumberOfLine(), for_s , keyPhrase);
			tokenTable.push_back(tmp);
			takeNextChar();
			return 1;
		}
		if(buffer == "main")
		{
			while(currentSign != ')')
			{
				buffer += currentSign;
				takeNextChar();
			}
			buffer += currentSign;
			keyPhrase = buffer;
			tmp = new KeyWord(src.getNumberOfLine(), main_s , keyPhrase);
			tokenTable.push_back(tmp);
			takeNextChar();
			return 1;
		}
	}
	return 0;
}
/**
 * Forth step check if string in buffer fits to be a identifier of a variable.
 * We take all digits and alphanumeric signs that were left and then we create a VAriable token
 */
bool Scanner:: addVariable()
{
	Variable* tmp;
	string nameOfIdent;
	while(isdigit(currentSign) || isalpha(currentSign) )
	{
		buffer += currentSign;
		takeNextChar();
	}
	if( isspace(currentSign) || currentSign==';' || currentSign == ']' || currentSign == '+'
			|| currentSign == '-' || currentSign == '*' || currentSign == '/' || currentSign == '=' )
	{
		nameOfIdent = buffer;
		tmp = new Variable(src.getNumberOfLine(), identyficator , nameOfIdent);
		tokenTable.push_back(tmp);
		return 1;
	}
return 0;
}
/**
 * Fifth step check if string in buffer fits to be a reference to the table.
 * The only condition for this is that the next char must be a '[' or a blank space.
 */
bool Scanner:: addReferenceToTable()
{
	TableReference* tmp;
	string nameOfIdent;
	while(isspace(currentSign))
		takeNextChar();
	if(currentSign == '[')
	{
		nameOfIdent = buffer;
		tmp = new TableReference(src.getNumberOfLine(), ref_to_table , nameOfIdent);
		tokenTable.push_back(tmp);
		return 1;
	}
	else
		return 0;
}
/**
 * The last step is that we add it as a plain text. Probably it will not be use
 * because we always report some errors.
 */
bool Scanner:: addPlainText()
{
	PlainText* tmp;
	string plainText;
	plainText = buffer;

	while(isalnum(currentSign))
	{
		plainText += currentSign;
		takeNextChar();
	}

	tmp = new PlainText(src.getNumberOfLine(), plain_text , plainText);
	tokenTable.push_back(tmp);
	takeNextChar();
	return 1;

}
/**
 * This method displays on the console what token are in tokenTable.
 */
void Scanner:: ShowTokens()
{
	for(unsigned int i = 0; i<tokenTable.size(); i++)
		tokenTable[i]->toWrite();
}


void Scanner:: saveTokens()
{	int line = 0;
	ofstream saveToFile("/home/kamil/Desktop/cd1/answers.cpp");
	for(unsigned int i = 0; i<tokenTable.size(); i++)
	{
		while(tokenTable[i]->getLineOfDocument() != line)
		{
			saveToFile<<"\n";
			++line;
		}
			saveToFile<<tokenTable[i]->getPhrase()<<" ";
	}
		saveToFile.close();
}
