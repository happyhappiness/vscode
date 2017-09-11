@@ -30,6 +30,7 @@
 #include "redis.h"
 #include "sha1.h"
 #include "rand.h"
+#include "cluster.h"
 
 #include <lua.h>
 #include <lauxlib.h>
@@ -291,6 +292,7 @@ int luaRedisGenericCommand(lua_State *lua, int raise_error) {
             luaPushError(lua,"Unknown Redis command called from Lua script");
         goto cleanup;
     }
+    c->cmd = cmd;
 
     /* There are commands that are not allowed inside scripts. */
     if (cmd->flags & REDIS_CMD_NOSCRIPT) {
@@ -337,8 +339,23 @@ int luaRedisGenericCommand(lua_State *lua, int raise_error) {
     if (cmd->flags & REDIS_CMD_RANDOM) server.lua_random_dirty = 1;
     if (cmd->flags & REDIS_CMD_WRITE) server.lua_write_dirty = 1;
 
+    /* If this is a Redis Cluster node, we need to make sure Lua is not
+     * trying to access non-local keys. */
+    if (server.cluster_enabled) {
+        /* Duplicate relevant flags in the lua client. */
+        c->flags &= ~(REDIS_READONLY|REDIS_ASKING);
+        c->flags |= server.lua_caller->flags & (REDIS_READONLY|REDIS_ASKING);
+        if (getNodeByQuery(c,c->cmd,c->argv,c->argc,NULL,NULL) !=
+                           server.cluster->myself)
+        {
+            luaPushError(lua,
+                "Lua script attempted to access a non local key in a "
+                "cluster node");
+            goto cleanup;
+        }
+    }
+
     /* Run the command */
-    c->cmd = cmd;
     call(c,REDIS_CALL_SLOWLOG | REDIS_CALL_STATS);
 
     /* Convert the result of the Redis command into a suitable Lua type.