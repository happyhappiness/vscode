static int mqtt_write(const data_set_t *ds, const value_list_t *vl,
                      user_data_t *user_data) {
  mqtt_client_conf_t *conf;
  char topic[MQTT_MAX_TOPIC_SIZE];
  char payload[MQTT_MAX_MESSAGE_SIZE];
  int status = 0;

  if ((user_data == NULL) || (user_data->data == NULL))
    return EINVAL;
  conf = user_data->data;

  status = format_topic(topic, sizeof(topic), ds, vl, conf);
  if (status != 0) {
    ERROR("mqtt plugin: format_topic failed with status %d.", status);
    return status;
  }

  status = format_values(payload, sizeof(payload), ds, vl, conf->store_rates);
  if (status != 0) {
    ERROR("mqtt plugin: format_values failed with status %d.", status);
    return status;
  }

  status = publish(conf, topic, payload, strlen(payload) + 1);
  if (status != 0) {
    ERROR("mqtt plugin: publish failed: %s", mosquitto_strerror(status));
    return status;
  }

  return status;
}