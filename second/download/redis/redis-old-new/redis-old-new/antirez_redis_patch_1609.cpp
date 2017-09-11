@@ -200,6 +200,41 @@ int luaRedisCommand(lua_State *lua) {
     return 1;
 }
 
+int luaLogCommand(lua_State *lua) {
+    int j, argc = lua_gettop(lua);
+    int level;
+    sds log;
+
+    if (argc < 2) {
+        luaPushError(lua, "redis.log() requires two arguments or more.");
+        return 1;
+    } else if (!lua_isnumber(lua,-argc)) {
+        luaPushError(lua, "First argument must be a number.");
+        return 1;
+    }
+    level = lua_tonumber(lua,-argc);
+    if (level < REDIS_DEBUG && level > REDIS_WARNING) {
+        luaPushError(lua, "Invalid debug level.");
+        return 1;
+    }
+
+    /* Glue together all the arguments */
+    log = sdsempty();
+    for (j = 1; j < argc; j++) {
+        size_t len;
+        char *s;
+
+        s = (char*)lua_tolstring(lua,(-argc)+j,&len);
+        if (s) {
+            if (j != 1) log = sdscatlen(log," ",1);
+            log = sdscatlen(log,s,len);
+        }
+    }
+    redisLogRaw(level,log);
+    sdsfree(log);
+    return 0;
+}
+
 void luaMaskCountHook(lua_State *lua, lua_Debug *ar) {
     long long elapsed;
     REDIS_NOTUSED(ar);
@@ -216,8 +251,36 @@ void scriptingInit(void) {
     lua_State *lua = lua_open();
     luaL_openlibs(lua);
 
-    /* Register the 'r' command */
+    /* Register the redis commands table and fields */
+    lua_newtable(lua);
+
+    /* redis.call */
+    lua_pushstring(lua,"call");
     lua_pushcfunction(lua,luaRedisCommand);
+    lua_settable(lua,-3);
+
+    /* redis.log and log levels. */
+    lua_pushstring(lua,"log");
+    lua_pushcfunction(lua,luaLogCommand);
+    lua_settable(lua,-3);
+
+    lua_pushstring(lua,"LOG_DEBUG");
+    lua_pushnumber(lua,REDIS_DEBUG);
+    lua_settable(lua,-3);
+
+    lua_pushstring(lua,"LOG_VERBOSE");
+    lua_pushnumber(lua,REDIS_VERBOSE);
+    lua_settable(lua,-3);
+
+    lua_pushstring(lua,"LOG_NOTICE");
+    lua_pushnumber(lua,REDIS_NOTICE);
+    lua_settable(lua,-3);
+
+    lua_pushstring(lua,"LOG_WARNING");
+    lua_pushnumber(lua,REDIS_WARNING);
+    lua_settable(lua,-3);
+
+    /* Finally set the table as 'redis' global var. */
     lua_setglobal(lua,"redis");
 
     /* Create the (non connected) client that we use to execute Redis commands