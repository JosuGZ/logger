#include "sidebarmodel.h"

#include <QDebug>

SideBarModel::SideBarModel(QObject *parent):
  QAbstractListModel(parent),
  mFiles(new std::vector<std::unique_ptr<QFile>>())
{

}

QModelIndex SideBarModel::addFile(const QFile &file) {
  int rowIndex = rowCount();
  beginInsertRows(QModelIndex(), rowIndex, rowIndex);
  std::unique_ptr<QFile> newFile(new QFile(file.fileName()));
  mFiles->push_back(move(newFile));
  endInsertRows();
  return index(rowIndex, 0);
}

void SideBarModel::removeFile(const QFile &file) {
  qDebug() << "Deleting" << file.fileName();
  for (int i=0; i<rowCount(); ++i) {
    const QFile &currentFile = *mFiles->at(static_cast<uint>(i));
    if (currentFile.fileName() == file.fileName()) {
      removeRows(i, 1);
      break;
    }
  }
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
int SideBarModel::rowCount(const QModelIndex &parent) const {
  return int(this->mFiles->size());
}
#pragma GCC diagnostic pop

QVariant SideBarModel::data(const QModelIndex &index, int role) const {
  return data(index.row(), role);
}

QVariant SideBarModel::data(int index, int role) const {
  if (!isIndexValid(index)) {
    return QVariant();
  }

  const QFile &file = *mFiles->at(static_cast<uint>(index));
  switch (role) {
    case Qt::DisplayRole:
      return file.fileName();
    default:
      return QVariant();
  }
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wreturn-type"
bool SideBarModel::setData(const QModelIndex &index, const QVariant &value, int role) {
  assert(false); // Not implemented
}
#pragma GCC diagnostic pop

bool SideBarModel::removeRows(int row, int count, const QModelIndex &parent) {
  beginRemoveRows(parent, row, row + count - 1);
  mFiles->erase(mFiles->begin() + row, mFiles->begin() + row + count);
  return true;
}

QHash<int, QByteArray> SideBarModel::roleNames() const {
  QHash<int, QByteArray> roles;
  roles[Roles::NameRole] = "display name";
  return roles;
}

bool SideBarModel::isIndexValid(int index) const {
  return index >= 0 && index < rowCount();
}

bool SideBarModel::isIndexValid(const QModelIndex &index) const {
  return isIndexValid(index.row());
}
