static int lua_cb_log_error(lua_State *L) /* {{{ */
{
  const char *msg = luaL_checkstring(L, 1);
  plugin_log(LOG_ERR, "%s", msg);
  return 0;
}