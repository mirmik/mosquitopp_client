#ifndef SIMPLECLIENT_MQTT_H
#define SIMPLECLIENT_MQTT_H

#include <cstdio>
#include <cstring>
#include <mosquittopp.h>
#include <string_view>

#define MAX_PAYLOAD 50
#define DEFAULT_KEEP_ALIVE 60

class mqtt_client : public mosqpp::mosquittopp
{
public:
    mqtt_client(const char *id, const char *host, int port);
    ~mqtt_client();

    int publish(const std::string_view &topic, const std::string_view &message);

    void on_connect(int rc);
    void on_message(const struct mosquitto_message *message);
    void on_subscribe(int mid, int qos_count, const int *granted_qos);
};

#endif // SIMPLECLIENT_MQTT_H
