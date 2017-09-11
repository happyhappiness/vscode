@@ -8,6 +8,8 @@
 char *redisProtocolToLuaType_Int(lua_State *lua, char *reply);
 char *redisProtocolToLuaType_Bulk(lua_State *lua, char *reply);
 char *redisProtocolToLuaType_Status(lua_State *lua, char *reply);
+char *redisProtocolToLuaType_Error(lua_State *lua, char *reply);
+char *redisProtocolToLuaType_MultiBulk(lua_State *lua, char *reply);
 
 /* Take a Redis reply in the Redis protocol format and convert it into a
  * Lua type. Thanks to this function, and the introduction of not connected
@@ -41,6 +43,12 @@ char *redisProtocolToLuaType(lua_State *lua, char* reply) {
     case '+':
         p = redisProtocolToLuaType_Status(lua,reply);
         break;
+    case '-':
+        p = redisProtocolToLuaType_Error(lua,reply);
+        break;
+    case '*':
+        p = redisProtocolToLuaType_MultiBulk(lua,reply);
+        break;
     }
     return p;
 }
@@ -75,6 +83,38 @@ char *redisProtocolToLuaType_Status(lua_State *lua, char *reply) {
     return p+2;
 }
 
+char *redisProtocolToLuaType_Error(lua_State *lua, char *reply) {
+    char *p = strchr(reply+1,'\r');
+
+    lua_newtable(lua);
+    lua_pushstring(lua,"err");
+    lua_pushlstring(lua,reply+1,p-reply-1);
+    lua_settable(lua,-3);
+    return p+2;
+}
+
+char *redisProtocolToLuaType_MultiBulk(lua_State *lua, char *reply) {
+    char *p = strchr(reply+1,'\r');
+    long long mbulklen;
+    int j = 0;
+
+    printf("--%s-- (%d)\n", reply,(int)(p-reply-1));
+    string2ll(reply+1,p-reply-1,&mbulklen);
+    p += 2;
+    if (mbulklen == -1) {
+        lua_pushnil(lua);
+        return p;
+    }
+    printf("BL: %lld\n", mbulklen);
+    lua_newtable(lua);
+    for (j = 0; j < mbulklen; j++) {
+        lua_pushnumber(lua,j);
+        p = redisProtocolToLuaType(lua,p);
+        lua_settable(lua,-3);
+    }
+    return p;
+}
+
 int luaRedisCommand(lua_State *lua) {
     int j, argc = lua_gettop(lua);
     struct redisCommand *cmd;
@@ -90,12 +130,18 @@ int luaRedisCommand(lua_State *lua) {
 
     /* Command lookup */
     cmd = lookupCommand(argv[0]->ptr);
-    if (!cmd) {
+    if (!cmd || ((cmd->arity > 0 && cmd->arity != argc) ||
+                   (argc < -cmd->arity)))
+    {
         for (j = 0; j < argc; j++) decrRefCount(argv[j]);
         zfree(argv);
         lua_newtable(lua);
         lua_pushstring(lua,"err");
-        lua_pushstring(lua,"Unknown Redis command called from Lua script");
+        if (cmd)
+            lua_pushstring(lua,
+                "Wrong number of args calling Redis command From Lua script");
+        else
+            lua_pushstring(lua,"Unknown Redis command called from Lua script");
         lua_settable(lua,-3);
         return 1;
     }
@@ -187,7 +233,8 @@ void luaReplyToRedisReply(redisClient *c, lua_State *lua) {
         lua_gettable(lua,-2);
         t = lua_type(lua,-1);
         if (t == LUA_TSTRING) {
-            addReplyError(c,(char*)lua_tostring(lua,-1));
+            addReplySds(c,sdscatprintf(sdsempty(),
+                    "-%s\r\n",(char*)lua_tostring(lua,-1)));
             lua_pop(lua,1);
         } else {
             void *replylen = addDeferredMultiBulkLength(c);