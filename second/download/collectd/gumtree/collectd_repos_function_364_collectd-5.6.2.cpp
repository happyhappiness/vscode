static int camqp_config_connection(oconfig_item_t *ci, /* {{{ */
                                   _Bool publish) {
  camqp_config_t *conf;
  int status;

  conf = calloc(1, sizeof(*conf));
  if (conf == NULL) {
    ERROR("amqp plugin: calloc failed.");
    return (ENOMEM);
  }

  /* Initialize "conf" {{{ */
  conf->publish = publish;
  conf->name = NULL;
  conf->format = CAMQP_FORMAT_COMMAND;
  conf->host = NULL;
  conf->port = 5672;
  conf->vhost = NULL;
  conf->user = NULL;
  conf->password = NULL;
  conf->exchange = NULL;
  conf->routing_key = NULL;
  conf->connection_retry_delay = 0;

  /* publish only */
  conf->delivery_mode = CAMQP_DM_VOLATILE;
  conf->store_rates = 0;
  conf->graphite_flags = 0;
  /* publish & graphite only */
  conf->prefix = NULL;
  conf->postfix = NULL;
  conf->escape_char = '_';
  /* subscribe only */
  conf->exchange_type = NULL;
  conf->queue = NULL;
  conf->queue_durable = 0;
  conf->queue_auto_delete = 1;
  /* general */
  conf->connection = NULL;
  pthread_mutex_init(&conf->lock, /* attr = */ NULL);
  /* }}} */

  status = cf_util_get_string(ci, &conf->name);
  if (status != 0) {
    sfree(conf);
    return (status);
  }

  for (int i = 0; i < ci->children_num; i++) {
    oconfig_item_t *child = ci->children + i;

    if (strcasecmp("Host", child->key) == 0)
      status = cf_util_get_string(child, &conf->host);
    else if (strcasecmp("Port", child->key) == 0) {
      status = cf_util_get_port_number(child);
      if (status > 0) {
        conf->port = status;
        status = 0;
      }
    } else if (strcasecmp("VHost", child->key) == 0)
      status = cf_util_get_string(child, &conf->vhost);
    else if (strcasecmp("User", child->key) == 0)
      status = cf_util_get_string(child, &conf->user);
    else if (strcasecmp("Password", child->key) == 0)
      status = cf_util_get_string(child, &conf->password);
    else if (strcasecmp("Exchange", child->key) == 0)
      status = cf_util_get_string(child, &conf->exchange);
    else if ((strcasecmp("ExchangeType", child->key) == 0) && !publish)
      status = cf_util_get_string(child, &conf->exchange_type);
    else if ((strcasecmp("Queue", child->key) == 0) && !publish)
      status = cf_util_get_string(child, &conf->queue);
    else if ((strcasecmp("QueueDurable", child->key) == 0) && !publish)
      status = cf_util_get_boolean(child, &conf->queue_durable);
    else if ((strcasecmp("QueueAutoDelete", child->key) == 0) && !publish)
      status = cf_util_get_boolean(child, &conf->queue_auto_delete);
    else if (strcasecmp("RoutingKey", child->key) == 0)
      status = cf_util_get_string(child, &conf->routing_key);
    else if ((strcasecmp("Persistent", child->key) == 0) && publish) {
      _Bool tmp = 0;
      status = cf_util_get_boolean(child, &tmp);
      if (tmp)
        conf->delivery_mode = CAMQP_DM_PERSISTENT;
      else
        conf->delivery_mode = CAMQP_DM_VOLATILE;
    } else if ((strcasecmp("StoreRates", child->key) == 0) && publish) {
      status = cf_util_get_boolean(child, &conf->store_rates);
      (void)cf_util_get_flag(child, &conf->graphite_flags,
                             GRAPHITE_STORE_RATES);
    } else if ((strcasecmp("Format", child->key) == 0) && publish)
      status = camqp_config_set_format(child, conf);
    else if ((strcasecmp("GraphiteSeparateInstances", child->key) == 0) &&
             publish)
      status = cf_util_get_flag(child, &conf->graphite_flags,
                                GRAPHITE_SEPARATE_INSTANCES);
    else if ((strcasecmp("GraphiteAlwaysAppendDS", child->key) == 0) && publish)
      status = cf_util_get_flag(child, &conf->graphite_flags,
                                GRAPHITE_ALWAYS_APPEND_DS);
    else if ((strcasecmp("GraphitePrefix", child->key) == 0) && publish)
      status = cf_util_get_string(child, &conf->prefix);
    else if ((strcasecmp("GraphitePostfix", child->key) == 0) && publish)
      status = cf_util_get_string(child, &conf->postfix);
    else if ((strcasecmp("GraphiteEscapeChar", child->key) == 0) && publish) {
      char *tmp_buff = NULL;
      status = cf_util_get_string(child, &tmp_buff);
      if (strlen(tmp_buff) > 1)
        WARNING("amqp plugin: The option \"GraphiteEscapeChar\" handles "
                "only one character. Others will be ignored.");
      conf->escape_char = tmp_buff[0];
      sfree(tmp_buff);
    } else if (strcasecmp("ConnectionRetryDelay", child->key) == 0)
      status = cf_util_get_int(child, &conf->connection_retry_delay);
    else
      WARNING("amqp plugin: Ignoring unknown "
              "configuration option \"%s\".",
              child->key);

    if (status != 0)
      break;
  } /* for (i = 0; i < ci->children_num; i++) */

  if ((status == 0) && (conf->exchange == NULL)) {
    if (conf->exchange_type != NULL)
      WARNING("amqp plugin: The option \"ExchangeType\" was given "
              "without the \"Exchange\" option. It will be ignored.");

    if (!publish && (conf->routing_key != NULL))
      WARNING("amqp plugin: The option \"RoutingKey\" was given "
              "without the \"Exchange\" option. It will be ignored.");
  }

  if (status != 0) {
    camqp_config_free(conf);
    return (status);
  }

  if (conf->exchange != NULL) {
    DEBUG("amqp plugin: camqp_config_connection: exchange = %s;",
          conf->exchange);
  }

  if (publish) {
    char cbname[128];
    user_data_t ud = {conf, camqp_config_free};

    ssnprintf(cbname, sizeof(cbname), "amqp/%s", conf->name);

    status = plugin_register_write(cbname, camqp_write, &ud);
    if (status != 0) {
      camqp_config_free(conf);
      return (status);
    }
  } else {
    status = camqp_subscribe_init(conf);
    if (status != 0) {
      camqp_config_free(conf);
      return (status);
    }
  }

  return (0);
}