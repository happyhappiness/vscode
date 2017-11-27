cdtime_t luaC_tocdtime(lua_State *L, int idx) /* {{{ */
{
  if (!lua_isnumber(L, /* stack pos = */ idx))
    return 0;

  double d = lua_tonumber(L, idx);

  return DOUBLE_TO_CDTIME_T(d);
}