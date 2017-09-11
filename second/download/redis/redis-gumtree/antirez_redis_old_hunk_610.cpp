    }
}

/* This is the core of our Lua debugger, called each time Lua is about
 * to start executing a new line. */
void luaLdbLineHook(lua_State *lua, lua_Debug *ar) {
    lua_getstack(lua,0,ar);
    lua_getinfo(lua,"Sl",ar);
    if(strstr(ar->short_src,"user_script") != NULL)
        printf("%s %d\n", ar->short_src, (int) ar->currentline);
}



