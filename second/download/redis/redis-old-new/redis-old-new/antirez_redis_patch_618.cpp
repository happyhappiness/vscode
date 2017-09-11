@@ -221,8 +221,11 @@ int luaRedisGenericCommand(lua_State *lua, int raise_error) {
      * To make this function reentrant is futile and makes it slower, but
      * we should at least detect such a misuse, and abort. */
     if (inuse) {
-        luaPushError(lua,
-            "luaRedisGenericCommand() recursive call detected. Are you doing funny stuff with Lua debug hooks?");
+        char *recursion_warning =
+            "luaRedisGenericCommand() recursive call detected. "
+            "Are you doing funny stuff with Lua debug hooks?";
+        redisLog(REDIS_WARNING,"%s",recursion_warning);
+        luaPushError(lua,recursion_warning);
         return 1;
     }
     inuse++;