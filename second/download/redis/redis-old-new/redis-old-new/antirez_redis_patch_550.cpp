@@ -612,23 +612,25 @@ void scriptingEnableGlobalsProtection(lua_State *lua) {
 
     /* strict.lua from: http://metalua.luaforge.net/src/lib/strict.lua.html.
      * Modified to be adapted to Redis. */
+    s[j++]="local dbg=debug\n";
     s[j++]="local mt = {}\n";
     s[j++]="setmetatable(_G, mt)\n";
     s[j++]="mt.__newindex = function (t, n, v)\n";
-    s[j++]="  if debug.getinfo(2) then\n";
-    s[j++]="    local w = debug.getinfo(2, \"S\").what\n";
+    s[j++]="  if dbg.getinfo(2) then\n";
+    s[j++]="    local w = dbg.getinfo(2, \"S\").what\n";
     s[j++]="    if w ~= \"main\" and w ~= \"C\" then\n";
     s[j++]="      error(\"Script attempted to create global variable '\"..tostring(n)..\"'\", 2)\n";
     s[j++]="    end\n";
     s[j++]="  end\n";
     s[j++]="  rawset(t, n, v)\n";
     s[j++]="end\n";
     s[j++]="mt.__index = function (t, n)\n";
-    s[j++]="  if debug.getinfo(2) and debug.getinfo(2, \"S\").what ~= \"C\" then\n";
+    s[j++]="  if dbg.getinfo(2) and dbg.getinfo(2, \"S\").what ~= \"C\" then\n";
     s[j++]="    error(\"Script attempted to access unexisting global variable '\"..tostring(n)..\"'\", 2)\n";
     s[j++]="  end\n";
     s[j++]="  return rawget(t, n)\n";
     s[j++]="end\n";
+    s[j++]="debug = nil\n";
     s[j++]=NULL;
 
     for (j = 0; s[j] != NULL; j++) code = sdscatlen(code,s[j],strlen(s[j]));
@@ -732,10 +734,11 @@ void scriptingInit(void) {
      * information about the caller, that's what makes sense from the point
      * of view of the user debugging a script. */
     {
-        char *errh_func =       "function __redis__err__handler(err)\n"
-                                "  local i = debug.getinfo(2,'nSl')\n"
+        char *errh_func =       "local dbg = debug\n"
+                                "function __redis__err__handler(err)\n"
+                                "  local i = dbg.getinfo(2,'nSl')\n"
                                 "  if i and i.what == 'C' then\n"
-                                "    i = debug.getinfo(3,'nSl')\n"
+                                "    i = dbg.getinfo(3,'nSl')\n"
                                 "  end\n"
                                 "  if i then\n"
                                 "    return i.source .. ':' .. i.currentline .. ': ' .. err\n"