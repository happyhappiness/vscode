        lua_pushlstring(L, data+pos, size - 1);
        break;
      }
      default: commoncases(L, opt, &fmt, &h);
    }
    pos += size;
  }
  lua_pushinteger(L, pos + 1);
  return lua_gettop(L) - 2;
}

/* }====================================================== */



static const struct luaL_reg thislib[] = {
  {"pack", b_pack},
  {"unpack", b_unpack},
  {NULL, NULL}
};


LUALIB_API int luaopen_struct (lua_State *L) {
  luaL_register(L, "struct", thislib);
  return 1;
}



/******************************************************************************
* Copyright (C) 2010 Lua.org, PUC-Rio.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining
* a copy of this software and associated documentation files (the
