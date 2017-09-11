@@ -224,7 +224,7 @@ int luaRedisGenericCommand(lua_State *lua, int raise_error) {
         char *recursion_warning =
             "luaRedisGenericCommand() recursive call detected. "
             "Are you doing funny stuff with Lua debug hooks?";
-        serverLog(REDIS_WARNING,"%s",recursion_warning);
+        serverLog(LL_WARNING,"%s",recursion_warning);
         luaPushError(lua,recursion_warning);
         return 1;
     }
@@ -309,22 +309,22 @@ int luaRedisGenericCommand(lua_State *lua, int raise_error) {
     c->cmd = cmd;
 
     /* There are commands that are not allowed inside scripts. */
-    if (cmd->flags & REDIS_CMD_NOSCRIPT) {
+    if (cmd->flags & CMD_NOSCRIPT) {
         luaPushError(lua, "This Redis command is not allowed from scripts");
         goto cleanup;
     }
 
     /* Write commands are forbidden against read-only slaves, or if a
      * command marked as non-deterministic was already called in the context
      * of this script. */
-    if (cmd->flags & REDIS_CMD_WRITE) {
+    if (cmd->flags & CMD_WRITE) {
         if (server.lua_random_dirty) {
             luaPushError(lua,
                 "Write commands not allowed after non deterministic commands");
             goto cleanup;
         } else if (server.masterhost && server.repl_slave_ro &&
                    !server.loading &&
-                   !(server.lua_caller->flags & REDIS_MASTER))
+                   !(server.lua_caller->flags & CLIENT_MASTER))
         {
             luaPushError(lua, shared.roslaveerr->ptr);
             goto cleanup;
@@ -342,24 +342,24 @@ int luaRedisGenericCommand(lua_State *lua, int raise_error) {
      * first write in the context of this script, otherwise we can't stop
      * in the middle. */
     if (server.maxmemory && server.lua_write_dirty == 0 &&
-        (cmd->flags & REDIS_CMD_DENYOOM))
+        (cmd->flags & CMD_DENYOOM))
     {
         if (freeMemoryIfNeeded() == C_ERR) {
             luaPushError(lua, shared.oomerr->ptr);
             goto cleanup;
         }
     }
 
-    if (cmd->flags & REDIS_CMD_RANDOM) server.lua_random_dirty = 1;
-    if (cmd->flags & REDIS_CMD_WRITE) server.lua_write_dirty = 1;
+    if (cmd->flags & CMD_RANDOM) server.lua_random_dirty = 1;
+    if (cmd->flags & CMD_WRITE) server.lua_write_dirty = 1;
 
     /* If this is a Redis Cluster node, we need to make sure Lua is not
      * trying to access non-local keys, with the exception of commands
      * received from our master. */
-    if (server.cluster_enabled && !(server.lua_caller->flags & REDIS_MASTER)) {
+    if (server.cluster_enabled && !(server.lua_caller->flags & CLIENT_MASTER)) {
         /* Duplicate relevant flags in the lua client. */
-        c->flags &= ~(REDIS_READONLY|REDIS_ASKING);
-        c->flags |= server.lua_caller->flags & (REDIS_READONLY|REDIS_ASKING);
+        c->flags &= ~(CLIENT_READONLY|CLIENT_ASKING);
+        c->flags |= server.lua_caller->flags & (CLIENT_READONLY|CLIENT_ASKING);
         if (getNodeByQuery(c,c->cmd,c->argv,c->argc,NULL,NULL) !=
                            server.cluster->myself)
         {
@@ -371,12 +371,12 @@ int luaRedisGenericCommand(lua_State *lua, int raise_error) {
     }
 
     /* Run the command */
-    call(c,REDIS_CALL_SLOWLOG | REDIS_CALL_STATS);
+    call(c,CMD_CALL_SLOWLOG | CMD_CALL_STATS);
 
     /* Convert the result of the Redis command into a suitable Lua type.
      * The first thing we need is to create a single string from the client
      * output buffers. */
-    if (listLength(c->reply) == 0 && c->bufpos < REDIS_REPLY_CHUNK_BYTES) {
+    if (listLength(c->reply) == 0 && c->bufpos < PROTO_REPLY_CHUNK_BYTES) {
         /* This is a fast path for the common case of a reply inside the
          * client static buffer. Don't create an SDS string but just use
          * the client buffer directly. */
@@ -397,7 +397,7 @@ int luaRedisGenericCommand(lua_State *lua, int raise_error) {
     redisProtocolToLuaType(lua,reply);
     /* Sort the output array if needed, assuming it is a non-null multi bulk
      * reply as expected. */
-    if ((cmd->flags & REDIS_CMD_SORT_FOR_SCRIPT) &&
+    if ((cmd->flags & CMD_SORT_FOR_SCRIPT) &&
         (reply[0] == '*' && reply[1] != '-')) {
             luaSortArray(lua);
     }
@@ -515,7 +515,7 @@ int luaLogCommand(lua_State *lua) {
         return 1;
     }
     level = lua_tonumber(lua,-argc);
-    if (level < REDIS_DEBUG || level > REDIS_WARNING) {
+    if (level < LL_DEBUG || level > LL_WARNING) {
         luaPushError(lua, "Invalid debug level.");
         return 1;
     }
@@ -539,12 +539,12 @@ int luaLogCommand(lua_State *lua) {
 
 void luaMaskCountHook(lua_State *lua, lua_Debug *ar) {
     long long elapsed;
-    REDIS_NOTUSED(ar);
-    REDIS_NOTUSED(lua);
+    UNUSED(ar);
+    UNUSED(lua);
 
     elapsed = mstime() - server.lua_time_start;
     if (elapsed >= server.lua_time_limit && server.lua_timedout == 0) {
-        serverLog(REDIS_WARNING,"Lua slow script detected: still in execution after %lld milliseconds. You can try killing the script using the SCRIPT KILL command.",elapsed);
+        serverLog(LL_WARNING,"Lua slow script detected: still in execution after %lld milliseconds. You can try killing the script using the SCRIPT KILL command.",elapsed);
         server.lua_timedout = 1;
         /* Once the script timeouts we reenter the event loop to permit others
          * to call SCRIPT KILL or SHUTDOWN NOSAVE if needed. For this reason
@@ -555,7 +555,7 @@ void luaMaskCountHook(lua_State *lua, lua_Debug *ar) {
     }
     if (server.lua_timedout) processEventsWhileBlocked();
     if (server.lua_kill) {
-        serverLog(REDIS_WARNING,"Lua script killed by user with SCRIPT KILL.");
+        serverLog(LL_WARNING,"Lua script killed by user with SCRIPT KILL.");
         lua_pushstring(lua,"Script killed by user with SCRIPT KILL...");
         lua_error(lua);
     }
@@ -668,20 +668,20 @@ void scriptingInit(void) {
     lua_pushcfunction(lua,luaLogCommand);
     lua_settable(lua,-3);
 
-    lua_pushstring(lua,"LOG_DEBUG");
-    lua_pushnumber(lua,REDIS_DEBUG);
+    lua_pushstring(lua,"LL_DEBUG");
+    lua_pushnumber(lua,LL_DEBUG);
     lua_settable(lua,-3);
 
-    lua_pushstring(lua,"LOG_VERBOSE");
-    lua_pushnumber(lua,REDIS_VERBOSE);
+    lua_pushstring(lua,"LL_VERBOSE");
+    lua_pushnumber(lua,LL_VERBOSE);
     lua_settable(lua,-3);
 
-    lua_pushstring(lua,"LOG_NOTICE");
-    lua_pushnumber(lua,REDIS_NOTICE);
+    lua_pushstring(lua,"LL_NOTICE");
+    lua_pushnumber(lua,LL_NOTICE);
     lua_settable(lua,-3);
 
-    lua_pushstring(lua,"LOG_WARNING");
-    lua_pushnumber(lua,REDIS_WARNING);
+    lua_pushstring(lua,"LL_WARNING");
+    lua_pushnumber(lua,LL_WARNING);
     lua_settable(lua,-3);
 
     /* redis.sha1hex */
@@ -752,7 +752,7 @@ void scriptingInit(void) {
      * by scriptingReset(). */
     if (server.lua_client == NULL) {
         server.lua_client = createClient(-1);
-        server.lua_client->flags |= REDIS_LUA_CLIENT;
+        server.lua_client->flags |= CLIENT_LUA;
     }
 
     /* Lua beginners often don't use "local", this is likely to introduce
@@ -1085,7 +1085,7 @@ void evalGenericCommand(client *c, int evalsha) {
             rewriteClientCommandArgument(c,0,
                 resetRefCount(createStringObject("EVAL",4)));
             rewriteClientCommandArgument(c,1,script);
-            forceCommandPropagation(c,REDIS_PROPAGATE_REPL|REDIS_PROPAGATE_AOF);
+            forceCommandPropagation(c,PROPAGATE_REPL|PROPAGATE_AOF);
         }
     }
 }
@@ -1182,7 +1182,7 @@ void scriptCommand(client *c) {
         }
         addReplyBulkCBuffer(c,funcname+2,40);
         sdsfree(sha);
-        forceCommandPropagation(c,REDIS_PROPAGATE_REPL|REDIS_PROPAGATE_AOF);
+        forceCommandPropagation(c,PROPAGATE_REPL|PROPAGATE_AOF);
     } else if (c->argc == 2 && !strcasecmp(c->argv[1]->ptr,"kill")) {
         if (server.lua_caller == NULL) {
             addReplySds(c,sdsnew("-NOTBUSY No scripts in execution right now.\r\n"));