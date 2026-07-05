#include "mainwidget.h"

#include <QApplication>
#include <QFileIconProvider>
#include <QCommandLineParser>
#include <QCommandLineOption>

CommandLineSettings parseCommandLine(const QApplication& app)
{
    QCommandLineParser parser;
    parser.setApplicationDescription("Qt Dir View Example");
    parser.addHelpOption();
    parser.addVersionOption();
    QCommandLineOption dontUseCustomDirectoryIconsOption("c", "Set QFileSystemModel::DontUseCustomDirectoryIcons");
    parser.addOption(dontUseCustomDirectoryIconsOption);
    QCommandLineOption dontWatchOption("w", "Set QFileSystemModel::DontWatch");
    parser.addOption(dontWatchOption);
    parser.addPositionalArgument("directory", "The directory to start in.");
    parser.process(app);
    const QString rootPath = parser.positionalArguments().isEmpty()
                                 ? QDir::homePath() : QDir::cleanPath(parser.positionalArguments().first());

    CommandLineSettings commandSettings;
    commandSettings.rootPath = rootPath;
    if (parser.isSet(dontUseCustomDirectoryIconsOption))
        commandSettings.dontUseCustomDirectoryIcons = true;
    if (parser.isSet(dontWatchOption))
        commandSettings.dontWatch = true;

    return commandSettings;
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QCoreApplication::setApplicationVersion(QT_VERSION_STR);

    CommandLineSettings settings = parseCommandLine(app);
    MainWidget mainWidget(settings);

    mainWidget.setWindowTitle(QObject::tr("Dir View"));
    mainWidget.show();

    return app.exec();
}
