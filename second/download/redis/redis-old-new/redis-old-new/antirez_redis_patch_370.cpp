@@ -375,15 +375,22 @@ int luaRedisGenericCommand(lua_State *lua, int raise_error) {
      * a Lua script in the context of AOF and slaves. */
     if (server.lua_replicate_commands &&
         !server.lua_multi_emitted &&
-        server.lua_write_dirty)
+        server.lua_write_dirty &&
+        server.lua_repl != PROPAGATE_NONE)
     {
         execCommandPropagateMulti(server.lua_caller);
         server.lua_multi_emitted = 1;
     }
 
     /* Run the command */
     int call_flags = CMD_CALL_SLOWLOG | CMD_CALL_STATS;
-    if (server.lua_replicate_commands) call_flags |= CMD_CALL_PROPAGATE;
+    if (server.lua_replicate_commands) {
+        call_flags |= CMD_CALL_PROPAGATE;
+        /* Don't propagate AOf / replication stream if a redis.set_repl()
+         * call changed the default replication policy. */
+        if (!(server.lua_repl & PROPAGATE_AOF)) preventCommandAOF(c);
+        if (!(server.lua_repl & PROPAGATE_REPL)) preventCommandReplication(c);
+    }
     call(c,call_flags);
 
     /* Convert the result of the Redis command into a suitable Lua type.
@@ -540,6 +547,31 @@ int luaRedisReplicateCommandsCommand(lua_State *lua) {
     return 1;
 }
 
+/* redis.set_repl()
+ *
+ * Set the propagation of write commands executed in the context of the
+ * script to on/off for AOF and slaves. */
+int luaRedisSetReplCommand(lua_State *lua) {
+    int argc = lua_gettop(lua);
+    int flags;
+
+    if (server.lua_replicate_commands == 0) {
+        luaPushError(lua, "You can set the replication behavior only after turning on single commands replication with redis.replicate_commands().");
+        return 1;
+    } else if (argc != 1) {
+        luaPushError(lua, "redis.set_repl() requires two arguments.");
+        return 1;
+    }
+
+    flags = lua_tonumber(lua,-1);
+    if ((flags & ~(PROPAGATE_AOF|PROPAGATE_REPL)) != 0) {
+        luaPushError(lua, "Invalid replication flags. Use REPL_AOF, REPL_SLAVE, REPL_ALL or REPL_NONE.");
+        return 1;
+    }
+    server.lua_repl = flags;
+    return 0;
+}
+
 /* redis.log() */
 int luaLogCommand(lua_State *lua) {
     int j, argc = lua_gettop(lua);
@@ -741,6 +773,27 @@ void scriptingInit(void) {
     lua_pushcfunction(lua, luaRedisReplicateCommandsCommand);
     lua_settable(lua, -3);
 
+    /* redis.set_repl and associated flags. */
+    lua_pushstring(lua,"set_repl");
+    lua_pushcfunction(lua,luaRedisSetReplCommand);
+    lua_settable(lua,-3);
+
+    lua_pushstring(lua,"REPL_NONE");
+    lua_pushnumber(lua,PROPAGATE_NONE);
+    lua_settable(lua,-3);
+
+    lua_pushstring(lua,"REPL_AOF");
+    lua_pushnumber(lua,PROPAGATE_AOF);
+    lua_settable(lua,-3);
+
+    lua_pushstring(lua,"REPL_SLAVE");
+    lua_pushnumber(lua,PROPAGATE_REPL);
+    lua_settable(lua,-3);
+
+    lua_pushstring(lua,"REPL_ALL");
+    lua_pushnumber(lua,PROPAGATE_AOF|PROPAGATE_REPL);
+    lua_settable(lua,-3);
+
     /* Finally set the table as 'redis' global var. */
     lua_setglobal(lua,"redis");
 
@@ -987,6 +1040,7 @@ void evalGenericCommand(client *c, int evalsha) {
     server.lua_write_dirty = 0;
     server.lua_replicate_commands = 0;
     server.lua_multi_emitted = 0;
+    server.lua_repl = PROPAGATE_AOF|PROPAGATE_REPL;
 
     /* Get the number of arguments that are keys */
     if (getLongLongFromObjectOrReply(c,c->argv[2],&numkeys,NULL) != C_OK)