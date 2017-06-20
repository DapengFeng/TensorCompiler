/********************************************************************************
** Form generated from reading UI file 'MatrixComplier.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MATRIXCOMPLIER_H
#define UI_MATRIXCOMPLIER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MatrixComplierClass
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QHBoxLayout *horizontalLayout_Main;
    QVBoxLayout *verticalLayout_Left;
    QVBoxLayout *verticalLayout_Dir;
    QTreeView *treeView;
    QVBoxLayout *verticalLayout_Info;
    QTableView *tableView_Info;
    QVBoxLayout *verticalLayout_Med;
    QPushButton *pushButton;
    QTextEdit *textEdit;
    QVBoxLayout *verticalLayout_Right;
    QVBoxLayout *verticalLayout_Var;
    QTableView *tableView_Var;
    QVBoxLayout *verticalLayout_Log;
    QTableView *tableView_Log;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MatrixComplierClass)
    {
        if (MatrixComplierClass->objectName().isEmpty())
            MatrixComplierClass->setObjectName(QStringLiteral("MatrixComplierClass"));
        MatrixComplierClass->resize(1111, 786);
        centralWidget = new QWidget(MatrixComplierClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout_Main = new QHBoxLayout();
        horizontalLayout_Main->setSpacing(6);
        horizontalLayout_Main->setObjectName(QStringLiteral("horizontalLayout_Main"));
        verticalLayout_Left = new QVBoxLayout();
        verticalLayout_Left->setSpacing(6);
        verticalLayout_Left->setObjectName(QStringLiteral("verticalLayout_Left"));
        verticalLayout_Left->setSizeConstraint(QLayout::SetDefaultConstraint);
        verticalLayout_Dir = new QVBoxLayout();
        verticalLayout_Dir->setSpacing(6);
        verticalLayout_Dir->setObjectName(QStringLiteral("verticalLayout_Dir"));
        treeView = new QTreeView(centralWidget);
        treeView->setObjectName(QStringLiteral("treeView"));
        treeView->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContentsOnFirstShow);
        treeView->setDragEnabled(true);
        treeView->setDragDropMode(QAbstractItemView::DragOnly);
        treeView->header()->setVisible(true);
        treeView->header()->setHighlightSections(false);
        treeView->header()->setStretchLastSection(false);

        verticalLayout_Dir->addWidget(treeView);


        verticalLayout_Left->addLayout(verticalLayout_Dir);

        verticalLayout_Info = new QVBoxLayout();
        verticalLayout_Info->setSpacing(6);
        verticalLayout_Info->setObjectName(QStringLiteral("verticalLayout_Info"));
        tableView_Info = new QTableView(centralWidget);
        tableView_Info->setObjectName(QStringLiteral("tableView_Info"));
        tableView_Info->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableView_Info->setAlternatingRowColors(true);
        tableView_Info->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableView_Info->setGridStyle(Qt::NoPen);
        tableView_Info->horizontalHeader()->setVisible(false);
        tableView_Info->horizontalHeader()->setCascadingSectionResizes(false);
        tableView_Info->horizontalHeader()->setStretchLastSection(true);
        tableView_Info->verticalHeader()->setVisible(false);

        verticalLayout_Info->addWidget(tableView_Info);


        verticalLayout_Left->addLayout(verticalLayout_Info);


        horizontalLayout_Main->addLayout(verticalLayout_Left);

        verticalLayout_Med = new QVBoxLayout();
        verticalLayout_Med->setSpacing(6);
        verticalLayout_Med->setObjectName(QStringLiteral("verticalLayout_Med"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        verticalLayout_Med->addWidget(pushButton);

        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));

        verticalLayout_Med->addWidget(textEdit);


        horizontalLayout_Main->addLayout(verticalLayout_Med);

        verticalLayout_Right = new QVBoxLayout();
        verticalLayout_Right->setSpacing(6);
        verticalLayout_Right->setObjectName(QStringLiteral("verticalLayout_Right"));
        verticalLayout_Var = new QVBoxLayout();
        verticalLayout_Var->setSpacing(6);
        verticalLayout_Var->setObjectName(QStringLiteral("verticalLayout_Var"));
        tableView_Var = new QTableView(centralWidget);
        tableView_Var->setObjectName(QStringLiteral("tableView_Var"));
        tableView_Var->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableView_Var->setAlternatingRowColors(true);
        tableView_Var->setShowGrid(false);
        tableView_Var->horizontalHeader()->setVisible(false);
        tableView_Var->horizontalHeader()->setStretchLastSection(true);
        tableView_Var->verticalHeader()->setVisible(false);

        verticalLayout_Var->addWidget(tableView_Var);


        verticalLayout_Right->addLayout(verticalLayout_Var);

        verticalLayout_Log = new QVBoxLayout();
        verticalLayout_Log->setSpacing(6);
        verticalLayout_Log->setObjectName(QStringLiteral("verticalLayout_Log"));
        tableView_Log = new QTableView(centralWidget);
        tableView_Log->setObjectName(QStringLiteral("tableView_Log"));
        tableView_Log->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableView_Log->setAlternatingRowColors(true);
        tableView_Log->setShowGrid(false);
        tableView_Log->horizontalHeader()->setVisible(false);
        tableView_Log->horizontalHeader()->setStretchLastSection(true);
        tableView_Log->verticalHeader()->setVisible(false);

        verticalLayout_Log->addWidget(tableView_Log);


        verticalLayout_Right->addLayout(verticalLayout_Log);


        horizontalLayout_Main->addLayout(verticalLayout_Right);

        horizontalLayout_Main->setStretch(0, 1);
        horizontalLayout_Main->setStretch(1, 2);
        horizontalLayout_Main->setStretch(2, 1);

        horizontalLayout->addLayout(horizontalLayout_Main);

        MatrixComplierClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MatrixComplierClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1111, 23));
        MatrixComplierClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MatrixComplierClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MatrixComplierClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MatrixComplierClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MatrixComplierClass->setStatusBar(statusBar);

        retranslateUi(MatrixComplierClass);

        QMetaObject::connectSlotsByName(MatrixComplierClass);
    } // setupUi

    void retranslateUi(QMainWindow *MatrixComplierClass)
    {
        MatrixComplierClass->setWindowTitle(QApplication::translate("MatrixComplierClass", "MatrixComplier", 0));
        pushButton->setText(QApplication::translate("MatrixComplierClass", "PushButton", 0));
    } // retranslateUi

};

namespace Ui {
    class MatrixComplierClass: public Ui_MatrixComplierClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MATRIXCOMPLIER_H
