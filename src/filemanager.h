#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "models/sidebarmodel.h"

#include <QFile>
#include <QDir>
#include <QObject>
#include <QFileSystemWatcher>

#define APP_FOLDER "Logger"

class FileManager : public QObject {
  Q_OBJECT
public:
  explicit FileManager(SideBarModel *sideBarModel, QObject *parent = nullptr);
  ~FileManager();
  QString fileDirPath();
  QDir fileDir();
  QFile *currentFile(); // TODO: Watch for changes, check for write access,
                        //       update as days pass, check for errors...
  QString readFile();

signals:
  void onFileChanged(QString text);

public slots:
  void saveFile(QString);

private:
  SideBarModel *mSidebarModel;
  QFileSystemWatcher *mFileWatcher;
  bool mIgnoreLastChange;

private slots:
  void fileChanged(QString path);
  void fileRemoved(QString path);
};

#endif // FILEMANAGER_H
