#include "MacroDefinition.h"
#include "TokenMatcher.h"
#include "RegularExpression.h"
#include <qstring.h>
#include <qregexp.h>

TokenMatcher::TokenMatcher(){
	this->sentence = "";
}

TokenMatcher::TokenMatcher(QString sentence){
	this->sentence = sentence;
}

TokenMatcher::~TokenMatcher(){

}

QString TokenMatcher::getSentence(){
	return this->sentence;
}

void TokenMatcher::setSentence(QString sentence){
	this->sentence = sentence;
}

QString TokenMatcher::RegExMatch(QString regExType){
	// Cby: match the first matched content
	QString pattern = "^(" + regExType + ").*$";
	QRegExp regEx(pattern);
	sentence.indexOf(regEx);

#ifdef TOKENMATCHER_REGEX_DEBUG_1

	if (sentence.indexOf(regEx) != -1)
		return regEx.cap(1);

#endif // TOKENMATCHER_REGEX_DEBUG_1

#ifdef TOKENMATCHER_REGEX_DEBUG_2

	if (regEx.cap(1) != QString::null)
		return regEx.cap(1);

#endif // TOKENMATCHER_REGEX_DEBUG_2
	
	return QString::null;
}

QString TokenMatcher::MatchNumber(){
	// Cby: match the first word, if it's a number, return the number, or return null;
	return RegExMatch(RegularExpression::number);
}

QString TokenMatcher::MatchReservedWord(){
	// Cby: match the first word, if it's a reserved word, return the reserved word, or return null;

	QString result(QString::null), *pointer = RegularExpression::arrReservedWord;

	while (pointer != QString::null) {
		if ((result = RegExMatch(*pointer)) != QString::null)
			return result;
		pointer++;
	}

	return result;
}

QString TokenMatcher::MatchVariable(){
	// Cby: match the first word, if it's a variable, return the variable, or return null;

	if (MatchReservedWord() != QString::null)
		return QString::null;

	return RegExMatch(RegularExpression::variable);
}

QString TokenMatcher::MatchSymbol(){
	// Cby: match the first word, if it's a symbol, return the symbol, or return null;

	QString result(QString::null), *pointer = RegularExpression::arrSymbol;

	while (pointer != QString::null) {
		if ((result = RegExMatch(*pointer)) != QString::null)
			return result;
		pointer++;
	}

	return result;
}

QString TokenMatcher::MatchSpace(){
	// Cby: match the first word, if it's a space, return the space, or return null;
	return RegExMatch(RegularExpression::SPACE);
}

Token TokenMatcher::MatchAll(){
	// Cby: match the first word, and return;

	QString result = MatchNumber();

	if (sentence == "" || sentence == QString::null)
		return Token("EOF", Token::EndOfFile);

	if (result != QString::null)
		return Token(result, Token::Number);
	
	if ((result = MatchReservedWord()) != QString::null)
		return Token(result, Token::ReservedWord);

	if ((result = MatchVariable()) != QString::null)
		return Token(result, Token::Variable);

	if ((result = MatchSymbol()) != QString::null)
		return Token(result, Token::Symbol);

	if ((result = MatchSpace()) != QString::null)
		return Token(result, Token::Space);

	return Token(QString("non defined token: ") + QString(sentence.at(0)), Token::Error);
}


