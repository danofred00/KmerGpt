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
    auto obj = QJsonDocument::fromJson(json);

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
