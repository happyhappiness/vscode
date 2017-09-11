@@ -212,7 +212,7 @@ int luaRedisGenericCommand(lua_State *lua, int raise_error) {
     static robj **argv = NULL;
     static int argv_size = 0;
     static robj *cached_objects[LUA_CMD_OBJCACHE_SIZE];
-    static int cached_objects_len[LUA_CMD_OBJCACHE_SIZE];
+    static size_t cached_objects_len[LUA_CMD_OBJCACHE_SIZE];
 
     /* Require at least one argument */
     if (argc == 0) {
@@ -910,6 +910,9 @@ void evalGenericCommand(redisClient *c, int evalsha) {
     if (numkeys > (c->argc - 3)) {
         addReplyError(c,"Number of keys can't be greater than number of args");
         return;
+    } else if (numkeys < 0) {
+        addReplyError(c,"Number of keys can't be negative");
+        return;
     }
 
     /* We obtain the script SHA1, then check if this function is already