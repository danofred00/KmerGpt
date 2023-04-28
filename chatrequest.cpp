#include "chatrequest.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

ChatRequest::ChatRequest(QObject *parent)
    : QObject{parent}
{

}

ChatRequest::ChatRequest(const QByteArray & json)
{
    QJsonParseError error;
    auto obj = QJsonDocument::fromJson(json, &error);

    if(error.error != QJsonParseError::NoError)
        qDebug() << "[PARSE_ERROR]" << error.errorString();

    m_model = obj["model"].toString();
    m_temperature = obj["temperature"].toDouble();
    m_n = obj["n"].toInt();

    const QJsonValue msg = obj["messages"].toArray().at(0);
    m_message.role = msg["role"].toString();
    m_message.content = msg["content"].toString();
    m_message.name = msg["name"].toString();

}

ChatRequest::ChatRequest(const ChatRequest & other) {
    *this = other;
}

ChatRequest & ChatRequest::operator=(const ChatRequest & other) {

    m_message = other.message();
    m_model = other.model();
    m_temperature = other.temperature();
    m_n = other.n();

    return *this;
}


QByteArray ChatRequest::toJson()
{
    QString jsonStr = QString(R"(
    {
        "model": "%1",
        "messages":[{
                "name": "%2"
                "role": "%3",
                "content": "%4"
        }],
        "temperature": %5,
        "n": %6
    })").arg(m_model, m_message.name, m_message.role, m_message.content, m_temperature, m_n);

    return jsonStr.toLatin1();
}

/////
/////
///

ChatResponse::ChatResponse(QObject *parent)
    : QObject{parent}
{

}



ChatResponse::ChatResponse(const QByteArray & json)
{
    QJsonParseError error;
    auto obj = QJsonDocument::fromJson(json, &error);

    if(error.error != QJsonParseError::NoError)
        qDebug() << "[PARSE_ERROR]" << error.errorString();

    m_model = obj["model"].toString();
    m_id = obj["id"].toString();
    m_object = obj["object"].toString();
    auto msg = obj["choices"].toArray().at(0)["message"].toObject();

    m_message.role = msg["role"].toString();
    m_message.content = msg["content"].toString();
    m_message.name = msg["name"].toString();
}

QByteArray ChatResponse::toJson()
{
    QString jsonStr = QString(R"(
    {
        "id": "%1",
        "model": "%2",
        "object": "%3",
        "choices":[{
            "message": {
                "role": "%4",
                "content": "%5"
            }
        }]
    })").arg(m_id, m_model, m_object, m_message.role, m_message.content);

    return jsonStr.toLatin1();
}

ChatResponse & ChatResponse::operator=(const ChatResponse & other) {
    m_id = other.id();
    m_message = other.message();
    m_model = other.model();
    m_object = other.object();

    return *this;
}

ChatResponse::ChatResponse(const ChatResponse & other)
{
    *this = other;
}
