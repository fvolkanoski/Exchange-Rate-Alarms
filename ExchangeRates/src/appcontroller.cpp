#include <QJsonDocument>
#include <QJsonObject>
#include <QQmlContext>

#include "appcontroller.h"

AppController::AppController(QObject *parent)
    : QObject{parent},
      _worker(new HttpRequestWorker(this))
{
    connect(_worker, SIGNAL(on_execution_finished(HttpRequestWorker*)), this, SLOT(handleResult(HttpRequestWorker*)));

    HttpRequestInput input("https://v6.exchangerate-api.com/v6/9efed49e0804bd71761a224e/latest/" + m_mainCurrency, "GET");
    _worker->execute(&input);
}

void AppController::showMsg()
{
    emit showTrayMessage("smth", "nothing");
}

void AppController::initializeQmlContext(QGuiApplication *app, QQmlApplicationEngine *engine)
{
    if (!engine)
        return;

    _engine = engine;
    _app = app;

    _engine->rootContext()->setContextProperty("appController", this);
    _engine->rootContext()->setContextProperty("currencyModel", &_currencyModel);
    _engine->rootContext()->setContextProperty("cbModel", &_cbModel);

    const QUrl url(u"qrc:/ExchangeRates/main.qml"_qs);

    QObject::connect(engine, &QQmlApplicationEngine::objectCreated,
                     app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine->load(url);
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
        //qDebug() << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-";
        //qDebug() << apiObjIt.key();
        //qDebug() << apiObjIt.value();
        //qDebug() << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-";

        if(apiObjIt.key() == "conversion_rates")
        {
            QJsonObject ratesObj = apiObjIt.value().toObject();
            QJsonObject::iterator ratesObjIt;

            for (ratesObjIt = ratesObj.begin(); ratesObjIt != ratesObj.end(); ratesObjIt++)
            {
                //qDebug() << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-";
                //qDebug() << ratesObjIt.key();
                //qDebug() << ratesObjIt.value();
                //qDebug() << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-";

                _currencyModel.addCurrency(Currency(ratesObjIt.key(), QString::number(ratesObjIt.value().toDouble())));
                _cbModel.addCurrency(Currency(ratesObjIt.key(), QString::number(ratesObjIt.value().toDouble())));
            }
        }
    }
}

const QString &AppController::mainCurrency() const
{
    return m_mainCurrency;
}

void AppController::setMainCurrency(const QString &newMainCurrency)
{
    if (m_mainCurrency == newMainCurrency)
        return;
    m_mainCurrency = newMainCurrency;

    HttpRequestInput input("https://v6.exchangerate-api.com/v6/9efed49e0804bd71761a224e/latest/" + m_mainCurrency, "GET");
    _worker->execute(&input);

    _currencyModel.clear();

    qDebug() << "Changing stuff for..." << m_mainCurrency;

    emit mainCurrencyChanged();
}
