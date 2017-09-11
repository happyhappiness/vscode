@@ -332,6 +332,34 @@ int luaRedisSha1hexCommand(lua_State *lua) {
     return 1;
 }
 
+/* Returns a table with a single field 'field' set to the string value
+ * passed as argument. This helper function is handy when returning
+ * a Redis Protocol error or status reply from Lua:
+ *
+ * return redis.error_reply("ERR Some Error")
+ * return redis.status_reply("ERR Some Error")
+ */
+int luaRedisReturnSingleFieldTable(lua_State *lua, char *field) {
+    if (lua_gettop(lua) != 1 || lua_type(lua,-1) != LUA_TSTRING) {
+        luaPushError(lua, "wrong number or type of arguments");
+        return 1;
+    }
+
+    lua_newtable(lua);
+    lua_pushstring(lua, field);
+    lua_pushvalue(lua, -3);
+    lua_settable(lua, -3);
+    return 1;
+}
+
+int luaRedisErrorReplyCommand(lua_State *lua) {
+    return luaRedisReturnSingleFieldTable(lua,"err");
+}
+
+int luaRedisStatusReplyCommand(lua_State *lua) {
+    return luaRedisReturnSingleFieldTable(lua,"ok");
+}
+
 int luaLogCommand(lua_State *lua) {
     int j, argc = lua_gettop(lua);
     int level;
@@ -524,6 +552,14 @@ void scriptingInit(void) {
     lua_settable(lua, -3);
     lua_settable(lua, -3);
 
+    /* redis.error_reply and redis.status_reply */
+    lua_pushstring(lua, "error_reply");
+    lua_pushcfunction(lua, luaRedisErrorReplyCommand);
+    lua_settable(lua, -3);
+    lua_pushstring(lua, "status_reply");
+    lua_pushcfunction(lua, luaRedisStatusReplyCommand);
+    lua_settable(lua, -3);
+
     /* Finally set the table as 'redis' global var. */
     lua_setglobal(lua,"redis");
 