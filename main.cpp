#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QMutex>
#include "src/cpp.h"
QMutex mutex;

void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    mutex.lock();
    FILE* f=fopen("log.txt","a");
    QByteArray localMsg = msg.toLocal8Bit();
    switch (type) {
    case QtDebugMsg:
        fprintf(f, "> %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtInfoMsg:
        fprintf(f, "i %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtWarningMsg:
        fprintf(f, "! %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtCriticalMsg:
        fprintf(f, "Critical: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtFatalMsg:
        fprintf(f, "Fatal: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        abort();
    }
    fclose(f);
    mutex.unlock();
}
int main(int argc, char *argv[])
{
#ifndef QT_DEBUG
    qInstallMessageHandler(myMessageOutput);
#endif
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    CPP cpp;
    engine.rootContext()->setContextProperty("CPP",&cpp);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
