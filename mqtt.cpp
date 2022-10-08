#include "mqtt.h"
#define PUBLISH_TOPIC "EXAMPLE_TOPIC"

#ifdef DEBUG
#include <iostream>
#endif

mqtt_client::mqtt_client(const char *id, const char *host, int port)
    : mosquittopp(id)
{
    int keepalive = DEFAULT_KEEP_ALIVE;
    connect(host, port, keepalive);
}

mqtt_client::~mqtt_client() {}

void mqtt_client::on_connect(int rc)
{
    if (!rc)
    {
#ifdef DEBUG
        std::cout << "Connected - code " << rc << std::endl;
#endif
    }
}

void mqtt_client::on_subscribe(int mid, int qos_count, const int *granted_qos)
{
#ifdef DEBUG
    std::cout << "Subscription succeeded." << std::endl;
#endif
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
    int payload_size = MAX_PAYLOAD + 1;
    char buf[payload_size];
}
