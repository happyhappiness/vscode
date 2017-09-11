        lua_pushlstring(L, data+pos, size - 1);
        break;
      }
      default: controloptions(L, opt, &fmt, &h);
    }
    pos += size;
  }
  lua_pushinteger(L, pos + 1);
  return lua_gettop(L) - 2;
}


static int b_size (lua_State *L) {
  Header h;
  const char *fmt = luaL_checkstring(L, 1);
  size_t pos = 0;
  defaultoptions(&h);
  while (*fmt) {
    int opt = *fmt++;
    size_t size = optsize(L, opt, &fmt);
    pos += gettoalign(pos, &h, opt, size);
    if (opt == 's')
      luaL_argerror(L, 1, "option 's' has no fixed size");
    else if (opt == 'c' && size == 0)
      luaL_argerror(L, 1, "option 'c0' has no fixed size");
    if (!isalnum(opt))
      controloptions(L, opt, &fmt, &h);
    pos += size;
  }
  lua_pushinteger(L, pos);
  return 1;
}

/* }====================================================== */



static const struct luaL_Reg thislib[] = {
  {"pack", b_pack},
  {"unpack", b_unpack},
  {"size", b_size},
  {NULL, NULL}
};


LUALIB_API int luaopen_struct (lua_State *L);

LUALIB_API int luaopen_struct (lua_State *L) {
  luaL_register(L, "struct", thislib);
  return 1;
}


/******************************************************************************
* Copyright (C) 2010-2012 Lua.org, PUC-Rio.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining
* a copy of this software and associated documentation files (the
