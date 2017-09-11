@@ -128,7 +128,7 @@ void luaPushError(lua_State *lua, char *error) {
     lua_settable(lua,-3);
 }
 
-int luaRedisCommand(lua_State *lua) {
+int luaRedisGenericCommand(lua_State *lua, int raise_error) {
     int j, argc = lua_gettop(lua);
     struct redisCommand *cmd;
     robj **argv;
@@ -205,6 +205,7 @@ int luaRedisCommand(lua_State *lua) {
         reply = sdscatlen(reply,o->ptr,sdslen(o->ptr));
         listDelNode(c->reply,listFirst(c->reply));
     }
+    if (raise_error && reply[0] != '-') raise_error = 0;
     redisProtocolToLuaType(lua,reply);
     sdsfree(reply);
 
@@ -215,9 +216,25 @@ int luaRedisCommand(lua_State *lua) {
         decrRefCount(c->argv[j]);
     zfree(c->argv);
 
+    if (raise_error) {
+        /* If we are here we should have an error in the stack, in the
+         * form of a table with an "err" field. Extract the string to
+         * return the plain error. */
+        lua_pushstring(lua,"err");
+        lua_gettable(lua,-2);
+        return lua_error(lua);
+    }
     return 1;
 }
 
+int luaRedisCallCommand(lua_State *lua) {
+    return luaRedisGenericCommand(lua,1);
+}
+
+int luaRedisPCallCommand(lua_State *lua) {
+    return luaRedisGenericCommand(lua,0);
+}
+
 int luaLogCommand(lua_State *lua) {
     int j, argc = lua_gettop(lua);
     int level;
@@ -301,7 +318,12 @@ void scriptingInit(void) {
 
     /* redis.call */
     lua_pushstring(lua,"call");
-    lua_pushcfunction(lua,luaRedisCommand);
+    lua_pushcfunction(lua,luaRedisCallCommand);
+    lua_settable(lua,-3);
+
+    /* redis.pcall */
+    lua_pushstring(lua,"pcall");
+    lua_pushcfunction(lua,luaRedisPCallCommand);
     lua_settable(lua,-3);
 
     /* redis.log and log levels. */