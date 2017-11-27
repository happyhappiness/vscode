static int luaC_pushdstypes(lua_State *L, const data_set_t *ds) /* {{{ */
{
  lua_newtable(L);
  for (size_t i = 0; i < ds->ds_num; i++) {
    lua_pushinteger(L, (lua_Integer)i);
    lua_pushstring(L, DS_TYPE_TO_STRING(ds->ds[i].type));
    lua_settable(L, -3);
  }

  return (0);
}