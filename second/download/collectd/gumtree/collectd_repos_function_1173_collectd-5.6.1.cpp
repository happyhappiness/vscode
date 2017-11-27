static int mqtt_reconnect (mqtt_client_conf_t *conf)
{
    int status;

    if (conf->connected)
        return (0);

    status = mosquitto_reconnect (conf->mosq);
    if (status != MOSQ_ERR_SUCCESS)
    {
        char errbuf[1024];
        ERROR ("mqtt_connect_broker: mosquitto_connect failed: %s",
                (status == MOSQ_ERR_ERRNO)
                ? sstrerror(errno, errbuf, sizeof (errbuf))
                : mosquitto_strerror (status));
        return (-1);
    }

    conf->connected = 1;

    c_release (LOG_INFO,
            &conf->complaint_cantpublish,
            "mqtt plugin: successfully reconnected to broker \"%s:%d\"",
            conf->host, conf->port);

    return (0);
}