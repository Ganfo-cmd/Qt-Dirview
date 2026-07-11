#ifndef FILESYSTEMPROXYMODEL_H
#define FILESYSTEMPROXYMODEL_H

#include "foldersizeworker.h"

#include <QSortFilterProxyModel>
#include <QThread>

class FileSystemProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit FileSystemProxyModel(QObject *parent = nullptr);
    ~FileSystemProxyModel();

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

public slots:
    void updateFolderSize(const QModelIndex &index);

signals:
    void calculateFolderSizeRequest(const QPersistentModelIndex &index, const QString &path);

private:
    QThread *m_folderSizeThread = nullptr;
    FolderSizeWorker *m_folderSizeWorker = nullptr;
    QHash<QString, quint64> m_foldersSizeByPath;

    void initializeThread();
};

#endif // FILESYSTEMPROXYMODEL_H
