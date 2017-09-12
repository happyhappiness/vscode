static size_t optsize (lua_State *L, char opt, const char **fmt) {
  switch (opt) {
    case 'B': case 'b': return sizeof(char);
    case 'H': case 'h': return sizeof(short);
    case 'L': case 'l': return sizeof(long);
    case 'f':  return sizeof(float);
    case 'd':  return sizeof(double);
    case 'x': return 1;
    case 'c': return getnum(fmt, 1);
    case 's': case ' ': case '<': case '>': case '!': return 0;
    case 'i': case 'I': {
      int sz = getnum(fmt, sizeof(int));
      if (!isp2(sz))
        luaL_error(L, "integral size %d is not a power of 2", sz);
      return sz;
    }
    default: {
      const char *msg = lua_pushfstring(L, "invalid format option [%c]", opt);
      return luaL_argerror(L, 1, msg);
    }
  }
}