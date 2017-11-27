static int mqtt_config_publisher(oconfig_item_t *ci) {
  mqtt_client_conf_t *conf;
  char cb_name[1024];
  int status;

  conf = calloc(1, sizeof(*conf));
  if (conf == NULL) {
    ERROR("mqtt plugin: calloc failed.");
    return -1;
  }
  conf->publish = 1;

  conf->name = NULL;
  status = cf_util_get_string(ci, &conf->name);
  if (status != 0) {
    mqtt_free(conf);
    return status;
  }

  conf->host = strdup(MQTT_DEFAULT_HOST);
  conf->port = MQTT_DEFAULT_PORT;
  conf->client_id = NULL;
  conf->qos = 0;
  conf->topic_prefix = strdup(MQTT_DEFAULT_TOPIC_PREFIX);
  conf->store_rates = 1;

  status = pthread_mutex_init(&conf->lock, NULL);
  if (status != 0) {
    mqtt_free(conf);
    return status;
  }

  C_COMPLAIN_INIT(&conf->complaint_cantpublish);

  for (int i = 0; i < ci->children_num; i++) {
    oconfig_item_t *child = ci->children + i;
    if (strcasecmp("Host", child->key) == 0)
      cf_util_get_string(child, &conf->host);
    else if (strcasecmp("Port", child->key) == 0) {
      int tmp = cf_util_get_port_number(child);
      if (tmp < 0)
        ERROR("mqtt plugin: Invalid port number.");
      else
        conf->port = tmp;
    } else if (strcasecmp("ClientId", child->key) == 0)
      cf_util_get_string(child, &conf->client_id);
    else if (strcasecmp("User", child->key) == 0)
      cf_util_get_string(child, &conf->username);
    else if (strcasecmp("Password", child->key) == 0)
      cf_util_get_string(child, &conf->password);
    else if (strcasecmp("QoS", child->key) == 0) {
      int tmp = -1;
      status = cf_util_get_int(child, &tmp);
      if ((status != 0) || (tmp < 0) || (tmp > 2))
        ERROR("mqtt plugin: Not a valid QoS setting.");
      else
        conf->qos = tmp;
    } else if (strcasecmp("Prefix", child->key) == 0)
      cf_util_get_string(child, &conf->topic_prefix);
    else if (strcasecmp("StoreRates", child->key) == 0)
      cf_util_get_boolean(child, &conf->store_rates);
    else if (strcasecmp("Retain", child->key) == 0)
      cf_util_get_boolean(child, &conf->retain);
    else if (strcasecmp("CACert", child->key) == 0)
      cf_util_get_string(child, &conf->cacertificatefile);
    else if (strcasecmp("CertificateFile", child->key) == 0)
      cf_util_get_string(child, &conf->certificatefile);
    else if (strcasecmp("CertificateKeyFile", child->key) == 0)
      cf_util_get_string(child, &conf->certificatekeyfile);
    else if (strcasecmp("TLSProtocol", child->key) == 0)
      cf_util_get_string(child, &conf->tlsprotocol);
    else if (strcasecmp("CipherSuite", child->key) == 0)
      cf_util_get_string(child, &conf->ciphersuite);
    else
      ERROR("mqtt plugin: Unknown config option: %s", child->key);
  }

  snprintf(cb_name, sizeof(cb_name), "mqtt/%s", conf->name);
  plugin_register_write(cb_name, mqtt_write,
                        &(user_data_t){
                            .data = conf,
                        });
  return 0;
}