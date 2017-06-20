#pragma once
#include <qstring.h>

struct RegularExpression
{
	/******************** number ********************/
	static QString digit;
	// Cby: a digit
	static QString integral;
	// Cby: an integer;
	static QString exponent;
	// Cby: scientific notation
	static QString fraction;
	// Cby: decimal
	static QString number;
	// Cby: a number

	/******************** variable ********************/
	static QString letter;
	// Cby: a letter
	static QString suffix;
	// Cby: a suffix
	static QString variable;
	// Cby: a word

	/******************** reserved word ********************/
	static QString IF;
	static QString ELSE;
	static QString END;

	/******************** bool ********************/
	static QString TRUE;
	static QString FALSE;

	/******************** reserved function ********************/
	static QString SIN;
	static QString COS;
	static QString MAX;
	static QString MIN;
	static QString FUNC;

	/******************** operator ********************/
	static QString PLUS;
	static QString MINUS;
	static QString MUL;
	static QString DIV;
	static QString POW;

	/******************** assign ********************/
	static QString VALUE;

	/******************** logical operator ********************/
	static QString EQUAL;
	static QString NOT_EQUAL;
	static QString LESS;
	static QString GREATER;
	static QString LESSorEQUAL;
	static QString GREATERorEQUAL;
	static QString AND;
	static QString OR;
	static QString NOT;

	/******************** punctuation ********************/
	static QString COMMA;
	static QString COLON;
	static QString SEMICOLON;
	static QString LEFT_PARENTHESIS;
	static QString RIGHT_PARENTHESIS;
	static QString LEFT_BRACKET;
	static QString RIGHT_BRACKET;
	static QString LEFT_BRACE;
	static QString RIGHT_BRACE;

	/******************** space ********************/
	static QString SPACE;
	
	static QString arrReservedWord[];
	// Cby: used for saving reserved keys
	static QString arrSymbol[];
	// Cby: used for saving symbles;

};

/******************** number ********************/
QString RegularExpression::digit = "[0-9]";
QString RegularExpression::integral = digit + "+";
QString RegularExpression::exponent = "[Ee][+-]?" + integral;
QString RegularExpression::fraction = "\\." + integral;
QString RegularExpression::number = integral + "(" + fraction + ")?" + "(" + exponent + ")?";

QString RegularExpression::letter = "[A-Za-z]";
QString RegularExpression::suffix = "((" + letter + ")|(" + digit + ")|(_))+";
QString RegularExpression::variable = letter + "(" + suffix + ")?";

QString RegularExpression::IF = "if";
QString RegularExpression::ELSE = "else";
QString RegularExpression::END = "end";

QString RegularExpression::TRUE = "(true|True|TRUE)";
QString RegularExpression::FALSE = "(false|False|FALSE)";

QString RegularExpression::SIN = "sin";
QString RegularExpression::COS = "cos";
QString RegularExpression::MAX = "max";
QString RegularExpression::MIN = "min";
QString RegularExpression::FUNC = "func";

QString RegularExpression::PLUS = "\\+";
QString RegularExpression::MINUS = "\\-";
QString RegularExpression::MUL = "\\*";
QString RegularExpression::DIV = "/";
QString RegularExpression::POW = "\\^";

QString RegularExpression::VALUE = "=";

QString RegularExpression::EQUAL = "==";
QString RegularExpression::NOT_EQUAL = "!=";
QString RegularExpression::LESS = "<";
QString RegularExpression::GREATER = ">";
QString RegularExpression::LESSorEQUAL = "<=";
QString RegularExpression::GREATERorEQUAL = ">=";
QString RegularExpression::AND = "&&";
QString RegularExpression::OR = "\\|\\|";
QString RegularExpression::NOT = "!";

QString RegularExpression::COMMA = ",";
QString RegularExpression::COLON = ":";
QString RegularExpression::SEMICOLON = ";";
QString RegularExpression::LEFT_PARENTHESIS = "\\(";
QString RegularExpression::RIGHT_PARENTHESIS = "\\)";
QString RegularExpression::LEFT_BRACKET = "\\[";
QString RegularExpression::RIGHT_BRACKET = "\\]";
QString RegularExpression::LEFT_BRACE = "\\{";
QString RegularExpression::RIGHT_BRACE = "\\}";

QString RegularExpression::SPACE = " ";

QString RegularExpression::arrReservedWord[] = {
	IF,
	ELSE,
	END,

	TRUE,
	FALSE,

	SIN,
	COS,
	MAX,
	MIN,
	FUNC,

	QString::null
};

QString RegularExpression::arrSymbol[] = {
	PLUS,
	MINUS,
	MUL,
	DIV,
	POW,

	EQUAL,
	NOT_EQUAL,
	LESSorEQUAL,
	GREATERorEQUAL,
	LESS,
	GREATER,
	AND,
	OR,
	NOT,

	COMMA,
	COLON,
	SEMICOLON,
	LEFT_PARENTHESIS,
	RIGHT_PARENTHESIS,
	LEFT_BRACKET,
	RIGHT_BRACKET,
	LEFT_BRACE,
	RIGHT_BRACE,

	VALUE,

	QString::null
};