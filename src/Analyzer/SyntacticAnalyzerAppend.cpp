#include "SyntacticAnalyzer.h"
#include "OutputType.h"

Token SyntacticAnalyzer::GetNextToken(){
	if (curPos == this->arrToken.size())
		return Token("", Token::EndOfFile);
	else if (curPos > this->arrToken.size())
		return Token("ERROR", Token::Error);
	return
		this->arrToken.at(curPos + 1);
}

void SyntacticAnalyzer::InitParsing(QList<Token> arrToken) {
	if (arrToken.size() == 0) {
		returnMsg.msgType = ReturnMsg::ERROR;
		returnMsg.msgContent = "No sentence";
		return;
	}

	returnMsg.msgType = ReturnMsg::START;
	returnMsg.msgContent = "start";
	this->arrToken = arrToken;
	this->arrToken.append(Token("#", Token::EndOfFile));
	curPos = -1;
	isError = false;
	exeState = false;
	operandStack.clear();
	arrNumber.clear();
	arrSubscript.clear();
	rows = 0;
	cols = 0;
	MoveAdvance();
}


void SyntacticAnalyzer::ExeBasicOeration(QString opr) {
	Tensor::Tensor operand1, operand2;
	try {
		if (opr == OutputType::Add) {
			operand2 = operandStack.pop();
			operand1 = operandStack.pop();
			operandStack.push(operand1 + operand2);
			//operandStack.push(operand1+operand2);
		}
		else if (opr == OutputType::Sub) {
			operand2 = operandStack.pop();
			operand1 = operandStack.pop();
			operandStack.push(operand1 - operand2);
		}
		else if (opr == OutputType::Mul) {
			operand2 = operandStack.pop();
			operand1 = operandStack.pop();
			operandStack.push(operand1 * operand2);
		}
		else if (opr == OutputType::Div) {
			operand2 = operandStack.pop();
			operand1 = operandStack.pop();
			operandStack.push(operand1 / operand2);
		}
		else if (opr == OutputType::Pow) {
			operand2 = operandStack.pop();
			operand1 = operandStack.pop();
			operandStack.push(operand1 ^ operand2);
		}
		else if (opr == OutputType::Minus) {
			operand1 = operandStack.pop();
			operandStack.push(-operand1);
		}
		else if (opr == OutputType::PushValue) {
			QString str = SYM.tokenContent;
			//double val = str.toDouble(); //val=123.45
			operandStack.push(Tensor::Tensor(str.toStdString()));
			//CBY mark
		}
		else if (opr == OutputType::PushMatrix) {
			std::vector<double> vec;
			for (auto temp : arrNumber) {
				vec.push_back(temp);
			}
			arrNumber.clear();
			cols = cols / rows;
			operandStack.push(Tensor::Tensor(rows, cols, vec));
			rows = 0;
			cols = 0;
		}
		else if (opr == OutputType::PushRangeMatrix) {
			operand1 = operandStack.pop();
			int row1 = arrSubscript[0];
			int row2 = arrSubscript[1];
			int col1 = arrSubscript[2];
			int col2 = arrSubscript[3];
			if (row2 == -1) {
				row2 = operand1.Rows();
			}
			if (col2 == -1) {
				col2 = operand1.Cols();
			}
			operandStack.push(operand1.getRange(row1, row2, col1, col2));
		}
		else if (opr == OutputType::DeleteVariable) {
			if (variableMap.contains(startVarName)) {
				returnMsg.msgType = ReturnMsg::DELETE;
				returnMsg.msgContent = startVarName;
			}
			else {
				Error(2);
				isError = true;
			}
			
		}
		else if (opr == OutputType::AssignmentVariable) {
			operand1 = operandStack.pop();
			returnMsg.msgType = ReturnMsg::ASSIGN;
			returnMsg.msgContent = startVarName + "=" + QString(operand1.toString().c_str());
			return;
		}
		else if (opr == OutputType::PushVariable) {
			if (variableMap.contains(curVarName)) {
				operandStack.push(variableMap[curVarName]);
			}
			else {
				Error(2);
				isError = true;
			}

		}
		else if (opr == OutputType::Hconcat) {
			operand2 = operandStack.pop();
			operand1 = operandStack.pop();
			operandStack.push_back(Tensor::hconcat(operand1, operand2));
		}
		else if (opr == OutputType::Vconcat) {
			operand2 = operandStack.pop();
			operand1 = operandStack.pop();
			operandStack.push_back(Tensor::vconcat(operand1, operand2));
		}
	}
	catch (std::exception ex) {
		Error(ex.what());
		isError = true;
	}
}

bool SyntacticAnalyzer::isFunc(){
	if (SYM.tokenType == Token::ReservedWord)
		if (SYM.tokenContent == "sin" || SYM.tokenContent == "cos" || SYM.tokenContent == "min" || SYM.tokenContent == "max" || SYM.tokenContent == "func")
			return true;
	return false;
}

#pragma region CallFunction(Dapeng Feng)
Tensor::Tensor SyntacticAnalyzer::ExeFuncOperations(QString funcName, QList<Tensor::Tensor> parameter) {
	Tensor::Tensor oper1, oper2;
	double dans;
	Tensor::Tensor tans;
	try {
		if (funcName == "sin") {
			if (parameter.size() != 1) {
				throw std::exception("The number of parameters does not meet the requirements");
			}
			else {
				oper1 = parameter[0];
				tans = oper1.Sine();
			}
		}
		else if (funcName == "cos") {
			if (parameter.size() != 1) {
				throw std::exception("The number of parameters does not meet the requirements");
			}
			else {
				oper1 = parameter[0];
				tans = oper1.Cosine();
			}
		}
		else if (funcName == "min") {
			if (parameter.size() != 1) {
				throw std::exception("The number of parameters does not meet the requirements");
			}
			else {
				oper1 = parameter[0];
				dans = oper1.Min();
				tans = Tensor::Tensor(1, dans);
			}
		}
		else if (funcName == "max") {
			if (parameter.size() != 1) {
				throw std::exception("The number of parameters does not meet the requirements");
			}
			else {
				oper1 = parameter[0];
				dans = oper1.Max();
				tans = Tensor::Tensor(1, dans);
			}
		}
		else if (funcName == "channels") {
			if (parameter.size() != 1) {
				throw std::exception("The number of parameters does not meet the requirements");
			}
			else {
				oper1 = parameter[0];
				dans = (double)oper1.Channels();
				tans = Tensor::Tensor(1, dans);
			}
		}
		else if (funcName == "rows") {
			if (parameter.size() != 1) {
				throw std::exception("The number of parameters does not meet the requirements");
			}
			else {
				oper1 = parameter[0];
				dans = (double)oper1.Rows();
				tans = Tensor::Tensor(1, dans);
			}
		}
		else if (funcName == "cols") {
			if (parameter.size() != 1) {
				throw std::exception("The number of parameters does not meet the requirements");
			}
			else {
				oper1 = parameter[0];
				dans = (double)oper1.Cols();
				tans = Tensor::Tensor(1, dans);
			}
		}
		else if (funcName == "det") {
			if (parameter.size() != 1) {
				throw std::exception("The number of parameters does not meet the requirements");
			}
			else {
				oper1 = parameter[0];
				dans = oper1.Det();
				tans = Tensor::Tensor(1, dans);
			}
		}
		else if (funcName == "transpose") {
			if (parameter.size() != 1) {
				throw std::exception("The number of parameters does not meet the requirements");
			}
			else {
				oper1 = parameter[0];
				tans = oper1.Transpose();
			}
		}
		else if (funcName == "inv") {
			if (parameter.size() != 1) {
				throw std::exception("The number of parameters does not meet the requirements");
			}
			else {
				oper1 = parameter[0];
				tans = oper1.Inv();
			}
		}
		else if (funcName == "rand") {
			if (parameter.size() == 1) {
				oper1 = parameter[0];
				int temp = (int)oper1.getMatrix().at<double>(0, 0);
				tans = Tensor::rand(temp);
			}
			else if (parameter.size() == 2) {
				oper1 = parameter[0];
				oper2 = parameter[1];
				int temp1 = (int)oper1.getMatrix().at<double>(0, 0);
				int temp2 = (int)oper2.getMatrix().at<double>(0, 0);
				tans = Tensor::rand(temp1, temp2);
			}
			else {
				throw std::exception("The number of parameters does not meet the requirements");
			}
		}
		else {
			throw std::exception("Undefined function");
		}
		parameter.clear();
		return tans;
	}
	catch (std::exception ex) {
		throw ex;
	}
}
#pragma endregion

bool SyntacticAnalyzer::MoveAdvance() {
	curPos++;
	if (curPos >= this->arrToken.size()) {
		isError = true;
		return false;
	}
	SYM = this->arrToken.at(curPos);
	return true;
}

void SyntacticAnalyzer::Error(int i) {
	QString errorType[] = {
		"ERROR!",
		"Not exist val",
		"Not exist Variable",
		"value can not be dived by zero",
		"function name error",
		"function without (",
		"function without )",
		QString::null
	};
	returnMsg.msgType = ReturnMsg::ERROR;
	returnMsg.msgContent = errorType[i];
}

void SyntacticAnalyzer::Error(std::string msg) {
	returnMsg.msgType = ReturnMsg::ERROR;
	returnMsg.msgContent = QString(msg.c_str());
}

void SyntacticAnalyzer::SetVariableMap(QHash<QString, Tensor::Tensor> variableMap){
	this->variableMap = variableMap;
}