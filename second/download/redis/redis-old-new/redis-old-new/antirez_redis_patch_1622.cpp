@@ -14,7 +14,7 @@ int luaRedisCommand(lua_State *lua) {
 
     argv = zmalloc(sizeof(robj*)*argc);
     for (j = 0; j < argc; j++)
-        argv[j] = createStringObject(lua_tostring(lua,j+1),lua_strlen(lua,j+1));
+        argv[j] = createStringObject((char*)lua_tostring(lua,j+1),lua_strlen(lua,j+1));
 
     /* Command lookup */
     cmd = lookupCommand(argv[0]->ptr);
@@ -34,7 +34,7 @@ int luaRedisCommand(lua_State *lua) {
      * output buffers. */
     reply = sdsempty();
     if (c->bufpos) {
-        reply = sdscatlen(reply,c->bufpos,c->buf);
+        reply = sdscatlen(reply,c->buf,c->bufpos);
         c->bufpos = 0;
     }
     while(listLength(c->reply)) {
@@ -43,7 +43,8 @@ int luaRedisCommand(lua_State *lua) {
         sdscatlen(reply,o->ptr,sdslen(o->ptr));
         listDelNode(c->reply,listFirst(c->reply));
     }
-    lua_pushnumber(lua,1);
+    lua_pushlstring(lua,reply,sdslen(reply));
+    sdsfree(reply);
 
     /* Clean up. Command code may have changed argv/argc so we use the
      * argv/argc of the client instead of the local variables. */
@@ -65,6 +66,7 @@ void scriptingInit(void) {
     /* Create the (non connected) client that we use to execute Redis commands
      * inside the Lua interpreter */
     server.lua_client = createClient(-1);
+    server.lua_client->flags |= REDIS_LUA_CLIENT;
 
     server.lua = lua;
 }
@@ -134,8 +136,10 @@ void evalCommand(redisClient *c) {
             addReplyErrorFormat(c,"Error compiling script (new function): %s\n",
                 lua_tostring(lua,-1));
             lua_pop(lua,1);
+            sdsfree(funcdef);
             return;
         }
+        sdsfree(funcdef);
         if (lua_pcall(lua,0,0,0)) {
             addReplyErrorFormat(c,"Error running script (new function): %s\n",
                 lua_tostring(lua,-1));