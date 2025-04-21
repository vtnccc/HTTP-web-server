#include <QApplication>
#include "mainwindow.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow window;
    window.setWindowTitle("HTTP Web Server");
    window.resize(600, 400);
    window.show();
    return app.exec();
}
