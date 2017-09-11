@@ -443,6 +443,7 @@ int luaRedisGenericCommand(lua_State *lua, int raise_error) {
             if (j == 10) {
                 cmdlog = sdscatprintf(cmdlog," ... (%d more)",
                     c->argc-j-1);
+                break;
             } else {
                 cmdlog = sdscatlen(cmdlog," ",1);
                 cmdlog = sdscatsds(cmdlog,c->argv[j]->ptr);