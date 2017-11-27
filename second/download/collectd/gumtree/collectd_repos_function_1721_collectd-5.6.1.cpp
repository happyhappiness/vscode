static int clua_write(const data_set_t *ds, const value_list_t *vl, /* {{{ */
                      user_data_t *ud) {
  clua_callback_data_t *cb = ud->data;

  pthread_mutex_lock(&cb->lock);

  lua_State *L = cb->lua_state;

  int status = clua_load_callback(L, cb->callback_id);
  if (status != 0) {
    ERROR("Lua plugin: Unable to load callback \"%s\" (id %i).",
          cb->lua_function_name, cb->callback_id);
    pthread_mutex_unlock(&cb->lock);
    return (-1);
  }
  /* +1 = 1 */

  status = luaC_pushvaluelist(L, ds, vl);
  if (status != 0) {
    lua_pop(L, 1); /* -1 = 0 */
    pthread_mutex_unlock(&cb->lock);
    ERROR("Lua plugin: luaC_pushvaluelist failed.");
    return (-1);
  }
  /* +1 = 2 */

  status = lua_pcall(L, 1, 1, 0); /* -2+1 = 1 */
  if (status != 0) {
    const char *errmsg = lua_tostring(L, -1);
    if (errmsg == NULL)
      ERROR("Lua plugin: Calling the write callback failed. "
            "In addition, retrieving the error message failed.");
    else
      ERROR("Lua plugin: Calling the write callback failed:\n%s", errmsg);
    lua_pop(L, 1); /* -1 = 0 */
    pthread_mutex_unlock(&cb->lock);
    return (-1);
  }

  if (!lua_isnumber(L, -1)) {
    ERROR("Lua plugin: Write function \"%s\" (id %i) did not return a numeric "
          "value.",
          cb->lua_function_name, cb->callback_id);
    status = -1;
  } else {
    status = (int)lua_tointeger(L, -1);
  }

  lua_pop(L, 1); /* -1 = 0 */
  pthread_mutex_unlock(&cb->lock);
  return (status);
}