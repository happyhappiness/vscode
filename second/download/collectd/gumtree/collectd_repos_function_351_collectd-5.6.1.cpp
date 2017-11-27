static int camqp_create_exchange (camqp_config_t *conf) /* {{{ */
{
    amqp_exchange_declare_ok_t *ed_ret;

    if (conf->exchange_type == NULL)
        return (0);

    ed_ret = amqp_exchange_declare (conf->connection,
            /* channel     = */ CAMQP_CHANNEL,
            /* exchange    = */ amqp_cstring_bytes (conf->exchange),
            /* type        = */ amqp_cstring_bytes (conf->exchange_type),
            /* passive     = */ 0,
            /* durable     = */ 0,
            /* auto_delete = */ 1,
            /* arguments   = */ AMQP_EMPTY_TABLE);
    if ((ed_ret == NULL) && camqp_is_error (conf))
    {
        char errbuf[1024];
        ERROR ("amqp plugin: amqp_exchange_declare failed: %s",
                camqp_strerror (conf, errbuf, sizeof (errbuf)));
        camqp_close_connection (conf);
        return (-1);
    }

    INFO ("amqp plugin: Successfully created exchange \"%s\" "
            "with type \"%s\".",
            conf->exchange, conf->exchange_type);

    return (0);
}