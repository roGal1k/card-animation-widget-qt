#include "cardanimationwidget.h"

#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QStandardPaths>
#include <QDateTime>

void customMessageHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg)
{
    QString logFilePath = QDir().filePath("LOGS/logfile_" + QDateTime::currentDateTime().toString("yyyy-MM-dd_hh-mm-ss") + ".txt");

    QFile logFile(logFilePath);
    if (logFile.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        QTextStream logStream(&logFile);
        logStream << msg << Qt::endl;
        logFile.close();
    }
    switch (type) {
        case QtDebugMsg:
            qDebug().noquote() << msg;
            break;
        case QtInfoMsg:
            qInfo().noquote() << msg;
            break;
        case QtWarningMsg:
            qWarning().noquote() << msg;
            break;
        case QtCriticalMsg:
            qCritical().noquote() << msg;
            break;
        case QtFatalMsg:
            qFatal("%s", msg.toUtf8().constData());
            break;
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qInstallMessageHandler(customMessageHandler);
    CardAnimationWidget w;
    w.show();
    return a.exec();
}
