#include "MatrixComplier.h"

void MatrixComplier::Initialization() {
	// Carl: abstract of initialization;

	ExplorerInit();
	FileInfoInit();
	MainTextAreaInit();
	VarListInit();
	LogListInit();

	ConnectionInit();

	StyleInit();
}

void MatrixComplier::ExplorerInit() {
	// Carl: initialization of file explorer; 

	// Carl: ----------------------define QFileSystemModel model--------------------------------
	QString rootPath = "";
	dirModel = new QFileSystemModel(this);
	//dirModel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
	// Carl: display files in a given directory or not;
	dirModel->setRootPath(rootPath);
	// Carl: set up QFileSystemModel to present directories;
	// Carl: ----------------------define QFileSystemModel model--------------------------------


	// Carl: -------------------- set tableView properities --------------------
	ui.treeView->setModel(dirModel);
	// Carl: set dirmodel;
	for (int i = 1; i < dirModel->columnCount(); i++)
		ui.treeView->hideColumn(i);
	// Carl: show the first column, name, of the directory tree;
	ui.treeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
	// Carl: make treewidget "horizontal" autoscroll activated;
	// Carl: -------------------- set tableView properities --------------------

}

void MatrixComplier::FileInfoInit() {
	// Carl: initialization of file information list;

	// Carl: ----------------------define QStandardItemModel model--------------------------------
	fileModel = new QStandardItemModel(this);
	fileModel->setColumnCount(3);
	fileModel->setHeaderData(0, Qt::Horizontal, QString::fromStdString("Property"));
	fileModel->setHeaderData(1, Qt::Horizontal, QString::fromStdString("Information"));
	fileModel->setHeaderData(2, Qt::Horizontal, QString::fromStdString(""));
	// Carl: set up QStansardItemModel to present properties;
	// Carl: -------------------- define QStandardItemModel model --------------------


	// Carl: -------------------- set tableView properities --------------------
	ui.tableView_Info->setModel(fileModel);
	// Carl: set fileModel
	ui.tableView_Info->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
	// Carl: set the content in the header align leftside
	ui.tableView_Info->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	// Carl: make treewidget "horizontal" autoscroll activated;
	// Carl: -------------------- set tableView properities --------------------


	// Carl: -------------------- add QStandardItem to tableView --------------------
	// Carl: add rows;
	QList<QStandardItem*> item;
	item << new QStandardItem(tr("File Name")) << new QStandardItem(tr(""));
	fileModel->appendRow(item);
	item.clear();
	item << new QStandardItem(tr("File Type")) << new QStandardItem(tr(""));
	fileModel->appendRow(item);
	item.clear();
	item << new QStandardItem(tr("File Path")) << new QStandardItem(tr(""));
	fileModel->appendRow(item);
	item.clear();
	item << new QStandardItem(tr("File Size")) << new QStandardItem(tr(""));
	fileModel->appendRow(item);
	item.clear();
	item << new QStandardItem(tr("Hidden")) << new QStandardItem(tr(""));
	fileModel->appendRow(item);
	item.clear();
	item << new QStandardItem(tr("Excutable")) << new QStandardItem(tr(""));
	fileModel->appendRow(item);
	item.clear();
	item << new QStandardItem(tr("Readability")) << new QStandardItem(tr(""));
	fileModel->appendRow(item);
	item.clear();
	item << new QStandardItem(tr("Writability")) << new QStandardItem(tr(""));
	fileModel->appendRow(item);
	item.clear();
	item << new QStandardItem(tr("Created")) << new QStandardItem(tr(""));
	fileModel->appendRow(item);
	item.clear();
	item << new QStandardItem(tr("Last Read")) << new QStandardItem(tr(""));
	fileModel->appendRow(item);
	item.clear();
	item << new QStandardItem(tr("Last Modified")) << new QStandardItem(tr(""));
	fileModel->appendRow(item);
	item.clear();
	item << new QStandardItem(tr("Owner")) << new QStandardItem(tr(""));
	fileModel->appendRow(item);
	item.clear();
	item << new QStandardItem(tr("Owner ID")) << new QStandardItem(tr(""));
	fileModel->appendRow(item);
	item.clear();
	item << new QStandardItem(tr("Group")) << new QStandardItem(tr(""));
	fileModel->appendRow(item);
	item.clear();
	item << new QStandardItem(tr("Group ID")) << new QStandardItem(tr(""));
	fileModel->appendRow(item);
	item.clear();
	// Carl: -------------------- add QStandardItem to tableView --------------------

}

void MatrixComplier::MainTextAreaInit() {
	// Carl: initialization of text edit;

	// Carl: ---------------------- input sign initialization ----------------------
	//ui.textEdit->setText(">> ");
	//staticContentLen = 3;
	StaticContentDisplayAtEnd(">> ");
	// Carl: ---------------------- input sign initialization ----------------------


	// Carl: ---------------------- install event filter ----------------------
	ui.textEdit->installEventFilter(this);
	ui.textEdit->viewport()->installEventFilter(this);
	// Carl install event filter for textEdit
	// Carl: ---------------------- install event filter ----------------------
	
}

void MatrixComplier::VarListInit() {
	// Carl: initialization of variable list;

	// Carl: ----------------------define QStandardItemModel model--------------------------------
	varModel = new QStandardItemModel(this);
	varModel->setColumnCount(3);
	varModel->setHeaderData(0, Qt::Horizontal, QString::fromStdString("Name"));
	varModel->setHeaderData(1, Qt::Horizontal, QString::fromStdString("Content"));
	varModel->setHeaderData(2, Qt::Horizontal, QString::fromStdString(""));
	// Carl: ----------------------define QStandardItemModel model--------------------------------

	// Carl: -------------------- set tableView properities --------------------
	ui.tableView_Var->setModel(varModel);
	// Carl: set varModel;
	ui.tableView_Var->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
	// Carl: set the content in the header align leftside
	ui.tableView_Var->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	// Carl: make treewidget "horizontal" autoscroll activated;
	// Carl: -------------------- set tableView properities --------------------

}

void MatrixComplier::LogListInit() {
	// Carl: initialization of log information list;

	// Carl: ----------------------define QStandardItemModel model--------------------------------
	logModel = new QStandardItemModel(this);
	logModel->setColumnCount(3);
	logModel->setHeaderData(0, Qt::Horizontal, QString::fromStdString("Time"));
	logModel->setHeaderData(1, Qt::Horizontal, QString::fromStdString("Instruction"));
	logModel->setHeaderData(2, Qt::Horizontal, QString::fromStdString(""));
	// Carl: set up QstandardItemModel to present properties
	// Carl: ----------------------define QStandardItemModel model--------------------------------


	// Carl: -------------------- set tableView properities --------------------
	ui.tableView_Log->setModel(logModel);
	// Carl: set logModel;
	ui.tableView_Log->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
	// Carl: set the content in the header align leftside
	ui.tableView_Log->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	// Carl: make treewidget "horizontal" autoscroll activated;
	// Carl: -------------------- set tableView properities --------------------


	// Carl: ---------------------- install event filter ----------------------
	ui.tableView_Log->installEventFilter(this);
	// Carl install event filter for textEdit
	// Carl: ---------------------- install event filter ----------------------

}

void MatrixComplier::ConnectionInit() {
	// Carl: initialization of connection between SIGNAL and SLOT

	connect(ui.treeView, SIGNAL(pressed(QModelIndex)), this, SLOT(FileInfoDisplay(QModelIndex)));

	connect(ui.tableView_Log, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(LogInstructionRecall(QModelIndex)));
	
}

void MatrixComplier::StyleInit() {
	// Carl: initialization of widget style

	// Carl: set style of file info table view 
	/*for (int i = 0; i < ui.tableView_Info->model()->rowCount(); i++) {
		if (i % 2 == 0) {
			ui.tableView_Info->model()->setData(ui.tableView_Info->model()->index(i, 0), QVariant(QColor(232, 232, 232)), Qt::BackgroundRole);
		}
	}*/

}