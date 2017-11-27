static int cr_config(oconfig_item_t *ci) {
  for (int i = 0; i < ci->children_num; i++) {
    oconfig_item_t *child = ci->children + i;

    if (strcasecmp("Router", child->key) == 0)
      cr_config_router(child);
    else {
      WARNING("routeros plugin: Unknown config option `%s'.", child->key);
    }
  }

  return 0;
}