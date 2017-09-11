@@ -318,9 +318,9 @@ int luaRedisGenericCommand(lua_State *lua, int raise_error) {
      * command marked as non-deterministic was already called in the context
      * of this script. */
     if (cmd->flags & CMD_WRITE) {
-        if (server.lua_random_dirty) {
+        if (server.lua_random_dirty && !server.lua_replicate_commands) {
             luaPushError(lua,
-                "Write commands not allowed after non deterministic commands");
+                "Write commands not allowed after non deterministic commands. Call redis.replicate_commands() at the start of your script in order to switch to single commands replication mode.");
             goto cleanup;
         } else if (server.masterhost && server.repl_slave_ro &&
                    !server.loading &&
@@ -370,8 +370,21 @@ int luaRedisGenericCommand(lua_State *lua, int raise_error) {
         }
     }
 
+    /* If we are using single commands replication, we need to wrap what
+     * we propagate into a MULTI/EXEC block, so that it will be atomic like
+     * a Lua script in the context of AOF and slaves. */
+    if (server.lua_replicate_commands &&
+        !server.lua_multi_emitted &&
+        server.lua_write_dirty)
+    {
+        execCommandPropagateMulti(server.lua_caller);
+        server.lua_multi_emitted = 1;
+    }
+
     /* Run the command */
-    call(c,CMD_CALL_SLOWLOG | CMD_CALL_STATS);
+    int call_flags = CMD_CALL_SLOWLOG | CMD_CALL_STATS;
+    if (server.lua_replicate_commands) call_flags |= CMD_CALL_PROPAGATE;
+    call(c,call_flags);
 
     /* Convert the result of the Redis command into a suitable Lua type.
      * The first thing we need is to create a single string from the client
@@ -398,6 +411,7 @@ int luaRedisGenericCommand(lua_State *lua, int raise_error) {
     /* Sort the output array if needed, assuming it is a non-null multi bulk
      * reply as expected. */
     if ((cmd->flags & CMD_SORT_FOR_SCRIPT) &&
+        (server.lua_replicate_commands == 0) &&
         (reply[0] == '*' && reply[1] != '-')) {
             luaSortArray(lua);
     }
@@ -447,10 +461,12 @@ int luaRedisGenericCommand(lua_State *lua, int raise_error) {
     return 1;
 }
 
+/* redis.call() */
 int luaRedisCallCommand(lua_State *lua) {
     return luaRedisGenericCommand(lua,1);
 }
 
+/* redis.pcall() */
 int luaRedisPCallCommand(lua_State *lua) {
     return luaRedisGenericCommand(lua,0);
 }
@@ -494,14 +510,37 @@ int luaRedisReturnSingleFieldTable(lua_State *lua, char *field) {
     return 1;
 }
 
+/* redis.error_reply() */
 int luaRedisErrorReplyCommand(lua_State *lua) {
     return luaRedisReturnSingleFieldTable(lua,"err");
 }
 
+/* redis.status_reply() */
 int luaRedisStatusReplyCommand(lua_State *lua) {
     return luaRedisReturnSingleFieldTable(lua,"ok");
 }
 
+/* redis.replicate_commands()
+ *
+ * Turn on single commands replication if the script never called
+ * a write command so far, and returns true. Otherwise if the script
+ * already started to write, returns false and stick to whole scripts
+ * replication, which is our default. */
+int luaRedisReplicateCommandsCommand(lua_State *lua) {
+    if (server.lua_write_dirty) {
+        lua_pushboolean(lua,0);
+    } else {
+        server.lua_replicate_commands = 1;
+        /* When we switch to single commands replication, we can provide
+         * different math.random() sequences at every call, which is what
+         * the user normally expects. */
+        redisSrand48(rand());
+        lua_pushboolean(lua,1);
+    }
+    return 1;
+}
+
+/* redis.log() */
 int luaLogCommand(lua_State *lua) {
     int j, argc = lua_gettop(lua);
     int level;
@@ -697,6 +736,11 @@ void scriptingInit(void) {
     lua_pushcfunction(lua, luaRedisStatusReplyCommand);
     lua_settable(lua, -3);
 
+    /* redis.replicate_commands */
+    lua_pushstring(lua, "replicate_commands");
+    lua_pushcfunction(lua, luaRedisReplicateCommandsCommand);
+    lua_settable(lua, -3);
+
     /* Finally set the table as 'redis' global var. */
     lua_setglobal(lua,"redis");
 
@@ -814,7 +858,8 @@ void luaReplyToRedisReply(client *c, lua_State *lua) {
     case LUA_TTABLE:
         /* We need to check if it is an array, an error, or a status reply.
          * Error are returned as a single element table with 'err' field.
-         * Status replies are returned as single element table with 'ok' field */
+         * Status replies are returned as single element table with 'ok'
+         * field. */
         lua_pushstring(lua,"err");
         lua_gettable(lua,-2);
         t = lua_type(lua,-1);
@@ -926,8 +971,8 @@ void evalGenericCommand(client *c, int evalsha) {
     long long numkeys;
     int delhook = 0, err;
 
-    /* We want the same PRNG sequence at every call so that our PRNG is
-     * not affected by external state. */
+    /* When we replicate whole scripts, we want the same PRNG sequence at
+     * every call so that our PRNG is not affected by external state. */
     redisSrand48(0);
 
     /* We set this flag to zero to remember that so far no random command
@@ -940,6 +985,8 @@ void evalGenericCommand(client *c, int evalsha) {
      * is called after a random command was used. */
     server.lua_random_dirty = 0;
     server.lua_write_dirty = 0;
+    server.lua_replicate_commands = 0;
+    server.lua_multi_emitted = 0;
 
     /* Get the number of arguments that are keys */
     if (getLongLongFromObjectOrReply(c,c->argv[2],&numkeys,NULL) != C_OK)
@@ -1073,7 +1120,7 @@ void evalGenericCommand(client *c, int evalsha) {
      * For repliation, everytime a new slave attaches to the master, we need to
      * flush our cache of scripts that can be replicated as EVALSHA, while
      * for AOF we need to do so every time we rewrite the AOF file. */
-    if (evalsha) {
+    if (evalsha && !server.lua_replicate_commands) {
         if (!replicationScriptCacheExists(c->argv[1]->ptr)) {
             /* This script is not in our script cache, replicate it as
              * EVAL, then add it into the script cache, as from now on
@@ -1088,6 +1135,19 @@ void evalGenericCommand(client *c, int evalsha) {
             forceCommandPropagation(c,PROPAGATE_REPL|PROPAGATE_AOF);
         }
     }
+
+    /* If we are using single commands replication, emit EXEC if there
+     * was at least a write. */
+    if (server.lua_replicate_commands) {
+        preventCommandPropagation(c);
+        if (server.lua_multi_emitted) {
+            robj *propargv[1];
+            propargv[0] = createStringObject("EXEC",4);
+            alsoPropagate(server.execCommand,c->db->id,propargv,1,
+                PROPAGATE_AOF|PROPAGATE_REPL);
+            decrRefCount(propargv[0]);
+        }
+    }
 }
 
 void evalCommand(client *c) {