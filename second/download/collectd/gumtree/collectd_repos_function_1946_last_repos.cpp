static int clua_store_thread(lua_State *L, int idx) /* {{{ */
{
  if (idx < 0)
    idx += lua_gettop(L) + 1;

  /* Copy the thread pointer */
  lua_pushvalue(L, idx); /* +1 = 3 */
  if (!lua_isthread(L, -1)) {
    lua_pop(L, 3); /* -3 = 0 */
    return -1;
  }

  luaL_ref(L, LUA_REGISTRYINDEX);
  lua_pop(L, 1); /* -1 = 0 */
  return 0;
}