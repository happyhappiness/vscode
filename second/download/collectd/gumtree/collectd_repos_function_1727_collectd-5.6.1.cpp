static int lua_cb_dispatch_values(lua_State *L) /* {{{ */
{
  int nargs = lua_gettop(L);

  if (nargs != 1)
    return luaL_error(L, "Invalid number of arguments (%d != 1)", nargs);

  luaL_checktype(L, 1, LUA_TTABLE);

  value_list_t *vl = luaC_tovaluelist(L, -1);
  if (vl == NULL)
    return luaL_error(L, "%s", "luaC_tovaluelist failed");

#if COLLECT_DEBUG
  char identifier[6 * DATA_MAX_NAME_LEN];
  FORMAT_VL(identifier, sizeof(identifier), vl);

  DEBUG("Lua plugin: collectd.dispatch_values(): Received value list \"%s\", "
        "time %.3f, interval %.3f.",
        identifier, CDTIME_T_TO_DOUBLE(vl->time),
        CDTIME_T_TO_DOUBLE(vl->interval));
#endif

  plugin_dispatch_values(vl);

  sfree(vl->values);
  sfree(vl);
  return 0;
}