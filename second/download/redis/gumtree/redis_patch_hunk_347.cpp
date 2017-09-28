         lua_call(lua,2,0);
     }
     /* Stack: array (sorted), table */
     lua_pop(lua,1);             /* Stack: array (sorted) */
 }
 
+#define LUA_CMD_OBJCACHE_SIZE 32
+#define LUA_CMD_OBJCACHE_MAX_LEN 64
 int luaRedisGenericCommand(lua_State *lua, int raise_error) {
     int j, argc = lua_gettop(lua);
     struct redisCommand *cmd;
-    robj **argv;
     redisClient *c = server.lua_client;
     sds reply;
 
+    /* Cached across calls. */
+    static robj **argv = NULL;
+    static int argv_size = 0;
+    static robj *cached_objects[LUA_CMD_OBJCACHE_SIZE];
+    static int cached_objects_len[LUA_CMD_OBJCACHE_SIZE];
+
     /* Require at least one argument */
     if (argc == 0) {
         luaPushError(lua,
             "Please specify at least one argument for redis.call()");
         return 1;
     }
 
     /* Build the arguments vector */
-    argv = zmalloc(sizeof(robj*)*argc);
+    if (!argv) {
+        argv = zmalloc(sizeof(robj*)*argc);
+    } else if (argv_size < argc) {
+        argv = zrealloc(argv,sizeof(robj*)*argc);
+        argv_size = argc;
+    }
+
     for (j = 0; j < argc; j++) {
-        if (!lua_isstring(lua,j+1)) break;
-        argv[j] = createStringObject((char*)lua_tostring(lua,j+1),
-                                     lua_strlen(lua,j+1));
+        char *obj_s;
+        size_t obj_len;
+        char dbuf[64];
+
+        if (lua_isnumber(lua,j+1)) {
+            /* We can't use lua_tolstring() for number -> string conversion
+             * since Lua uses a format specifier that loses precision. */
+            lua_Number num = lua_tonumber(lua,j+1);
+
+            obj_len = snprintf(dbuf,sizeof(dbuf),"%.17g",(double)num);
+            obj_s = dbuf;
+        } else {
+            obj_s = (char*)lua_tolstring(lua,j+1,&obj_len);
+            if (obj_s == NULL) break; /* Not a string. */
+        }
+
+        /* Try to use a cached object. */
+        if (j < LUA_CMD_OBJCACHE_SIZE && cached_objects[j] &&
+            cached_objects_len[j] >= obj_len)
+        {
+            char *s = cached_objects[j]->ptr;
+            struct sdshdr *sh = (void*)(s-(sizeof(struct sdshdr)));
+
+            argv[j] = cached_objects[j];
+            cached_objects[j] = NULL;
+            memcpy(s,obj_s,obj_len+1);
+            sh->free += sh->len - obj_len;
+            sh->len = obj_len;
+        } else {
+            argv[j] = createStringObject(obj_s, obj_len);
+        }
     }
-    
+
     /* Check if one of the arguments passed by the Lua script
      * is not a string or an integer (lua_isstring() return true for
      * integers as well). */
     if (j != argc) {
         j--;
         while (j >= 0) {
             decrRefCount(argv[j]);
             j--;
         }
-        zfree(argv);
         luaPushError(lua,
             "Lua redis() command arguments must be strings or integers");
         return 1;
     }
 
     /* Setup our fake client for command execution */
