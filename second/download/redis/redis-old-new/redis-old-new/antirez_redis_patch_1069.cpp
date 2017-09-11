@@ -876,7 +876,12 @@ void evalGenericCommand(redisClient *c, int evalsha) {
             addReply(c, shared.noscripterr);
             return;
         }
-        if (luaCreateFunction(c,lua,funcname,c->argv[1]) == REDIS_ERR) return;
+        if (luaCreateFunction(c,lua,funcname,c->argv[1]) == REDIS_ERR) {
+            lua_pop(lua,1); /* remove the error handler from the stack. */
+            /* The error is sent to the client by luaCreateFunction()
+             * itself when it returns REDIS_ERR. */
+            return;
+        }
         /* Now the following is guaranteed to return non nil */
         lua_getglobal(lua, funcname);
         redisAssert(!lua_isnil(lua,-1));
@@ -905,7 +910,6 @@ void evalGenericCommand(redisClient *c, int evalsha) {
     /* At this point whether this script was never seen before or if it was
      * already defined, we can call it. We have zero arguments and expect
      * a single return value. */
-
     err = lua_pcall(lua,0,1,-2);
 
     /* Perform some cleanup that we need to do both on error and success. */
@@ -924,11 +928,12 @@ void evalGenericCommand(redisClient *c, int evalsha) {
     if (err) {
         addReplyErrorFormat(c,"Error running script (call to %s): %s\n",
             funcname, lua_tostring(lua,-1));
-        lua_pop(lua,1); /* Consume the Lua reply. */
+        lua_pop(lua,2); /* Consume the Lua reply and remove error handler. */
     } else {
         /* On success convert the Lua return value into Redis protocol, and
          * send it to * the client. */
-        luaReplyToRedisReply(c,lua);
+        luaReplyToRedisReply(c,lua); /* Convert and consume the reply. */
+        lua_pop(lua,1); /* Remove the error handler. */
     }
 
     /* EVALSHA should be propagated to Slave and AOF file as full EVAL, unless