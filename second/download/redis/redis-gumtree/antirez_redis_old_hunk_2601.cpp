      h->align = a;
      return;
    }
    default: assert(0);
  }
}


static void putinteger (lua_State *L, luaL_Buffer *b, int arg, int endian,
                        int size) {
  lua_Number n = luaL_checknumber(L, arg);
  unsigned long value;
  if (n < (lua_Number)LONG_MAX)
    value = (long)n;
  else
    value = (unsigned long)n;
  if (endian == LITTLE) {
    int i;
    for (i = 0; i < size; i++)
      luaL_addchar(b, (value >> 8*i) & 0xff);
  }
  else {
    int i;
    for (i = size - 1; i >= 0; i--)
      luaL_addchar(b, (value >> 8*i) & 0xff);
  }
}


