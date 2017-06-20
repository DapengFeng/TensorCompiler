#pragma once

#include <qhash.h>
#include <qlist.h>

#include <Tensor.h>


class InstructionProcessor
{
public:
	InstructionProcessor();
	InstructionProcessor(QHash<QString, Tensor::Tensor> variableMap, QString instruction);
	~InstructionProcessor();


	void SetInstruction(QString instruction);

	QHash<QString, Tensor::Tensor> GetVariableMap();
	// Carl: set and get;

	QList<QString> Process();


private:
	QString instruction;
	// Carl: used for storing instrustion 

	QList<QString> uiKeyWordsList;
	// Carl: usef for storting defined instructions;

	//QList<Matrix> variableList;
	//// Carl: used for storing created variables
public:
	QHash<QString, Tensor::Tensor> variableMap;
	// Carl: used for storing created variables
};
