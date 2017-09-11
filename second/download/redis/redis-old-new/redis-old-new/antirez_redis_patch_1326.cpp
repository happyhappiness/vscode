@@ -444,7 +444,7 @@ void scriptingEnableGlobalsProtection(lua_State *lua) {
     s[j++]=NULL;
 
     for (j = 0; s[j] != NULL; j++) code = sdscatlen(code,s[j],strlen(s[j]));
-    luaL_loadbuffer(lua,code,sdslen(code),"enable_strict_lua");
+    luaL_loadbuffer(lua,code,sdslen(code),"@enable_strict_lua");
     lua_pcall(lua,0,0,0);
     sdsfree(code);
 }
@@ -525,7 +525,7 @@ void scriptingInit(void) {
                                 "  if b == false then b = '' end\n"
                                 "  return a<b\n"
                                 "end\n";
-        luaL_loadbuffer(lua,compare_func,strlen(compare_func),"cmp_func_def");
+        luaL_loadbuffer(lua,compare_func,strlen(compare_func),"@cmp_func_def");
         lua_pcall(lua,0,0,0);
     }
 
@@ -676,7 +676,7 @@ int luaCreateFunction(redisClient *c, lua_State *lua, char *funcname, robj *body
     funcdef = sdscatlen(funcdef,body->ptr,sdslen(body->ptr));
     funcdef = sdscatlen(funcdef," end",4);
 
-    if (luaL_loadbuffer(lua,funcdef,sdslen(funcdef),"func definition")) {
+    if (luaL_loadbuffer(lua,funcdef,sdslen(funcdef),"@user_script")) {
         addReplyErrorFormat(c,"Error compiling script (new function): %s\n",
             lua_tostring(lua,-1));
         lua_pop(lua,1);