    case 'f':  return sizeof(float);
    case 'd':  return sizeof(double);
    case 'x': return 1;
    case 'c': return getnum(L, fmt, 1);
    case 'i': case 'I': {
      int sz = getnum(L, fmt, sizeof(int));
      if (sz > MAXINTSIZE)
        luaL_error(L, "integral size %d is larger than limit of %d",
                       sz, MAXINTSIZE);
