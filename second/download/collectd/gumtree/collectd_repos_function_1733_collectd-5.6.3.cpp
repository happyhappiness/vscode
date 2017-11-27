static int open_collectd(lua_State *L) /* {{{ */
{
#if LUA_VERSION_NUM < 502
  luaL_register(L, "collectd", collectdlib);
#else
  luaL_newlib(L, collectdlib);
#endif
  return 1;
}