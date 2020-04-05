#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "models/sidebarmodel.h"
#include "filemanager.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

public slots:
  void onFileChanged(const QString &text);
  void log(const QString &text);
  void paste();
  void toggleOnTop();
  void enter();
  void undo();
  void addDate();
  void addSeparator();

private:
  Ui::MainWindow *ui;
  SideBarModel *mSideBarModel;
  FileManager *mFileManager;
};

#endif // MAINWINDOW_H
