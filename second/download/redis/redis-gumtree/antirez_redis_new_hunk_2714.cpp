#endif
}

/* This function installs metamethods in the global table _G that prevent
 * the creation of globals accidentally.
 *
 * It should be the last to be called in the scripting engine initialization
 * sequence, because it may interact with creation of globals.
 * Note that the function is designed to be called multiple times if needed
 * without issues, because it is possible to enabled/disable globals protection
 * at runtime with CONFIG SET. */
void scriptingEnableGlobalsProtection(lua_State *lua) {
    char *s[32];
    sds code = sdsempty();
    int j = 0;

    /* strict.lua from: http://metalua.luaforge.net/src/lib/strict.lua.html.
     * Modified to be adapted to Redis. */
    s[j++]="mt = {}\n";
    s[j++]="setmetatable(_G, mt)\n";
    s[j++]="mt.declared = {}\n";
    s[j++]="mt.__newindex = function (t, n, v)\n";
    s[j++]="  if not mt.declared[n] and debug.getinfo(2) then\n";
    s[j++]="    local w = debug.getinfo(2, \"S\").what\n";
    s[j++]="    if w ~= \"main\" and w ~= \"C\" then\n";
    s[j++]="      error(\"assignment to undeclared global variable '\"..n..\"'\", 2)\n";
    s[j++]="    end\n";
    s[j++]="    mt.declared[n] = true\n";
    s[j++]="  end\n";
    s[j++]="  rawset(t, n, v)\n";
    s[j++]="end\n";
    s[j++]="mt.__index = function (t, n)\n";
    s[j++]="  if debug.getinfo(2) and not mt.declared[n] and debug.getinfo(2, \"S\").what ~= \"C\" then\n";
    s[j++]="    error(\"global variable '\"..n..\"' is not declared\", 2)\n";
    s[j++]="  end\n";
    s[j++]="  return rawget(t, n)\n";
    s[j++]="end\n";
    s[j++]="function global(...)\n";
    s[j++]="   for _, v in ipairs{...} do mt.declared[v] = true end\n";
    s[j++]="end\n";
    s[j++]=NULL;

    for (j = 0; s[j] != NULL; j++) code = sdscatlen(code,s[j],strlen(s[j]));
    luaL_loadbuffer(lua,code,sdslen(code),"enable_strict_lua");
    lua_pcall(lua,0,0,0);
    sdsfree(code);
}

void scriptingDisableGlobalsProtection(lua_State *lua) {
    char *s = "setmetatable(_G, nil)\n";
    luaL_loadbuffer(lua,s,strlen(s),"disable_strict_lua");
    lua_pcall(lua,0,0,0);
}

/* Initialize the scripting environment.
 * It is possible to call this function to reset the scripting environment
 * assuming that we call scriptingRelease() before.
