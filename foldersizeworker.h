#ifndef FOLDERSIZEWORKER_H
#define FOLDERSIZEWORKER_H

#include <QObject>

class FolderSizeWorker : public QObject
{
    Q_OBJECT

public slots:
    void calculateFolderSize(const QPersistentModelIndex &index, const QString &path);

signals:
    void finished(const QPersistentModelIndex &index, const QString &path, quint64 size);
};

#endif // FOLDERSIZEWORKER_H
