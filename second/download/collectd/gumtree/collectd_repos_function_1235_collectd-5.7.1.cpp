static int mqtt_config_subscriber(oconfig_item_t *ci) {
  mqtt_client_conf_t **tmp;
  mqtt_client_conf_t *conf;
  int status;

  conf = calloc(1, sizeof(*conf));
  if (conf == NULL) {
    ERROR("mqtt plugin: calloc failed.");
    return (-1);
  }
  conf->publish = 0;

  conf->name = NULL;
  status = cf_util_get_string(ci, &conf->name);
  if (status != 0) {
    mqtt_free(conf);
    return (status);
  }

  conf->host = strdup(MQTT_DEFAULT_HOST);
  conf->port = MQTT_DEFAULT_PORT;
  conf->client_id = NULL;
  conf->qos = 2;
  conf->topic = strdup(MQTT_DEFAULT_TOPIC);
  conf->clean_session = 1;

  status = pthread_mutex_init(&conf->lock, NULL);
  if (status != 0) {
    mqtt_free(conf);
    return (status);
  }

  C_COMPLAIN_INIT(&conf->complaint_cantpublish);

  for (int i = 0; i < ci->children_num; i++) {
    oconfig_item_t *child = ci->children + i;
    if (strcasecmp("Host", child->key) == 0)
      cf_util_get_string(child, &conf->host);
    else if (strcasecmp("Port", child->key) == 0) {
      status = cf_util_get_port_number(child);
      if (status < 0)
        ERROR("mqtt plugin: Invalid port number.");
      else
        conf->port = status;
    } else if (strcasecmp("ClientId", child->key) == 0)
      cf_util_get_string(child, &conf->client_id);
    else if (strcasecmp("User", child->key) == 0)
      cf_util_get_string(child, &conf->username);
    else if (strcasecmp("Password", child->key) == 0)
      cf_util_get_string(child, &conf->password);
    else if (strcasecmp("QoS", child->key) == 0) {
      int qos = -1;
      status = cf_util_get_int(child, &qos);
      if ((status != 0) || (qos < 0) || (qos > 2))
        ERROR("mqtt plugin: Not a valid QoS setting.");
      else
        conf->qos = qos;
    } else if (strcasecmp("Topic", child->key) == 0)
      cf_util_get_string(child, &conf->topic);
    else if (strcasecmp("CleanSession", child->key) == 0)
      cf_util_get_boolean(child, &conf->clean_session);
    else
      ERROR("mqtt plugin: Unknown config option: %s", child->key);
  }

  tmp = realloc(subscribers, sizeof(*subscribers) * (subscribers_num + 1));
  if (tmp == NULL) {
    ERROR("mqtt plugin: realloc failed.");
    mqtt_free(conf);
    return (-1);
  }
  subscribers = tmp;
  subscribers[subscribers_num] = conf;
  subscribers_num++;

  return (0);
}