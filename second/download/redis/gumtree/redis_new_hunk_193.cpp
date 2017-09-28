        } else {
            c->err = MP_CUR_ERROR_BADFMT;
        }
    }
}

static int mp_unpack_full(lua_State *L, int limit, int offset) {
    size_t len;
    const char *s;
    mp_cur c;
    int cnt; /* Number of objects unpacked */
    int decode_all = (!limit && !offset);

    s = luaL_checklstring(L,1,&len); /* if no match, exits */

    if (offset < 0 || limit < 0) /* requesting negative off or lim is invalid */
        return luaL_error(L,
            "Invalid request to unpack with offset of %d and limit of %d.",
            offset, len);
    else if (offset > len)
        return luaL_error(L,
            "Start offset %d greater than input length %d.", offset, len);

    if (decode_all) limit = INT_MAX;

    mp_cur_init(&c,(const unsigned char *)s+offset,len-offset);

    /* We loop over the decode because this could be a stream
     * of multiple top-level values serialized together */
    for(cnt = 0; c.left > 0 && cnt < limit; cnt++) {
        mp_decode_to_lua_type(L,&c);

        if (c.err == MP_CUR_ERROR_EOF) {
            return luaL_error(L,"Missing bytes in input.");
        } else if (c.err == MP_CUR_ERROR_BADFMT) {
            return luaL_error(L,"Bad data format in input.");
        }
    }

    if (!decode_all) {
        /* c->left is the remaining size of the input buffer.
         * subtract the entire buffer size from the unprocessed size
         * to get our next start offset */
        int offset = len - c.left;
        /* Return offset -1 when we have have processed the entire buffer. */
        lua_pushinteger(L, c.left == 0 ? -1 : offset);
        /* Results are returned with the arg elements still
         * in place. Lua takes care of only returning
         * elements above the args for us.
         * In this case, we have one arg on the stack
         * for this function, so we insert our first return
         * value at position 2. */
        lua_insert(L, 2);
        cnt += 1; /* increase return count by one to make room for offset */
    }

    return cnt;
}

static int mp_unpack(lua_State *L) {
    return mp_unpack_full(L, 0, 0);
}

static int mp_unpack_one(lua_State *L) {
    int offset = luaL_optint(L, 2, 0);
    /* Variable pop because offset may not exist */
    lua_pop(L, lua_gettop(L)-1);
    return mp_unpack_full(L, 1, offset);
}

static int mp_unpack_limit(lua_State *L) {
    int limit = luaL_checkint(L, 2);
    int offset = luaL_optint(L, 3, 0);
    /* Variable pop because offset may not exist */
    lua_pop(L, lua_gettop(L)-1);

    return mp_unpack_full(L, limit, offset);
}

static int mp_safe(lua_State *L) {
    int argc, err, total_results;

    argc = lua_gettop(L);

    /* This adds our function to the bottom of the stack
     * (the "call this function" position) */
    lua_pushvalue(L, lua_upvalueindex(1));
    lua_insert(L, 1);

    err = lua_pcall(L, argc, LUA_MULTRET, 0);
    total_results = lua_gettop(L);

    if (!err) {
        return total_results;
    } else {
        lua_pushnil(L);
        lua_insert(L,-2);
        return 2;
    }
}

/* -------------------------------------------------------------------------- */
static const struct luaL_Reg cmds[] = {
    {"pack", mp_pack},
    {"unpack", mp_unpack},
    {"unpack_one", mp_unpack_one},
    {"unpack_limit", mp_unpack_limit},
    {0}
};

static int luaopen_create(lua_State *L) {
    int i;
    /* Manually construct our module table instead of
     * relying on _register or _newlib */
    lua_newtable(L);

    for (i = 0; i < (sizeof(cmds)/sizeof(*cmds) - 1); i++) {
        lua_pushcfunction(L, cmds[i].func);
        lua_setfield(L, -2, cmds[i].name);
    }

    /* Add metadata */
    lua_pushliteral(L, LUACMSGPACK_NAME);
    lua_setfield(L, -2, "_NAME");
    lua_pushliteral(L, LUACMSGPACK_VERSION);
    lua_setfield(L, -2, "_VERSION");
    lua_pushliteral(L, LUACMSGPACK_COPYRIGHT);
    lua_setfield(L, -2, "_COPYRIGHT");
    lua_pushliteral(L, LUACMSGPACK_DESCRIPTION);
    lua_setfield(L, -2, "_DESCRIPTION");
    return 1;
}

LUALIB_API int luaopen_cmsgpack(lua_State *L) {
    luaopen_create(L);

#if LUA_VERSION_NUM < 502
    /* Register name globally for 5.1 */
    lua_pushvalue(L, -1);
    lua_setglobal(L, LUACMSGPACK_NAME);
#endif

    return 1;
}

LUALIB_API int luaopen_cmsgpack_safe(lua_State *L) {
    int i;

    luaopen_cmsgpack(L);

    /* Wrap all functions in the safe handler */
    for (i = 0; i < (sizeof(cmds)/sizeof(*cmds) - 1); i++) {
        lua_getfield(L, -1, cmds[i].name);
        lua_pushcclosure(L, mp_safe, 1);
        lua_setfield(L, -2, cmds[i].name);
    }

#if LUA_VERSION_NUM < 502
    /* Register name globally for 5.1 */
    lua_pushvalue(L, -1);
    lua_setglobal(L, LUACMSGPACK_SAFE_NAME);
#endif

    return 1;
}

/******************************************************************************
* Copyright (C) 2012 Salvatore Sanfilippo.  All rights reserved.
*
