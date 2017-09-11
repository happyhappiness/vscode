@@ -203,7 +203,6 @@ void luaMaskCountHook(lua_State *lua, lua_Debug *ar) {
     long long elapsed;
     REDIS_NOTUSED(ar);
 
-    if (server.lua_time_limit <= 0) return;
     elapsed = (ustime()/1000) - server.lua_time_start;
     if (elapsed >= server.lua_time_limit) {
         redisLog(REDIS_NOTICE,"Lua script aborted for max execution time after %lld milliseconds of running time.",elapsed);
@@ -225,10 +224,6 @@ void scriptingInit(void) {
     server.lua_client = createClient(-1);
     server.lua_client->flags |= REDIS_LUA_CLIENT;
 
-    /* Set an hook in order to be able to stop the script execution if it
-     * is running for too much time. */
-    lua_sethook(lua,luaMaskCountHook,LUA_MASKCOUNT,100000);
-
     server.lua = lua;
 }
 
@@ -389,10 +384,20 @@ void evalCommand(redisClient *c) {
     /* Select the right DB in the context of the Lua client */
     selectDb(server.lua_client,c->db->id);
     
+    /* Set an hook in order to be able to stop the script execution if it
+     * is running for too much time.
+     * We set the hook only if the time limit is enabled as the hook will
+     * make the Lua script execution slower. */
+    if (server.lua_time_limit > 0) {
+        lua_sethook(lua,luaMaskCountHook,LUA_MASKCOUNT,100000);
+        server.lua_time_start = ustime()/1000;
+    } else {
+        lua_sethook(lua,luaMaskCountHook,0,0);
+    }
+
     /* At this point whatever this script was never seen before or if it was
      * already defined, we can call it. We have zero arguments and expect
      * a single return value. */
-    server.lua_time_start = ustime()/1000;
     if (lua_pcall(lua,0,1,0)) {
         selectDb(c,server.lua_client->db->id); /* set DB ID from Lua client */
         addReplyErrorFormat(c,"Error running script (call to %s): %s\n",