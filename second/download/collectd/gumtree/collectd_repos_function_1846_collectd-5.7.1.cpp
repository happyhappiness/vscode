static int lua_script_init(lua_script_t *script) /* {{{ */
{
  memset(script, 0, sizeof(*script));

  /* initialize the lua context */
  script->lua_state = luaL_newstate();
  if (script->lua_state == NULL) {
    ERROR("Lua plugin: luaL_newstate() failed.");
    return (-1);
  }

  /* Open up all the standard Lua libraries. */
  luaL_openlibs(script->lua_state);

/* Load the 'collectd' library */
#if LUA_VERSION_NUM < 502
  lua_pushcfunction(script->lua_state, open_collectd);
  lua_pushstring(script->lua_state, "collectd");
  lua_call(script->lua_state, 1, 0);
#else
  luaL_requiref(script->lua_state, "collectd", open_collectd, 1);
  lua_pop(script->lua_state, 1);
#endif

  /* Prepend BasePath to package.path */
  if (base_path[0] != '\0') {
    lua_getglobal(script->lua_state, "package");
    lua_getfield(script->lua_state, -1, "path");

    const char *cur_path = lua_tostring(script->lua_state, -1);
    char *new_path = ssnprintf_alloc("%s/?.lua;%s", base_path, cur_path);

    lua_pop(script->lua_state, 1);
    lua_pushstring(script->lua_state, new_path);

    free(new_path);

    lua_setfield(script->lua_state, -2, "path");
    lua_pop(script->lua_state, 1);
  }

  return (0);
}