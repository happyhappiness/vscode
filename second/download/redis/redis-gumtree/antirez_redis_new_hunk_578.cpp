    }
}

/* Implements the "print" command (without arguments) of the Lua debugger.
 * Prints all the variables in the current stack frame. */
void ldbPrintAll(lua_State *lua) {
    lua_Debug ar;
    int vars = 0;

    if (lua_getstack(lua,0,&ar) != 0) {
        const char *name;
        int i = 1; /* Variable index. */
        while((name = lua_getlocal(lua,&ar,i)) != NULL) {
            i++;
            if (!strstr(name,"(*temporary)")) {
                sds prefix = sdscatprintf(sdsempty(),"<value> %s = ",name);
                ldbLogStackValue(lua,prefix);
                sdsfree(prefix);
                vars++;
            }
            lua_pop(lua,1);
        }
    }

    if (vars == 0) {
        ldbLog(sdsnew("No local variables in the current context."));
    }
}

/* Implements the break command to list, add and remove breakpoints. */
void ldbBreak(sds *argv, int argc) {
    if (argc == 1) {
