    lua_pop(lua,2);             /* Discard the result and clean the stack. */
}

/* Read debugging commands from client. */
void ldbRepl(lua_State *lua) {
    sds *argv;
