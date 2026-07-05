#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QFileSystemModel>
#include <QTreeView>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QSortFilterProxyModel>

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
    CommandLineSettings settings_;
    QLineEdit *filterLine_ = nullptr;

    QFileSystemModel *model_ = nullptr;
    QSortFilterProxyModel *proxyModel_ = nullptr;
    QTreeView *tree_ = nullptr;

    void initialize();
    void initializeFilterLine(QVBoxLayout *layout);
    void initializeTreeView(QVBoxLayout *layout);

    void updateRootIndex();
};

#endif // MAINWIDGET_H
