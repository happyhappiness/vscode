static int luaC_pushvalues(lua_State *L, const data_set_t *ds,
                           const value_list_t *vl) /* {{{ */
{
  assert(vl->values_len == ds->ds_num);

  lua_newtable(L);
  for (size_t i = 0; i < vl->values_len; i++) {
    lua_pushinteger(L, (lua_Integer)i + 1);
    luaC_pushvalue(L, vl->values[i], ds->ds[i].type);
    lua_settable(L, -3);
  }

  return 0;
}