@@ -488,6 +488,52 @@ void luaSetGlobalArray(lua_State *lua, char *var, robj **elev, int elec) {
     lua_setglobal(lua,var);
 }
 
+/* Define a lua function with the specified function name and body.
+ * The function name musts be a 2 characters long string, since all the
+ * functions we defined in the Lua context are in the form:
+ *
+ *   f_<hex sha1 sum>
+ *
+ * On success REDIS_OK is returned, and nothing is left on the Lua stack.
+ * On error REDIS_ERR is returned and an appropriate error is set in the
+ * client context. */
+int luaCreateFunction(redisClient *c, lua_State *lua, char *funcname, robj *body) {
+    sds funcdef = sdsempty();
+
+    lua_pop(lua,1); /* remove the nil from the stack */
+    funcdef = sdscat(funcdef,"function ");
+    funcdef = sdscatlen(funcdef,funcname,42);
+    funcdef = sdscatlen(funcdef," ()\n",4);
+    funcdef = sdscatlen(funcdef,body->ptr,sdslen(body->ptr));
+    funcdef = sdscatlen(funcdef,"\nend\n",5);
+
+    if (luaL_loadbuffer(lua,funcdef,sdslen(funcdef),"func definition")) {
+        addReplyErrorFormat(c,"Error compiling script (new function): %s\n",
+            lua_tostring(lua,-1));
+        lua_pop(lua,1);
+        sdsfree(funcdef);
+        return REDIS_ERR;
+    }
+    sdsfree(funcdef);
+    if (lua_pcall(lua,0,0,0)) {
+        addReplyErrorFormat(c,"Error running script (new function): %s\n",
+            lua_tostring(lua,-1));
+        lua_pop(lua,1);
+        return REDIS_ERR;
+    }
+
+    /* We also save a SHA1 -> Original script map in a dictionary
+     * so that we can replicate / write in the AOF all the
+     * EVALSHA commands as EVAL using the original script. */
+    {
+        int retval = dictAdd(server.lua_scripts,
+                             sdsnewlen(funcname+2,40),body);
+        redisAssertWithInfo(c,NULL,retval == DICT_OK);
+        incrRefCount(body);
+    }
+    return REDIS_OK;
+}
+
 void evalGenericCommand(redisClient *c, int evalsha) {
     lua_State *lua = server.lua;
     char funcname[43];
@@ -532,10 +578,9 @@ void evalGenericCommand(redisClient *c, int evalsha) {
         funcname[42] = '\0';
     }
 
+    /* Try to lookup the Lua function */
     lua_getglobal(lua, funcname);
     if (lua_isnil(lua,1)) {
-        sds funcdef;
-      
         /* Function not defined... let's define it if we have the
          * body of the funciton. If this is an EVALSHA call we can just
          * return an error. */
@@ -544,41 +589,10 @@ void evalGenericCommand(redisClient *c, int evalsha) {
             lua_pop(lua,1); /* remove the nil from the stack */
             return;
         }
-        funcdef = sdsempty();
-
-        lua_pop(lua,1); /* remove the nil from the stack */
-        funcdef = sdscat(funcdef,"function ");
-        funcdef = sdscatlen(funcdef,funcname,42);
-        funcdef = sdscatlen(funcdef," ()\n",4);
-        funcdef = sdscatlen(funcdef,c->argv[1]->ptr,sdslen(c->argv[1]->ptr));
-        funcdef = sdscatlen(funcdef,"\nend\n",5);
-        /* printf("Defining:\n%s\n",funcdef); */
-
-        if (luaL_loadbuffer(lua,funcdef,sdslen(funcdef),"func definition")) {
-            addReplyErrorFormat(c,"Error compiling script (new function): %s\n",
-                lua_tostring(lua,-1));
-            lua_pop(lua,1);
-            sdsfree(funcdef);
-            return;
-        }
-        sdsfree(funcdef);
-        if (lua_pcall(lua,0,0,0)) {
-            addReplyErrorFormat(c,"Error running script (new function): %s\n",
-                lua_tostring(lua,-1));
-            lua_pop(lua,1);
-            return;
-        }
+        if (luaCreateFunction(c,lua,funcname,c->argv[1]) == REDIS_ERR) return;
+        /* Now the following is guaranteed to return non nil */
         lua_getglobal(lua, funcname);
-
-        /* We also save a SHA1 -> Original script map in a dictionary
-         * so that we can replicate / write in the AOF all the
-         * EVALSHA commands as EVAL using the original script. */
-        {
-            int retval = dictAdd(server.lua_scripts,
-                                 sdsnewlen(funcname+2,40),c->argv[1]);
-            redisAssertWithInfo(c,NULL,retval == DICT_OK);
-            incrRefCount(c->argv[1]);
-        }
+        redisAssert(!lua_isnil(lua,1));
     }
 
     /* Populate the argv and keys table accordingly to the arguments that
@@ -709,6 +723,17 @@ void scriptCommand(redisClient *c) {
             else
                 addReply(c,shared.czero);
         }
+    } else if (c->argc == 3 && !strcasecmp(c->argv[1]->ptr,"load")) {
+        /* We obtain the script SHA1, then check if this function is already
+         * defined into the Lua state */
+        char funcname[43];
+
+        funcname[0] = 'f';
+        funcname[1] = '_';
+        hashScript(funcname+2,c->argv[2]->ptr,sdslen(c->argv[2]->ptr));
+        if (luaCreateFunction(c,server.lua,funcname,c->argv[2]) == REDIS_ERR)
+            return;
+        addReply(c,shared.ok);
     } else {
         addReplyError(c, "Unknown SCRIPT subcommand or wrong # of args.");
     }