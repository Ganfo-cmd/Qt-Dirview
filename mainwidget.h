#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QFileSystemModel>
#include <QTreeView>
#include <QVBoxLayout>

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
    explicit MainWidget(const CommandLineSettings &commandSettings, QWidget *parent = nullptr);
    ~MainWidget() = default;

private:
    QFileSystemModel *model_ = nullptr;
    QTreeView *tree_ = nullptr;

    void initialize(const CommandLineSettings &commandSettings);
    void initializeTreeView(QVBoxLayout *layout, const CommandLineSettings &commandSettings);
};

#endif // MAINWIDGET_H
