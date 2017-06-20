#include "SyntacticAnalyzer.h"
#include "OutputType.h"

SyntacticAnalyzer::SyntacticAnalyzer() {
	this->sentence = "";
}

SyntacticAnalyzer::SyntacticAnalyzer(QString sentence){
	this->sentence = sentence;
}

SyntacticAnalyzer::~SyntacticAnalyzer() {

}


void SyntacticAnalyzer::AssignmentDeletionOperation(){
	if (isError)
		return;
	if (SYM.tokenContent == "{" && SYM.tokenType == Token::Symbol) {
		MoveAdvance();
		if (SYM.tokenContent == "}" && SYM.tokenType == Token::Symbol) {
			MoveAdvance();
			if(exeState)
				ExeBasicOeration(OutputType::DeleteVariable);
			//if (exeState)
			//	returnMsg.msgContent = startVarName + " is deleted!";
			// Carl: Query
		}
		else {
			Error(0);
			isError = true;
		}
	}
	else {
		ArithExprLevel_1();
		if (isError)
			return;
		if (exeState)
			ExeBasicOeration(OutputType::AssignmentVariable);
		//if (exeState)
		//	returnMsg.msgContent = startVarName + " = " + QString(operandStack.pop().toString().c_str());
		// Carl: Query
	}
}


void SyntacticAnalyzer::RecursiveDescentParsing(QList<Token> arrToken) {
	InitParsing(arrToken);
	if (returnMsg.msgType != ReturnMsg::START)
		return;
	exeState = true;
	Command();
	if (isError == false && SYM.tokenType != Token::EndOfFile)
		Error(0);
	/*if (returnMsg.msgType != ReturnMsg::ERROR)
		returnMsg.msgType = ReturnMsg::SUCCESS;*/
}



void SyntacticAnalyzer::Command() {
	if (isError)
		return;
	Sentence();
	if (SYM.tokenContent == ";" && SYM.tokenType == Token::Symbol)
		MoveAdvance();
}

void SyntacticAnalyzer::Sentence(){
	if (isError)
		return;
	if (SYM.tokenType == Token::Variable) {
		curVarName = SYM.tokenContent;
		startVarName = SYM.tokenContent;
		Token nextToken = GetNextToken();
		if (nextToken.tokenContent == "=" && nextToken.tokenType == Token::Symbol) {
			MoveAdvance();
			MoveAdvance();
			AssignmentDeletionOperation();
		}
		else {
			ArithExprLevel_1();
			if (isError)
				return;
			if (exeState)
				returnMsg.msgContent = QString(operandStack.pop().toString().c_str());
			// Carl: Query
		}
	}
	else if (SYM.tokenContent == "if" && SYM.tokenType == Token::ReservedWord) {
		if (isError)
			return;
	}
	else {
		ArithExprLevel_1();
		if (isError)
			return;
		if (exeState)
			returnMsg.msgContent = QString(operandStack.pop().toString().c_str());
		// Carl: Query
	}
}

void SyntacticAnalyzer::ArithExprLevel_1(){
	if (isError)
		return;
	ArithExprLevel_2();
	if (isError)
		return;
	Add_Sub();
}

void SyntacticAnalyzer::ArithExprLevel_2(){
	if (isError)
		return;
	ArithExprLevel_3();
	if (isError)
		return;
	Mul_Div();
}

void SyntacticAnalyzer::ArithExprLevel_3(){
	if (isError)
		return;
	ArithExprLevel_4();
	if (isError)
		return;
	Pow();
}

void SyntacticAnalyzer::ArithExprLevel_4(){
	if (isError)
		return;
	if (SYM.tokenContent == "-" && SYM.tokenType == Token::Symbol) {
		MoveAdvance();
		ArithExprLevel_4();
		if (exeState)
			ExeBasicOeration(OutputType::Minus);
	}
	else
		ArithExprLevel_5();
}

void SyntacticAnalyzer::ArithExprLevel_5(){
	if (isError)
		return;
	if (isFunc())
		Func();
	else if (SYM.tokenType != Token::EndOfFile)
		ArithExprLevel_6();
}

void SyntacticAnalyzer::ArithExprLevel_6(){
	if (isError)
		return;
	if (SYM.tokenType == Token::Number) {
		if (exeState)
			ExeBasicOeration(OutputType::PushValue);
		MoveAdvance();
	}
	else if (SYM.tokenType == Token::Variable) {
		curVarName = SYM.tokenContent;
		if (exeState)
			ExeBasicOeration(OutputType::PushVariable);
		MoveAdvance();
	}
	else if (SYM.tokenContent == "(" && SYM.tokenType == Token::Symbol) {
		MoveAdvance();
		ArithExprLevel_1();
		if (SYM.tokenContent == ")" && SYM.tokenType == Token::Symbol)
			MoveAdvance();
		else {
			Error("without )");
			isError = true;
		}
	} 
	else if (SYM.tokenContent == "[" && SYM.tokenType == Token::Symbol) {
		MoveAdvance();
		Tensor();
		if (SYM.tokenContent == "]" && SYM.tokenType == Token::Symbol) {
			MoveAdvance();
			//ExeBasicOeration(OutputType::PushMatrix);
		}
		else {
			Error("without ]");
			isError = true;
		}
	}
	else {
		Error(0);
		isError = true;
	}
}

#pragma region Tensor(Dapeng Feng)
void SyntacticAnalyzer::Tensor() {
	if (isError)
		return;
	Matrix();
	if (isError)
		return;
	if (SYM.tokenContent == "," && SYM.tokenType == Token::Symbol) {
		MoveAdvance();
		Tensor();
		ExeBasicOeration(OutputType::Hconcat);
	}
	else if (SYM.tokenContent == ";" && SYM.tokenType == Token::Symbol) {
		MoveAdvance();
		Tensor();
		ExeBasicOeration(OutputType::Vconcat);
	}
	else {

	}
}

void SyntacticAnalyzer::Matrix() {
	if (SYM.tokenContent == "[" && SYM.tokenType == Token::Symbol) {
		MoveAdvance();
		Rows();
		if (SYM.tokenContent == "]" && SYM.tokenType == Token::Symbol) {
			MoveAdvance();
			ExeBasicOeration(OutputType::PushMatrix);
		}
		else {
			Error("without ]");
			isError = true;
		}
	}
	else if (SYM.tokenType == Token::Variable) {
		curVarName = SYM.tokenContent;
		if (exeState)
			ExeBasicOeration(OutputType::PushVariable);
		MoveAdvance();
		if (SYM.tokenContent == "(" && SYM.tokenType == Token::Symbol) {
			MoveAdvance();
			Subscript();
			if (SYM.tokenContent == ")" && SYM.tokenType == Token::Symbol) {
				MoveAdvance();
				ExeBasicOeration(OutputType::PushRangeMatrix);
			}
			else {
				Error("without )");
				isError = true;
			}
		}
		else {

		}
	}
	else {
		Error("Defintion Error");
		isError = true;
	}
}

void SyntacticAnalyzer::Rows() {
	Cols();
	rows++;
	if (SYM.tokenContent == ";" && SYM.tokenType == Token::Symbol) {
		MoveAdvance();
		Rows();
	}
	else {

	}
}

void SyntacticAnalyzer::Cols() {
	if (SYM.tokenType == Token::Number) {
		arrNumber.push_back(SYM.tokenContent.toDouble());
		cols++;
		MoveAdvance();
	}
	if (SYM.tokenContent == "," && SYM.tokenType == Token::Symbol) {
		MoveAdvance();
		Cols();
	}
	else {

	}
}

void SyntacticAnalyzer::Subscript() {
	if (isError)
		return;
	Range();
	if (isError) {
		return;
	}
	if (SYM.tokenContent == "," && SYM.tokenType == Token::Symbol) {
		MoveAdvance();
	}
	else {
		Error(0);
		isError = true;
	}
	Range();
}

void SyntacticAnalyzer::Range() {
	if (isError)
		return;
	if (SYM.tokenContent == ":" && SYM.tokenType == Token::Symbol) {
		arrSubscript.push_back(0);
		arrSubscript.push_back(-1);
		MoveAdvance();
	}
	else if (SYM.tokenType == Token::Number) {
		arrSubscript.push_back(SYM.tokenContent.toDouble());
		MoveAdvance();
		if (SYM.tokenContent == ":" && SYM.tokenType == Token::Symbol) {
			MoveAdvance();
			if (SYM.tokenType == Token::Number) {
				arrSubscript.push_back(SYM.tokenContent.toDouble());
				MoveAdvance();
			}
			else {
				Error(0);
				isError = true;
			}
		}
		else {
			Error(0);
			isError = true;
		}

	}
	else {
		Error(0);
		isError = true;
	}
}

#pragma endregion

void SyntacticAnalyzer::ArithExprList(int & pc){
	pc++;
	ArithExprLevel_1();
	if (isError)
		return;
	ArithExprList_(pc);
}

void SyntacticAnalyzer::ArithExprList_(int & pc){
	if(SYM.tokenContent == "," && SYM.tokenType == Token::Symbol) {
		MoveAdvance();
		ArithExprList(pc);
	}
}

void SyntacticAnalyzer::Add_Sub(){
	if (isError)
		return;
	if (SYM.tokenContent == "+" && SYM.tokenType == Token::Symbol) {
		MoveAdvance();
		ArithExprLevel_2();
		if (isError)
			return;
		if (exeState)
			ExeBasicOeration(OutputType::Add);
		Add_Sub();
	}
	else if (SYM.tokenContent == "-" && SYM.tokenType == Token::Symbol) {
		MoveAdvance();
		ArithExprLevel_2();
		if (isError)
			return;
		if (exeState)
			ExeBasicOeration(OutputType::Sub);
		Add_Sub();
	}
	else {

	}
}

void SyntacticAnalyzer::Mul_Div(){
	if (isError)
		return;
	if (SYM.tokenContent == "*" && SYM.tokenType == Token::Symbol) {
		MoveAdvance();
		ArithExprLevel_3();
		if (isError)
			return;
		if (exeState)
			ExeBasicOeration(OutputType::Mul);
		Mul_Div();
	}
	else if (SYM.tokenContent == "/" && SYM.tokenType == Token::Symbol) {
		MoveAdvance();
		ArithExprLevel_3();
		if (isError)
			return;
		if (exeState)
			ExeBasicOeration(OutputType::Div);
		Mul_Div();
	}
}

void SyntacticAnalyzer::Pow(){
	if (isError)
		return;
	if (SYM.tokenContent == "^" && SYM.tokenType == Token::Symbol) {
		MoveAdvance();
		ArithExprLevel_3();
		Pow();
		if (exeState)
			ExeBasicOeration(OutputType::Pow);
	}
}

void SyntacticAnalyzer::Func(){
	QString curFuncName = "";
	bool isFunc = false;
	if (isError)
		return;
	if (SYM.tokenType == Token::ReservedWord) {
		if (SYM.tokenContent == "sin" || SYM.tokenContent == "cos" || SYM.tokenContent == "min" || SYM.tokenContent == "max")
			isFunc = true;
		else if (SYM.tokenContent == "func") {
			isFunc = true;
			MoveAdvance();
			if (SYM.tokenType != Token::Variable) {
				Error(4);
				isError = true;
				return;
			}
		}
	}
	if (isFunc) {
		curFuncName = SYM.tokenContent;
		int parameterCounter = 0;
		QList<Tensor::Tensor> parameter;
		MoveAdvance();
		if (SYM.tokenContent == "(" && SYM.tokenType == Token::Symbol) {
			MoveAdvance();
			ArithExprList(parameterCounter);
			if (SYM.tokenContent == ")" && SYM.tokenType == Token::Symbol) {
				MoveAdvance();
				for (int i = 0; i < parameterCounter; i++)
					parameter.push_front(operandStack.pop());
				try {
					operandStack.push_back(ExeFuncOperations(curFuncName, parameter));
				}
				catch (std::exception ex) {
					Error(ex.what());
					isError = true;
				}
			}
			else {
				Error(6);
				isError = true;
				return;
			}
		}
		else {
			Error(5);
			isError = true;
			return;
		}
	}
	
}
