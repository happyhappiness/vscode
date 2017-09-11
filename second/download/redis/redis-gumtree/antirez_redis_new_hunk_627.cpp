        /* If we are here we should have an error in the stack, in the
         * form of a table with an "err" field. Extract the string to
         * return the plain error. */
        inuse--;
        return luaRaiseError(lua);
    }
    inuse--;
    return 1;
