static int lua_config_base_path(const oconfig_item_t *ci) /* {{{ */
{
  int status = cf_util_get_string_buffer(ci, base_path, sizeof(base_path));
  if (status != 0)
    return (status);

  size_t len = strlen(base_path);
  while ((len > 0) && (base_path[len - 1] == '/')) {
    len--;
    base_path[len] = '\0';
  }

  DEBUG("Lua plugin: base_path = \"%s\";", base_path);

  return (0);
}