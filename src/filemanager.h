#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QFile>
#include <QDir>
#include <QObject>

#define APP_FOLDER "Logger"

class FileManager : public QObject {
  Q_OBJECT
public:
  explicit FileManager(QObject *parent = nullptr);
  QDir fileDir();
  QFile *currentFile(); // TODO: Watch for changes, check for write access,
                        //       update as days pass, check for errors...
  QString readFile();

signals:

public slots:
  void saveFile(QString);
};

#endif // FILEMANAGER_H
