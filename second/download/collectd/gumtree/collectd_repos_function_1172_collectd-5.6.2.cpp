static void mqtt_free(mqtt_client_conf_t *conf) {
  if (conf == NULL)
    return;

  if (conf->connected)
    (void)mosquitto_disconnect(conf->mosq);
  conf->connected = 0;
  (void)mosquitto_destroy(conf->mosq);

  sfree(conf->host);
  sfree(conf->username);
  sfree(conf->password);
  sfree(conf->client_id);
  sfree(conf->topic_prefix);
  sfree(conf);
}