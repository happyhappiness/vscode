@@ -224,7 +224,7 @@ int luaRedisGenericCommand(lua_State *lua, int raise_error) {
         char *recursion_warning =
             "luaRedisGenericCommand() recursive call detected. "
             "Are you doing funny stuff with Lua debug hooks?";
-        redisLog(REDIS_WARNING,"%s",recursion_warning);
+        serverLog(REDIS_WARNING,"%s",recursion_warning);
         luaPushError(lua,recursion_warning);
         return 1;
     }
@@ -532,7 +532,7 @@ int luaLogCommand(lua_State *lua) {
             log = sdscatlen(log,s,len);
         }
     }
-    redisLogRaw(level,log);
+    serverLogRaw(level,log);
     sdsfree(log);
     return 0;
 }
@@ -544,7 +544,7 @@ void luaMaskCountHook(lua_State *lua, lua_Debug *ar) {
 
     elapsed = mstime() - server.lua_time_start;
     if (elapsed >= server.lua_time_limit && server.lua_timedout == 0) {
-        redisLog(REDIS_WARNING,"Lua slow script detected: still in execution after %lld milliseconds. You can try killing the script using the SCRIPT KILL command.",elapsed);
+        serverLog(REDIS_WARNING,"Lua slow script detected: still in execution after %lld milliseconds. You can try killing the script using the SCRIPT KILL command.",elapsed);
         server.lua_timedout = 1;
         /* Once the script timeouts we reenter the event loop to permit others
          * to call SCRIPT KILL or SHUTDOWN NOSAVE if needed. For this reason
@@ -555,7 +555,7 @@ void luaMaskCountHook(lua_State *lua, lua_Debug *ar) {
     }
     if (server.lua_timedout) processEventsWhileBlocked();
     if (server.lua_kill) {
-        redisLog(REDIS_WARNING,"Lua script killed by user with SCRIPT KILL.");
+        serverLog(REDIS_WARNING,"Lua script killed by user with SCRIPT KILL.");
         lua_pushstring(lua,"Script killed by user with SCRIPT KILL...");
         lua_error(lua);
     }