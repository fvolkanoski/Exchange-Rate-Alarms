#include "appcontroller.h"

AppController::AppController(QObject *parent)
    : QObject{parent}
{

}

void AppController::showMsg()
{
    emit showTrayMessage();
}
