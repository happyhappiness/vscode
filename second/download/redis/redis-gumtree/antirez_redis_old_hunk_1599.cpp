         * return the plain error. */
        lua_pushstring(lua,"err");
        lua_gettable(lua,-2);
        return lua_error(lua);
    }
    return 1;
}

