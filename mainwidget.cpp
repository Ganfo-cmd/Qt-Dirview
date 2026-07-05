#include "mainwidget.h"

#include <QScreen>
#include <QScroller>
#include <QHeaderView>

MainWidget::MainWidget(const CommandLineSettings &commandSettings, QWidget *parent)
    : QWidget{parent}
{
    initialize(commandSettings);
}

void MainWidget::initialize(const CommandLineSettings &commandSettings)
{
    const QSize availableSize = screen()->availableGeometry().size();
    resize(availableSize / 2);

    QVBoxLayout *layout = new QVBoxLayout(this);
    initializeTreeView(layout, commandSettings);
}

void MainWidget::initializeTreeView(QVBoxLayout *layout, const CommandLineSettings &commandSettings)
{
    model_ = new QFileSystemModel(this);
    model_->setRootPath(commandSettings.rootPath);
    model_->setFilter(QDir::AllEntries | QDir::NoDotAndDotDot | QDir::Hidden);

    if(commandSettings.dontUseCustomDirectoryIcons)
        model_->setOption(QFileSystemModel::DontUseCustomDirectoryIcons);
    if(commandSettings.dontWatch)
        model_->setOption(QFileSystemModel::DontWatchForChanges);

    tree_ = new QTreeView(this);
    tree_->setModel(model_);
    const QModelIndex rootIndex = model_->index(commandSettings.rootPath);
    if (rootIndex.isValid())
        tree_->setRootIndex(rootIndex);

    // Demonstrating look and feel features
    tree_->setAnimated(false);
    tree_->setIndentation(20);
    tree_->setSortingEnabled(true);
    tree_->header()->setSectionResizeMode(0, QHeaderView::Stretch);

    // Make it flickable on touchscreens
    QScroller::grabGesture(tree_, QScroller::TouchGesture);

    layout->addWidget(tree_);
}
