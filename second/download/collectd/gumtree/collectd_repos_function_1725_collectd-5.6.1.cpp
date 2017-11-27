static int lua_cb_log_notice(lua_State *L) /* {{{ */
{
  const char *msg = luaL_checkstring(L, 1);
  plugin_log(LOG_NOTICE, "%s", msg);
  return 0;
}