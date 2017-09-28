        } else {
            c->err = MP_CUR_ERROR_BADFMT;
        }
    }
}

static int mp_unpack(lua_State *L) {
    size_t len;
    const unsigned char *s;
    mp_cur *c;

    if (!lua_isstring(L,-1)) {
        lua_pushstring(L,"MessagePack decoding needs a string as input.");
        lua_error(L);
    }

    s = (const unsigned char*) lua_tolstring(L,-1,&len);
    c = mp_cur_new(s,len);
    mp_decode_to_lua_type(L,c);
    
    if (c->err == MP_CUR_ERROR_EOF) {
        mp_cur_free(c);
        lua_pushstring(L,"Missing bytes in input.");
        lua_error(L);
    } else if (c->err == MP_CUR_ERROR_BADFMT) {
        mp_cur_free(c);
        lua_pushstring(L,"Bad data format in input.");
        lua_error(L);
    } else if (c->left != 0) {
        mp_cur_free(c);
        lua_pushstring(L,"Extra bytes in input.");
        lua_error(L);
    }
    mp_cur_free(c);
    return 1;
}

/* ---------------------------------------------------------------------------- */

static const struct luaL_reg thislib[] = {
    {"pack", mp_pack},
    {"unpack", mp_unpack},
    {NULL, NULL}
};

LUALIB_API int luaopen_cmsgpack (lua_State *L) {
    luaL_register(L, "cmsgpack", thislib);

    lua_pushliteral(L, LUACMSGPACK_VERSION);
    lua_setfield(L, -2, "_VERSION");
    lua_pushliteral(L, LUACMSGPACK_COPYRIGHT);
    lua_setfield(L, -2, "_COPYRIGHT");
    lua_pushliteral(L, LUACMSGPACK_DESCRIPTION);
    lua_setfield(L, -2, "_DESCRIPTION"); 
    return 1;
}

/******************************************************************************
* Copyright (C) 2012 Salvatore Sanfilippo.  All rights reserved.
*
