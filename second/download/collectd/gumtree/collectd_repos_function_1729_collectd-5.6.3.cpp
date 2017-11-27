static int lua_cb_log_warning(lua_State *L) /* {{{ */
{
  const char *msg = luaL_checkstring(L, 1);
  plugin_log(LOG_WARNING, "%s", msg);
  return 0;
}