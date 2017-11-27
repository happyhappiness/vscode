static int mqtt_connect (mqtt_client_conf_t *conf)
{
    char const *client_id;
    int status;

    if (conf->mosq != NULL)
        return mqtt_reconnect (conf);

    if (conf->client_id)
        client_id = conf->client_id;
    else
        client_id = hostname_g;

#if LIBMOSQUITTO_MAJOR == 0
    conf->mosq = mosquitto_new (client_id, /* user data = */ conf);
#else
    conf->mosq = mosquitto_new (client_id, conf->clean_session, /* user data = */ conf);
#endif
    if (conf->mosq == NULL)
    {
        ERROR ("mqtt plugin: mosquitto_new failed");
        return (-1);
    }

#if LIBMOSQUITTO_MAJOR != 0
    if (conf->cacertificatefile) {
        status = mosquitto_tls_set(conf->mosq, conf->cacertificatefile, NULL,
	                           conf->certificatefile, conf->certificatekeyfile, /* pw_callback */NULL);
        if (status != MOSQ_ERR_SUCCESS) {
            ERROR ("mqtt plugin: cannot mosquitto_tls_set: %s", mosquitto_strerror(status));
            mosquitto_destroy (conf->mosq);
            conf->mosq = NULL;
            return (-1);
        }

        status = mosquitto_tls_opts_set(conf->mosq, SSL_VERIFY_PEER, conf->tlsprotocol, conf->ciphersuite);
        if (status != MOSQ_ERR_SUCCESS) {
            ERROR ("mqtt plugin: cannot mosquitto_tls_opts_set: %s", mosquitto_strerror(status));
            mosquitto_destroy (conf->mosq);
            conf->mosq = NULL;
            return (-1);
        }

        status = mosquitto_tls_insecure_set(conf->mosq, false);
        if (status != MOSQ_ERR_SUCCESS) {
            ERROR ("mqtt plugin: cannot mosquitto_tls_insecure_set: %s", mosquitto_strerror(status));
            mosquitto_destroy (conf->mosq);
            conf->mosq = NULL;
            return (-1);
        }
    }
#endif

    if (conf->username && conf->password)
    {
        status = mosquitto_username_pw_set (conf->mosq, conf->username, conf->password);
        if (status != MOSQ_ERR_SUCCESS)
        {
            char errbuf[1024];
            ERROR ("mqtt plugin: mosquitto_username_pw_set failed: %s",
                    (status == MOSQ_ERR_ERRNO)
                    ? sstrerror (errno, errbuf, sizeof (errbuf))
                    : mosquitto_strerror (status));

            mosquitto_destroy (conf->mosq);
            conf->mosq = NULL;
            return (-1);
        }
    }

#if LIBMOSQUITTO_MAJOR == 0
    status = mosquitto_connect (conf->mosq, conf->host, conf->port,
            /* keepalive = */ MQTT_KEEPALIVE, /* clean session = */ conf->clean_session);
#else
    status = mosquitto_connect (conf->mosq, conf->host, conf->port, MQTT_KEEPALIVE);
#endif
    if (status != MOSQ_ERR_SUCCESS)
    {
        char errbuf[1024];
        ERROR ("mqtt plugin: mosquitto_connect failed: %s",
                (status == MOSQ_ERR_ERRNO)
                ? sstrerror (errno, errbuf, sizeof (errbuf))
                : mosquitto_strerror (status));

        mosquitto_destroy (conf->mosq);
        conf->mosq = NULL;
        return (-1);
    }

    if (!conf->publish)
    {
        mosquitto_message_callback_set (conf->mosq, on_message);

        status = mosquitto_subscribe (conf->mosq,
                /* message_id = */ NULL,
                conf->topic, conf->qos);
        if (status != MOSQ_ERR_SUCCESS)
        {
            ERROR ("mqtt plugin: Subscribing to \"%s\" failed: %s",
                    conf->topic, mosquitto_strerror (status));

            mosquitto_disconnect (conf->mosq);
            mosquitto_destroy (conf->mosq);
            conf->mosq = NULL;
            return (-1);
        }
    }

    conf->connected = 1;
    return (0);
}