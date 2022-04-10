#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "src/appcontroller.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    AppController appController;

    appController.initializeQmlContext(&app, &engine);

    appController.showMsg();

    return app.exec();
}
