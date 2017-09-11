@@ -463,7 +463,7 @@ int luaRedisGenericCommand(lua_State *lua, int raise_error) {
             luaPushError(lua,"Unknown Redis command called from Lua script");
         goto cleanup;
     }
-    c->cmd = cmd;
+    c->cmd = c->lastcmd = cmd;
 
     /* There are commands that are not allowed inside scripts. */
     if (cmd->flags & CMD_NOSCRIPT) {