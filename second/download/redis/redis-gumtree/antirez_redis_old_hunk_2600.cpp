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


static int gettoalign (size_t len, Header *h, int opt, size_t size) {
  if (size == 0 || opt == 'c') return 0;
  if (size > (size_t)h->align) size = h->align;  /* respect max. alignment */
  return  (size - (len & (size - 1))) & (size - 1);
}


static void commoncases (lua_State *L, int opt, const char **fmt, Header *h) {
  switch (opt) {
    case  ' ': return;  /* ignore white spaces */
    case '>': h->endian = BIG; return;
