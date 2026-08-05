#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    // QSettings keys the saved progress off these.
    QCoreApplication::setOrganizationName(QStringLiteral("QtProjects"));
    QCoreApplication::setApplicationName(QStringLiteral("CrazyPoppers"));

    QQmlApplicationEngine engine;
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
                     &app, []() { QCoreApplication::exit(-1); },
                     Qt::QueuedConnection);
    engine.loadFromModule("CrazyPoppers", "Main");

    return app.exec();
}
