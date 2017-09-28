 
     /* Cached across calls. */
     static robj **argv = NULL;
     static int argv_size = 0;
     static robj *cached_objects[LUA_CMD_OBJCACHE_SIZE];
     static size_t cached_objects_len[LUA_CMD_OBJCACHE_SIZE];
+    static int inuse = 0;   /* Recursive calls detection. */
+
+    /* By using Lua debug hooks it is possible to trigger a recursive call
+     * to luaRedisGenericCommand(), which normally should never happen.
+     * To make this function reentrant is futile and makes it slower, but
+     * we should at least detect such a misuse, and abort. */
+    if (inuse) {
+        char *recursion_warning =
+            "luaRedisGenericCommand() recursive call detected. "
+            "Are you doing funny stuff with Lua debug hooks?";
+        redisLog(REDIS_WARNING,"%s",recursion_warning);
+        luaPushError(lua,recursion_warning);
+        return 1;
+    }
+    inuse++;
 
     /* Require at least one argument */
     if (argc == 0) {
         luaPushError(lua,
             "Please specify at least one argument for redis.call()");
+        inuse--;
         return 1;
     }
 
     /* Build the arguments vector */
     if (argv_size < argc) {
         argv = zrealloc(argv,sizeof(robj*)*argc);
