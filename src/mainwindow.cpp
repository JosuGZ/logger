#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <stdlib.h>
#include <time.h>

#include "QDateTime"
#include <QClipboard>
#include <QClipboard>
#include <QDebug>

#include <string>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mSideBarModel(new SideBarModel()),
    mFileManager(new FileManager(mSideBarModel))
{
  ui->setupUi(this);

  QTextDocument *log = new QTextDocument("log");
  ui->logViewer->setDocument(log);
  onFileChanged(mFileManager->readFile());
  ui->fileList->setModel(mSideBarModel);
#ifdef __linux__
  ui->actionToggleOnTop->setVisible(false);
#endif
  connect(ui->Enter,SIGNAL(clicked()),this,SLOT(paste()));
  connect(ui->actionToggleOnTop,SIGNAL(triggered()),this,SLOT(toggleOnTop()));
  connect(ui->actionUndo,SIGNAL(triggered()),this,SLOT(undo()));
  connect(ui->enterButton,SIGNAL(clicked()),this,SLOT(enter()));
  connect(ui->lineEdit,SIGNAL(returnPressed()),this,SLOT(enter()));
  connect(ui->logViewer, &QPlainTextEdit::textChanged, this, [=] {
    mFileManager->saveFile(ui->logViewer->toPlainText());
  });
  connect(mFileManager, &FileManager::onFileChanged, this, &MainWindow::onFileChanged);
  this->log("App starting...");
  ui->lineEdit->setFocus();
}

void MainWindow::toggleOnTop() {
  if( this->windowFlags() & Qt::WindowStaysOnTopHint ) {
#ifdef __linux__
    this->setWindowFlags(this->windowFlags() & ~( Qt::WindowStaysOnTopHint | Qt::X11BypassWindowManagerHint ) );
#else
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowStaysOnTopHint);
#endif
  } else {
#ifdef __linux__
    this->setWindowFlags(this->windowFlags() | Qt::WindowStaysOnTopHint | Qt::X11BypassWindowManagerHint);
#else
    this->setWindowFlags(this->windowFlags() | Qt::WindowStaysOnTopHint);
#endif
  }
  this->show();
}

void MainWindow::log(const QString &text) {
  ui->logViewer->appendPlainText(
    QDateTime::currentDateTime().toString("hh:mm:ss") +
    " -> " + text
  );
  ui->logViewer->moveCursor(QTextCursor::MoveOperation::End);
}

void MainWindow::paste() {
  const QClipboard *clipboard = QApplication::clipboard();
  log(clipboard->text());
}

void MainWindow::enter() {
  log(ui->lineEdit->text());
  ui->lineEdit->clear();
}

void MainWindow::undo() {
  ui->logViewer->document()->undo();
}

MainWindow::~MainWindow() {
  delete mFileManager;
  delete mSideBarModel;
  delete ui;
}

void MainWindow::onFileChanged(const QString &text) {
  ui->logViewer->setPlainText(text);
}
