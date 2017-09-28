     selectDb(c,server.lua_client->db->id); /* set DB ID from Lua client */
     lua_gc(lua,LUA_GCSTEP,1);
 
     if (err) {
         addReplyErrorFormat(c,"Error running script (call to %s): %s\n",
             funcname, lua_tostring(lua,-1));
-        lua_pop(lua,1); /* Consume the Lua reply. */
+        lua_pop(lua,2); /* Consume the Lua reply and remove error handler. */
     } else {
         /* On success convert the Lua return value into Redis protocol, and
          * send it to * the client. */
-        luaReplyToRedisReply(c,lua);
+        luaReplyToRedisReply(c,lua); /* Convert and consume the reply. */
+        lua_pop(lua,1); /* Remove the error handler. */
     }
 
-    /* If we have slaves attached we want to replicate this command as
-     * EVAL instead of EVALSHA. We do this also in the AOF as currently there
-     * is no easy way to propagate a command in a different way in the AOF
-     * and in the replication link.
+    /* EVALSHA should be propagated to Slave and AOF file as full EVAL, unless
+     * we are sure that the script was already in the context of all the
+     * attached slaves *and* the current AOF file if enabled.
      *
-     * IMPROVEMENT POSSIBLE:
-     * 1) Replicate this command as EVALSHA in the AOF.
-     * 2) Remember what slave already received a given script, and replicate
-     *    the EVALSHA against this slaves when possible.
-     */
+     * To do so we use a cache of SHA1s of scripts that we already propagated
+     * as full EVAL, that's called the Replication Script Cache.
+     *
+     * For repliation, everytime a new slave attaches to the master, we need to
+     * flush our cache of scripts that can be replicated as EVALSHA, while
+     * for AOF we need to do so every time we rewrite the AOF file. */
     if (evalsha) {
-        robj *script = dictFetchValue(server.lua_scripts,c->argv[1]->ptr);
-
-        redisAssertWithInfo(c,NULL,script != NULL);
-        rewriteClientCommandArgument(c,0,
-            resetRefCount(createStringObject("EVAL",4)));
-        rewriteClientCommandArgument(c,1,script);
+        if (!replicationScriptCacheExists(c->argv[1]->ptr)) {
+            /* This script is not in our script cache, replicate it as
+             * EVAL, then add it into the script cache, as from now on
+             * slaves and AOF know about it. */
+            robj *script = dictFetchValue(server.lua_scripts,c->argv[1]->ptr);
+
+            replicationScriptCacheAdd(c->argv[1]->ptr);
+            redisAssertWithInfo(c,NULL,script != NULL);
+            rewriteClientCommandArgument(c,0,
+                resetRefCount(createStringObject("EVAL",4)));
+            rewriteClientCommandArgument(c,1,script);
+        }
     }
 }
 
 void evalCommand(redisClient *c) {
     evalGenericCommand(c,0);
 }
