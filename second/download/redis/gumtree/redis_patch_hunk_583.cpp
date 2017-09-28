     lua_pushstring(lua, field);
     lua_pushvalue(lua, -3);
     lua_settable(lua, -3);
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
+/* redis.breakpoint()
+ *
+ * Allows to stop execution during a debuggign session from within
+ * the Lua code implementation, like if a breakpoint was set in the code
+ * immediately after the function. */
+int luaRedisBreakpointCommand(lua_State *lua) {
+    if (ldb.active) {
+        ldb.luabp = 1;
+        lua_pushboolean(lua,1);
+    } else {
+        lua_pushboolean(lua,0);
+    }
+    return 1;
+}
+
+/* redis.debug()
+ *
+ * Log a string message into the output console.
+ * Can take multiple arguments that will be separated by commas.
+ * Nothing is returned to the caller. */
+int luaRedisDebugCommand(lua_State *lua) {
+    if (!ldb.active) return 0;
+    int argc = lua_gettop(lua);
+    sds log = sdscatprintf(sdsempty(),"<debug> line %d: ", ldb.currentline);
+    while(argc--) {
+        log = ldbCatStackValue(log,lua,-1 - argc);
+        if (argc != 0) log = sdscatlen(log,", ",2);
+    }
+    ldbLog(log);
+    return 0;
+}
+
+/* redis.set_repl()
+ *
+ * Set the propagation of write commands executed in the context of the
+ * script to on/off for AOF and slaves. */
+int luaRedisSetReplCommand(lua_State *lua) {
+    int argc = lua_gettop(lua);
+    int flags;
+
+    if (server.lua_replicate_commands == 0) {
+        lua_pushstring(lua, "You can set the replication behavior only after turning on single commands replication with redis.replicate_commands().");
+        return lua_error(lua);
+    } else if (argc != 1) {
+        lua_pushstring(lua, "redis.set_repl() requires two arguments.");
+        return lua_error(lua);
+    }
+
+    flags = lua_tonumber(lua,-1);
+    if ((flags & ~(PROPAGATE_AOF|PROPAGATE_REPL)) != 0) {
+        lua_pushstring(lua, "Invalid replication flags. Use REPL_AOF, REPL_SLAVE, REPL_ALL or REPL_NONE.");
+        return lua_error(lua);
+    }
+    server.lua_repl = flags;
+    return 0;
+}
+
+/* redis.log() */
 int luaLogCommand(lua_State *lua) {
     int j, argc = lua_gettop(lua);
     int level;
     sds log;
 
     if (argc < 2) {
-        luaPushError(lua, "redis.log() requires two arguments or more.");
-        return 1;
+        lua_pushstring(lua, "redis.log() requires two arguments or more.");
+        return lua_error(lua);
     } else if (!lua_isnumber(lua,-argc)) {
-        luaPushError(lua, "First argument must be a number (log level).");
-        return 1;
+        lua_pushstring(lua, "First argument must be a number (log level).");
+        return lua_error(lua);
     }
     level = lua_tonumber(lua,-argc);
-    if (level < REDIS_DEBUG || level > REDIS_WARNING) {
-        luaPushError(lua, "Invalid debug level.");
-        return 1;
+    if (level < LL_DEBUG || level > LL_WARNING) {
+        lua_pushstring(lua, "Invalid debug level.");
+        return lua_error(lua);
     }
 
     /* Glue together all the arguments */
     log = sdsempty();
     for (j = 1; j < argc; j++) {
         size_t len;
