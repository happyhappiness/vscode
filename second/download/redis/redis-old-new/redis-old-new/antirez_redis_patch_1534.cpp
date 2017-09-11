@@ -158,24 +158,29 @@ int luaRedisCommand(lua_State *lua) {
         return 1;
     }
 
+    /* Setup our fake client for command execution */
+    c->argv = argv;
+    c->argc = argc;
+
     /* Command lookup */
     cmd = lookupCommand(argv[0]->ptr);
     if (!cmd || ((cmd->arity > 0 && cmd->arity != argc) ||
                    (argc < -cmd->arity)))
     {
-        for (j = 0; j < argc; j++) decrRefCount(argv[j]);
-        zfree(argv);
         if (cmd)
             luaPushError(lua,
                 "Wrong number of args calling Redis command From Lua script");
         else
             luaPushError(lua,"Unknown Redis command called from Lua script");
-        return 1;
+        goto cleanup;
     }
 
-    /* Run the command in the context of a fake client */
-    c->argv = argv;
-    c->argc = argc;
+    if (cmd->flags & REDIS_CMD_NOSCRIPT) {
+        luaPushError(lua, "This Redis command is not allowed from scripts");
+        goto cleanup;
+    }
+
+    /* Run the command */
     cmd->proc(c);
 
     /* Convert the result of the Redis command into a suitable Lua type.
@@ -195,6 +200,7 @@ int luaRedisCommand(lua_State *lua) {
     redisProtocolToLuaType(lua,reply);
     sdsfree(reply);
 
+cleanup:
     /* Clean up. Command code may have changed argv/argc so we use the
      * argv/argc of the client instead of the local variables. */
     for (j = 0; j < c->argc; j++)