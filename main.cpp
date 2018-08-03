#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "cardlist.h"
#include "cardmodel.h"
#include "walletlist.h"
#include "walletmodel.h"


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);


    qmlRegisterType<CardModel>("DoCard", 1, 0, "CardModel");
    qmlRegisterUncreatableType<CardList>("DoCard", 1, 0, "CardList",
        QStringLiteral("CardList should not be created in QML"));

    qmlRegisterType<WalletModel>("DoWallet", 1, 0, "WalletModel");
    qmlRegisterUncreatableType<WalletList>("DoWallet", 1, 0, "WalletList",
        QStringLiteral("WalletList should not be created in QML"));

    CardList cardList;

    WalletList walletList;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty(QStringLiteral("walletList"), &walletList);

    engine.rootContext()->setContextProperty(QStringLiteral("cardList"), &cardList);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
