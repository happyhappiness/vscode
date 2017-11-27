static int lua_config_script(const oconfig_item_t *ci) /* {{{ */
{
  char rel_path[PATH_MAX];

  int status = cf_util_get_string_buffer(ci, rel_path, sizeof(rel_path));
  if (status != 0)
    return status;

  char abs_path[PATH_MAX];

  if (base_path[0] == '\0')
    sstrncpy(abs_path, rel_path, sizeof(abs_path));
  else
    snprintf(abs_path, sizeof(abs_path), "%s/%s", base_path, rel_path);

  DEBUG("Lua plugin: abs_path = \"%s\";", abs_path);

  status = lua_script_load(abs_path);
  if (status != 0)
    return status;

  INFO("Lua plugin: File \"%s\" loaded successfully", abs_path);

  return 0;
}