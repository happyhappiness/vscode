    }
}

/* Produce a debugger log entry representing the value of the Lua object
 * currently on the top of the stack. */
void ldbLogStackValue(lua_State *lua) {
    int t = lua_type(lua,-1);
    sds s = sdsnew("<value> ");

    switch(t) {
    case LUA_TSTRING:
        s = sdscat(s,lua_tostring(lua,-1));
        break;
    case LUA_TBOOLEAN:
        s = sdscat(s,lua_toboolean(lua,-1) ? "true" : "false");
        break;
    case LUA_TNUMBER:
        s = sdscatprintf(s,"%g",(double)lua_tonumber(lua,-1));
        break;
    case LUA_TNIL:
        s = sdscat(s,"nil");
        break;
    case LUA_TTABLE:
    case LUA_TFUNCTION:
    case LUA_TUSERDATA:
    case LUA_TTHREAD:
    case LUA_TLIGHTUSERDATA:
        {
        const void *p = lua_topointer(lua,-1);
        char *typename = "unknown";
        if (t == LUA_TTABLE) typename = "table";
        else if (t == LUA_TFUNCTION) typename = "function";
        else if (t == LUA_TUSERDATA) typename = "userdata";
        else if (t == LUA_TTHREAD) typename = "thread";
        else if (t == LUA_TLIGHTUSERDATA) typename = "light-userdata";
        s = sdscatprintf(s,"%s at %p",typename,p);
        }
        break;
    default:
        s = sdscat(s,"?");
        break;
    }
    ldbLog(s);
    lua_pop(lua,1);
}

/* Implements the "print" command of the Lua debugger. It scans for Lua
 * var "varname" starting from the current stack frame up to the top stack
 * frame. The first matching variable is printed. */
void ldbPrint(lua_State *lua, lua_Debug *orig_ar, char *varname) {
    lua_Debug ar;
    int l = 0; /* Stack level. */
    while (lua_getstack(lua,l,&ar) != 0) {
        l++;
        const char *name;
        int i = 1; /* Variable index. */
        while((name = lua_getlocal(lua,&ar,i)) != NULL) {
            i++;
            if (strcmp(varname,name) == 0) {
                ldbLogStackValue(lua);
                return;
            } else {
                lua_pop(lua,1); /* Discard the var name on the stack. */
            }
        }
    }
    ldbLog(sdsnew("No such variable."));
}

/* Read debugging commands from client. */
void ldbRepl(lua_State *lua, lua_Debug *ar) {
    sds *argv;
    int argc;

