             decrRefCount(argv[j]);
             j--;
         }
         luaPushError(lua,
             "Lua redis() command arguments must be strings or integers");
         inuse--;
-        return 1;
+        return raise_error ? luaRaiseError(lua) : 1;
     }
 
     /* Setup our fake client for command execution */
     c->argv = argv;
     c->argc = argc;
 
+    /* Log the command if debugging is active. */
+    if (ldb.active && ldb.step) {
+        sds cmdlog = sdsnew("<redis>");
+        for (j = 0; j < c->argc; j++) {
+            if (j == 10) {
+                cmdlog = sdscatprintf(cmdlog," ... (%d more)",
+                    c->argc-j-1);
+            } else {
+                cmdlog = sdscatlen(cmdlog," ",1);
+                cmdlog = sdscatsds(cmdlog,c->argv[j]->ptr);
+            }
+        }
+        ldbLog(cmdlog);
+    }
+
     /* Command lookup */
     cmd = lookupCommand(argv[0]->ptr);
     if (!cmd || ((cmd->arity > 0 && cmd->arity != argc) ||
                    (argc < -cmd->arity)))
     {
         if (cmd)
             luaPushError(lua,
                 "Wrong number of args calling Redis command From Lua script");
         else
             luaPushError(lua,"Unknown Redis command called from Lua script");
         goto cleanup;
     }
-    c->cmd = cmd;
+    c->cmd = c->lastcmd = cmd;
 
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
-        if (server.lua_random_dirty) {
+    if (cmd->flags & CMD_WRITE) {
+        if (server.lua_random_dirty && !server.lua_replicate_commands) {
             luaPushError(lua,
-                "Write commands not allowed after non deterministic commands");
+                "Write commands not allowed after non deterministic commands. Call redis.replicate_commands() at the start of your script in order to switch to single commands replication mode.");
             goto cleanup;
         } else if (server.masterhost && server.repl_slave_ro &&
                    !server.loading &&
-                   !(server.lua_caller->flags & REDIS_MASTER))
+                   !(server.lua_caller->flags & CLIENT_MASTER))
         {
             luaPushError(lua, shared.roslaveerr->ptr);
             goto cleanup;
         } else if (server.stop_writes_on_bgsave_err &&
                    server.saveparamslen > 0 &&
-                   server.lastbgsave_status == REDIS_ERR)
+                   server.lastbgsave_status == C_ERR)
         {
             luaPushError(lua, shared.bgsaveerr->ptr);
             goto cleanup;
         }
     }
 
     /* If we reached the memory limit configured via maxmemory, commands that
      * could enlarge the memory usage are not allowed, but only if this is the
      * first write in the context of this script, otherwise we can't stop
      * in the middle. */
     if (server.maxmemory && server.lua_write_dirty == 0 &&
-        (cmd->flags & REDIS_CMD_DENYOOM))
+        (cmd->flags & CMD_DENYOOM))
     {
-        if (freeMemoryIfNeeded() == REDIS_ERR) {
+        if (freeMemoryIfNeeded() == C_ERR) {
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
-     * received from our master. */
-    if (server.cluster_enabled && !(server.lua_caller->flags & REDIS_MASTER)) {
+     * received from our master or when loading the AOF back in memory. */
+    if (server.cluster_enabled && !server.loading &&
+        !(server.lua_caller->flags & CLIENT_MASTER))
+    {
         /* Duplicate relevant flags in the lua client. */
-        c->flags &= ~(REDIS_READONLY|REDIS_ASKING);
-        c->flags |= server.lua_caller->flags & (REDIS_READONLY|REDIS_ASKING);
+        c->flags &= ~(CLIENT_READONLY|CLIENT_ASKING);
+        c->flags |= server.lua_caller->flags & (CLIENT_READONLY|CLIENT_ASKING);
         if (getNodeByQuery(c,c->cmd,c->argv,c->argc,NULL,NULL) !=
                            server.cluster->myself)
         {
             luaPushError(lua,
                 "Lua script attempted to access a non local key in a "
                 "cluster node");
             goto cleanup;
         }
     }
 
+    /* If we are using single commands replication, we need to wrap what
+     * we propagate into a MULTI/EXEC block, so that it will be atomic like
+     * a Lua script in the context of AOF and slaves. */
+    if (server.lua_replicate_commands &&
+        !server.lua_multi_emitted &&
+        server.lua_write_dirty &&
+        server.lua_repl != PROPAGATE_NONE)
+    {
+        execCommandPropagateMulti(server.lua_caller);
+        server.lua_multi_emitted = 1;
+    }
+
     /* Run the command */
-    call(c,REDIS_CALL_SLOWLOG | REDIS_CALL_STATS);
+    int call_flags = CMD_CALL_SLOWLOG | CMD_CALL_STATS;
+    if (server.lua_replicate_commands) {
+        /* Set flags according to redis.set_repl() settings. */
+        if (server.lua_repl & PROPAGATE_AOF)
+            call_flags |= CMD_CALL_PROPAGATE_AOF;
+        if (server.lua_repl & PROPAGATE_REPL)
+            call_flags |= CMD_CALL_PROPAGATE_REPL;
+    }
+    call(c,call_flags);
 
     /* Convert the result of the Redis command into a suitable Lua type.
      * The first thing we need is to create a single string from the client
      * output buffers. */
-    if (listLength(c->reply) == 0 && c->bufpos < REDIS_REPLY_CHUNK_BYTES) {
+    if (listLength(c->reply) == 0 && c->bufpos < PROTO_REPLY_CHUNK_BYTES) {
         /* This is a fast path for the common case of a reply inside the
          * client static buffer. Don't create an SDS string but just use
          * the client buffer directly. */
         c->buf[c->bufpos] = '\0';
         reply = c->buf;
         c->bufpos = 0;
