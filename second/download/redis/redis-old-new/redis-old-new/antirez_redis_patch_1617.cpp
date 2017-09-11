@@ -67,7 +67,7 @@ char *redisProtocolToLuaType_Bulk(lua_State *lua, char *reply) {
     long long bulklen;
 
     string2ll(reply+1,p-reply-1,&bulklen);
-    if (bulklen == 0) {
+    if (bulklen == -1) {
         lua_pushnil(lua);
         return p+2;
     } else {
@@ -113,6 +113,13 @@ char *redisProtocolToLuaType_MultiBulk(lua_State *lua, char *reply) {
     return p;
 }
 
+void luaPushError(lua_State *lua, char *error) {
+    lua_newtable(lua);
+    lua_pushstring(lua,"err");
+    lua_pushstring(lua, error);
+    lua_settable(lua,-3);
+}
+
 int luaRedisCommand(lua_State *lua) {
     int j, argc = lua_gettop(lua);
     struct redisCommand *cmd;
@@ -122,9 +129,26 @@ int luaRedisCommand(lua_State *lua) {
 
     /* Build the arguments vector */
     argv = zmalloc(sizeof(robj*)*argc);
-    for (j = 0; j < argc; j++)
+    for (j = 0; j < argc; j++) {
+        if (!lua_isstring(lua,j+1)) break;
         argv[j] = createStringObject((char*)lua_tostring(lua,j+1),
                                      lua_strlen(lua,j+1));
+    }
+    
+    /* Check if one of the arguments passed by the Lua script
+     * is not a string or an integer (lua_isstring() return true for
+     * integers as well). */
+    if (j != argc) {
+        j--;
+        while (j >= 0) {
+            decrRefCount(argv[j]);
+            j--;
+        }
+        zfree(argv);
+        luaPushError(lua,
+            "Lua redis() command arguments must be strings or integers");
+        return 1;
+    }
 
     /* Command lookup */
     cmd = lookupCommand(argv[0]->ptr);
@@ -133,14 +157,11 @@ int luaRedisCommand(lua_State *lua) {
     {
         for (j = 0; j < argc; j++) decrRefCount(argv[j]);
         zfree(argv);
-        lua_newtable(lua);
-        lua_pushstring(lua,"err");
         if (cmd)
-            lua_pushstring(lua,
+            luaPushError(lua,
                 "Wrong number of args calling Redis command From Lua script");
         else
-            lua_pushstring(lua,"Unknown Redis command called from Lua script");
-        lua_settable(lua,-3);
+            luaPushError(lua,"Unknown Redis command called from Lua script");
         return 1;
     }
 
@@ -309,7 +330,7 @@ void evalCommand(redisClient *c) {
         funcdef = sdscatlen(funcdef," ()\n",4);
         funcdef = sdscatlen(funcdef,c->argv[1]->ptr,sdslen(c->argv[1]->ptr));
         funcdef = sdscatlen(funcdef,"\nend\n",5);
-        printf("Defining:\n%s\n",funcdef);
+        /* printf("Defining:\n%s\n",funcdef); */
 
         if (luaL_loadbuffer(lua,funcdef,sdslen(funcdef),"func definition")) {
             addReplyErrorFormat(c,"Error compiling script (new function): %s\n",