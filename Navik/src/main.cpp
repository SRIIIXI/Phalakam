#include <QGuiApplication>
#include <QtQml/qqmlapplicationengine.h>
#include <QtWebEngineQuick/qtwebenginequickglobal.h>

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(Navik);

    // Initialize WebEngine
    //QtWebEngineQuick::initialize();
    
    QGuiApplication app(argc, argv);
    app.setOrganizationName("TreOnz");
    app.setApplicationName("Navik File Manager");
    
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
