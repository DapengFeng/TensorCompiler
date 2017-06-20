#include "MacroDefinition.h"
#include "MatrixComplier.h"
#include "InstructionProcessor.h"
#include <ReturnMsg.h>
#include <QtCore\qdatetime.h>

void MatrixComplier::FileInfoDisplay(QModelIndex index) {
	// Carl: used for displaying file information

	if (dirModel->fileInfo(index).isFile()) {
		// Carl: a file is selected from Explorer, and display its infomation at tableView_Info

		ui.tableView_Info->model()->setData(ui.tableView_Info->model()->index(0, 1), dirModel->fileInfo(index).completeBaseName());
		// Carl: File Name
		/* QFileInfo fi("/tmp/archive.tar.gz");
		* QString base = fi.baseName();  // base = "archive"*/

		ui.tableView_Info->model()->setData(ui.tableView_Info->model()->index(1, 1), dirModel->fileInfo(index).suffix());
		// Carl: File Type
		/* Carl: QFileInfo fi("/tmp/archive.tar.gz");
		* Carl: QString ext = fi.suffix();  // ext = "gz"*/

		ui.tableView_Info->model()->setData(ui.tableView_Info->model()->index(2, 1), dirModel->fileInfo(index).absoluteFilePath());
		// Carl: File Path
		/* Carl: QFileInfo fi("c:/temp/foo");
		* Carl: QString path = fi.absoluteFilePath();  // path = "C:/temp/foo"*/

		ui.tableView_Info->model()->setData(ui.tableView_Info->model()->index(3, 1), QString::number(dirModel->fileInfo(index).size()) + QString::fromStdString(" Byte"));
		// Carl: File Size

		ui.tableView_Info->model()->setData(ui.tableView_Info->model()->index(4, 1), dirModel->fileInfo(index).isHidden());
		// Carl: Hidden

		ui.tableView_Info->model()->setData(ui.tableView_Info->model()->index(5, 1), dirModel->fileInfo(index).isExecutable());
		// Carl: Excutable

		ui.tableView_Info->model()->setData(ui.tableView_Info->model()->index(6, 1), dirModel->fileInfo(index).isReadable());
		// Carl: Readability

		ui.tableView_Info->model()->setData(ui.tableView_Info->model()->index(7, 1), dirModel->fileInfo(index).isWritable());
		// Carl: Writability

		ui.tableView_Info->model()->setData(ui.tableView_Info->model()->index(8, 1), dirModel->fileInfo(index).created());
		// Carl: Created

		ui.tableView_Info->model()->setData(ui.tableView_Info->model()->index(9, 1), dirModel->fileInfo(index).lastRead());
		// Carl: Last Read

		ui.tableView_Info->model()->setData(ui.tableView_Info->model()->index(10, 1), dirModel->fileInfo(index).lastModified());
		// Carl: Last Modified

		ui.tableView_Info->model()->setData(ui.tableView_Info->model()->index(11, 1), dirModel->fileInfo(index).owner());
		// Carl: Owner

		ui.tableView_Info->model()->setData(ui.tableView_Info->model()->index(12, 1), dirModel->fileInfo(index).ownerId());
		// Carl: Owner ID

		ui.tableView_Info->model()->setData(ui.tableView_Info->model()->index(13, 1), dirModel->fileInfo(index).group());
		// Carl: Group

		ui.tableView_Info->model()->setData(ui.tableView_Info->model()->index(14, 1), dirModel->fileInfo(index).groupId());
		// Carl: Group ID

	}
	else {

	}

}

void MatrixComplier::StaticContentDisplayAtEnd(QString content) {
	// Carl: used for add static content into QtextEdit
	/* static content means that when you input one piece of instruction and press enter key,
	* any content you entered before the enter key is called static content.
	* this is a protection for the misinput of content */

	QTextCursor cursor = ui.textEdit->textCursor();
	cursor.movePosition(QTextCursor::End);
	ui.textEdit->setTextCursor(cursor);
	// Carl: set current cursor

	cursor.insertText(content);
	// Carl: add static content
	staticContentLen = ui.textEdit->toPlainText().size();
	// Carl: used for update the length of static content
}

void MatrixComplier::StaticContentDisplayAt(int pos, QString content) {
	// Carl: used for add static content into QtextEdit at given position
	/* static content means that when you input one piece of instruction and press enter key,
	* any content you entered before the enter key is called static content.
	* this is a protection for the misinput of content */

	QTextCursor cursor = ui.textEdit->textCursor();
	cursor.setPosition(pos);
	ui.textEdit->setTextCursor(cursor);
	// Carl: set current cursor

	cursor.insertText(content);
	// Carl: add static content
	staticContentLen = ui.textEdit->toPlainText().size();
	// Carl: used for update the length of static content
}

void MatrixComplier::StaticContentDeleteAt(int pos, int len) {
	// Carl: used for delete static content from QtextEdit

	QTextCursor cursor = ui.textEdit->textCursor();
	cursor.setPosition(pos);
	ui.textEdit->setTextCursor(cursor);
	// Carl: set current cursor

	for (int i = 0; i < len; i++)
		cursor.deleteChar();

	staticContentLen = ui.textEdit->toPlainText().size();
	// Carl: used for update the length of static content

	cursor.setPosition(staticContentLen);
	ui.textEdit->setTextCursor(cursor);
	// Carl: moved the cursor to the end of text;

}

void MatrixComplier::StaticContentDeleteBefore(int pos, int len) {
	// Carl: used for delete static content from QtextEdit

	QTextCursor cursor = ui.textEdit->textCursor();
	cursor.setPosition(pos);
	ui.textEdit->setTextCursor(cursor);
	// Carl: set current cursor

	for (int i = 0; i < len; i++)
		cursor.deletePreviousChar();

	staticContentLen = ui.textEdit->toPlainText().size();
	// Carl: used for update the length of static content

	cursor.setPosition(staticContentLen);
	ui.textEdit->setTextCursor(cursor);
	// Carl: moved the cursor to the end of text;
}

void MatrixComplier::LogInsert(QString content) {
	// Carl: insert lastest log into the list

	QDateTime current = QDateTime::currentDateTime();
	QString time = current.toString();
	// Carl: get time when instruction inputed;

	// Carl: add rows to log table;
	QList<QStandardItem*> item;
	item << new QStandardItem(time) << new QStandardItem("      " + content);
	// Carl: for visual comfortability
	logModel->appendRow(item);
	item.clear();

}

void MatrixComplier::VarInsert(QString name, QString content){
	// Carl: insert current variable into the list
	QList<QStandardItem*> list = varModel->findItems(name, Qt::MatchExactly, 0);
	if (!list.isEmpty())
		VarDelete(name);

	QList<QStandardItem*> item;
	item << new QStandardItem(name) << new QStandardItem(content);
	varModel->appendRow(item);
	item.clear();
}

void MatrixComplier::VarDelete(QString name){
	// Carl: delete the given variable
	int i = 0;
	for (i = 0; i < varModel->rowCount(); i++) {
		if (varModel->item(i, 0)->text() == name) {
			// Carl: delete info
			varModel->removeRow(i);
		}
	}
	if (i == varModel->rowCount()) {
		// Carl: the variable is not existed
		// StaticContentDisplayAtEnd("Variable " + name + " is not existed");
		// fix bug by Dapeng Feng
	}
}

void MatrixComplier::LogInstructionRecall(QModelIndex index) {
	// Carl: process instruction get from logView
	
	if (index.column()) {
		// Carl: click the instructions
		QString instruction = ui.tableView_Log->model()->data(index).toString();

		instruction = instruction.right(instruction.size() - 6);
		// Carl: inserted log is added with "      " for visual comfortability

		StaticContentDisplayAtEnd(instruction);
		// Carl: display instruction

		LogInsert(instruction);
		// Carl: insert lastest log into the list

		InstructionProcess(instruction);
		// Carl: process instructions
	}

}

void MatrixComplier::InstructionProcess(QString instruction) {
	// Carl: process instructions


#ifndef INSTRUCTION_PROCESSOR

	if (instruction == "clear") {
		ui.textEdit->setText("");
	}
	else {
		StaticContentDisplayAtEnd("\n");
		// Carl: break

		StaticContentDisplayAtEnd("Processing " + instruction);
		// Carl: simulate processing

		StaticContentDisplayAtEnd("\n");
		// Carl: break
	}

	StaticContentDisplayAtEnd(">> ");
	// Carl:  input token;

#else

	/*analyse and send useful variable to processor*/

	instructionProcessor.SetInstruction(instruction);

	QList<QString> returnInfo = instructionProcessor.Process();

	bool Assign = false;
	bool Delete = false;
	bool Image = false;

	for (QList<QString>::iterator i = returnInfo.begin(); i != returnInfo.end(); i++) {
		// Carl: deal with the return info;

		if (Assign) {
			// Carl: tenser assign;
			QStringList variable = (*i).split("=");
			instructionProcessor.variableMap.insert(variable.at(0), Tensor::Tensor(variable.at(1).toStdString()));
			VarInsert(variable.at(0), variable.at(1));
			Assign = false;
		}
		if (Delete) {
			instructionProcessor.variableMap.take((*i));
			VarDelete(*i);
		}
		if (Image) {
			std::stringstream ss;
			ss << instructionProcessor.variableMap[*i].size();
			VarInsert(*i, QString(ss.str().c_str()));
			Image = false;
		}
		if (*i == "clear" || *i == "clear text") {
			ui.textEdit->setText("");
		}
		else if (*i == "clear log") {
			ui.tableView_Log->model()->removeRows(0, ui.tableView_Log->model()->rowCount());
		}
		else if (*i == "clear var") {
			ui.tableView_Var->model()->removeRows(0, ui.tableView_Var->model()->rowCount());
			instructionProcessor.variableMap.clear();
			// fix bug by Dapeng Feng
		}
		else if (*i == "clear all") {
			ui.textEdit->setText("");
			ui.tableView_Log->model()->removeRows(0, ui.tableView_Log->model()->rowCount());
			ui.tableView_Var->model()->removeRows(0, ui.tableView_Var->model()->rowCount());
			instructionProcessor.variableMap.clear();
			// fix bug by Dapeng Feng
		}
		else if (*i == ReturnMsg::ASSIGN) {
			Assign = true;
		}
		else if (*i == ReturnMsg::DELETE) {
			Delete = true;
		}
		else if (*i == "Image") {
			Image = true;
		}
		else {
			StaticContentDisplayAtEnd(*i);
			StaticContentDisplayAtEnd("\n");
		}
	}

	StaticContentDisplayAtEnd(">> ");
	// Carl:  input token;

#endif // !INSTRUCTION_PROCESSOR


}
