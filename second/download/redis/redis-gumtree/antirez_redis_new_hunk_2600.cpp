    case 'B': case 'b': return sizeof(char);
    case 'H': case 'h': return sizeof(short);
    case 'L': case 'l': return sizeof(long);
    case 'T': return sizeof(size_t);
    case 'f':  return sizeof(float);
    case 'd':  return sizeof(double);
    case 'x': return 1;
    case 'c': return getnum(fmt, 1);
    case 'i': case 'I': {
      int sz = getnum(fmt, sizeof(int));
      if (sz > MAXINTSIZE)
        luaL_error(L, "integral size %d is larger than limit of %d",
                       sz, MAXINTSIZE);
      return sz;
    }
    default: return 0;  /* other cases do not need alignment */
  }
}


/*
** return number of bytes needed to align an element of size 'size'
** at current position 'len'
*/
static int gettoalign (size_t len, Header *h, int opt, size_t size) {
  if (size == 0 || opt == 'c') return 0;
  if (size > (size_t)h->align)
    size = h->align;  /* respect max. alignment */
  return (size - (len & (size - 1))) & (size - 1);
}


/*
** options to control endianess and alignment
*/
static void controloptions (lua_State *L, int opt, const char **fmt,
                            Header *h) {
  switch (opt) {
    case  ' ': return;  /* ignore white spaces */
    case '>': h->endian = BIG; return;
