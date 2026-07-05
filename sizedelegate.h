#ifndef SIZEDELEGATE_H
#define SIZEDELEGATE_H

#include "roles.h"

#include <QStyledItemDelegate>

class SizeDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    SizeDelegate(QObject *parent = nullptr);

signals:
    void SizeUpdateRequest(const QModelIndex &index);

private:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) override;
};

#endif // SIZEDELEGATE_H
