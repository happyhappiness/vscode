int luaC_pushcdtime(lua_State *L, cdtime_t t) /* {{{ */
{
  double d = CDTIME_T_TO_DOUBLE(t);

  lua_pushnumber(L, (lua_Number)d);
  return (0);
}