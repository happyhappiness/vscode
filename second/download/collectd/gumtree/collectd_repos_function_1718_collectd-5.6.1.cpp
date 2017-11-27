static int clua_load_callback(lua_State *L, int callback_ref) /* {{{ */
{
  lua_rawgeti(L, LUA_REGISTRYINDEX, callback_ref);

  if (!lua_isfunction(L, -1)) {
    lua_pop(L, 1);
    return (-1);
  }

  return (0);
}