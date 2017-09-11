         * return the plain error. */
        lua_pushstring(lua,"err");
        lua_gettable(lua,-2);
        inuse--;
        return lua_error(lua);
    }
    inuse--;
    return 1;
}

