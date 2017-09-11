@@ -273,13 +273,15 @@ int luaLogCommand(lua_State *lua) {
 void luaMaskCountHook(lua_State *lua, lua_Debug *ar) {
     long long elapsed;
     REDIS_NOTUSED(ar);
+    REDIS_NOTUSED(lua);
 
     elapsed = (ustime()/1000) - server.lua_time_start;
-    if (elapsed >= server.lua_time_limit) {
-        redisLog(REDIS_NOTICE,"Lua script aborted for max execution time after %lld milliseconds of running time.",elapsed);
-        lua_pushstring(lua,"Script aborted for max execution time.");
-        lua_error(lua);
+    if (elapsed >= server.lua_time_limit && server.lua_timedout == 0) {
+        redisLog(REDIS_WARNING,"Lua slow script detected: still in execution after %lld milliseconds. You can shut down the server using the SHUTDOWN command.",elapsed);
+        server.lua_timedout = 1;
     }
+    if (server.lua_timedout)
+        aeProcessEvents(server.el, AE_FILE_EVENTS|AE_DONT_WAIT);
 }
 
 void luaLoadLib(lua_State *lua, const char *libname, lua_CFunction luafunc) {
@@ -606,7 +608,7 @@ void evalGenericCommand(redisClient *c, int evalsha) {
      * is running for too much time.
      * We set the hook only if the time limit is enabled as the hook will
      * make the Lua script execution slower. */
-    if (server.lua_time_limit > 0 && server.masterhost != NULL) {
+    if (server.lua_time_limit > 0 && server.masterhost == NULL) {
         lua_sethook(lua,luaMaskCountHook,LUA_MASKCOUNT,100000);
         server.lua_time_start = ustime()/1000;
     } else {
@@ -617,13 +619,15 @@ void evalGenericCommand(redisClient *c, int evalsha) {
      * already defined, we can call it. We have zero arguments and expect
      * a single return value. */
     if (lua_pcall(lua,0,1,0)) {
+        server.lua_timedout = 0;
         selectDb(c,server.lua_client->db->id); /* set DB ID from Lua client */
         addReplyErrorFormat(c,"Error running script (call to %s): %s\n",
             funcname, lua_tostring(lua,-1));
         lua_pop(lua,1);
         lua_gc(lua,LUA_GCCOLLECT,0);
         return;
     }
+    server.lua_timedout = 0;
     selectDb(c,server.lua_client->db->id); /* set DB ID from Lua client */
     luaReplyToRedisReply(c,lua);
     lua_gc(lua,LUA_GCSTEP,1);