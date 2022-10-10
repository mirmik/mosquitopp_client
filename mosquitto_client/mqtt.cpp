#include <mosquitto_client/mqtt.h>

mqtt_client::mqtt_client(const char *id, const char *host, int port)
    : mosquittopp(id)
{
    int keepalive = DEFAULT_KEEP_ALIVE;
    connect(host, port, keepalive);
}

void mqtt_client::on_connect(int rc) {}

void mqtt_client::on_subscribe(int mid, int qos_count, const int *granted_qos)
{
}

int mqtt_client::publish(const std::string_view &topic,
                         const std::string_view &message)
{
    int ret = mosqpp::mosquittopp::publish(NULL,
                                           (const char *)topic.data(),
                                           (int)message.length(),
                                           (const void *)message.data(),
                                           0,
                                           false);
    return ret;
}

void mqtt_client::on_message(const struct mosquitto_message *message)
{
    std::string topic = message->topic;
    auto payload_size = message->payloadlen;
    std::string payload = std::string((char *)message->payload, payload_size);

    if (_subscriptions.find(topic) != _subscriptions.end())
    {
        _subscriptions[topic](payload);
    }
}

void mqtt_client::subscribe(const std::string_view &topic,
                            std::function<void(const std::string &)> callback)
{
    _subscriptions[std::string(topic)] += callback;
    mosqpp::mosquittopp::subscribe(NULL, (const char *)topic.data());
}