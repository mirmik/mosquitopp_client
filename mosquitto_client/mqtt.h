#ifndef SIMPLECLIENT_MQTT_H
#define SIMPLECLIENT_MQTT_H

#include <cstdio>
#include <cstring>
#include <functional>
#include <igris/event/multiple_function.h>
#include <mosquittopp.h>
#include <string>
#include <string_view>
#include <unordered_map>

#define MAX_PAYLOAD 50
#define DEFAULT_KEEP_ALIVE 60

class mqtt_client : public mosqpp::mosquittopp
{
    std::unordered_map<std::string,
                       igris::multiple_function<const std::string &>>
        _subscriptions;

public:
    mqtt_client(const char *id, const char *host, int port);
    ~mqtt_client() = default;

    int publish(const std::string_view &topic, const std::string_view &message);
    void subscribe(const std::string_view &topic,
                   std::function<void(const std::string &)> callback);

    void on_connect(int rc);
    void on_message(const struct mosquitto_message *message);
    void on_subscribe(int mid, int qos_count, const int *granted_qos);
};

#endif // SIMPLECLIENT_MQTT_H
