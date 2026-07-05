#include "mainwidget.h"

#include <QScreen>
#include <QScroller>
#include <QHeaderView>

MainWidget::MainWidget(CommandLineSettings commandSettings, QWidget *parent)
    : QWidget{parent}, settings_(std::move(commandSettings))
{
    initialize();
}

void MainWidget::initialize()
{
    const QSize availableSize = screen()->availableGeometry().size();
    resize(availableSize / 2);

    QVBoxLayout *layout = new QVBoxLayout(this);
    initializeFilterLine(layout);
    initializeTreeView(layout);
}

void MainWidget::initializeFilterLine(QVBoxLayout *layout)
{
    filterLine_ = new QLineEdit(this);
    filterLine_->setPlaceholderText("Введите имя файла или папки");
    layout->addWidget(filterLine_);

    connect(filterLine_, &QLineEdit::textChanged, this, &MainWidget::filterTextChanged);
}

void MainWidget::initializeTreeView(QVBoxLayout *layout)
{
    model_ = new QFileSystemModel(this);
    model_->setRootPath(settings_.rootPath);
    model_->setFilter(QDir::AllEntries | QDir::NoDotAndDotDot | QDir::Hidden);

    if(settings_.dontUseCustomDirectoryIcons)
        model_->setOption(QFileSystemModel::DontUseCustomDirectoryIcons);
    if(settings_.dontWatch)
        model_->setOption(QFileSystemModel::DontWatchForChanges);

    proxyModel_ = new QSortFilterProxyModel(this);
    proxyModel_->setSourceModel(model_);
    proxyModel_->setFilterKeyColumn(0);
    proxyModel_->setFilterCaseSensitivity(Qt::CaseInsensitive);
    proxyModel_->setRecursiveFilteringEnabled(true);

    tree_ = new QTreeView(this);
    tree_->setModel(proxyModel_);

    updateRootIndex();

    // Demonstrating look and feel features
    tree_->setAnimated(false);
    tree_->setIndentation(20);
    tree_->setSortingEnabled(true);
    tree_->header()->setSectionResizeMode(0, QHeaderView::Stretch);

    // Make it flickable on touchscreens
    QScroller::grabGesture(tree_, QScroller::TouchGesture);

    layout->addWidget(tree_);
}

void MainWidget::filterTextChanged(const QString &text)
{
    proxyModel_->setFilterRegularExpression(QRegularExpression::escape(text));
    updateRootIndex();
}

void MainWidget::updateRootIndex()
{
    const QModelIndex sourceIndex = model_->index(settings_.rootPath);
    const QModelIndex proxyIndex = proxyModel_->mapFromSource(sourceIndex);

    if (proxyIndex.isValid())
        tree_->setRootIndex(proxyIndex);
}
