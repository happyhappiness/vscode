static int ltoc_values(lua_State *L, /* {{{ */
                       const data_set_t *ds, value_t *ret_values) {
  if (!lua_istable(L, -1)) {
    WARNING("ltoc_values: not a table");
    return (-1);
  }

  /* Push initial key */
  lua_pushnil(L); /* +1 = 1 */
  size_t i = 0;
  while (lua_next(L, -2) != 0) /* -1+2 = 2 || -1 = 0 */
  {
    if (i >= ds->ds_num) {
      lua_pop(L, 2); /* -2 = 0 */
      i++;
      break;
    }

    ret_values[i] = luaC_tovalue(L, -1, ds->ds[i].type);

    /* Pop the value */
    lua_pop(L, 1); /* -1 = 1 */
    i++;
  } /* while (lua_next) */

  if (i != ds->ds_num) {
    WARNING("ltoc_values: invalid size for datasource \"%s\": expected %zu, "
            "got %zu",
            ds->type, ds->ds_num, i);
    return (-1);
  }

  return (0);
}