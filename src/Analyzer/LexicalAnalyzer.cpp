#include "LexicalAnalyzer.h"
#include <qregexp.h>
#include <qlist.h>

LexicalAnalyzer::LexicalAnalyzer(){
	this->command = "";
	this->tokenMatcher = TokenMatcher();
}

LexicalAnalyzer::LexicalAnalyzer(QString command){
	this->command = command;
	this->tokenMatcher = TokenMatcher();
}

LexicalAnalyzer::~LexicalAnalyzer(){

}

void LexicalAnalyzer::setCommand(QString command){
	this->command = command;
}

QString LexicalAnalyzer::getCommand(){
	return this->command;
}

QString LexicalAnalyzer::PreProcess(){
	// Cby: sentence preprocess;
	QString processedCommand = this->command;
	processedCommand = processedCommand.replace(QRegExp("[\\s]+"), " ");
	return processedCommand + " ";
}

int LexicalAnalyzer::GetNextState(QString tokentype){
	// Cby: decided next value based on token
	int len(0);
	while (DFA[0][len] != QString::null)
		len++;
	for (int i = 1; i < len; i++) {
		if (tokentype == DFA[0][i]) {
			return i;
		}
	}
	return 0;
}

bool LexicalAnalyzer::isNumeric(QString str){
	// Cby: decided if the string is a number
	QRegExp regEx("([0-9]*)");
	str.indexOf(regEx);
	if (regEx.cap(1) == "")
		return false;
	return true;
}

QList<Token> LexicalAnalyzer::SentenceScanner(){
	// Cby: lexical analyzer, analyze lexical and return a list to store token

	QList<Token> arrToken = QList<Token>();
	QString sentence = this->command;
	tokenMatcher.setSentence(sentence);

	if (sentence == "" || sentence == QString::null){
		arrToken.append(Token("NO COMMAND SENTENCE", Token::Error));
		return arrToken;
	}

	QString curSentence = PreProcess();
	// Cby: define current on-matching sentence
	QString nextSentence = "";
	// Cby: define current available sentence
	Token curToken = Token();
	// Cby: current token
	Token nextToken = Token();
	// Cby: next token
	QString curTokenStr = "";
	// Cby: current matched string
	int curSTATE = 1;
	// Cby: current dfa state
	int nextSTATE;
	// Cby: next dfa state

	while (!(curSentence == "" || curSentence.length() == 0)) {
		tokenMatcher.setSentence(curSentence);
		nextToken = tokenMatcher.MatchAll();

		if (nextToken.tokenType == Token::Error) {
			arrToken.append(Token(nextToken.tokenContent, Token::Error));
			return arrToken;
		}

		nextSTATE = GetNextState(nextToken.tokenType);
		QString jumpMsg = DFA[curSTATE][nextSTATE];

		if (isNumeric(jumpMsg)) {
			curSTATE = jumpMsg.toInt();
			curTokenStr += nextToken.tokenContent;
			int len1 = nextToken.tokenContent.length();
			int len2 = curSentence.length();
			curSentence = curSentence.mid(len1, len2 - len1);
		}
		else {
			QStringList tokenMsg = jumpMsg.split("#");
			if (tokenMsg[0] == Token::Error) {
				arrToken.append(Token(tokenMsg[1] + " : " + curTokenStr + nextToken.tokenContent, Token::Error));
				return arrToken;
			}
			arrToken.append(Token(curTokenStr, tokenMsg[1]));
			curSTATE = 1;
			curTokenStr = "";
		}
	}
	for (int i = 0; i < arrToken.size(); i++) {
		if (arrToken.at(i).tokenType == Token::Space) {
			arrToken.removeAt(i);
			i--;
		}
	}
	return arrToken;
}

