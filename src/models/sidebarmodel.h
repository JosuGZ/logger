#ifndef SIDEBARMODEL_H
#define SIDEBARMODEL_H

#include <vector>
#include <memory>
#include <assert.h>

#include <QFile>
#include <QAbstractListModel>

class SideBarModel : public QAbstractListModel {
  Q_OBJECT

public:
  enum Roles {
    NameRole = Qt::UserRole + 1
  };
  SideBarModel(QObject *parent = nullptr);
  QModelIndex addFile(const QFile &file);
  void removeFile(const QFile &file);
  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
  QVariant data(int index, int role = Qt::DisplayRole) const;
  bool setData(const QModelIndex &index, const QVariant &value, int role) override;
  bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
  QHash<int, QByteArray> roleNames() const override;

private:
  bool isIndexValid(const QModelIndex &index) const;
  bool isIndexValid(int index) const;
  // Todo: ¿cómo iba esto?
  // Todo: ¿m?
  // Todo: Investigar un poco sobre las referencias y si afectan al tipo o a la variable, como los punteros
  // Todo: IdRole???
  std::unique_ptr<std::vector<std::unique_ptr<QFile>>> mFiles;
};

#endif // SIDEBARMODEL_H
