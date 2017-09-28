     sds funcdef = sdsempty();
 
     funcdef = sdscat(funcdef,"function ");
     funcdef = sdscatlen(funcdef,funcname,42);
     funcdef = sdscatlen(funcdef,"() ",3);
     funcdef = sdscatlen(funcdef,body->ptr,sdslen(body->ptr));
-    funcdef = sdscatlen(funcdef," end",4);
+    funcdef = sdscatlen(funcdef,"\nend",4);
 
     if (luaL_loadbuffer(lua,funcdef,sdslen(funcdef),"@user_script")) {
         addReplyErrorFormat(c,"Error compiling script (new function): %s\n",
             lua_tostring(lua,-1));
         lua_pop(lua,1);
         sdsfree(funcdef);
