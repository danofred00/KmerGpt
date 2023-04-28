#include "chatrequest.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

ChatRequest::ChatRequest(QObject *parent)
    : QObject{parent}
{

}

ChatRequest * ChatRequest::fromJson(const QByteArray &json)
{
    ChatRequest * request = new ChatRequest;
    QList<Message> list;
    QJsonParseError error;
    auto obj = QJsonDocument::fromJson(json, &error);

    if(error.error != QJsonParseError::NoError)
        qDebug() << "[PARSE_ERROR]" << error.errorString();

    request->m_model = obj["model"].toString();
    request->m_temperature = obj["temperature"].toDouble();
    request->m_n = obj["n"].toInt();

    foreach (const QJsonValue msg, obj["messages"].toArray()) {
        Message m;
        m.role = msg["role"].toString();
        m.content = msg["content"].toString();
        m.name = msg["name"].toString();

        list.append(m);
    }

    request->m_messages = list;

    return request;
}

QByteArray ChatRequest::toJson()
{
    QJsonObject json;
    QJsonArray arrMsg;
    json.insert("model", QJsonValue::fromVariant(m_model));
    json["n"] = m_n;
    json["temperature"] = m_temperature;

    // parse messages
    for (const auto & msg : m_messages) {

        QJsonObject msgJson;

        msgJson.insert("role", msg.role);
        msgJson.insert("content", msg.content);
        msgJson.insert("name", msg.name);

        arrMsg.push_back(msgJson);
    }

    json["messages"] = arrMsg;

    return QJsonDocument(json).toJson();
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

ChatResponse::ChatResponse(const ChatResponse &copy)
{
    m_id = copy.id();
    m_message = copy.message();
    m_model = copy.model();
    m_object = copy.object();
}
