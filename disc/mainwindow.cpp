#include <QtGui>

#include "finddialog.h"
#include "gotocelldialog.h"
#include "mainwindow.h"
#include "sortdialog.h"
#include "spreadsheet.h"


MainWindow::MainWindow()
{
    spreadsheet = new Spreadsheet;
    setCentralWidget(spreadsheet);

    creatActions();
    creatMenus();
    creatContextMenu();
    creatToolBars();
    creatStatusBar();

    readSettings();

    findDialog = 0;

    setWindowIcon(":/images/icon.png");
    setCurrentFile("");
}

MainWindow::createActions()
{
    newAction = new QAction(tr("&New"), this);
    newAction->setIcon(QIcon(":/images/new.png"));
    newAction->setShortCut(QKeySequence::New);
    newAction->setStatusTip(tr("Create a new spreadsheet file"));
    connect(newAction, SIGNAL(triggered()), this, SLOT(newFile());

    openAction = new Qaction(tr("&Open..."), this);
    openAction->setIcon(QIcon(":/images/open.png"));
    openAction->setShortCut(QKeySequence::Open);
    openAction->setStatusTip(tr("Open a spreadsheet file"));
    connect(openAction, SIGNAL(triggered()), this, SLOT(open());

    saveAction = new Qaction(tr("&Save"), this);
    saveAction->setIcon(QIcon(":/images/save.png"));
    saveAction->setShortCut(QKeySequence::Save);
    saveAction->setStatusTip(tr("Save a spreadsheet file"));
    connect(saveAction, SIGNAL(triggered()), this, SLOT(save());

    saveAsAction = new Qaction(tr("Save &As..."), this);
    saveAsAction->setShortCut(QKeySequence::SaveAs);
    saveAsAction->setStatusTip(tr("Save as a spreadsheet file"));
    connect(saveAsAction, SIGNAL(triggered()), this, SLOT(saveAs());

    for(int i = 0; i < MaxRecentFiles; ++i){
        recentFileActions[i] = new QAction(this);
        recentFileActions[i]->setVisible(false);
        connect(recentFileActions[i], SIGNAL(triggered()), this, SLOT(openRecentFile());
    }

    exitAction = new QAction(tr("E&xit"), this);
    exitAction->setShortCut(tr("Ctrl+Q"));
    exitAction->setStatusTips(tr("Exit the application"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close());

    cutAction = new QAction(tr("Cu&t"), this);
    cutAction->setIcon(QIcon(":/images/cut.png"));
    cutAction->setShortCut(QKeySequence::Cut);
    cutAction->setStatusTip(tr("Cut"));
    connect(cutAction, SIGNAL(triggered()), this, SLOT(cut());

    copyAction = new QAction(tr("Cu&t"), this);
    copyAction->setIcon(QIcon(":/images/copy.png"));
    copyAction->setShortCut(QKeySequence::Copy);
    copyAction->setStatusTip(tr("Copy"));
    connect(copyAction, SIGNAL(triggered()), this, SLOT(copy());

    pasteAction = new QAction(tr("Cu&t"), this);
    pasteAction->setIcon(QIcon(":/images/paste.png"));
    pasteAction->setShortCut(QKeySequence::Paste);
    pasteAction->setStatusTip(tr("Paste"));
    connect(pasteAction, SIGNAL(triggered()), this, SLOT(paste());

    deleteAction = new QAction(tr("Cu&t"), this);
    deleteAction->setShortCut(QKeySequence::Delete);
    deleteAction->setStatusTip(tr("Delete"));
    connect(deleteAction, SIGNAL(triggered()), this, SLOT(deleteStuff());

    selectRowAction = new QAction(tr("&Row"), this);
    selectRowAction->setStatusTip(tr("Select an entire row in the spreadsheet"));
    connect(selectRowAction, SIGNAL(triggered()), spreadsheet, SLOT(selectrow()));

    selectColAction = new QAction(tr("&Col"), this);
    selectColAction->setStatusTip(tr("Select an entire coloumn in the spreadsheet"));
    connect(selectColAction, SIGNAL(triggered()), spreadsheet, SLOT(selectcol()));

    selectAllAction = new QAction(tr("&All"), this);
    selectAllAction->setShortCut(QKeySequence::SelectAll);
    selectAllAction->setStatusTip(tr("Select all the cells in the spreadsheet"));
    connect(selectAllAction, SIGNAL(triggered()), spreadsheet, SLOT(selectall()));

    findAction = new QAction(tr("&Find..."), this);
    findAction->setIcon(QIcon(":/images/find.png"));
    findAction->setShortCut(QKeySequence::Find);
    findAction->setStatusTip(tr("Find"));
    connect(findAction, SIGNAL(triggered()), this, SLOT(find());

    goToCellAction = new QAction(tr("&Go to Cell..."), this);
    goToCellAction->setIcon(QIcon(":/images/gotocell.png"));
    goToCellAction->setShortCut(tr("Ctrl+G"));
    goToCellAction->setStatusTip(tr("Find"));
    connect(goToCellAction, SIGNAL(triggered()), this, SLOT(goToCell());

    recalculateAction = new QAction(tr("&Recalculate"), this);
    recalculateAction->setShortCut(tr("F9"));
    recalculateAction->setStatusTip(tr("Recalculate"));
    connect(recalculateAction, SIGNAL(triggered()), this, SLOT(recalculate());

    sortAction = new QAction(tr("&Sort"), this);
    sortAction->setStatusTip(tr("Sort"));
    connect(sortAction, SIGNAL(triggered()), this, SLOT(sort());

    showGridAction = new QAction(tr("&Show Grid"), this);
    showGridAction->setCheckable(true);
    showGridAction->setStatusTip(tr("Show or hide the spreadseet's grid"));
    connect(showGridAction, SIGNAL(toggled(bool)), spreadsheet, SLOT(setShowGrid(bool)));

    autoRecalculateAction = new QAction(tr("&Auto-Recalculate"), this);
    autoRecalculateAction->setCheckable(true);
    autoRecalculateAction->setStatusTip(tr("Auto-recalculate or not"));
    connect(autoRecalculateAction, SIGNAL(toggled(bool)), spreadsheet, SLOT(setAutoRecalculation(bool)));

    aboutAction = new QAction(tr("&About"), this);
    aboutAction->setStatusTip(tr("Show the SpreadSheet's About box"));
    connect(aboutAction, SIGNAL(triggered()), qApp, SLOT(about()));

    aboutQtAction = new QAction(tr("About &Qt"), this);
    aboutQtAction->setStatusTip(tr("Show the Qt library's About box"));
    connect(aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

void MainWindow::createMenus(){
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(saveAsAction);
    separatorAction = fileMenu->addSeparator();
    for(int i = 0; i < MaxRecentFiles; ++i)
        fileMenu->addAction(recentFileActions[i]);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(cutAction);
    editMenu->addAction(copyAction);
}
