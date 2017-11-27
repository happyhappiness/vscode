static int luaC_pushdsnames(lua_State *L, const data_set_t *ds) /* {{{ */
{
  lua_newtable(L);
  for (size_t i = 0; i < ds->ds_num; i++) {
    lua_pushinteger(L, (lua_Integer)i);
    lua_pushstring(L, ds->ds[i].name);
    lua_settable(L, -3);
  }

  return (0);
}