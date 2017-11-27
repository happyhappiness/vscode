value_list_t *luaC_tovaluelist(lua_State *L, int idx) /* {{{ */
{
#if COLLECT_DEBUG
  int stack_top_before = lua_gettop(L);
#endif

  /* Convert relative indexes to absolute indexes, so it doesn't change when we
   * push / pop stuff. */
  if (idx < 1)
    idx += lua_gettop(L) + 1;

  /* Check that idx is in the valid range */
  if ((idx < 1) || (idx > lua_gettop(L))) {
    DEBUG("luaC_tovaluelist: idx(%d), top(%d)", idx, stack_top_before);
    return (NULL);
  }

  value_list_t *vl = calloc(1, sizeof(*vl));
  if (vl == NULL) {
    DEBUG("luaC_tovaluelist: calloc failed");
    return (NULL);
  }

  /* Push initial key */
  lua_pushnil(L);
  while (lua_next(L, idx) != 0) {
    const char *key = lua_tostring(L, -2);

    if (key == NULL) {
      DEBUG("luaC_tovaluelist: Ignoring non-string key.");
    } else if (strcasecmp("host", key) == 0)
      luaC_tostringbuffer(L, -1, vl->host, sizeof(vl->host));
    else if (strcasecmp("plugin", key) == 0)
      luaC_tostringbuffer(L, -1, vl->plugin, sizeof(vl->plugin));
    else if (strcasecmp("plugin_instance", key) == 0)
      luaC_tostringbuffer(L, -1, vl->plugin_instance,
                          sizeof(vl->plugin_instance));
    else if (strcasecmp("type", key) == 0)
      luaC_tostringbuffer(L, -1, vl->type, sizeof(vl->type));
    else if (strcasecmp("type_instance", key) == 0)
      luaC_tostringbuffer(L, -1, vl->type_instance, sizeof(vl->type_instance));
    else if (strcasecmp("time", key) == 0)
      vl->time = luaC_tocdtime(L, -1);
    else if (strcasecmp("interval", key) == 0)
      vl->interval = luaC_tocdtime(L, -1);
    else if (strcasecmp("values", key) == 0) {
      /* This key is not handled here, because we have to assure "type" is read
       * first. */
    } else {
      DEBUG("luaC_tovaluelist: Ignoring unknown key \"%s\".", key);
    }

    /* Pop the value */
    lua_pop(L, 1);
  }

  const data_set_t *ds = plugin_get_ds(vl->type);
  if (ds == NULL) {
    INFO("utils_lua: Unable to lookup type \"%s\".", vl->type);
    sfree(vl);
    return (NULL);
  }

  int status = ltoc_table_values(L, idx, ds, vl);
  if (status != 0) {
    WARNING("utils_lua: ltoc_table_values failed.");
    sfree(vl);
    return (NULL);
  }

#if COLLECT_DEBUG
  assert(stack_top_before == lua_gettop(L));
#endif
  return (vl);
}