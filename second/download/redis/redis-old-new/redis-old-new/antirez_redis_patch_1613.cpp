@@ -199,6 +199,19 @@ int luaRedisCommand(lua_State *lua) {
     return 1;
 }
 
+void luaMaskCountHook(lua_State *lua, lua_Debug *ar) {
+    long long elapsed;
+    REDIS_NOTUSED(ar);
+
+    if (server.lua_time_limit <= 0) return;
+    elapsed = (ustime()/1000) - server.lua_time_start;
+    if (elapsed >= server.lua_time_limit) {
+        lua_pushstring(lua,"Script aborted for max execution time...");
+        lua_error(lua);
+        redisLog(REDIS_NOTICE,"Lua script aborted for max execution time after %lld milliseconds of running time",elapsed);
+    }
+}
+
 void scriptingInit(void) {
     lua_State *lua = lua_open();
     luaL_openlibs(lua);
@@ -212,6 +225,10 @@ void scriptingInit(void) {
     server.lua_client = createClient(-1);
     server.lua_client->flags |= REDIS_LUA_CLIENT;
 
+    /* Set an hook in order to be able to stop the script execution if it
+     * is running for too much time. */
+    lua_sethook(lua,luaMaskCountHook,LUA_MASKCOUNT,10000);
+
     server.lua = lua;
 }
 
@@ -375,6 +392,7 @@ void evalCommand(redisClient *c) {
     /* At this point whatever this script was never seen before or if it was
      * already defined, we can call it. We have zero arguments and expect
      * a single return value. */
+    server.lua_time_start = ustime()/1000;
     if (lua_pcall(lua,0,1,0)) {
         selectDb(c,server.lua_client->db->id); /* set DB ID from Lua client */
         addReplyErrorFormat(c,"Error running script (call to %s): %s\n",