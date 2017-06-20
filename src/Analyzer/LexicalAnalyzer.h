#pragma once
#include <qstring.h>
#include "TokenMatcher.h"

class LexicalAnalyzer
{
	// Cby: lexical analyzer
private:
	QString command;
	TokenMatcher tokenMatcher;

public:
	LexicalAnalyzer();
	LexicalAnalyzer(QString command);
	~LexicalAnalyzer();

	QString DFA[9][9] = {
		// Cby: DFA table
		{ "0", Token::Number, Token::ReservedWord, Token::Variable, Token::Symbol, Token::Space, Token::EndOfFile, Token::Error, QString::null},
		{ "1", "2", "3", "4", "5", "6", "7", "8" },
		{ "2", "Error#wrong number", "Error#wrong variable name", "Error#wrong variable name", "Token#Number", "Token#Number", "Token#Number", "Error#Error", QString::null },
		{ "3", "4", "4", "4", "Token#ReservedWord", "Token#ReservedWord",  "Token#ReservedWord", "Error#Error", QString::null },
		{ "4", "4", "4", "4", "Token#Variable", "Token#Variable", "Token#Variable", "Error#Error", QString::null },
		{ "5", "Token#" + Token::Symbol, "Token#" + Token::Symbol, "Token#" + Token::Symbol, "Token#" + Token::Symbol, "Token#" + Token::Symbol, "Token#" + Token::Symbol, "Token#" + Token::Symbol, QString::null },
		{ "6", "Token#" + Token::Space, "Token#" + Token::Space, "Token#" + Token::Space, "Token#" + Token::Space, "Token#" + Token::Space, "Token#" + Token::Space, "Token#" + Token::Space, QString::null },
		{ "7", "Token#" + Token::EndOfFile, "Token#" + Token::EndOfFile, "Token#" + Token::EndOfFile, "Token#" + Token::EndOfFile, "Token#" + Token::EndOfFile, "Token#" + Token::EndOfFile, "Token#" + Token::EndOfFile, QString::null },
		{ "8", "Token#" + Token::Error, "Token#" + Token::Error, "Token#" + Token::Error, "Token#" + Token::Error, "Token#" + Token::Error, "Token#" + Token::Error, "Token#" + Token::Error, QString::null }
	};

	void setCommand(QString command);
	QString getCommand();

	QString PreProcess();
	// Cby: sentence preprocess;

	int GetNextState(QString tokentype);
	// Cby: decided next value based on token

	bool isNumeric(QString str);
	// Cby: decided if the string is a number

	QList<Token> SentenceScanner();
	// Cby: lexical analyzer, analyze lexical and return a list to store token


};