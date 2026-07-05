#include "filesystemproxymodel.h"
#include "roles.h"

#include <QFileSystemModel>
#include <QLocale>

FileSystemProxyModel::FileSystemProxyModel(QObject *parent) : QSortFilterProxyModel(parent)
{

}

QVariant FileSystemProxyModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return {};

    QModelIndex sourceIndex = mapToSource(index);
    QFileSystemModel* model = qobject_cast<QFileSystemModel *>(sourceModel());
    if(!model)
        return QSortFilterProxyModel::data(index, role);

    if(role == IsFolderRole)
        return model->isDir(sourceIndex);

    if(role == FolderSizeRole && index.column() == 1)
    {
        if(!model->isDir(sourceIndex))
            return {};

        QString path = model->filePath(sourceIndex);
        auto it = foldersSizeByPath_.find(path);
        if(it != foldersSizeByPath_.end())
        {
            return QLocale().formattedDataSize(it.value());
        }

        return {};
    }

    return QSortFilterProxyModel::data(index, role);
}

void FileSystemProxyModel::updateFolderSize(const QModelIndex &index)
{
    QModelIndex sourceIndex = mapToSource(index);
    QFileSystemModel* model = qobject_cast<QFileSystemModel *>(sourceModel());
    if (!model || !model->isDir(sourceIndex))
        return;

    QString path = model->filePath(sourceIndex);

    foldersSizeByPath_[path] = calculateFolderSize(path);
    emit dataChanged(index, index, {FolderSizeRole, Qt::DisplayRole});
}

quint64 FileSystemProxyModel::calculateFolderSize(const QString &path)
{
    quint64 totalSize = 0;

    // Data size is calculated only for data that is physically
    // located within the folder
    QDirIterator it(path,  QDir::Files | QDir::NoDotAndDotDot | QDir::Hidden , QDirIterator::Subdirectories);

    while(it.hasNext())
    {
        it.next();

        QFileInfo info = it.fileInfo();
        if(info.isFile())
        {
            totalSize += info.size();
        }
    }

    return totalSize;
}
