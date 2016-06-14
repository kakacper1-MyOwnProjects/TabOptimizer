#include "../headers/structures/Token.h"
#include "../headers/structures/Variable.h"
#include "../headers/Source.h"
#include "../headers/Scanner.h"
#include <iostream>
#include <string.h>
#include <vector>
using namespace std;
#define MAX_LINE 101

/**
 * 	What type of path we use:
 * /home/kamil/Desktop/cd1/Source.cpp
 * /home/kamil/Desktop/cd1/bug.cpp
 * /home/kamil/Desktop/cd1/newSource.cpp
 */

int main()
{
	char  nameOfFile[MAX_LINE];
	cout << "Type path of the source file:\n";
	cin>>nameOfFile;
	Source* src = new Source(nameOfFile);
	if( src->isOpenSource()  )
	{
		cout<<"Program could not open a file"<<endl ;
		return 1;
	}
	Scanner* scanner = new Scanner(src);
	if(scanner->run())
	{
		scanner->ShowTokens();
		scanner->saveTokens();
	}
	else
		cout<<"Program is finished";

	delete scanner;
	delete src;
	return 0;
	}

