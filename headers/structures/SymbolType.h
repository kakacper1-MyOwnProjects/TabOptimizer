/*
 * SymbolType.h
 *
 *  Created on: May 29, 2016
 *      Author: kamil
 */

#ifndef SYMBOLTYPE_H_
#define SYMBOLTYPE_H_

/**Use  to sign what type of tokens are the code statement
 * 1.line contains keywords type of token
 * 2. and 3.line contains all ASCII signs
 * 4. line contains declaration statement and directives to the preprocessor
 * 5. line contains identyficator to the variable
 */
enum SymbolType
{ 	if_s, for_s, else_s, main_s, int_s, char_s, using_s, return_s,
	l_parentheses, r_parentheses, l_bracket, r_bracket, l_braces, r_braces,
	plus_o, minus_o, star_o, div_o, semicolon, equal_o,
	define_s, include_s, int_const, char_const,
	plain_text, ref_to_table, identyficator,
};


#endif /* SYMBOLTYPE_H_ */
