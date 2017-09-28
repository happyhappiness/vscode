 
     if (luaL_loadbuffer(lua,funcdef,sdslen(funcdef),"@user_script")) {
         addReplyErrorFormat(c,"Error compiling script (new function): %s\n",
             lua_tostring(lua,-1));
         lua_pop(lua,1);
         sdsfree(funcdef);
-        return REDIS_ERR;
+        return C_ERR;
     }
     sdsfree(funcdef);
     if (lua_pcall(lua,0,0,0)) {
         addReplyErrorFormat(c,"Error running script (new function): %s\n",
             lua_tostring(lua,-1));
         lua_pop(lua,1);
-        return REDIS_ERR;
+        return C_ERR;
     }
 
     /* We also save a SHA1 -> Original script map in a dictionary
      * so that we can replicate / write in the AOF all the
      * EVALSHA commands as EVAL using the original script. */
     {
         int retval = dictAdd(server.lua_scripts,
                              sdsnewlen(funcname+2,40),body);
-        redisAssertWithInfo(c,NULL,retval == DICT_OK);
+        serverAssertWithInfo(c,NULL,retval == DICT_OK);
         incrRefCount(body);
     }
-    return REDIS_OK;
+    return C_OK;
 }
 
-void evalGenericCommand(redisClient *c, int evalsha) {
+/* This is the Lua script "count" hook that we use to detect scripts timeout. */
+void luaMaskCountHook(lua_State *lua, lua_Debug *ar) {
+    long long elapsed;
+    UNUSED(ar);
+    UNUSED(lua);
+
+    elapsed = mstime() - server.lua_time_start;
+    if (elapsed >= server.lua_time_limit && server.lua_timedout == 0) {
+        serverLog(LL_WARNING,"Lua slow script detected: still in execution after %lld milliseconds. You can try killing the script using the SCRIPT KILL command.",elapsed);
+        server.lua_timedout = 1;
+        /* Once the script timeouts we reenter the event loop to permit others
+         * to call SCRIPT KILL or SHUTDOWN NOSAVE if needed. For this reason
+         * we need to mask the client executing the script from the event loop.
+         * If we don't do that the client may disconnect and could no longer be
+         * here when the EVAL command will return. */
+         aeDeleteFileEvent(server.el, server.lua_caller->fd, AE_READABLE);
+    }
+    if (server.lua_timedout) processEventsWhileBlocked();
+    if (server.lua_kill) {
+        serverLog(LL_WARNING,"Lua script killed by user with SCRIPT KILL.");
+        lua_pushstring(lua,"Script killed by user with SCRIPT KILL...");
+        lua_error(lua);
+    }
+}
+
+void evalGenericCommand(client *c, int evalsha) {
     lua_State *lua = server.lua;
     char funcname[43];
     long long numkeys;
     int delhook = 0, err;
 
-    /* We want the same PRNG sequence at every call so that our PRNG is
-     * not affected by external state. */
+    /* When we replicate whole scripts, we want the same PRNG sequence at
+     * every call so that our PRNG is not affected by external state. */
     redisSrand48(0);
 
     /* We set this flag to zero to remember that so far no random command
      * was called. This way we can allow the user to call commands like
      * SRANDMEMBER or RANDOMKEY from Lua scripts as far as no write command
      * is called (otherwise the replication and AOF would end with non
      * deterministic sequences).
      *
      * Thanks to this flag we'll raise an error every time a write command
      * is called after a random command was used. */
     server.lua_random_dirty = 0;
     server.lua_write_dirty = 0;
+    server.lua_replicate_commands = server.lua_always_replicate_commands;
+    server.lua_multi_emitted = 0;
+    server.lua_repl = PROPAGATE_AOF|PROPAGATE_REPL;
 
     /* Get the number of arguments that are keys */
-    if (getLongLongFromObjectOrReply(c,c->argv[2],&numkeys,NULL) != REDIS_OK)
+    if (getLongLongFromObjectOrReply(c,c->argv[2],&numkeys,NULL) != C_OK)
         return;
     if (numkeys > (c->argc - 3)) {
         addReplyError(c,"Number of keys can't be greater than number of args");
         return;
     } else if (numkeys < 0) {
         addReplyError(c,"Number of keys can't be negative");
