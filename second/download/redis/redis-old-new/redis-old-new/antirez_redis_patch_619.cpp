@@ -221,7 +221,9 @@ int luaRedisGenericCommand(lua_State *lua, int raise_error) {
      * To make this function reentrant is futile and makes it slower, but
      * we should at least detect such a misuse, and abort. */
     if (inuse) {
-        redisPanic("luaRedisGenericCommand() recursive call detected. Are you doing funny stuff with Lua debug hooks?");
+        luaPushError(lua,
+            "luaRedisGenericCommand() recursive call detected. Are you doing funny stuff with Lua debug hooks?");
+        return 1;
     }
     inuse++;
 