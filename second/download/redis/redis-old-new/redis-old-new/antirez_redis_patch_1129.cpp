@@ -269,6 +269,7 @@ int luaRedisGenericCommand(lua_State *lua, int raise_error) {
                 "Write commands not allowed after non deterministic commands");
             goto cleanup;
         } else if (server.masterhost && server.repl_slave_ro &&
+                   !server.loading &&
                    !(server.lua_caller->flags & REDIS_MASTER))
         {
             luaPushError(lua, shared.roslaveerr->ptr);