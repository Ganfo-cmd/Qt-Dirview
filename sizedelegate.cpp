#include "sizedelegate.h"

#include <QApplication>
#include <QMouseEvent>
#include <QSortFilterProxyModel>
#include <QFileSystemModel>
#include <QPainter>

SizeDelegate::SizeDelegate(QObject *parent) : QStyledItemDelegate(parent)
{

}

void SizeDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyledItemDelegate::paint(painter, option, index);

    if(index.data(IsFolderRole).toBool())
    {
        QRect textRect = option.rect;
        textRect.setWidth(80);

        painter->drawText(textRect, Qt::AlignVCenter | Qt::AlignRight, index.data(FolderSizeRole).toString());

        QRect buttonRect = option.rect;
        buttonRect.setLeft(textRect.right());
        buttonRect.setWidth(18);

        QStyleOptionButton button;
        button.rect = buttonRect;
        button.icon = QApplication::style()->standardIcon(QStyle::SP_BrowserReload);

        QApplication::style()->drawControl(QStyle::CE_PushButton, &button, painter);
    }
}

bool SizeDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    Q_UNUSED(model);

    if (event->type() != QEvent::MouseButtonRelease)
    {
        return false;
    }

    if(!index.data(IsFolderRole).toBool())
    {
        return false;
    }

    QRect textRect = option.rect;
    textRect.setWidth(80);

    QRect buttonRect = option.rect;
    buttonRect.setLeft(textRect.right());
    buttonRect.setWidth(18);

    QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
    if (buttonRect.contains(mouseEvent->pos()))
    {
        emit SizeUpdateRequest(index);
        return true;
    }


    return false;
}