@@ -500,7 +500,6 @@ void luaSetGlobalArray(lua_State *lua, char *var, robj **elev, int elec) {
 int luaCreateFunction(redisClient *c, lua_State *lua, char *funcname, robj *body) {
     sds funcdef = sdsempty();
 
-    lua_pop(lua,1); /* remove the nil from the stack */
     funcdef = sdscat(funcdef,"function ");
     funcdef = sdscatlen(funcdef,funcname,42);
     funcdef = sdscatlen(funcdef," ()\n",4);
@@ -581,12 +580,12 @@ void evalGenericCommand(redisClient *c, int evalsha) {
     /* Try to lookup the Lua function */
     lua_getglobal(lua, funcname);
     if (lua_isnil(lua,1)) {
+        lua_pop(lua,1); /* remove the nil from the stack */
         /* Function not defined... let's define it if we have the
          * body of the funciton. If this is an EVALSHA call we can just
          * return an error. */
         if (evalsha) {
             addReply(c, shared.noscripterr);
-            lua_pop(lua,1); /* remove the nil from the stack */
             return;
         }
         if (luaCreateFunction(c,lua,funcname,c->argv[1]) == REDIS_ERR) return;
@@ -724,15 +723,21 @@ void scriptCommand(redisClient *c) {
                 addReply(c,shared.czero);
         }
     } else if (c->argc == 3 && !strcasecmp(c->argv[1]->ptr,"load")) {
-        /* We obtain the script SHA1, then check if this function is already
-         * defined into the Lua state */
         char funcname[43];
+        sds sha;
 
         funcname[0] = 'f';
         funcname[1] = '_';
         hashScript(funcname+2,c->argv[2]->ptr,sdslen(c->argv[2]->ptr));
-        if (luaCreateFunction(c,server.lua,funcname,c->argv[2]) == REDIS_ERR)
-            return;
+        sha = sdsnewlen(funcname+2,40);
+        if (dictFind(server.lua_scripts,sha) == NULL) {
+            if (luaCreateFunction(c,server.lua,funcname,c->argv[2])
+                    == REDIS_ERR) {
+                sdsfree(sha);
+                return;
+            }
+        }
+        sdsfree(sha);
         addReply(c,shared.ok);
     } else {
         addReplyError(c, "Unknown SCRIPT subcommand or wrong # of args.");