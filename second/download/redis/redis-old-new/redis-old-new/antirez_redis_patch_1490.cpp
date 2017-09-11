@@ -187,6 +187,7 @@ int luaRedisGenericCommand(lua_State *lua, int raise_error) {
     }
 
     if (cmd->flags & REDIS_CMD_RANDOM) server.lua_random_dirty = 1;
+    if (cmd->flags & REDIS_CMD_WRITE) server.lua_write_dirty = 1;
 
     /* Run the command */
     cmd->proc(c);
@@ -277,11 +278,22 @@ void luaMaskCountHook(lua_State *lua, lua_Debug *ar) {
 
     elapsed = (ustime()/1000) - server.lua_time_start;
     if (elapsed >= server.lua_time_limit && server.lua_timedout == 0) {
-        redisLog(REDIS_WARNING,"Lua slow script detected: still in execution after %lld milliseconds. You can shut down the server using the SHUTDOWN command.",elapsed);
+        redisLog(REDIS_WARNING,"Lua slow script detected: still in execution after %lld milliseconds. You can try killing the script using the SCRIPT KILL command.",elapsed);
         server.lua_timedout = 1;
+        /* Once the script timeouts we reenter the event loop to permit others
+         * to call SCRIPT KILL or SHUTDOWN NOSAVE if needed. For this reason
+         * we need to mask the client executing the script from the event loop.
+         * If we don't do that the client may disconnect and could no longer be
+         * here when the EVAL command will return. */
+         aeDeleteFileEvent(server.el, server.lua_caller->fd, AE_READABLE);
     }
     if (server.lua_timedout)
         aeProcessEvents(server.el, AE_FILE_EVENTS|AE_DONT_WAIT);
+    if (server.lua_kill) {
+        redisLog(REDIS_WARNING,"Lua script killed by user with SCRIPT KILL.");
+        lua_pushstring(lua,"Script killed by user with SCRIPT KILL...");
+        lua_error(lua);
+    }
 }
 
 void luaLoadLib(lua_State *lua, const char *libname, lua_CFunction luafunc) {
@@ -553,6 +565,7 @@ void evalGenericCommand(redisClient *c, int evalsha) {
      * Thanks to this flag we'll raise an error every time a write command
      * is called after a random command was used. */
     server.lua_random_dirty = 0;
+    server.lua_write_dirty = 0;
 
     /* Get the number of arguments that are keys */
     if (getLongLongFromObjectOrReply(c,c->argv[2],&numkeys,NULL) != REDIS_OK)
@@ -610,16 +623,25 @@ void evalGenericCommand(redisClient *c, int evalsha) {
      * make the Lua script execution slower. */
     if (server.lua_time_limit > 0 && server.masterhost == NULL) {
         lua_sethook(lua,luaMaskCountHook,LUA_MASKCOUNT,100000);
-        server.lua_time_start = ustime()/1000;
     } else {
         lua_sethook(lua,luaMaskCountHook,0,0);
     }
 
     /* At this point whatever this script was never seen before or if it was
      * already defined, we can call it. We have zero arguments and expect
      * a single return value. */
+    server.lua_caller = c;
+    server.lua_time_start = ustime()/1000;
+    server.lua_kill = 0;
     if (lua_pcall(lua,0,1,0)) {
-        server.lua_timedout = 0;
+        if (server.lua_timedout) {
+            server.lua_timedout = 0;
+            /* Restore the readable handler that was unregistered when the
+             * script timeout was detected. */
+            aeCreateFileEvent(server.el,c->fd,AE_READABLE,
+                              readQueryFromClient,c);
+        }
+        server.lua_caller = NULL;
         selectDb(c,server.lua_client->db->id); /* set DB ID from Lua client */
         addReplyErrorFormat(c,"Error running script (call to %s): %s\n",
             funcname, lua_tostring(lua,-1));
@@ -628,6 +650,7 @@ void evalGenericCommand(redisClient *c, int evalsha) {
         return;
     }
     server.lua_timedout = 0;
+    server.lua_caller = NULL;
     selectDb(c,server.lua_client->db->id); /* set DB ID from Lua client */
     luaReplyToRedisReply(c,lua);
     lua_gc(lua,LUA_GCSTEP,1);
@@ -743,6 +766,15 @@ void scriptCommand(redisClient *c) {
         }
         addReplyBulkCBuffer(c,funcname+2,40);
         sdsfree(sha);
+    } else if (c->argc == 2 && !strcasecmp(c->argv[1]->ptr,"kill")) {
+        if (server.lua_caller == NULL) {
+            addReplyError(c,"No scripts in execution right now.");
+        } else if (server.lua_write_dirty) {
+            addReplyError(c, "Sorry the script already executed write commands against the dataset. You can either wait the script termination or kill the server in an hard way using the SHUTDOWN NOSAVE command.");
+        } else {
+            server.lua_kill = 1;
+            addReply(c,shared.ok);
+        }
     } else {
         addReplyError(c, "Unknown SCRIPT subcommand or wrong # of args.");
     }