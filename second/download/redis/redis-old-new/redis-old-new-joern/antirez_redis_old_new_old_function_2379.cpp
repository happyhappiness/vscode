void scriptingProtectGlobals(lua_State *lua) {
    char *s[26];
    sds code = sdsempty();
    int j;

    /* strict.lua from: http://metalua.luaforge.net/src/lib/strict.lua.html */
    s[0]="local mt = getmetatable(_G)\n";
    s[1]="if mt == nil then\n";
    s[2]="  mt = {}\n";
    s[3]="  setmetatable(_G, mt)\n";
    s[4]="end\n";
    s[5]="__STRICT = true\n";
    s[6]="mt.__declared = {}\n";
    s[7]="mt.__newindex = function (t, n, v)\n";
    s[8]="  if __STRICT and not mt.__declared[n] and debug.getinfo(2) then\n";
    s[9]="    local w = debug.getinfo(2, \"S\").what\n";
    s[10]="    if w ~= \"main\" and w ~= \"C\" then\n";
    s[11]="      error(\"assign to undeclared global var '\"..n..\"'\", 2)\n";
    s[12]="    end\n";
    s[13]="    mt.__declared[n] = true\n";
    s[14]="  end\n";
    s[15]="  rawset(t, n, v)\n";
    s[16]="end\n";
    s[17]="mt.__index = function (t, n)\n";
    s[18]="  if debug.getinfo(2) and not mt.__declared[n] and debug.getinfo(2, \"S\").what ~= \"C\" then\n";
    s[19]="    error(\"global var '\"..n..\"' is not declared\", 2)\n";
    s[20]="  end\n";
    s[21]="  return rawget(t, n)\n";
    s[22]="end\n";
    s[23]="function global(...)\n";
    s[24]="   for _, v in ipairs{...} do mt.__declared[v] = true end\n";
    s[25]="end\n";

    for (j = 0; j < 26; j++) code = sdscatlen(code,s[j],strlen(s[j]));
    luaL_loadbuffer(lua,code,sdslen(code),"strict_lua");
    lua_pcall(lua,0,0,0);
    sdsfree(code);
}