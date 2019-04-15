#include "filemanager.h"

#include <QDateTime>
#include <QStandardPaths>

FileManager::FileManager(QObject *parent) : QObject(parent) {

}

QDir FileManager::fileDir() {
  QString path = (
    QStandardPaths::QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) +
    "/" + APP_FOLDER
  );
  QDir dir(path);
  if (!dir.exists()) {
    dir.mkpath(path); // TODO: Check for errors
  }
  return dir;
}

QFile *FileManager::currentFile() {
  QDir dir = fileDir();
  QString fileName = QDateTime::currentDateTime().toString("yyyy-MM-dd") + ".txt";
  QFile *file = new QFile(dir.path() + "/" + fileName); // TODO: Windows?
  return file;
}

void FileManager::saveFile(QString text) {
  QFile *file = currentFile();
  file->open(QIODevice::WriteOnly | QIODevice::Text);
  file->write(text.toStdString().c_str());
  file->close();
  delete file;
}
