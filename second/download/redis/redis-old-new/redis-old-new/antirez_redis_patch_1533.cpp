@@ -180,6 +180,14 @@ int luaRedisCommand(lua_State *lua) {
         goto cleanup;
     }
 
+    if (cmd->flags & REDIS_CMD_WRITE && server.lua_random_dirty) {
+        luaPushError(lua,
+            "Write commands not allowed after non deterministic commands");
+        goto cleanup;
+    }
+
+    if (cmd->flags & REDIS_CMD_RANDOM) server.lua_random_dirty = 1;
+
     /* Run the command */
     cmd->proc(c);
 
@@ -425,6 +433,16 @@ void evalGenericCommand(redisClient *c, int evalsha) {
      * not affected by external state. */
     redisSrand48(0);
 
+    /* We set this flag to zero to remember that so far no random command
+     * was called. This way we can allow the user to call commands like
+     * SRANDMEMBER or RANDOMKEY from Lua scripts as far as no write command
+     * is called (otherwise the replication and AOF would end with non
+     * deterministic sequences).
+     *
+     * Thanks to this flag we'll raise an error every time a write command
+     * is called after a random command was used. */
+    server.lua_random_dirty = 0;
+
     /* Get the number of arguments that are keys */
     if (getLongLongFromObjectOrReply(c,c->argv[2],&numkeys,NULL) != REDIS_OK)
         return;