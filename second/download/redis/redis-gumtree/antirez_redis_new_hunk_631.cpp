    return 0;
}

/* ---------------------------------------------------------------------------
 * Lua engine initialization and reset.
 * ------------------------------------------------------------------------- */

void luaLoadLib(lua_State *lua, const char *libname, lua_CFunction luafunc) {
  lua_pushcfunction(lua, luafunc);
