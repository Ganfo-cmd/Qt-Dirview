#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "filesystemproxymodel.h"
#include "sizedelegate.h"

#include <QWidget>
#include <QFileSystemModel>
#include <QTreeView>
#include <QVBoxLayout>
#include <QLineEdit>

struct CommandLineSettings
{
    QString rootPath;
    bool dontUseCustomDirectoryIcons = false;
    bool dontWatch = false;
};

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(CommandLineSettings commandSettings, QWidget *parent = nullptr);
    ~MainWidget() = default;

private slots:
    void filterTextChanged(const QString &text);

private:
    CommandLineSettings m_settings;
    QLineEdit *m_filterLine = nullptr;

    QFileSystemModel *m_model = nullptr;
    FileSystemProxyModel *m_proxyModel = nullptr;

    SizeDelegate *m_delegate = nullptr;
    QTreeView *m_tree = nullptr;

    void initialize();
    void initializeFilterLine(QVBoxLayout *layout);
    void initializeModels();
    void initializeDelegate();
    void initializeTreeView(QVBoxLayout *layout);

    void updateRootIndex();
};

#endif // MAINWIDGET_H
