#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <openai.h>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    Logger logger;
    OpenAI openAI = OpenAI(&logger);

    QQmlApplicationEngine engine;
    QQmlContext * context;
    // QList<QQmlContext::PropertyPair> qmlProperties;

    const QUrl url("qrc:/view/qml/Main.qml");
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    // add items to context
    // update properties
    //qmlProperties.append(QQmlContext::PropertyPair{"Bot", QVariant::fromStdVariant(chatBot)});
    //qmlProperties.append(QQmlContext::PropertyPair{"Logger", QVariant::fromValue(logger)});

    context = engine.rootContext();
    context->setContextProperty("OpenAI", &openAI);
    //context->setContextProperties(qmlProperties);
//    qmlRegisterType<OpenAI *>("cm.danofred.test", 1,0,"OpenAI");
//    qmlRegisterType<Logger *>("cm.danofred.test", 1,0,"Logger");

    engine.load(url);

    return app.exec();
}
