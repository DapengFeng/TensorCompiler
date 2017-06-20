#include <qstring.h>
#include <qhash.h>
#include <Tensor.h>
#include <SyntacticAnalyzer.h>
#include <TokenMatcher.h>
#include <LexicalAnalyzer.h>
#include <SyntacticAnalyzer.h>

#include "MacroDefinition.h"
#include "InstructionProcessor.h"
#include "UIKeyWords.h"

InstructionProcessor::InstructionProcessor(){
	this->instruction = "";
	QString *pointer = uiKeyWords;
	while (*pointer != QString::null) {
		uiKeyWordsList.append(*pointer);
		pointer++;
	}
}

InstructionProcessor::InstructionProcessor(QHash<QString, Tensor::Tensor> variableMap, QString instruction){
	this->instruction = instruction;
	this->variableMap = variableMap;
}

InstructionProcessor::~InstructionProcessor(){

}

void InstructionProcessor::SetInstruction(QString instruction){
	this->instruction = instruction;
}

QHash<QString, Tensor::Tensor> InstructionProcessor::GetVariableMap(){
	return this->variableMap;
}

QList<QString> InstructionProcessor::Process(){
	// Carl: process instructions;

	QList<QString> outputList;
	// Carl: used for storing return output info;

	if (uiKeyWordsList.contains(instruction)){
		// Carl: return instruction to upper layer
		outputList.append(instruction);
	}
	else if (instruction.count("imageReader") || instruction.count("imread")) {
		try {
			QString filePath = instruction.split(" ").at(1);
			filePath = filePath.replace("/", "\\");
			QString file = instruction.split("\\").back();
			QString fileName = file.split(".").at(0);
			Tensor::Tensor img;
			img.imread("D:\\Tensor", filePath.toStdString());
			//InstructionProcessor::ImageMap.insert(fileName, img);
			this->variableMap[fileName] = img;
			outputList.append("Image");
			outputList.append(fileName);
		}
		catch (std::exception ex) {
			outputList.append(ReturnMsg::ERROR);
			outputList.append(ex.what());
		}
	}
	else if (instruction.count("imshow")) {
		try {
			QString fileName = instruction.split(" ").at(1);
			this->variableMap[fileName].imshow();
		}
		catch (std::exception ex) {
			outputList.append(ReturnMsg::ERROR);
			outputList.append(ex.what());
		}
	}
	else if (instruction.count("imsave")) {
		try {
			QString filePath = instruction.split(" ").at(2);
			QString fileName = instruction.split(".").at(1);
			filePath = filePath.replace("/", "\\");
			this->variableMap[fileName].imsave("D:\\Tensor", filePath.toStdString());
		}
		catch (std::exception ex) {
			outputList.append(ReturnMsg::ERROR);
			outputList.append(ex.what());
		}
	}
	else if (instruction.count("rgb2gray")) {
		try {
			QStringList cmd = instruction.split(" ");
			QString src = cmd[1];
			QString dst = "ans";
			if (cmd.size() == 3) {
				dst = cmd[2];
			}
			this->variableMap[dst] = this->variableMap[src].RGB2GRAY();
			outputList.append("Image");
			outputList.append(dst);
		}
		catch (std::exception ex) {
			outputList.append(ReturnMsg::ERROR);
			outputList.append(ex.what());
		}
	}
	else {
		// Carl: deal with instructions and return results to upper layer
		//outputList.append("Process " + instruction);

#ifdef TOKENMATHER_TEST

		TokenMatcher tm = TokenMatcher();
		tm.setSentence(instruction);
		Token t = tm.MatchAll();

		outputList.append("TokenContent " + t.tokenContent);
		outputList.append("TokenType " + t.tokenType);

#endif // TOKENMATHER_TEST

#ifdef LEXICALANALYZER_TEST

		LexicalAnalyzer lexicalAnalyzer = LexicalAnalyzer(instruction);
		QList<Token> arrToken = lexicalAnalyzer.SentenceScanner();
		for (QList<Token>::iterator i = arrToken.begin(); i != arrToken.end(); i++)
			outputList.append("<" + (*i).tokenContent + " " + (*i).tokenType + ">");

#endif // LEXICALANALYZER_TEST

#ifdef SYNTACTICANALYZER_TEST

		LexicalAnalyzer lexicalAnalyzer = LexicalAnalyzer(instruction);
		QList<Token> arrToken = lexicalAnalyzer.SentenceScanner();

		// find out the variable note from arrToken;
		QHash<QString, Tensor::Tensor> needVarMap;
		for (QList<Token>::iterator i = arrToken.begin(); i != arrToken.end(); i++) {
			if ((*i).tokenType == Token::Variable && variableMap.contains((*i).tokenContent))
				needVarMap.insert((*i).tokenContent, variableMap[(*i).tokenContent]);
		}

		SyntacticAnalyzer syntacticAnalyzer = SyntacticAnalyzer();
		syntacticAnalyzer.SetVariableMap(needVarMap);
		syntacticAnalyzer.RecursiveDescentParsing(arrToken);
		outputList.append(syntacticAnalyzer.returnMsg.msgType);
		outputList.append(syntacticAnalyzer.returnMsg.msgContent);


#endif // SYNTACTICANALYZER_TEST
		
	}

	return outputList;

}
