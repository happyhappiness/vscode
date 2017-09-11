@@ -330,7 +330,7 @@ int luaRedisGenericCommand(lua_State *lua, int raise_error) {
             goto cleanup;
         } else if (server.stop_writes_on_bgsave_err &&
                    server.saveparamslen > 0 &&
-                   server.lastbgsave_status == REDIS_ERR)
+                   server.lastbgsave_status == C_ERR)
         {
             luaPushError(lua, shared.bgsaveerr->ptr);
             goto cleanup;
@@ -344,7 +344,7 @@ int luaRedisGenericCommand(lua_State *lua, int raise_error) {
     if (server.maxmemory && server.lua_write_dirty == 0 &&
         (cmd->flags & REDIS_CMD_DENYOOM))
     {
-        if (freeMemoryIfNeeded() == REDIS_ERR) {
+        if (freeMemoryIfNeeded() == C_ERR) {
             luaPushError(lua, shared.oomerr->ptr);
             goto cleanup;
         }
@@ -881,8 +881,8 @@ void luaSetGlobalArray(lua_State *lua, char *var, robj **elev, int elec) {
  *
  *   f_<hex sha1 sum>
  *
- * On success REDIS_OK is returned, and nothing is left on the Lua stack.
- * On error REDIS_ERR is returned and an appropriate error is set in the
+ * On success C_OK is returned, and nothing is left on the Lua stack.
+ * On error C_ERR is returned and an appropriate error is set in the
  * client context. */
 int luaCreateFunction(client *c, lua_State *lua, char *funcname, robj *body) {
     sds funcdef = sdsempty();
@@ -898,14 +898,14 @@ int luaCreateFunction(client *c, lua_State *lua, char *funcname, robj *body) {
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
@@ -917,7 +917,7 @@ int luaCreateFunction(client *c, lua_State *lua, char *funcname, robj *body) {
         serverAssertWithInfo(c,NULL,retval == DICT_OK);
         incrRefCount(body);
     }
-    return REDIS_OK;
+    return C_OK;
 }
 
 void evalGenericCommand(client *c, int evalsha) {
@@ -942,7 +942,7 @@ void evalGenericCommand(client *c, int evalsha) {
     server.lua_write_dirty = 0;
 
     /* Get the number of arguments that are keys */
-    if (getLongLongFromObjectOrReply(c,c->argv[2],&numkeys,NULL) != REDIS_OK)
+    if (getLongLongFromObjectOrReply(c,c->argv[2],&numkeys,NULL) != C_OK)
         return;
     if (numkeys > (c->argc - 3)) {
         addReplyError(c,"Number of keys can't be greater than number of args");
@@ -988,10 +988,10 @@ void evalGenericCommand(client *c, int evalsha) {
             addReply(c, shared.noscripterr);
             return;
         }
-        if (luaCreateFunction(c,lua,funcname,c->argv[1]) == REDIS_ERR) {
+        if (luaCreateFunction(c,lua,funcname,c->argv[1]) == C_ERR) {
             lua_pop(lua,1); /* remove the error handler from the stack. */
             /* The error is sent to the client by luaCreateFunction()
-             * itself when it returns REDIS_ERR. */
+             * itself when it returns C_ERR. */
             return;
         }
         /* Now the following is guaranteed to return non nil */
@@ -1175,7 +1175,7 @@ void scriptCommand(client *c) {
         sha = sdsnewlen(funcname+2,40);
         if (dictFind(server.lua_scripts,sha) == NULL) {
             if (luaCreateFunction(c,server.lua,funcname,c->argv[2])
-                    == REDIS_ERR) {
+                    == C_ERR) {
                 sdsfree(sha);
                 return;
             }