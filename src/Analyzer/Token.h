#pragma once
#include <qstring.h>

class Token
{
	// CBY: define the type of words, contains a two-tuples;
public:
	QString tokenContent;
	QString tokenType;
	
	static QString Number;
	static QString ReservedWord;
	static QString Variable;
	static QString Space;
	static QString Symbol;
	static QString Error;
	static QString EndOfFile;

public:
	Token();
	Token(QString, QString);
	~Token();
};