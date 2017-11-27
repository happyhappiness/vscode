int luaC_pushvalue(lua_State *L, value_t v, int ds_type) /* {{{ */
{
  if (ds_type == DS_TYPE_GAUGE)
    lua_pushnumber(L, (lua_Number)v.gauge);
  else if (ds_type == DS_TYPE_DERIVE)
    lua_pushinteger(L, (lua_Integer)v.derive);
  else if (ds_type == DS_TYPE_COUNTER)
    lua_pushinteger(L, (lua_Integer)v.counter);
  else if (ds_type == DS_TYPE_ABSOLUTE)
    lua_pushinteger(L, (lua_Integer)v.absolute);
  else
    return -1;
  return 0;
}