#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtWebEngineQuick/qtwebenginequickglobal.h>

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(Anveshak);

    // Initialize WebEngine
    QtWebEngineQuick::initialize();
    
    QGuiApplication app(argc, argv);
    app.setOrganizationName("TreOnz");
    app.setApplicationName("Anveshak Browser");
    
    QQmlApplicationEngine engine;
    
    // Load main QML file
    const QUrl url(QStringLiteral("qrc:///qml/main.qml"));

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    
    engine.load(url);
    
    return app.exec();
}
