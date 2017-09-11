@@ -412,6 +412,43 @@ void luaLoadLibraries(lua_State *lua) {
 #endif
 }
 
+/* This function installs metamethods in the global table _G that prevent
+ * the creation of globals accidentally.
+ *
+ * It should be the last to be called in the scripting engine initialization
+ * sequence, because it may interact with creation of globals. */
+void scriptingEnableGlobalsProtection(lua_State *lua) {
+    char *s[32];
+    sds code = sdsempty();
+    int j = 0;
+
+    /* strict.lua from: http://metalua.luaforge.net/src/lib/strict.lua.html.
+     * Modified to be adapted to Redis. */
+    s[j++]="local mt = {}\n";
+    s[j++]="setmetatable(_G, mt)\n";
+    s[j++]="mt.__newindex = function (t, n, v)\n";
+    s[j++]="  if debug.getinfo(2) then\n";
+    s[j++]="    local w = debug.getinfo(2, \"S\").what\n";
+    s[j++]="    if w ~= \"main\" and w ~= \"C\" then\n";
+    s[j++]="      error(\"Script attempted to create global variable '\"..tostring(n)..\"'\", 2)\n";
+    s[j++]="    end\n";
+    s[j++]="  end\n";
+    s[j++]="  rawset(t, n, v)\n";
+    s[j++]="end\n";
+    s[j++]="mt.__index = function (t, n)\n";
+    s[j++]="  if debug.getinfo(2) and debug.getinfo(2, \"S\").what ~= \"C\" then\n";
+    s[j++]="    error(\"Script attempted to access unexisting global variable '\"..tostring(n)..\"'\", 2)\n";
+    s[j++]="  end\n";
+    s[j++]="  return rawget(t, n)\n";
+    s[j++]="end\n";
+    s[j++]=NULL;
+
+    for (j = 0; s[j] != NULL; j++) code = sdscatlen(code,s[j],strlen(s[j]));
+    luaL_loadbuffer(lua,code,sdslen(code),"@enable_strict_lua");
+    lua_pcall(lua,0,0,0);
+    sdsfree(code);
+}
+
 /* Initialize the scripting environment.
  * It is possible to call this function to reset the scripting environment
  * assuming that we call scriptingRelease() before.
@@ -488,7 +525,7 @@ void scriptingInit(void) {
                                 "  if b == false then b = '' end\n"
                                 "  return a<b\n"
                                 "end\n";
-        luaL_loadbuffer(lua,compare_func,strlen(compare_func),"cmp_func_def");
+        luaL_loadbuffer(lua,compare_func,strlen(compare_func),"@cmp_func_def");
         lua_pcall(lua,0,0,0);
     }
 
@@ -501,6 +538,11 @@ void scriptingInit(void) {
         server.lua_client->flags |= REDIS_LUA_CLIENT;
     }
 
+    /* Lua beginners ofter don't use "local", this is likely to introduce
+     * subtle bugs in their code. To prevent problems we protect accesses
+     * to global variables. */
+    scriptingEnableGlobalsProtection(lua);
+
     server.lua = lua;
 }
 
@@ -634,7 +676,7 @@ int luaCreateFunction(redisClient *c, lua_State *lua, char *funcname, robj *body
     funcdef = sdscatlen(funcdef,body->ptr,sdslen(body->ptr));
     funcdef = sdscatlen(funcdef," end",4);
 
-    if (luaL_loadbuffer(lua,funcdef,sdslen(funcdef),"func definition")) {
+    if (luaL_loadbuffer(lua,funcdef,sdslen(funcdef),"@user_script")) {
         addReplyErrorFormat(c,"Error compiling script (new function): %s\n",
             lua_tostring(lua,-1));
         lua_pop(lua,1);