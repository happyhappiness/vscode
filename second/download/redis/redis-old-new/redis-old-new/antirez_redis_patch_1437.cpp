@@ -516,9 +516,9 @@ int luaCreateFunction(redisClient *c, lua_State *lua, char *funcname, robj *body
 
     funcdef = sdscat(funcdef,"function ");
     funcdef = sdscatlen(funcdef,funcname,42);
-    funcdef = sdscatlen(funcdef," ()\n",4);
+    funcdef = sdscatlen(funcdef,"() ",3);
     funcdef = sdscatlen(funcdef,body->ptr,sdslen(body->ptr));
-    funcdef = sdscatlen(funcdef,"\nend\n",5);
+    funcdef = sdscatlen(funcdef," end",4);
 
     if (luaL_loadbuffer(lua,funcdef,sdslen(funcdef),"func definition")) {
         addReplyErrorFormat(c,"Error compiling script (new function): %s\n",