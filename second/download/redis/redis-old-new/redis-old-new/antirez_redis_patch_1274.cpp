@@ -167,6 +167,13 @@ int luaRedisGenericCommand(lua_State *lua, int raise_error) {
     redisClient *c = server.lua_client;
     sds reply;
 
+    /* Require at least one argument */
+    if (argc == 0) {
+        luaPushError(lua,
+            "Please specify at least one argument for redis.call()");
+        return 1;
+    }
+
     /* Build the arguments vector */
     argv = zmalloc(sizeof(robj*)*argc);
     for (j = 0; j < argc; j++) {