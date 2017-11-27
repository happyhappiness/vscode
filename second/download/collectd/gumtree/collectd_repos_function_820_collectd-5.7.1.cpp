static int ltoc_table_values(lua_State *L, int idx, /* {{{ */
                             const data_set_t *ds, value_list_t *vl) {
  /* We're only called from "luaC_tovaluelist", which ensures that "idx" is an
   * absolute index (i.e. a positive number) */
  assert(idx > 0);

  lua_getfield(L, idx, "values");
  if (!lua_istable(L, -1)) {
    WARNING("utils_lua: ltoc_table_values: The \"values\" member is a %s "
            "value, not a table.",
            lua_typename(L, lua_type(L, -1)));
    lua_pop(L, 1);
    return (-1);
  }

  vl->values_len = ds->ds_num;
  vl->values = calloc(vl->values_len, sizeof(*vl->values));
  if (vl->values == NULL) {
    ERROR("utils_lua: calloc failed.");
    vl->values_len = 0;
    lua_pop(L, 1);
    return (-1);
  }

  int status = ltoc_values(L, ds, vl->values);

  lua_pop(L, 1);

  if (status != 0) {
    vl->values_len = 0;
    sfree(vl->values);
  }

  return (status);
}