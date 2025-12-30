#include <QApplication>
#include "MainWindow.hpp"

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(Navik);
    QApplication app(argc, argv);
    app.setOrganizationName("TreOnz");
    app.setApplicationName("Navik");

    MainWindow mainWin;
    mainWin.setWindowIcon(QIcon(":FILEMANAGER"));

    if(!mainWin.Initialize())
    {
        QMessageBox msg;
        msg.setText("The file manager has failed to initialize successfully");
        msg.exec();
    }

    mainWin.show();

    return app.exec();
}
