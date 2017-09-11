    lua_setglobal(lua,var);
}

/* Define a lua function with the specified function name and body.
 * The function name musts be a 42 characters long string, since all the
 * functions we defined in the Lua context are in the form:
