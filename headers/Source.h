#ifndef SOURCE_H_
#define SOURCE_H_

#include <stdio.h>
#define MAX_LINE 101

class Source
{
private:
	char *fileName;
	FILE *filePointer;
	char Line[MAX_LINE+1];
	int	lineOfDocument , positionInLine;
public:

    Source(const char *file);
    ~Source();

    int nextChar();
    int nextLine();
    char getCharFromLine();
    char* printLine();
    int getNumberOfLine();

};

#endif /* SOURCE_H_ */
