#include "MacroDefinition.h"
#include "MatrixComplier.h"
#include <QtGui>
#include <qscrollbar.h>

bool MatrixComplier::eventFilter(QObject *object, QEvent *e) {

	int plainTextSize = ui.textEdit->toPlainText().size();
	int staticContent = this->staticContentLen;
	int cursorPos = ui.textEdit->textCursor().position();
	int cursorStart = ui.textEdit->textCursor().selectionStart();
	int cursorEnd = ui.textEdit->textCursor().selectionEnd();

	ui.pushButton->setText("PlainText: " + QString::number(plainTextSize)
		+ " staticContentLen: " + QString::number(staticContent) 
		+ " cursorPos: " + QString::number(cursorPos) 
		+ " cursorStart: " + QString::number(cursorStart) 
		+ " cursorEnd: " + QString::number(cursorEnd));

	/****************************************ui.textEdit****************************************/
	if (object == ui.textEdit) {

		if (isDropped){


			if (!isCursorReset && ui.textEdit->textCursor().position() < ui.textEdit->toPlainText().size()) {
				// Carl: set isCursorReset flag
				/* the unsatisfied content is printed on the screen, it should be removed,
				* cause the machnism of eventfilter, 
				* flag is used for dealing with following process */

				isCursorReset = true;

				staticContentLen = ui.textEdit->toPlainText().size() + droppedContent.size();
				// Carl: synchronize static content

				//return true;

				return eventFilter(object, e);
			}

			if (isCursorReset) {
				// Carl: after set isCursorReset flag, the next eventfilter should deal with this block, which is used for effacing 

				StaticContentDeleteBefore(ui.textEdit->textCursor().position(), droppedContent.size());
				// Carl: used for delete static content from QtextEdit

				isCursorReset = false;
				// Carl: this process is finished, the next eventfilter should deal with next block, which is if (droppedContent.size())

				//return true;

				return eventFilter(object, e);
			}

			if (droppedContent.size()) {

				QString path = droppedContent.right(droppedContent.size() - 8);
				// Carl: newInput has the format of "file:///.*"

				QFileInfo *fileInfo = new QFileInfo(path);

				if (fileInfo->isFile()){
					// Carl: the input path is a file path;

					QString instruction = "fileReader(" + fileInfo->absoluteFilePath() + ")";

					if (fileInfo->suffix() == "txt"){
						instruction = "textReader(" + fileInfo->absoluteFilePath() + ")";
					}
					else if (fileInfo->suffix() == "jpg") {
						instruction = "imageReader " + fileInfo->absoluteFilePath();
					}

					StaticContentDisplayAt(staticContentLen, instruction);
					// Carl: add function called text

					StaticContentDeleteAt(ui.textEdit->textCursor().position(), droppedContent.size());
					// Carl: delete the auto-created filepath

					LogInsert(instruction);
					// Carl: insert lastest log into the list

					StaticContentDisplayAtEnd("\n");
					// Carl: enter

					InstructionProcess(instruction);
					// Carl: process instruction

					isDropped = false;
					droppedContent = "";

					return true;


				}
				else if (fileInfo->isDir()) {
					// Carl: the input path is a directory path;
					ui.pushButton->setText("is not a file");

				}

			}

			return false;
		}
		

		if (e->type() == QEvent::KeyPress) {

			QKeyEvent *keyEvent = static_cast<QKeyEvent *>(e);
			QTextCursor cursor = ui.textEdit->textCursor();

			if (keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter){
				// Carl: used for dealing with the enter key

				QString newInput = ui.textEdit->toPlainText().right(ui.textEdit->toPlainText().size() - staticContentLen);
				// Carl: get latest input content;

				if (newInput.size()) {
					// Carl: latest input is not empty

					LogInsert(newInput);
					// Carl: insert lastest log into the list

					StaticContentDisplayAtEnd("\n");
					// Carl: enter

					InstructionProcess(newInput);
					// Carl: process the lastes input

				}
				else {
					StaticContentDisplayAtEnd("\n>> ");
					// Carl: add static content "\n>> "
				}

#ifdef KEY_RETURN_VERSION_1

				ui.textEdit->setText(ui.textEdit->toPlainText() + "\n>> ");
				// Carl: add input sign ">> "

				staticContentLen = ui.textEdit->toPlainText().size();
				// Carl: used for update saved content length, "+4" is represented for "\n>> "

				cursor.movePosition(QTextCursor::End);
				ui.textEdit->setTextCursor(cursor);
				// Carl: move cursor to the end of text;

#endif // KEY_RETURN_VERSION_1

#ifdef KEY_RETURN_VERSION_2
				// Carl: higher efficiency compared with KEY_RETURN_VERSION_1

				//if (cursor.position() < staticContentLen) {
				//	cursor.movePosition(QTextCursor::End);
				//	ui.textEdit->setTextCursor(cursor);
				//}
				//// Carl: move cursor to the end of text;

				//StaticContentDisplayAtEnd("\n>> ");
				//// Carl: add static content "\n>> "

				QScrollBar *scrollBar = ui.textEdit->verticalScrollBar();
				scrollBar->setValue(scrollBar->maximum());
				// Carl: set scrollBar to the bottom position

#endif // KEY_RETURN_VERSION_2

				return true;
			}
			else if (keyEvent->key() == Qt::Key_Backspace){
				// Carl: used for dealing with the backspace key

				// Carl: deal with input content 
				/* when length of input content is larger than staticContentLen, 
				* the current string is able to be deleted.
				* when length of input content is equal to staticContentLen, 
				* the current string is not able to be deleted */
				if (ui.textEdit->toPlainText().size() <= staticContentLen) {
					// Carl: eat event;
					return true;
				}
					
				else {
					if (!ui.textEdit->textCursor().hasSelection() && ui.textEdit->textCursor().position() <= staticContent) {
						return true;
					}

					if (ui.textEdit->textCursor().hasSelection()) {

						if (ui.textEdit->textCursor().selectionEnd() < staticContentLen) {
							return true;
						}
						else if (ui.textEdit->textCursor().selectionStart() < staticContentLen) {
							int delectedLen = ui.textEdit->textCursor().selectionEnd() - staticContentLen;
							cursor.setPosition(staticContentLen);
							ui.textEdit->setTextCursor(cursor);
							for (int i = 0; i < delectedLen; i++)
								cursor.deleteChar();
							return true;
						}
						else if (ui.textEdit->textCursor().selectionStart() > staticContentLen) {
							int delectedLen = ui.textEdit->textCursor().selectedText().size();
							cursor.setPosition(ui.textEdit->textCursor().selectionStart());
							ui.textEdit->setTextCursor(cursor);
							for (int i = 0; i < delectedLen; i++)
								cursor.deleteChar();
							return true;
						}
						else {
							return false;
						}

					}
				}

			}
			else if (keyEvent->key() == Qt::UpArrow) {
				return true;
			}
			else if (cursor.position() < staticContentLen) {
				// Carl: used for detecting if the cursor is inserted into the static content;
				/* static content means that when you input one piece of instruction and press enter key,
				* any content you entered before the enter key is called static content.
				* this is a protection for the misinput of content */

				cursor.movePosition(QTextCursor::End);
				ui.textEdit->setTextCursor(cursor);

				return false;
			}
		}


	}
	/****************************************ui.textEdit****************************************/



	/****************************************ui.textEdit->viewport()****************************************/
	if (object == ui.textEdit->viewport()) {

		if (e->type() == QEvent::Drop){
			// Carl: catch drop event in textEdit
			/* Because the path string is added to the textEdit after this function is finished execution,
			* bool variable "isDropped" is designed to solve this question, 
			* transmit this uncomplished function to the next eventfilter execution, 
			* which is at the begining of object == ui.textEdit part */
			
			isDropped = true;

			QDropEvent *dropEvent = static_cast<QDropEvent *>(e);
			droppedContent = dropEvent->mimeData()->text();
			// Carl: store the dragged content

			return false;

		}

	}
	/****************************************ui.textEdit->viewport()****************************************/



	/****************************************ui.tableView_Log****************************************/
	if (object == ui.tableView_Log->viewport()) {

		

	}
	/****************************************ui.tableView_Log****************************************/


	return false;
}