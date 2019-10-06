#include "filemanager.h"

#include <QDateTime>
#include <QStandardPaths>
#include <QDebug>

FileManager::FileManager(SideBarModel *sideBarModel, QObject *parent):
  QObject(parent),
  mSidebarModel(sideBarModel)
{
  // TODO: What happens after resuming the computer?
  mFileWatcher = new QFileSystemWatcher();
  mIgnoreLastChange = false;
  mFileWatcher->addPath(fileDirPath());
  QStringList files = fileDir().entryList(QStringList() << "*.txt", QDir::Files);
  foreach(QString filename, files) {
    sideBarModel->addFile(QFile(fileDirPath() + "/" + filename));
    mFileWatcher->addPath(fileDirPath() + "/" + filename);
    qDebug() << "filename" << filename;
  }
  connect(mFileWatcher, &QFileSystemWatcher::directoryChanged, this, [=] (QString path) {
    qDebug() << "directoryChanged" << path;
    QDir dir(path);
    QStringList files = dir.entryList(QStringList() << "*.txt", QDir::Files);
    qDebug() << files;
    // Add new files
    foreach(QString filename, files) {
      QString fullPath = fileDirPath() + "/" + filename;
      if (!mFileWatcher->files().contains(fullPath)) {
        qDebug() << "New file:" << fullPath;
        sideBarModel->addFile(QFile(fullPath));
        mFileWatcher->addPath(fullPath);
      }
    }
    // Remove deleted files
    foreach(QString fullPath, mFileWatcher->files()) {
      auto chunks = fullPath.split("/");
      qDebug() << "chunks:" << chunks;
      QString fileName = chunks[chunks.length() - 1];
      qDebug() << "fileName:" << fileName;
      if (!files.contains(fileName)) {
        fileRemoved(fullPath);
      }
    }
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
    mIgnoreLastChange = true;
    QFile *file = currentFile();
    file->open(QIODevice::WriteOnly | QIODevice::Text);
    file->write(text.toStdString().c_str());
    file->close();
    delete file;
  } else {
    qDebug() << "Same content...";
  }
}

void FileManager::fileChanged(QString path) {
  qDebug() << "fileChanged" << path;
  if (QFile(path).exists()){
    if (path == this->currentFile()->fileName()) {
      if (mIgnoreLastChange) {
        qDebug() << "Ignoring..." << path;
        mIgnoreLastChange = false;
      } else {
        emit onFileChanged(this->readFile());
      }
    }
  } else {
    fileRemoved(path);
  }
}

void FileManager::fileRemoved(QString path) {
  qDebug() << "Deleted file:" << path;
  mSidebarModel->removeFile(QFile(path));
  mFileWatcher->removePath(path); // TODO: It triggers as changed, what to do?
}
