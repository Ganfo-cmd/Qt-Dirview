#include "foldersizeworker.h"

#include <QDirIterator>

void FolderSizeWorker::calculateFolderSize(const QPersistentModelIndex &index, const QString &path)
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

    emit finished(index, path, totalSize);
}
