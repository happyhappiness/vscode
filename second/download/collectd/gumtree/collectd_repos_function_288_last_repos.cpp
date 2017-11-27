static int camqp_setup_queue(camqp_config_t *conf) /* {{{ */
{
  amqp_queue_declare_ok_t *qd_ret;
  amqp_basic_consume_ok_t *cm_ret;

  qd_ret = amqp_queue_declare(conf->connection,
                              /* channel     = */ CAMQP_CHANNEL,
                              /* queue       = */ (conf->queue != NULL)
                                  ? amqp_cstring_bytes(conf->queue)
                                  : AMQP_EMPTY_BYTES,
                              /* passive     = */ 0,
                              /* durable     = */ conf->queue_durable,
                              /* exclusive   = */ 0,
                              /* auto_delete = */ conf->queue_auto_delete,
                              /* arguments   = */ AMQP_EMPTY_TABLE);
  if (qd_ret == NULL) {
    ERROR("amqp plugin: amqp_queue_declare failed.");
    camqp_close_connection(conf);
    return -1;
  }

  if (conf->queue == NULL) {
    conf->queue = camqp_bytes_cstring(&qd_ret->queue);
    if (conf->queue == NULL) {
      ERROR("amqp plugin: camqp_bytes_cstring failed.");
      camqp_close_connection(conf);
      return -1;
    }

    INFO("amqp plugin: Created queue \"%s\".", conf->queue);
  }
  DEBUG("amqp plugin: Successfully created queue \"%s\".", conf->queue);

  /* bind to an exchange */
  if (conf->exchange != NULL) {
    amqp_queue_bind_ok_t *qb_ret;

    assert(conf->queue != NULL);
    qb_ret =
        amqp_queue_bind(conf->connection,
                        /* channel     = */ CAMQP_CHANNEL,
                        /* queue       = */ amqp_cstring_bytes(conf->queue),
                        /* exchange    = */ amqp_cstring_bytes(conf->exchange),
                        /* routing_key = */ (conf->routing_key != NULL)
                            ? amqp_cstring_bytes(conf->routing_key)
                            : AMQP_EMPTY_BYTES,
                        /* arguments   = */ AMQP_EMPTY_TABLE);
    if ((qb_ret == NULL) && camqp_is_error(conf)) {
      char errbuf[1024];
      ERROR("amqp plugin: amqp_queue_bind failed: %s",
            camqp_strerror(conf, errbuf, sizeof(errbuf)));
      camqp_close_connection(conf);
      return -1;
    }

    DEBUG("amqp plugin: Successfully bound queue \"%s\" to exchange \"%s\".",
          conf->queue, conf->exchange);
  } /* if (conf->exchange != NULL) */

  cm_ret =
      amqp_basic_consume(conf->connection,
                         /* channel      = */ CAMQP_CHANNEL,
                         /* queue        = */ amqp_cstring_bytes(conf->queue),
                         /* consumer_tag = */ AMQP_EMPTY_BYTES,
                         /* no_local     = */ 0,
                         /* no_ack       = */ 1,
                         /* exclusive    = */ 0,
                         /* arguments    = */ AMQP_EMPTY_TABLE);
  if ((cm_ret == NULL) && camqp_is_error(conf)) {
    char errbuf[1024];
    ERROR("amqp plugin: amqp_basic_consume failed: %s",
          camqp_strerror(conf, errbuf, sizeof(errbuf)));
    camqp_close_connection(conf);
    return -1;
  }

  return 0;
}