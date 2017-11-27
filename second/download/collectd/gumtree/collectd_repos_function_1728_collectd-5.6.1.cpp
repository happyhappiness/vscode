static int lua_cb_register_read(lua_State *L) /* {{{ */
{
  int nargs = lua_gettop(L);

  if (nargs != 1)
    return luaL_error(L, "Invalid number of arguments (%d != 1)", nargs);

  luaL_checktype(L, 1, LUA_TFUNCTION);

  char function_name[DATA_MAX_NAME_LEN];
  ssnprintf(function_name, sizeof(function_name), "lua/%s", lua_tostring(L, 1));

  int callback_id = clua_store_callback(L, 1);
  if (callback_id < 0)
    return luaL_error(L, "%s", "Storing callback function failed");

  lua_State *thread = lua_newthread(L);
  if (thread == NULL)
    return luaL_error(L, "%s", "lua_newthread failed");
  clua_store_thread(L, -1);
  lua_pop(L, 1);

  clua_callback_data_t *cb = calloc(1, sizeof(*cb));
  if (cb == NULL)
    return luaL_error(L, "%s", "calloc failed");

  cb->lua_state = thread;
  cb->callback_id = callback_id;
  cb->lua_function_name = strdup(function_name);
  pthread_mutex_init(&cb->lock, NULL);

  user_data_t ud = {
    .data = cb
  };

  int status = plugin_register_complex_read(/* group = */ "lua",
                                            /* name      = */ function_name,
                                            /* callback  = */ clua_read,
                                            /* interval  = */ 0,
                                            /* user_data = */ &ud);

  if (status != 0)
    return luaL_error(L, "%s", "plugin_register_complex_read failed");
  return 0;
}