@@ -182,6 +182,11 @@ char *redisProtocolToLuaType_MultiBulk(lua_State *lua, char *reply) {
     return p;
 }
 
+/* This function is used in order to push an error on the Lua stack in the
+ * format used by redis.pcall to return errors, which is a lua table
+ * with a single "err" field set to the error string. Note that this
+ * table is never a valid reply by proper commands, since the returned
+ * tables are otherwise always indexed by integers, never by strings. */
 void luaPushError(lua_State *lua, char *error) {
     lua_Debug dbg;
 
@@ -200,6 +205,16 @@ void luaPushError(lua_State *lua, char *error) {
     lua_settable(lua,-3);
 }
 
+/* In case the error set into the Lua stack by luaPushError() was generated
+ * by the non-error-trapping version of redis.pcall(), which is redis.call(),
+ * this function will raise the Lua error so that the execution of the
+ * script will be halted. */
+int luaRaiseError(lua_State *lua) {
+    lua_pushstring(lua,"err");
+    lua_gettable(lua,-2);
+    return lua_error(lua);
+}
+
 /* Sort the array currently in the stack. We do this to make the output
  * of commands like KEYS or SMEMBERS something deterministic when called
  * from Lua (to play well with AOf/replication).
@@ -338,7 +353,7 @@ int luaRedisGenericCommand(lua_State *lua, int raise_error) {
         luaPushError(lua,
             "Please specify at least one argument for redis.call()");
         inuse--;
-        return 1;
+        return raise_error ? luaRaiseError(lua) : 1;
     }
 
     /* Build the arguments vector */
@@ -390,7 +405,7 @@ int luaRedisGenericCommand(lua_State *lua, int raise_error) {
         luaPushError(lua,
             "Lua redis() command arguments must be strings or integers");
         inuse--;
-        return 1;
+        return raise_error ? luaRaiseError(lua) : 1;
     }
 
     /* Setup our fake client for command execution */
@@ -562,10 +577,8 @@ int luaRedisGenericCommand(lua_State *lua, int raise_error) {
         /* If we are here we should have an error in the stack, in the
          * form of a table with an "err" field. Extract the string to
          * return the plain error. */
-        lua_pushstring(lua,"err");
-        lua_gettable(lua,-2);
         inuse--;
-        return lua_error(lua);
+        return luaRaiseError(lua);
     }
     inuse--;
     return 1;