@@ -487,8 +487,8 @@ int luaRedisSha1hexCommand(lua_State *lua) {
     char *s;
 
     if (argc != 1) {
-        luaPushError(lua, "wrong number of arguments");
-        return 1;
+        lua_pushstring(lua, "wrong number of arguments");
+        return lua_error(lua);
     }
 
     s = (char*)lua_tolstring(lua,1,&len);
@@ -556,17 +556,17 @@ int luaRedisSetReplCommand(lua_State *lua) {
     int flags;
 
     if (server.lua_replicate_commands == 0) {
-        luaPushError(lua, "You can set the replication behavior only after turning on single commands replication with redis.replicate_commands().");
-        return 1;
+        lua_pushstring(lua, "You can set the replication behavior only after turning on single commands replication with redis.replicate_commands().");
+        return lua_error(lua);
     } else if (argc != 1) {
-        luaPushError(lua, "redis.set_repl() requires two arguments.");
-        return 1;
+        lua_pushstring(lua, "redis.set_repl() requires two arguments.");
+        return lua_error(lua);
     }
 
     flags = lua_tonumber(lua,-1);
     if ((flags & ~(PROPAGATE_AOF|PROPAGATE_REPL)) != 0) {
-        luaPushError(lua, "Invalid replication flags. Use REPL_AOF, REPL_SLAVE, REPL_ALL or REPL_NONE.");
-        return 1;
+        lua_pushstring(lua, "Invalid replication flags. Use REPL_AOF, REPL_SLAVE, REPL_ALL or REPL_NONE.");
+        return lua_error(lua);
     }
     server.lua_repl = flags;
     return 0;
@@ -579,16 +579,16 @@ int luaLogCommand(lua_State *lua) {
     sds log;
 
     if (argc < 2) {
-        luaPushError(lua, "redis.log() requires two arguments or more.");
-        return 1;
+        lua_pushstring(lua, "redis.log() requires two arguments or more.");
+        return lua_error(lua);
     } else if (!lua_isnumber(lua,-argc)) {
-        luaPushError(lua, "First argument must be a number (log level).");
-        return 1;
+        lua_pushstring(lua, "First argument must be a number (log level).");
+        return lua_error(lua);
     }
     level = lua_tonumber(lua,-argc);
     if (level < LL_DEBUG || level > LL_WARNING) {
-        luaPushError(lua, "Invalid debug level.");
-        return 1;
+        lua_pushstring(lua, "Invalid debug level.");
+        return lua_error(lua);
     }
 
     /* Glue together all the arguments */