@@ -412,45 +412,57 @@ void luaLoadLibraries(lua_State *lua) {
 #endif
 }
 
-void scriptingProtectGlobals(lua_State *lua) {
-    char *s[26];
+/* This function installs metamethods in the global table _G that prevent
+ * the creation of globals accidentally.
+ *
+ * It should be the last to be called in the scripting engine initialization
+ * sequence, because it may interact with creation of globals.
+ * Note that the function is designed to be called multiple times if needed
+ * without issues, because it is possible to enabled/disable globals protection
+ * at runtime with CONFIG SET. */
+void scriptingEnableGlobalsProtection(lua_State *lua) {
+    char *s[32];
     sds code = sdsempty();
-    int j;
+    int j = 0;
 
-    /* strict.lua from: http://metalua.luaforge.net/src/lib/strict.lua.html */
-    s[0]="local mt = getmetatable(_G)\n";
-    s[1]="if mt == nil then\n";
-    s[2]="  mt = {}\n";
-    s[3]="  setmetatable(_G, mt)\n";
-    s[4]="end\n";
-    s[5]="__STRICT = true\n";
-    s[6]="mt.__declared = {}\n";
-    s[7]="mt.__newindex = function (t, n, v)\n";
-    s[8]="  if __STRICT and not mt.__declared[n] and debug.getinfo(2) then\n";
-    s[9]="    local w = debug.getinfo(2, \"S\").what\n";
-    s[10]="    if w ~= \"main\" and w ~= \"C\" then\n";
-    s[11]="      error(\"assign to undeclared global var '\"..n..\"'\", 2)\n";
-    s[12]="    end\n";
-    s[13]="    mt.__declared[n] = true\n";
-    s[14]="  end\n";
-    s[15]="  rawset(t, n, v)\n";
-    s[16]="end\n";
-    s[17]="mt.__index = function (t, n)\n";
-    s[18]="  if debug.getinfo(2) and not mt.__declared[n] and debug.getinfo(2, \"S\").what ~= \"C\" then\n";
-    s[19]="    error(\"global var '\"..n..\"' is not declared\", 2)\n";
-    s[20]="  end\n";
-    s[21]="  return rawget(t, n)\n";
-    s[22]="end\n";
-    s[23]="function global(...)\n";
-    s[24]="   for _, v in ipairs{...} do mt.__declared[v] = true end\n";
-    s[25]="end\n";
-
-    for (j = 0; j < 26; j++) code = sdscatlen(code,s[j],strlen(s[j]));
-    luaL_loadbuffer(lua,code,sdslen(code),"strict_lua");
+    /* strict.lua from: http://metalua.luaforge.net/src/lib/strict.lua.html.
+     * Modified to be adapted to Redis. */
+    s[j++]="mt = {}\n";
+    s[j++]="setmetatable(_G, mt)\n";
+    s[j++]="mt.declared = {}\n";
+    s[j++]="mt.__newindex = function (t, n, v)\n";
+    s[j++]="  if not mt.declared[n] and debug.getinfo(2) then\n";
+    s[j++]="    local w = debug.getinfo(2, \"S\").what\n";
+    s[j++]="    if w ~= \"main\" and w ~= \"C\" then\n";
+    s[j++]="      error(\"assignment to undeclared global variable '\"..n..\"'\", 2)\n";
+    s[j++]="    end\n";
+    s[j++]="    mt.declared[n] = true\n";
+    s[j++]="  end\n";
+    s[j++]="  rawset(t, n, v)\n";
+    s[j++]="end\n";
+    s[j++]="mt.__index = function (t, n)\n";
+    s[j++]="  if debug.getinfo(2) and not mt.declared[n] and debug.getinfo(2, \"S\").what ~= \"C\" then\n";
+    s[j++]="    error(\"global variable '\"..n..\"' is not declared\", 2)\n";
+    s[j++]="  end\n";
+    s[j++]="  return rawget(t, n)\n";
+    s[j++]="end\n";
+    s[j++]="function global(...)\n";
+    s[j++]="   for _, v in ipairs{...} do mt.declared[v] = true end\n";
+    s[j++]="end\n";
+    s[j++]=NULL;
+
+    for (j = 0; s[j] != NULL; j++) code = sdscatlen(code,s[j],strlen(s[j]));
+    luaL_loadbuffer(lua,code,sdslen(code),"enable_strict_lua");
     lua_pcall(lua,0,0,0);
     sdsfree(code);
 }
 
+void scriptingDisableGlobalsProtection(lua_State *lua) {
+    char *s = "setmetatable(_G, nil)\n";
+    luaL_loadbuffer(lua,s,strlen(s),"disable_strict_lua");
+    lua_pcall(lua,0,0,0);
+}
+
 /* Initialize the scripting environment.
  * It is possible to call this function to reset the scripting environment
  * assuming that we call scriptingRelease() before.
@@ -543,7 +555,8 @@ void scriptingInit(void) {
     /* Lua beginners ofter don't use "local", this is likely to introduce
      * subtle bugs in their code. To prevent problems we protect accesses
      * to global variables. */
-    scriptingProtectGlobals(lua);
+    if (server.lua_protect_globals)
+        scriptingEnableGlobalsProtection(lua);
 
     server.lua = lua;
 }