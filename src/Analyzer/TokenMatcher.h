#pragma once
#include "qstring.h"
#include "Token.h"

class TokenMatcher
{
public:
	TokenMatcher();
	TokenMatcher(QString sentence);
	~TokenMatcher();

	QString getSentence();
	void setSentence(QString sentence);

	QString RegExMatch(QString regExType);
	// Cby: match the first matched content
	QString MatchNumber();
	// Cby: match the first word, if it's a number, return the number, or return null;
	QString MatchReservedWord();
	// Cby: match the first word, if it's a reserved word, return the reserved word, or return null;
	QString MatchVariable();
	// Cby: match the first word, if it's a variable, return the variable, or return null;
	QString MatchSymbol();
	// Cby: match the first word, if it's a symbol, return the symbol, or return null;
	QString MatchSpace();
	// Cby: match the first word, if it's a space, return the space, or return null;
	Token MatchAll();
	// Cby: match the first word, and return;

private:
	QString sentence;
};
