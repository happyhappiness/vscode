static void *subscribers_thread (void *arg)
{
    mqtt_client_conf_t *conf = arg;
    int status;

    conf->loop = 1;

    while (conf->loop)
    {
        status = mqtt_connect (conf);
        if (status != 0)
        {
            sleep (1);
            continue;
        }

        /* The documentation says "0" would map to the default (1000ms), but
         * that does not work on some versions. */
#if LIBMOSQUITTO_MAJOR == 0
        status = mosquitto_loop (conf->mosq, /* timeout = */ 1000 /* ms */);
#else
        status = mosquitto_loop (conf->mosq,
                /* timeout[ms] = */ 1000,
                /* max_packets = */  100);
#endif
        if (status == MOSQ_ERR_CONN_LOST)
        {
            conf->connected = 0;
            continue;
        }
        else if (status != MOSQ_ERR_SUCCESS)
        {
            ERROR ("mqtt plugin: mosquitto_loop failed: %s",
                    mosquitto_strerror (status));
            mosquitto_destroy (conf->mosq);
            conf->mosq = NULL;
            conf->connected = 0;
            continue;
        }

        DEBUG ("mqtt plugin: mosquitto_loop succeeded.");
    } /* while (conf->loop) */

    pthread_exit (0);
}