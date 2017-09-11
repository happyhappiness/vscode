@@ -45,7 +45,37 @@ char *redisProtocolToLuaType_Error(lua_State *lua, char *reply);
 char *redisProtocolToLuaType_MultiBulk(lua_State *lua, char *reply);
 int redis_math_random (lua_State *L);
 int redis_math_randomseed (lua_State *L);
-void sha1hex(char *digest, char *script, size_t len);
+
+/* ---------------------------------------------------------------------------
+ * Utility functions.
+ * ------------------------------------------------------------------------- */
+
+/* Perform the SHA1 of the input string. We use this both for hashing script
+ * bodies in order to obtain the Lua function name, and in the implementation
+ * of redis.sha1().
+ *
+ * 'digest' should point to a 41 bytes buffer: 40 for SHA1 converted into an
+ * hexadecimal number, plus 1 byte for null term. */
+void sha1hex(char *digest, char *script, size_t len) {
+    SHA1_CTX ctx;
+    unsigned char hash[20];
+    char *cset = "0123456789abcdef";
+    int j;
+
+    SHA1Init(&ctx);
+    SHA1Update(&ctx,(unsigned char*)script,len);
+    SHA1Final(hash,&ctx);
+
+    for (j = 0; j < 20; j++) {
+        digest[j*2] = cset[((hash[j]&0xF0)>>4)];
+        digest[j*2+1] = cset[(hash[j]&0xF)];
+    }
+    digest[40] = '\0';
+}
+
+/* ---------------------------------------------------------------------------
+ * Redis reply to Lua type conversion functions.
+ * ------------------------------------------------------------------------- */
 
 /* Take a Redis reply in the Redis protocol format and convert it into a
  * Lua type. Thanks to this function, and the introduction of not connected
@@ -201,6 +231,79 @@ void luaSortArray(lua_State *lua) {
     lua_pop(lua,1);             /* Stack: array (sorted) */
 }
 
+/* ---------------------------------------------------------------------------
+ * Lua reply to Redis reply conversion functions.
+ * ------------------------------------------------------------------------- */
+
+void luaReplyToRedisReply(client *c, lua_State *lua) {
+    int t = lua_type(lua,-1);
+
+    switch(t) {
+    case LUA_TSTRING:
+        addReplyBulkCBuffer(c,(char*)lua_tostring(lua,-1),lua_strlen(lua,-1));
+        break;
+    case LUA_TBOOLEAN:
+        addReply(c,lua_toboolean(lua,-1) ? shared.cone : shared.nullbulk);
+        break;
+    case LUA_TNUMBER:
+        addReplyLongLong(c,(long long)lua_tonumber(lua,-1));
+        break;
+    case LUA_TTABLE:
+        /* We need to check if it is an array, an error, or a status reply.
+         * Error are returned as a single element table with 'err' field.
+         * Status replies are returned as single element table with 'ok'
+         * field. */
+        lua_pushstring(lua,"err");
+        lua_gettable(lua,-2);
+        t = lua_type(lua,-1);
+        if (t == LUA_TSTRING) {
+            sds err = sdsnew(lua_tostring(lua,-1));
+            sdsmapchars(err,"\r\n","  ",2);
+            addReplySds(c,sdscatprintf(sdsempty(),"-%s\r\n",err));
+            sdsfree(err);
+            lua_pop(lua,2);
+            return;
+        }
+
+        lua_pop(lua,1);
+        lua_pushstring(lua,"ok");
+        lua_gettable(lua,-2);
+        t = lua_type(lua,-1);
+        if (t == LUA_TSTRING) {
+            sds ok = sdsnew(lua_tostring(lua,-1));
+            sdsmapchars(ok,"\r\n","  ",2);
+            addReplySds(c,sdscatprintf(sdsempty(),"+%s\r\n",ok));
+            sdsfree(ok);
+            lua_pop(lua,1);
+        } else {
+            void *replylen = addDeferredMultiBulkLength(c);
+            int j = 1, mbulklen = 0;
+
+            lua_pop(lua,1); /* Discard the 'ok' field value we popped */
+            while(1) {
+                lua_pushnumber(lua,j++);
+                lua_gettable(lua,-2);
+                t = lua_type(lua,-1);
+                if (t == LUA_TNIL) {
+                    lua_pop(lua,1);
+                    break;
+                }
+                luaReplyToRedisReply(c, lua);
+                mbulklen++;
+            }
+            setDeferredMultiBulkLength(c,replylen,mbulklen);
+        }
+        break;
+    default:
+        addReply(c,shared.nullbulk);
+    }
+    lua_pop(lua,1);
+}
+
+/* ---------------------------------------------------------------------------
+ * Lua redis.* functions implementations.
+ * ------------------------------------------------------------------------- */
+
 #define LUA_CMD_OBJCACHE_SIZE 32
 #define LUA_CMD_OBJCACHE_MAX_LEN 64
 int luaRedisGenericCommand(lua_State *lua, int raise_error) {
@@ -608,29 +711,9 @@ int luaLogCommand(lua_State *lua) {
     return 0;
 }
 
-void luaMaskCountHook(lua_State *lua, lua_Debug *ar) {
-    long long elapsed;
-    UNUSED(ar);
-    UNUSED(lua);
-
-    elapsed = mstime() - server.lua_time_start;
-    if (elapsed >= server.lua_time_limit && server.lua_timedout == 0) {
-        serverLog(LL_WARNING,"Lua slow script detected: still in execution after %lld milliseconds. You can try killing the script using the SCRIPT KILL command.",elapsed);
-        server.lua_timedout = 1;
-        /* Once the script timeouts we reenter the event loop to permit others
-         * to call SCRIPT KILL or SHUTDOWN NOSAVE if needed. For this reason
-         * we need to mask the client executing the script from the event loop.
-         * If we don't do that the client may disconnect and could no longer be
-         * here when the EVAL command will return. */
-         aeDeleteFileEvent(server.el, server.lua_caller->fd, AE_READABLE);
-    }
-    if (server.lua_timedout) processEventsWhileBlocked();
-    if (server.lua_kill) {
-        serverLog(LL_WARNING,"Lua script killed by user with SCRIPT KILL.");
-        lua_pushstring(lua,"Script killed by user with SCRIPT KILL...");
-        lua_error(lua);
-    }
-}
+/* ---------------------------------------------------------------------------
+ * Lua engine initialization and reset.
+ * ------------------------------------------------------------------------- */
 
 void luaLoadLib(lua_State *lua, const char *libname, lua_CFunction luafunc) {
   lua_pushcfunction(lua, luafunc);
@@ -872,94 +955,6 @@ void scriptingReset(void) {
     scriptingInit();
 }
 
-/* Perform the SHA1 of the input string. We use this both for hashing script
- * bodies in order to obtain the Lua function name, and in the implementation
- * of redis.sha1().
- *
- * 'digest' should point to a 41 bytes buffer: 40 for SHA1 converted into an
- * hexadecimal number, plus 1 byte for null term. */
-void sha1hex(char *digest, char *script, size_t len) {
-    SHA1_CTX ctx;
-    unsigned char hash[20];
-    char *cset = "0123456789abcdef";
-    int j;
-
-    SHA1Init(&ctx);
-    SHA1Update(&ctx,(unsigned char*)script,len);
-    SHA1Final(hash,&ctx);
-
-    for (j = 0; j < 20; j++) {
-        digest[j*2] = cset[((hash[j]&0xF0)>>4)];
-        digest[j*2+1] = cset[(hash[j]&0xF)];
-    }
-    digest[40] = '\0';
-}
-
-void luaReplyToRedisReply(client *c, lua_State *lua) {
-    int t = lua_type(lua,-1);
-
-    switch(t) {
-    case LUA_TSTRING:
-        addReplyBulkCBuffer(c,(char*)lua_tostring(lua,-1),lua_strlen(lua,-1));
-        break;
-    case LUA_TBOOLEAN:
-        addReply(c,lua_toboolean(lua,-1) ? shared.cone : shared.nullbulk);
-        break;
-    case LUA_TNUMBER:
-        addReplyLongLong(c,(long long)lua_tonumber(lua,-1));
-        break;
-    case LUA_TTABLE:
-        /* We need to check if it is an array, an error, or a status reply.
-         * Error are returned as a single element table with 'err' field.
-         * Status replies are returned as single element table with 'ok'
-         * field. */
-        lua_pushstring(lua,"err");
-        lua_gettable(lua,-2);
-        t = lua_type(lua,-1);
-        if (t == LUA_TSTRING) {
-            sds err = sdsnew(lua_tostring(lua,-1));
-            sdsmapchars(err,"\r\n","  ",2);
-            addReplySds(c,sdscatprintf(sdsempty(),"-%s\r\n",err));
-            sdsfree(err);
-            lua_pop(lua,2);
-            return;
-        }
-
-        lua_pop(lua,1);
-        lua_pushstring(lua,"ok");
-        lua_gettable(lua,-2);
-        t = lua_type(lua,-1);
-        if (t == LUA_TSTRING) {
-            sds ok = sdsnew(lua_tostring(lua,-1));
-            sdsmapchars(ok,"\r\n","  ",2);
-            addReplySds(c,sdscatprintf(sdsempty(),"+%s\r\n",ok));
-            sdsfree(ok);
-            lua_pop(lua,1);
-        } else {
-            void *replylen = addDeferredMultiBulkLength(c);
-            int j = 1, mbulklen = 0;
-
-            lua_pop(lua,1); /* Discard the 'ok' field value we popped */
-            while(1) {
-                lua_pushnumber(lua,j++);
-                lua_gettable(lua,-2);
-                t = lua_type(lua,-1);
-                if (t == LUA_TNIL) {
-                    lua_pop(lua,1);
-                    break;
-                }
-                luaReplyToRedisReply(c, lua);
-                mbulklen++;
-            }
-            setDeferredMultiBulkLength(c,replylen,mbulklen);
-        }
-        break;
-    default:
-        addReply(c,shared.nullbulk);
-    }
-    lua_pop(lua,1);
-}
-
 /* Set an array of Redis String Objects as a Lua array (table) stored into a
  * global variable. */
 void luaSetGlobalArray(lua_State *lua, char *var, robj **elev, int elec) {
@@ -973,6 +968,53 @@ void luaSetGlobalArray(lua_State *lua, char *var, robj **elev, int elec) {
     lua_setglobal(lua,var);
 }
 
+/* ---------------------------------------------------------------------------
+ * Redis provided math.random
+ * ------------------------------------------------------------------------- */
+
+/* We replace math.random() with our implementation that is not affected
+ * by specific libc random() implementations and will output the same sequence
+ * (for the same seed) in every arch. */
+
+/* The following implementation is the one shipped with Lua itself but with
+ * rand() replaced by redisLrand48(). */
+int redis_math_random (lua_State *L) {
+  /* the `%' avoids the (rare) case of r==1, and is needed also because on
+     some systems (SunOS!) `rand()' may return a value larger than RAND_MAX */
+  lua_Number r = (lua_Number)(redisLrand48()%REDIS_LRAND48_MAX) /
+                                (lua_Number)REDIS_LRAND48_MAX;
+  switch (lua_gettop(L)) {  /* check number of arguments */
+    case 0: {  /* no arguments */
+      lua_pushnumber(L, r);  /* Number between 0 and 1 */
+      break;
+    }
+    case 1: {  /* only upper limit */
+      int u = luaL_checkint(L, 1);
+      luaL_argcheck(L, 1<=u, 1, "interval is empty");
+      lua_pushnumber(L, floor(r*u)+1);  /* int between 1 and `u' */
+      break;
+    }
+    case 2: {  /* lower and upper limits */
+      int l = luaL_checkint(L, 1);
+      int u = luaL_checkint(L, 2);
+      luaL_argcheck(L, l<=u, 2, "interval is empty");
+      lua_pushnumber(L, floor(r*(u-l+1))+l);  /* int between `l' and `u' */
+      break;
+    }
+    default: return luaL_error(L, "wrong number of arguments");
+  }
+  return 1;
+}
+
+int redis_math_randomseed (lua_State *L) {
+  redisSrand48(luaL_checkint(L, 1));
+  return 0;
+}
+
+/* ---------------------------------------------------------------------------
+ * EVAL and SCRIPT commands implementation
+ * ------------------------------------------------------------------------- */
+
 /* Define a lua function with the specified function name and body.
  * The function name musts be a 42 characters long string, since all the
  * functions we defined in the Lua context are in the form:
@@ -1018,6 +1060,31 @@ int luaCreateFunction(client *c, lua_State *lua, char *funcname, robj *body) {
     return C_OK;
 }
 
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
 void evalGenericCommand(client *c, int evalsha) {
     lua_State *lua = server.lua;
     char funcname[43];
@@ -1221,49 +1288,6 @@ void evalShaCommand(client *c) {
     evalGenericCommand(c,1);
 }
 
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
-    }
-    default: return luaL_error(L, "wrong number of arguments");
-  }
-  return 1;
-}
-
-int redis_math_randomseed (lua_State *L) {
-  redisSrand48(luaL_checkint(L, 1));
-  return 0;
-}
-
-/* ---------------------------------------------------------------------------
- * SCRIPT command for script environment introspection and control
- * ------------------------------------------------------------------------- */
-
 void scriptCommand(client *c) {
     if (c->argc == 2 && !strcasecmp(c->argv[1]->ptr,"flush")) {
         scriptingReset();
@@ -1311,3 +1335,5 @@ void scriptCommand(client *c) {
         addReplyError(c, "Unknown SCRIPT subcommand or wrong # of args.");
     }
 }
+
+