#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
  void paste();
  void toggleOnTop();
  void enter();
  void undo();

private:
  Ui::MainWindow *ui;
  FileManager mFileManager;
};

#endif // MAINWINDOW_H
