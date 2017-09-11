@@ -206,15 +206,45 @@ int luaRedisGenericCommand(lua_State *lua, int raise_error) {
         goto cleanup;
     }
 
+    /* There are commands that are not allowed inside scripts. */
     if (cmd->flags & REDIS_CMD_NOSCRIPT) {
         luaPushError(lua, "This Redis command is not allowed from scripts");
         goto cleanup;
     }
 
-    if (cmd->flags & REDIS_CMD_WRITE && server.lua_random_dirty) {
-        luaPushError(lua,
-            "Write commands not allowed after non deterministic commands");
-        goto cleanup;
+    /* Write commands are forbidden against read-only slaves, or if a
+     * command marked as non-deterministic was already called in the context
+     * of this script. */
+    if (cmd->flags & REDIS_CMD_WRITE) {
+        if (server.lua_random_dirty) {
+            luaPushError(lua,
+                "Write commands not allowed after non deterministic commands");
+            goto cleanup;
+        } else if (server.masterhost && server.repl_slave_ro &&
+                   !(server.lua_caller->flags & REDIS_MASTER))
+        {
+            luaPushError(lua, shared.roslaveerr->ptr);
+            goto cleanup;
+        } else if (server.stop_writes_on_bgsave_err &&
+                   server.saveparamslen > 0 &&
+                   server.lastbgsave_status == REDIS_ERR)
+        {
+            luaPushError(lua, shared.bgsaveerr->ptr);
+            goto cleanup;
+        }
+    }
+
+    /* If we reached the memory limit configured via maxmemory, commands that
+     * could enlarge the memory usage are not allowed, but only if this is the
+     * first write in the context of this script, otherwise we can't stop
+     * in the middle. */
+    if (server.maxmemory && server.lua_write_dirty == 0 &&
+        (cmd->flags & REDIS_CMD_DENYOOM))
+    {
+        if (freeMemoryIfNeeded() == REDIS_ERR) {
+            luaPushError(lua, shared.oomerr->ptr);
+            goto cleanup;
+        }
     }
 
     if (cmd->flags & REDIS_CMD_RANDOM) server.lua_random_dirty = 1;