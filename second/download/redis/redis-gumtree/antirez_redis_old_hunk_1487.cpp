
    /* strict.lua from: http://metalua.luaforge.net/src/lib/strict.lua.html.
     * Modified to be adapted to Redis. */
    s[j++]="local mt = {}\n";
    s[j++]="setmetatable(_G, mt)\n";
    s[j++]="mt.__newindex = function (t, n, v)\n";
    s[j++]="  if debug.getinfo(2) then\n";
    s[j++]="    local w = debug.getinfo(2, \"S\").what\n";
    s[j++]="    if w ~= \"main\" and w ~= \"C\" then\n";
    s[j++]="      error(\"Script attempted to create global variable '\"..tostring(n)..\"'\", 2)\n";
    s[j++]="    end\n";
    s[j++]="  end\n";
    s[j++]="  rawset(t, n, v)\n";
    s[j++]="end\n";
    s[j++]="mt.__index = function (t, n)\n";
    s[j++]="  if debug.getinfo(2) and debug.getinfo(2, \"S\").what ~= \"C\" then\n";
    s[j++]="    error(\"Script attempted to access unexisting global variable '\"..tostring(n)..\"'\", 2)\n";
    s[j++]="  end\n";
    s[j++]="  return rawget(t, n)\n";
    s[j++]="end\n";
    s[j++]=NULL;

    for (j = 0; s[j] != NULL; j++) code = sdscatlen(code,s[j],strlen(s[j]));
