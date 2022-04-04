#ifndef APPCONTROLLER_H
#define APPCONTROLLER_H

#include <QObject>

class AppController : public QObject
{
    Q_OBJECT
public:
    explicit AppController(QObject *parent = nullptr);

    Q_INVOKABLE void showMsg();

signals:
    void showTrayMessage();
};

#endif // APPCONTROLLER_H
