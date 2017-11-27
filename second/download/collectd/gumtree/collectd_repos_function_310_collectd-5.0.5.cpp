static int camqp_subscribe_init (camqp_config_t *conf) /* {{{ */
{
    int status;
    pthread_t *tmp;

    tmp = realloc (subscriber_threads,
            sizeof (*subscriber_threads) * (subscriber_threads_num + 1));
    if (tmp == NULL)
    {
        ERROR ("amqp plugin: realloc failed.");
        camqp_config_free (conf);
        return (ENOMEM);
    }
    subscriber_threads = tmp;
    tmp = subscriber_threads + subscriber_threads_num;
    memset (tmp, 0, sizeof (*tmp));

    status = pthread_create (tmp, /* attr = */ NULL,
            camqp_subscribe_thread, conf);
    if (status != 0)
    {
        char errbuf[1024];
        ERROR ("amqp plugin: pthread_create failed: %s",
                sstrerror (status, errbuf, sizeof (errbuf)));
        camqp_config_free (conf);
        return (status);
    }

    subscriber_threads_num++;

    return (0);
}