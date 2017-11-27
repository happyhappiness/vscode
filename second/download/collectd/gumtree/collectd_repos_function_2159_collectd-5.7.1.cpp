static int ctail_config(oconfig_item_t *ci) {
  for (int i = 0; i < ci->children_num; i++) {
    oconfig_item_t *option = ci->children + i;

    if (strcasecmp("File", option->key) == 0)
      ctail_config_add_file(option);
    else {
      WARNING("tail plugin: Option `%s' not allowed here.", option->key);
    }
  } /* for (i = 0; i < ci->children_num; i++) */

  return (0);
}