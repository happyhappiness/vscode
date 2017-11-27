static int lua_cb_log_info(lua_State *L) /* {{{ */
{
  const char *msg = luaL_checkstring(L, 1);
  plugin_log(LOG_INFO, "%s", msg);
  return 0;
}