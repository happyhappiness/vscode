     dictRelease(server.lua_scripts);
     lua_close(server.lua);
 }
 
 void scriptingReset(void) {
     scriptingRelease();
-    scriptingInit();
+    scriptingInit(0);
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
+/* Set an array of Redis String Objects as a Lua array (table) stored into a
+ * global variable. */
+void luaSetGlobalArray(lua_State *lua, char *var, robj **elev, int elec) {
     int j;
 
-    SHA1Init(&ctx);
-    SHA1Update(&ctx,(unsigned char*)script,len);
-    SHA1Final(hash,&ctx);
-
-    for (j = 0; j < 20; j++) {
-        digest[j*2] = cset[((hash[j]&0xF0)>>4)];
-        digest[j*2+1] = cset[(hash[j]&0xF)];
+    lua_newtable(lua);
+    for (j = 0; j < elec; j++) {
+        lua_pushlstring(lua,(char*)elev[j]->ptr,sdslen(elev[j]->ptr));
+        lua_rawseti(lua,-2,j+1);
     }
-    digest[40] = '\0';
+    lua_setglobal(lua,var);
 }
 
-void luaReplyToRedisReply(redisClient *c, lua_State *lua) {
-    int t = lua_type(lua,-1);
+/* ---------------------------------------------------------------------------
+ * Redis provided math.random
+ * ------------------------------------------------------------------------- */
 
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
-         * Status replies are returned as single element table with 'ok' field */
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
+/* We replace math.random() with our implementation that is not affected
+ * by specific libc random() implementations and will output the same sequence
+ * (for the same seed) in every arch. */
 
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
     }
-    lua_pop(lua,1);
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
 }
 
-/* Set an array of Redis String Objects as a Lua array (table) stored into a
- * global variable. */
-void luaSetGlobalArray(lua_State *lua, char *var, robj **elev, int elec) {
-    int j;
-
-    lua_newtable(lua);
-    for (j = 0; j < elec; j++) {
-        lua_pushlstring(lua,(char*)elev[j]->ptr,sdslen(elev[j]->ptr));
-        lua_rawseti(lua,-2,j+1);
-    }
-    lua_setglobal(lua,var);
+int redis_math_randomseed (lua_State *L) {
+  redisSrand48(luaL_checkint(L, 1));
+  return 0;
 }
 
+/* ---------------------------------------------------------------------------
+ * EVAL and SCRIPT commands implementation
+ * ------------------------------------------------------------------------- */
+
 /* Define a lua function with the specified function name and body.
- * The function name musts be a 2 characters long string, since all the
+ * The function name musts be a 42 characters long string, since all the
  * functions we defined in the Lua context are in the form:
  *
  *   f_<hex sha1 sum>
  *
- * On success REDIS_OK is returned, and nothing is left on the Lua stack.
- * On error REDIS_ERR is returned and an appropriate error is set in the
+ * On success C_OK is returned, and nothing is left on the Lua stack.
+ * On error C_ERR is returned and an appropriate error is set in the
  * client context. */
-int luaCreateFunction(redisClient *c, lua_State *lua, char *funcname, robj *body) {
+int luaCreateFunction(client *c, lua_State *lua, char *funcname, robj *body) {
     sds funcdef = sdsempty();
 
     funcdef = sdscat(funcdef,"function ");
     funcdef = sdscatlen(funcdef,funcname,42);
     funcdef = sdscatlen(funcdef,"() ",3);
     funcdef = sdscatlen(funcdef,body->ptr,sdslen(body->ptr));
