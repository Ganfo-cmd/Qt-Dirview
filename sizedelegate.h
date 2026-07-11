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
    static constexpr int s_textWidth = 80;
    static constexpr int s_buttonWidth = 18;

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) override;

    QRect createTextRect(const QStyleOptionViewItem &option) const;
    QRect createButtonRect(const QStyleOptionViewItem &option) const;
};

#endif // SIZEDELEGATE_H
