#pragma once

#include "Token.h"
#include "ReturnMsg.h"
#include <qlist.h>
#include <qstack.h>
#include <qhash.h>
#include <Tensor.h>

class SyntacticAnalyzer
{
public:
	SyntacticAnalyzer();
	SyntacticAnalyzer(QString sentence);
	~SyntacticAnalyzer();

public:
	QString sentence;
	// Cby: 
	int curPos;
	// Cby: current position
	Token SYM;
	// Cby: current token
	QList<Token> arrToken;
	// Cby: used for storing token;
	QStack<Tensor::Tensor> operandStack;
	// Cby: used for storing operands
	QList<double> arrNumber;
	// Fdp: used for storing number
	QList<int> arrSubscript;
	// Fdp: used for storing subscript
	int rows;
	// Fdp: rows of the matrix
	int cols;
	// Fdp: cols of the matrix 
	ReturnMsg returnMsg;
	// Cby: return massage
	bool isError = false;
	// Cby: if is an error
	bool exeState = false;
	// Cby: if the program is executing
	//QHash<QString, double> variableValueMap;
	//// Cby: used for storing the map relation between varialbe and value;
	QHash<QString, Tensor::Tensor> variableMap;
	// Carl: used for storing the variables to be processed;
	QString curVarName;
	// Cby: used for storing the name of current variable;
	QString startVarName;
	// Cby: used for storing the name of first varialbe in the command;
	
public:
	/********************SyntacticAppend.cpp********************/
	//Cby SyntacticAppend
	Token GetNextToken();
	// Cby: get next token

	void InitParsing(QList<Token> arrToken);
	// Cby: initialization

	void ExeBasicOeration(QString opr);
	// Cby: execute basic operations;
	bool isFunc();
	// Cby: decided if it is a function;
	Tensor::Tensor ExeFuncOperations(QString funcName, QList<Tensor::Tensor> parameter);
	// Cby: execute function operation
	bool MoveAdvance();
	// Cby: move one character foreward
	void Error(int i);

	void Error(std::string msg);

	void SetVariableMap(QHash<QString, Tensor::Tensor> variableMap);


	/********************SyntacticAnalyzer.cpp********************/
	//Cby SyntacticAnalyzer
	void RecursiveDescentParsing(QList<Token> arrToken);
	// Cby: recursive descent parsing;
	void Command();

	void Sentence();
	void AssignmentDeletionOperation();
	// Cby: execute assignment or deletion;
	void ArithExprLevel_1();
	void Add_Sub();
	void ArithExprLevel_2();
	void Mul_Div();
	void ArithExprLevel_3();
	void Pow();
	void ArithExprLevel_4();
	void ArithExprLevel_5();
	void Func();
	void ArithExprList(int &pc);
	void ArithExprList_(int &pc);
	void ArithExprLevel_6();
	void Tensor();
	void Matrix();
	void Rows();
	void Cols();
	void Subscript();
	void Range();

};
