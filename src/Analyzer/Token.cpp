#include "Token.h"
#include <qstring.h>

QString Token::Number = "Number";
QString Token::ReservedWord = "ReservedWord";
QString Token::Variable = "Variable";
QString Token::Space = "Space";
QString Token::Symbol = "Symbol";
QString Token::Error = "Error";
QString Token::EndOfFile = "";

Token::Token(){
	this->tokenContent = "";
	this->tokenType = "";
}

Token::Token(QString tokenContent, QString tokenType){
	this->tokenContent = tokenContent;
	this->tokenType = tokenType;
}

Token::~Token(){

}