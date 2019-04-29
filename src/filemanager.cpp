#include "filemanager.h"

#include <QDateTime>
#include <QStandardPaths>
#include <QDebug>

FileManager::FileManager(QObject *parent) : QObject(parent) {
  // TODO: What happens after resuming computer?
  mFileWatcher = new QFileSystemWatcher();
  mFileWatcher->addPath(fileDirPath());
  QStringList files = fileDir().entryList(QStringList() << "*.txt", QDir::Files);
  foreach(QString filename, files) {
    mFileWatcher->addPath(fileDirPath() + "/" + filename);
    qDebug() << "filename" << filename;
  }
  connect(mFileWatcher, &QFileSystemWatcher::directoryChanged, this, [=] (QString path) {
    qDebug() << "directoryChanged" << path;
  });
  connect(mFileWatcher, &QFileSystemWatcher::fileChanged, this, &FileManager::fileChanged);
}

FileManager::~FileManager() {
  delete mFileWatcher;
}

QString FileManager::fileDirPath() {
  QString path = (
    QStandardPaths::QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) +
    "/" + APP_FOLDER
  );
  return path;
}

QDir FileManager::fileDir() {
  QString path = fileDirPath();
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

QString FileManager::readFile() {
  QFile *file = currentFile();
  file->open(QIODevice::ReadOnly | QIODevice::Text);
  QString text = QString::fromStdString(file->readAll().toStdString());
  file->close();
  delete file;
  return text;
}

void FileManager::saveFile(QString text) {
  qDebug() << "Saving file...";
  if (text != readFile()) { // TODO:
    QFile *file = currentFile();
    file->open(QIODevice::WriteOnly | QIODevice::Text);
    file->write(text.toStdString().c_str());
    file->close();
    delete file;
  } else {
    qDebug() << "File not changed...";
  }
}

void FileManager::fileChanged(QString path) {
  qDebug() << "fileChanged" << path;
  if (path == this->currentFile()->fileName()) {
    emit onFileChanged(this->readFile());
  }
}
