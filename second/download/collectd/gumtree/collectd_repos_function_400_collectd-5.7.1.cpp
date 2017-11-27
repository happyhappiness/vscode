static int camqp_write(const data_set_t *ds, const value_list_t *vl, /* {{{ */
                       user_data_t *user_data) {
  camqp_config_t *conf = user_data->data;
  char routing_key[6 * DATA_MAX_NAME_LEN];
  char buffer[8192];
  int status;

  if ((ds == NULL) || (vl == NULL) || (conf == NULL))
    return (EINVAL);

  if (conf->routing_key != NULL) {
    sstrncpy(routing_key, conf->routing_key, sizeof(routing_key));
  } else {
    ssnprintf(routing_key, sizeof(routing_key), "collectd/%s/%s/%s/%s/%s",
              vl->host, vl->plugin, vl->plugin_instance, vl->type,
              vl->type_instance);

    /* Switch slashes (the only character forbidden by collectd) and dots
     * (the separation character used by AMQP). */
    for (size_t i = 0; routing_key[i] != 0; i++) {
      if (routing_key[i] == '.')
        routing_key[i] = '/';
      else if (routing_key[i] == '/')
        routing_key[i] = '.';
    }
  }

  if (conf->format == CAMQP_FORMAT_COMMAND) {
    status = cmd_create_putval(buffer, sizeof(buffer), ds, vl);
    if (status != 0) {
      ERROR("amqp plugin: cmd_create_putval failed with status %i.", status);
      return (status);
    }
  } else if (conf->format == CAMQP_FORMAT_JSON) {
    size_t bfree = sizeof(buffer);
    size_t bfill = 0;

    format_json_initialize(buffer, &bfill, &bfree);
    format_json_value_list(buffer, &bfill, &bfree, ds, vl, conf->store_rates);
    format_json_finalize(buffer, &bfill, &bfree);
  } else if (conf->format == CAMQP_FORMAT_GRAPHITE) {
    status =
        format_graphite(buffer, sizeof(buffer), ds, vl, conf->prefix,
                        conf->postfix, conf->escape_char, conf->graphite_flags);
    if (status != 0) {
      ERROR("amqp plugin: format_graphite failed with status %i.", status);
      return (status);
    }
  } else {
    ERROR("amqp plugin: Invalid format (%i).", conf->format);
    return (-1);
  }

  pthread_mutex_lock(&conf->lock);
  status = camqp_write_locked(conf, buffer, routing_key);
  pthread_mutex_unlock(&conf->lock);

  return (status);
}