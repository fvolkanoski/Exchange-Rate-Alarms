#include <QJsonDocument>
#include <QJsonObject>

#include "appcontroller.h"

AppController::AppController(QObject *parent)
    : QObject{parent},
      _worker(new HttpRequestWorker(this))
{
    connect(_worker, SIGNAL(on_execution_finished(HttpRequestWorker*)), this, SLOT(handleResult(HttpRequestWorker*)));

    HttpRequestInput input("https://v6.exchangerate-api.com/v6/9efed49e0804bd71761a224e/latest/EUR", "GET");
    _worker->execute(&input);
}

void AppController::showMsg()
{
    emit showTrayMessage("smth", "nothing");
}

void AppController::handleResult(HttpRequestWorker *worker)
{
    if (worker->error_type == QNetworkReply::NoError)
         parseCurrencyResponse(worker->response);
     else
        qDebug() << "Error while getting currency data: " + worker->error_str;
}

void AppController::parseCurrencyResponse(QByteArray apiResponse)
{
    QJsonDocument apiRes = QJsonDocument::fromJson(apiResponse);
    QJsonObject apiObj = apiRes.object();
    QJsonObject::iterator apiObjIt;


    for (apiObjIt = apiObj.begin(); apiObjIt != apiObj.end(); apiObjIt++)
    {
        qDebug() << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-";
        qDebug() << apiObjIt.key();
        qDebug() << apiObjIt.value();
        qDebug() << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-";
    }
}
