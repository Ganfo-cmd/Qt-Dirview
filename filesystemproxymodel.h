#ifndef FILESYSTEMPROXYMODEL_H
#define FILESYSTEMPROXYMODEL_H

#include <QSortFilterProxyModel>

class FileSystemProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit FileSystemProxyModel(QObject *parent = nullptr);

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

public slots:
    void updateFolderSize(const QModelIndex &index);

private:
    QHash<QString, quint64> foldersSizeByPath_;

    quint64 calculateFolderSize(const QString &path);
};

#endif // FILESYSTEMPROXYMODEL_H
