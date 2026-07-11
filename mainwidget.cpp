#include "mainwidget.h"

#include <QScreen>
#include <QScroller>
#include <QHeaderView>

MainWidget::MainWidget(CommandLineSettings commandSettings, QWidget *parent)
    : QWidget{parent}, m_settings(std::move(commandSettings))
{
    initialize();
}

void MainWidget::initialize()
{
    const QSize availableSize = screen()->availableGeometry().size();
    resize(availableSize / 2);

    QVBoxLayout *layout = new QVBoxLayout(this);
    initializeFilterLine(layout);
    initializeModels();
    initializeTreeView(layout);
    initializeDelegate();
}

void MainWidget::initializeFilterLine(QVBoxLayout *layout)
{
    m_filterLine = new QLineEdit(this);
    m_filterLine->setPlaceholderText("Введите имя файла или папки");
    layout->addWidget(m_filterLine);

    connect(m_filterLine, &QLineEdit::textChanged, this, &MainWidget::filterTextChanged);
}

void MainWidget::initializeModels()
{
    m_model = new QFileSystemModel(this);
    m_model->setRootPath(m_settings.rootPath);
    m_model->setFilter(QDir::AllEntries | QDir::NoDotAndDotDot | QDir::Hidden);

    if(m_settings.dontUseCustomDirectoryIcons)
        m_model->setOption(QFileSystemModel::DontUseCustomDirectoryIcons);
    if(m_settings.dontWatch)
        m_model->setOption(QFileSystemModel::DontWatchForChanges);

    m_proxyModel = new FileSystemProxyModel(this);
    m_proxyModel->setSourceModel(m_model);
    m_proxyModel->setFilterKeyColumn(0);
    m_proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
    m_proxyModel->setRecursiveFilteringEnabled(true);
}

void MainWidget::initializeDelegate()
{
    m_delegate = new SizeDelegate(this);
    m_tree->setItemDelegateForColumn(1, m_delegate);
    connect(m_delegate, &SizeDelegate::SizeUpdateRequest, m_proxyModel, &FileSystemProxyModel::updateFolderSize);
}

void MainWidget::initializeTreeView(QVBoxLayout *layout)
{
    m_tree = new QTreeView(this);
    m_tree->setModel(m_proxyModel);

    updateRootIndex();

    // Demonstrating look and feel features
    m_tree->setAnimated(false);
    m_tree->setIndentation(20);
    m_tree->setSortingEnabled(true);
    m_tree->header()->setSectionResizeMode(0, QHeaderView::Stretch);

    // Make it flickable on touchscreens
    QScroller::grabGesture(m_tree, QScroller::TouchGesture);

    layout->addWidget(m_tree);
}

void MainWidget::filterTextChanged(const QString &text)
{
    m_proxyModel->setFilterRegularExpression(QRegularExpression::escape(text));
    updateRootIndex();
}

void MainWidget::updateRootIndex()
{
    const QModelIndex sourceIndex = m_model->index(m_settings.rootPath);
    const QModelIndex proxyIndex = m_proxyModel->mapFromSource(sourceIndex);

    if (proxyIndex.isValid())
        m_tree->setRootIndex(proxyIndex);
}
