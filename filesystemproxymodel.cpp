#include "filesystemproxymodel.h"
#include "roles.h"

#include <QFileSystemModel>
#include <QLocale>

FileSystemProxyModel::FileSystemProxyModel(QObject *parent) : QSortFilterProxyModel(parent)
{
    initializeThread();
}

FileSystemProxyModel::~FileSystemProxyModel()
{
    m_folderSizeThread->quit();
    m_folderSizeThread->wait();
}

void FileSystemProxyModel::initializeThread()
{
    m_folderSizeThread = new QThread(this);

    m_folderSizeWorker = new FolderSizeWorker();
    m_folderSizeWorker->moveToThread(m_folderSizeThread);

    connect(m_folderSizeThread, &QThread::finished, m_folderSizeWorker, &QObject::deleteLater);

    m_folderSizeThread->start();

    connect(this, &FileSystemProxyModel::calculateFolderSizeRequest, m_folderSizeWorker, &FolderSizeWorker::calculateFolderSize, Qt::QueuedConnection);

    connect(m_folderSizeWorker, &FolderSizeWorker::finished, this,
            [this](const QPersistentModelIndex & index, const QString &path, quint64 size)
            {
                m_foldersSizeByPath[path] = size;
                emit dataChanged(index, index, {FolderSizeRole});
            });
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
        auto it = m_foldersSizeByPath.find(path);
        if(it != m_foldersSizeByPath.end())
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

    emit calculateFolderSizeRequest(index, path);
}
