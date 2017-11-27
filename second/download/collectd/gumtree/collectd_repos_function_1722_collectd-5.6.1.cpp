static int lua_cb_log_debug(lua_State *L) /* {{{ */
{
  const char *msg = luaL_checkstring(L, 1);
  plugin_log(LOG_DEBUG, "%s", msg);
  return 0;
}