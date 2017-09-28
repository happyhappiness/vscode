         /* On success convert the Lua return value into Redis protocol, and
          * send it to * the client. */
         luaReplyToRedisReply(c,lua); /* Convert and consume the reply. */
         lua_pop(lua,1); /* Remove the error handler. */
     }
 
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
+
     /* EVALSHA should be propagated to Slave and AOF file as full EVAL, unless
      * we are sure that the script was already in the context of all the
      * attached slaves *and* the current AOF file if enabled.
      *
      * To do so we use a cache of SHA1s of scripts that we already propagated
      * as full EVAL, that's called the Replication Script Cache.
      *
      * For repliation, everytime a new slave attaches to the master, we need to
      * flush our cache of scripts that can be replicated as EVALSHA, while
      * for AOF we need to do so every time we rewrite the AOF file. */
-    if (evalsha) {
+    if (evalsha && !server.lua_replicate_commands) {
         if (!replicationScriptCacheExists(c->argv[1]->ptr)) {
             /* This script is not in our script cache, replicate it as
              * EVAL, then add it into the script cache, as from now on
              * slaves and AOF know about it. */
             robj *script = dictFetchValue(server.lua_scripts,c->argv[1]->ptr);
 
             replicationScriptCacheAdd(c->argv[1]->ptr);
-            redisAssertWithInfo(c,NULL,script != NULL);
+            serverAssertWithInfo(c,NULL,script != NULL);
             rewriteClientCommandArgument(c,0,
                 resetRefCount(createStringObject("EVAL",4)));
             rewriteClientCommandArgument(c,1,script);
-            forceCommandPropagation(c,REDIS_PROPAGATE_REPL|REDIS_PROPAGATE_AOF);
+            forceCommandPropagation(c,PROPAGATE_REPL|PROPAGATE_AOF);
         }
     }
 }
 
-void evalCommand(redisClient *c) {
-    evalGenericCommand(c,0);
+void evalCommand(client *c) {
+    if (!(c->flags & CLIENT_LUA_DEBUG))
+        evalGenericCommand(c,0);
+    else
+        evalGenericCommandWithDebugging(c,0);
 }
 
-void evalShaCommand(redisClient *c) {
+void evalShaCommand(client *c) {
     if (sdslen(c->argv[1]->ptr) != 40) {
         /* We know that a match is not possible if the provided SHA is
          * not the right length. So we return an error ASAP, this way
          * evalGenericCommand() can be implemented without string length
          * sanity check */
         addReply(c, shared.noscripterr);
         return;
     }
-    evalGenericCommand(c,1);
-}
-
-/* We replace math.random() with our implementation that is not affected
- * by specific libc random() implementations and will output the same sequence
- * (for the same seed) in every arch. */
-
-/* The following implementation is the one shipped with Lua itself but with
- * rand() replaced by redisLrand48(). */
-int redis_math_random (lua_State *L) {
-  /* the `%' avoids the (rare) case of r==1, and is needed also because on
-     some systems (SunOS!) `rand()' may return a value larger than RAND_MAX */
-  lua_Number r = (lua_Number)(redisLrand48()%REDIS_LRAND48_MAX) /
-                                (lua_Number)REDIS_LRAND48_MAX;
-  switch (lua_gettop(L)) {  /* check number of arguments */
-    case 0: {  /* no arguments */
-      lua_pushnumber(L, r);  /* Number between 0 and 1 */
-      break;
-    }
-    case 1: {  /* only upper limit */
-      int u = luaL_checkint(L, 1);
-      luaL_argcheck(L, 1<=u, 1, "interval is empty");
-      lua_pushnumber(L, floor(r*u)+1);  /* int between 1 and `u' */
-      break;
-    }
-    case 2: {  /* lower and upper limits */
-      int l = luaL_checkint(L, 1);
-      int u = luaL_checkint(L, 2);
-      luaL_argcheck(L, l<=u, 2, "interval is empty");
-      lua_pushnumber(L, floor(r*(u-l+1))+l);  /* int between `l' and `u' */
-      break;
+    if (!(c->flags & CLIENT_LUA_DEBUG))
+        evalGenericCommand(c,1);
+    else {
+        addReplyError(c,"Please use EVAL instead of EVALSHA for debugging");
+        return;
     }
-    default: return luaL_error(L, "wrong number of arguments");
-  }
-  return 1;
-}
-
-int redis_math_randomseed (lua_State *L) {
-  redisSrand48(luaL_checkint(L, 1));
-  return 0;
 }
 
-/* ---------------------------------------------------------------------------
- * SCRIPT command for script environment introspection and control
- * ------------------------------------------------------------------------- */
-
-void scriptCommand(redisClient *c) {
+void scriptCommand(client *c) {
     if (c->argc == 2 && !strcasecmp(c->argv[1]->ptr,"flush")) {
         scriptingReset();
         addReply(c,shared.ok);
         replicationScriptCacheFlush();
         server.dirty++; /* Propagating this command is a good idea. */
     } else if (c->argc >= 2 && !strcasecmp(c->argv[1]->ptr,"exists")) {
