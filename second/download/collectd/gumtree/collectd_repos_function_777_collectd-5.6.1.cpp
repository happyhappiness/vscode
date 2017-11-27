value_t luaC_tovalue(lua_State *L, int idx, int ds_type) /* {{{ */
{
  value_t v = { 0 };

  if (!lua_isnumber(L, idx))
    return (v);

  if (ds_type == DS_TYPE_GAUGE)
    v.gauge = (gauge_t)lua_tonumber(L, /* stack pos = */ -1);
  else if (ds_type == DS_TYPE_DERIVE)
    v.derive = (derive_t)lua_tointeger(L, /* stack pos = */ -1);
  else if (ds_type == DS_TYPE_COUNTER)
    v.counter = (counter_t)lua_tointeger(L, /* stack pos = */ -1);
  else if (ds_type == DS_TYPE_ABSOLUTE)
    v.absolute = (absolute_t)lua_tointeger(L, /* stack pos = */ -1);

  return (v);
}