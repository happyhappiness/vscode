@@ -416,10 +416,7 @@ void luaLoadLibraries(lua_State *lua) {
  * the creation of globals accidentally.
  *
  * It should be the last to be called in the scripting engine initialization
- * sequence, because it may interact with creation of globals.
- * Note that the function is designed to be called multiple times if needed
- * without issues, because it is possible to enabled/disable globals protection
- * at runtime with CONFIG SET. */
+ * sequence, because it may interact with creation of globals. */
 void scriptingEnableGlobalsProtection(lua_State *lua) {
     char *s[32];
     sds code = sdsempty();
@@ -434,25 +431,18 @@ void scriptingEnableGlobalsProtection(lua_State *lua) {
     s[j++]="  if not mt.declared[n] and debug.getinfo(2) then\n";
     s[j++]="    local w = debug.getinfo(2, \"S\").what\n";
     s[j++]="    if w ~= \"main\" and w ~= \"C\" then\n";
-    s[j++]="      error(\"assignment to undeclared global variable '\"..n..\"'\", 2)\n";
+    s[j++]="      error(\"Script attempted to create global variable '\"..tostring(n)..\"'\", 2)\n";
     s[j++]="    end\n";
     s[j++]="    mt.declared[n] = true\n";
     s[j++]="  end\n";
     s[j++]="  rawset(t, n, v)\n";
     s[j++]="end\n";
     s[j++]="mt.__index = function (t, n)\n";
     s[j++]="  if debug.getinfo(2) and not mt.declared[n] and debug.getinfo(2, \"S\").what ~= \"C\" then\n";
-    s[j++]="    error(\"global variable '\"..n..\"' is not declared\", 2)\n";
+    s[j++]="    error(\"Script attempted to access unexisting global variable '\"..n..\"'\", 2)\n";
     s[j++]="  end\n";
     s[j++]="  return rawget(t, n)\n";
     s[j++]="end\n";
-    s[j++]="function global(...)\n";
-    s[j++]="  local nargs = select(\"#\",...)\n";
-    s[j++]="  for i = 1, nargs do\n";
-    s[j++]="    local v = select(i,...)\n";
-    s[j++]="    mt.declared[v] = true\n";
-    s[j++]="  end\n";
-    s[j++]="end\n";
     s[j++]=NULL;
 
     for (j = 0; s[j] != NULL; j++) code = sdscatlen(code,s[j],strlen(s[j]));
@@ -461,12 +451,6 @@ void scriptingEnableGlobalsProtection(lua_State *lua) {
     sdsfree(code);
 }
 
-void scriptingDisableGlobalsProtection(lua_State *lua) {
-    char *s = "setmetatable(_G, nil)\n";
-    luaL_loadbuffer(lua,s,strlen(s),"disable_strict_lua");
-    lua_pcall(lua,0,0,0);
-}
-
 /* Initialize the scripting environment.
  * It is possible to call this function to reset the scripting environment
  * assuming that we call scriptingRelease() before.
@@ -559,8 +543,7 @@ void scriptingInit(void) {
     /* Lua beginners ofter don't use "local", this is likely to introduce
      * subtle bugs in their code. To prevent problems we protect accesses
      * to global variables. */
-    if (server.lua_protect_globals)
-        scriptingEnableGlobalsProtection(lua);
+    scriptingEnableGlobalsProtection(lua);
 
     server.lua = lua;
 }