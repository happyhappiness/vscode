static int camqp_write_locked(camqp_config_t *conf, /* {{{ */
                              const char *buffer, const char *routing_key) {
  int status;

  status = camqp_connect(conf);
  if (status != 0)
    return status;

  amqp_basic_properties_t props = {._flags = AMQP_BASIC_CONTENT_TYPE_FLAG |
                                             AMQP_BASIC_DELIVERY_MODE_FLAG |
                                             AMQP_BASIC_APP_ID_FLAG,
                                   .delivery_mode = conf->delivery_mode,
                                   .app_id = amqp_cstring_bytes("collectd")};

  if (conf->format == CAMQP_FORMAT_COMMAND)
    props.content_type = amqp_cstring_bytes("text/collectd");
  else if (conf->format == CAMQP_FORMAT_JSON)
    props.content_type = amqp_cstring_bytes("application/json");
  else if (conf->format == CAMQP_FORMAT_GRAPHITE)
    props.content_type = amqp_cstring_bytes("text/graphite");
  else
    assert(23 == 42);

  status = amqp_basic_publish(
      conf->connection,
      /* channel = */ 1, amqp_cstring_bytes(CONF(conf, exchange)),
      amqp_cstring_bytes(routing_key),
      /* mandatory = */ 0,
      /* immediate = */ 0, &props, amqp_cstring_bytes(buffer));
  if (status != 0) {
    ERROR("amqp plugin: amqp_basic_publish failed with status %i.", status);
    camqp_close_connection(conf);
  }

  return status;
}