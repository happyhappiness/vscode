    case '>': h->endian = BIG; return;
    case '<': h->endian = LITTLE; return;
    case '!': {
      int a = getnum(fmt, MAXALIGN);
      if (!isp2(a))
        luaL_error(L, "alignment %d is not a power of 2", a);
      h->align = a;
