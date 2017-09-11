@@ -1145,7 +1145,7 @@ int luaCreateFunction(client *c, lua_State *lua, char *funcname, robj *body) {
     funcdef = sdscatlen(funcdef,funcname,42);
     funcdef = sdscatlen(funcdef,"() ",3);
     funcdef = sdscatlen(funcdef,body->ptr,sdslen(body->ptr));
-    funcdef = sdscatlen(funcdef," end",4);
+    funcdef = sdscatlen(funcdef,"\nend",4);
 
     if (luaL_loadbuffer(lua,funcdef,sdslen(funcdef),"@user_script")) {
         addReplyErrorFormat(c,"Error compiling script (new function): %s\n",