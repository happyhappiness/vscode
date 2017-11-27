static int lua_script_load(const char *script_path) /* {{{ */
{
  lua_script_t *script = malloc(sizeof(*script));
  if (script == NULL) {
    ERROR("Lua plugin: malloc failed.");
    return -1;
  }

  int status = lua_script_init(script);
  if (status != 0) {
    lua_script_free(script);
    return status;
  }

  script->script_path = strdup(script_path);
  if (script->script_path == NULL) {
    ERROR("Lua plugin: strdup failed.");
    lua_script_free(script);
    return -1;
  }

  status = luaL_loadfile(script->lua_state, script->script_path);
  if (status != 0) {
    ERROR("Lua plugin: luaL_loadfile failed: %s",
          lua_tostring(script->lua_state, -1));
    lua_pop(script->lua_state, 1);
    lua_script_free(script);
    return -1;
  }

  status = lua_pcall(script->lua_state,
                     /* nargs = */ 0,
                     /* nresults = */ LUA_MULTRET,
                     /* errfunc = */ 0);
  if (status != 0) {
    const char *errmsg = lua_tostring(script->lua_state, -1);

    if (errmsg == NULL)
      ERROR("Lua plugin: lua_pcall failed with status %i. "
            "In addition, no error message could be retrieved from the stack.",
            status);
    else
      ERROR("Lua plugin: Executing script \"%s\" failed:\n%s",
            script->script_path, errmsg);

    lua_script_free(script);
    return -1;
  }

  /* Append this script to the global list of scripts. */
  if (scripts) {
    lua_script_t *last = scripts;
    while (last->next)
      last = last->next;

    last->next = script;
  } else {
    scripts = script;
  }

  return 0;
}