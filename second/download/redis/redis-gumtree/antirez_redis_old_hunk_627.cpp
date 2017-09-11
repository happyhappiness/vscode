        /* If we are here we should have an error in the stack, in the
         * form of a table with an "err" field. Extract the string to
         * return the plain error. */
        lua_pushstring(lua,"err");
        lua_gettable(lua,-2);
        inuse--;
        return lua_error(lua);
    }
    inuse--;
    return 1;
