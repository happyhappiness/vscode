static int camqp_connect (camqp_config_t *conf) /* {{{ */
{
    amqp_rpc_reply_t reply;
    int sockfd;
    int status;

    if (conf->connection != NULL)
        return (0);

    conf->connection = amqp_new_connection ();
    if (conf->connection == NULL)
    {
        ERROR ("amqp plugin: amqp_new_connection failed.");
        return (ENOMEM);
    }

    sockfd = amqp_open_socket (CONF(conf, host), conf->port);
    if (sockfd < 0)
    {
        char errbuf[1024];
        status = (-1) * sockfd;
        ERROR ("amqp plugin: amqp_open_socket failed: %s",
                sstrerror (status, errbuf, sizeof (errbuf)));
        amqp_destroy_connection (conf->connection);
        conf->connection = NULL;
        return (status);
    }
    amqp_set_sockfd (conf->connection, sockfd);

    reply = amqp_login (conf->connection, CONF(conf, vhost),
            /* channel max = */      0,
            /* frame max   = */ 131072,
            /* heartbeat   = */      0,
            /* authentication = */ AMQP_SASL_METHOD_PLAIN,
            CONF(conf, user), CONF(conf, password));
    if (reply.reply_type != AMQP_RESPONSE_NORMAL)
    {
        ERROR ("amqp plugin: amqp_login (vhost = %s, user = %s) failed.",
                CONF(conf, vhost), CONF(conf, user));
        amqp_destroy_connection (conf->connection);
        close (sockfd);
        conf->connection = NULL;
        return (1);
    }

    amqp_channel_open (conf->connection, /* channel = */ 1);
    /* FIXME: Is checking "reply.reply_type" really correct here? How does
     * it get set? --octo */
    if (reply.reply_type != AMQP_RESPONSE_NORMAL)
    {
        ERROR ("amqp plugin: amqp_channel_open failed.");
        amqp_connection_close (conf->connection, AMQP_REPLY_SUCCESS);
        amqp_destroy_connection (conf->connection);
        close(sockfd);
        conf->connection = NULL;
        return (1);
    }

    INFO ("amqp plugin: Successfully opened connection to vhost \"%s\" "
            "on %s:%i.", CONF(conf, vhost), CONF(conf, host), conf->port);

    status = camqp_create_exchange (conf);
    if (status != 0)
        return (status);

    if (!conf->publish)
        return (camqp_setup_queue (conf));
    return (0);
}