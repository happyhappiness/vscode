static int mqtt_config(oconfig_item_t *ci) {
  for (int i = 0; i < ci->children_num; i++) {
    oconfig_item_t *child = ci->children + i;

    if (strcasecmp("Publish", child->key) == 0)
      mqtt_config_publisher(child);
    else if (strcasecmp("Subscribe", child->key) == 0)
      mqtt_config_subscriber(child);
    else
      ERROR("mqtt plugin: Unknown config option: %s", child->key);
  }

  return 0;
}