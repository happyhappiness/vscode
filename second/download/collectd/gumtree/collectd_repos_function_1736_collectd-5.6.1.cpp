static int lua_config(oconfig_item_t *ci) /* {{{ */
{
  int status = 0;
  for (int i = 0; i < ci->children_num; i++) {
    oconfig_item_t *child = ci->children + i;

    if (strcasecmp("BasePath", child->key) == 0) {
      status = lua_config_base_path(child);
    } else if (strcasecmp("Script", child->key) == 0) {
      status = lua_config_script(child);
    } else {
      ERROR("Lua plugin: Option `%s' is not allowed here.", child->key);
      status = 1;
    }
  }

  return status;
}