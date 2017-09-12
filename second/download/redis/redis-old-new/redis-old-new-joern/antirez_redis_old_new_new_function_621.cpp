void luaLdbLineHook(lua_State *lua, lua_Debug *ar) {
    lua_getstack(lua,0,ar);
    lua_getinfo(lua,"Sl",ar);
    if(strstr(ar->short_src,"user_script") != NULL)
        printf("%s %d\n", ar->short_src, (int) ar->currentline);
}