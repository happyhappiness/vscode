        lua_settable(lua,-3);
    }
    return p;
}

void luaPushError(lua_State *lua, char *error) {
    lua_newtable(lua);
    lua_pushstring(lua,"err");
    lua_pushstring(lua, error);
    lua_settable(lua,-3);
}

/* Sort the array currently in the stack. We do this to make the output
 * of commands like KEYS or SMEMBERS something deterministic when called
 * from Lua (to play well with AOf/replication).
