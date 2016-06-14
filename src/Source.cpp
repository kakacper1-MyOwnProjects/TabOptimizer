#include "../headers/Source.h"
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <string>
#define MAX_LINE 101

using namespace std;

Source:: Source( const char *file )
{
	int length = strlen(file);
    strcpy(fileName = new char[length+1], file);
    filePointer = fopen( fileName , "r" );
    lineOfDocument = 0;
    positionInLine = 0;
    endOfLine = false;
}

Source:: ~Source()
{
	fclose(filePointer);
	delete [] fileName;
}

char Source:: getCharFromLine()
{
	if(endOfLine==true)
		if(!nextLine())
			return EOF;

	positionInLine++;
	if(line[positionInLine]=='\n')
		endOfLine = true;
	return line[positionInLine];
}

int Source:: getNumberOfLine()
{
	return lineOfDocument;
}

char* Source:: getWholeLine()
{
	return line;
}

int Source:: nextLine()
{
	if(!fgets(line, MAX_LINE, filePointer))
		return 0;
	endOfLine = false;
	lineOfDocument++;
	positionInLine=-1;
	return 1;
}

bool Source:: isOpenSource()
{
	if(!filePointer)
	{
		cout<<"Source: Fatal error - cannot open the file \n";
		return 1;
	}
	else
	{
		cout<<"Source: Successfully opened the file \n";
		nextLine();
		return 0;
	}
}

bool Source:: isEndOfLine()
{
	return endOfLine;
}

void Source:: writeError( string errorPhrase )
{
	cout<<"\nError has occurred. Unexpected phrase:"<<errorPhrase<<" in line number "<<lineOfDocument<<endl;
	cout<<lineOfDocument<<". "<<line;
	for(int i = -4; i < positionInLine; ++i )
		cout<<" ";
	cout<<"^"<<endl;
}

