@@ -206,9 +206,9 @@ void luaMaskCountHook(lua_State *lua, lua_Debug *ar) {
     if (server.lua_time_limit <= 0) return;
     elapsed = (ustime()/1000) - server.lua_time_start;
     if (elapsed >= server.lua_time_limit) {
-        lua_pushstring(lua,"Script aborted for max execution time...");
+        redisLog(REDIS_NOTICE,"Lua script aborted for max execution time after %lld milliseconds of running time.",elapsed);
+        lua_pushstring(lua,"Script aborted for max execution time.");
         lua_error(lua);
-        redisLog(REDIS_NOTICE,"Lua script aborted for max execution time after %lld milliseconds of running time",elapsed);
     }
 }
 