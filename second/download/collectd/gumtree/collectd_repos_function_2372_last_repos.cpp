static int aquaero_config(oconfig_item_t *ci) {
  for (int i = 0; i < ci->children_num; i++) {
    oconfig_item_t *child = ci->children + i;

    if (strcasecmp("Device", child->key))
      cf_util_get_string(child, &conf_device);
    else {
      ERROR("aquaero plugin: Unknown config option \"%s\".", child->key);
    }
  }

  return 0;
}