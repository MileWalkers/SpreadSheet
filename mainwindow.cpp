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

    openAction = new Qaction(tr("&Open"), this);
    openAction->setIcon(QIcon(":/images/open.png"));
    openAction->setShortCut(QKeySequence::Open);
    openAction->setStatusTip(tr("Open a spreadsheet file"));
    connect(openAction, SIGNAL(triggered()), this, SLOT(open());

    saveAction = new Qaction(tr("&Save"), this);
    saveAction->setIcon(QIcon(":/images/save.png"));
    saveAction->setShortCut(QKeySequence::Save);
    saveAction->setStatusTip(tr("Save a spreadsheet file"));
    connect(saveAction, SIGNAL(triggered()), this, SLOT(save());

    saveAsAction = new Qaction(tr("&Save as"), this);
    saveAsAction->setIcon(QIcon(":/images/saveas.png"));
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

    selectAllAction = new QAction(tr("&All"), this);
    selectAllAction->setShortCut(QKeySequence::SelectAll);
    selectAllAction->setStatusTip(tr("Select all the cells in the spreadsheet"));
    connect(selectAllAction, SIGNAL(triggered()), spreadsheet, SLOT(selectall()));

    showGridAction = new QAction(tr("&Show Grid"), this);
    showGridAction->setCheckable(true);
    showGridAction->setStatusTip(tr("Show or hide the spreadseet's grid"));
    connect(showGridAction, SIGNAL(toggled(bool)), spreadsheet, SLOT(setShowGrid(bool)));

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
