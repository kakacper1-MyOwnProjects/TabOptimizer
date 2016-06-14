#ifndef SOURCE_H_
#define SOURCE_H_
#define MAX_LINE 101
#include<string>
#include <stdio.h>
using namespace std;
class Source
{
private:
	/**
	 *	flag using to tell when is time to take next line of document
	 */
	bool endOfLine;
	/**
	 *	it contains current document line
	 */
	char line[MAX_LINE+1];
	/**
	 *	it contains all path to the file we are analyzing
	 */
	char *fileName;
	/**
	 *	it is a pointer to the file
	 */
	FILE *filePointer;
	/**
	 *	current line of file we are analyzing
	 */
	int	lineOfDocument;
	/**
	 * current sign in analyzing line
	 */
	int positionInLine;
public:
	/**
	 * The only proper way to create this object is to pass him a path to file
	 */
    Source(const char *file);
    /**
     *	default destructor and some delete operations
     */
    ~Source();
    /**
     *	Usually use by Scanner to take next char form line
     */
    char getCharFromLine();
    /**
     *	Use by scanner to create tokens and when we write erors
     */
    int getNumberOfLine();
    /**
     *	Provides a pointer to whole line
     */
    char* getWholeLine();
    /**
     *	This method runs when we hit end of analyzing line
     */
    int nextLine();
    /**
     *	Check if file has been properly opened
     */
    bool isOpenSource();
    /**
     *	Check if we hit end of line
     */
    bool isEndOfLine();
    /**
     *	Use to write full information about an error
     */
    void writeError( string );

};

#endif /* SOURCE_H_ */
