static int format_topic(char *buf, size_t buf_len, data_set_t const *ds,
                        value_list_t const *vl, mqtt_client_conf_t *conf) {
  char name[MQTT_MAX_TOPIC_SIZE];
  int status;
  char *c;

  if ((conf->topic_prefix == NULL) || (conf->topic_prefix[0] == 0))
    return (FORMAT_VL(buf, buf_len, vl));

  status = FORMAT_VL(name, sizeof(name), vl);
  if (status != 0)
    return (status);

  status = ssnprintf(buf, buf_len, "%s/%s", conf->topic_prefix, name);
  if ((status < 0) || (((size_t)status) >= buf_len))
    return (ENOMEM);

  while((c = strchr(buf, '#')) || (c = strchr(buf, '+'))) {
       *c = '_';
  }

  return (0);
}