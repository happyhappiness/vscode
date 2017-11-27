static int clua_store_callback(lua_State *L, int idx) /* {{{ */
{
  /* Copy the function pointer */
  lua_pushvalue(L, idx);

  return luaL_ref(L, LUA_REGISTRYINDEX);
}