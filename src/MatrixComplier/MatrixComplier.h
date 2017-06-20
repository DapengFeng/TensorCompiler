#pragma once

#include <QtWidgets/QMainWindow>
#include <qfilesystemmodel.h>
#include <qstandarditemmodel.h>
#include "InstructionProcessor.h"
#include "ui_MatrixComplier.h"

class MatrixComplier : public QMainWindow
{
	Q_OBJECT

public:
	MatrixComplier(QWidget *parent = Q_NULLPTR);

private:
	Ui::MatrixComplierClass ui;

	QFileSystemModel *dirModel;
	QStandardItemModel *fileModel;
	QStandardItemModel *varModel;
	QStandardItemModel *logModel;

	int staticContentLen = 0;
	// Carl: used for saving the length of excuted content;
	bool isDropped = false;
	// Carl: used for detecting drop event;
	QString droppedContent;
	// Carl: used for storing dropped content;
	bool isCursorReset = false;
	// Carl: used for reset cursor;

	InstructionProcessor instructionProcessor;

	/********************FileManager.cpp********************/
	void Initialization();
	// Carl: abstract of inilization;
	void ExplorerInit();
	// Carl: initialization of file explorer; 
	void FileInfoInit();
	// Carl: initialization of file information list;
	void MainTextAreaInit();
	// Carl: initialization of text edit;
	void VarListInit();
	// Carl: initialization of variable list;
	void LogListInit();
	// Carl: initialization of log information list;
	void ConnectionInit();
	// Carl: initialization of connection between SIGNAL and SLOT
	void StyleInit();
	// Carl: initialization of widget style
	/********************FileManager.cpp********************/


	/********************EventFilter.cpp********************/
	bool eventFilter(QObject *, QEvent *);
	/********************EventFilter.cpp********************/


private slots:
	/********************SlotFunction.cpp********************/
	void FileInfoDisplay(QModelIndex);
	// Carl: used for displaying file information

	void StaticContentDisplayAtEnd(QString content);
	void StaticContentDisplayAt(int pos, QString content);
	// Carl: used for add static content into QtextEdit
	/* static content means that when you input one piece of instruction and press enter key,
	* any content you entered before the enter key is called static content.
	* this is a protection for the misinput of content */

	void StaticContentDeleteAt(int pos, int len);
	void StaticContentDeleteBefore(int pos, int len);
	// Carl: used for delete static content from QtextEdit

	void LogInsert(QString content);
	// Carl: insert lastest log into the list
	void VarInsert(QString name, QString content);
	// Carl: insert current variable into the list
	void VarDelete(QString name);
	// Carl: delete the given variable

	void LogInstructionRecall(QModelIndex index);
	// Carl: process instruction get from logView
	void InstructionProcess(QString instruction);
	// Carl: process instructions

	/********************SlotFunction.cpp********************/


};
