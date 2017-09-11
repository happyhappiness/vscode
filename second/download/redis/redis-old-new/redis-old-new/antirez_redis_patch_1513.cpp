@@ -304,6 +304,10 @@ void luaLoadLibraries(lua_State *lua) {
 #endif
 }
 
+/* Initialize the scripting environment.
+ * It is possible to call this function to reset the scripting environment
+ * assuming that we call scriptingRelease() before.
+ * See scriptingReset() for more information. */
 void scriptingInit(void) {
     lua_State *lua = lua_open();
     luaLoadLibraries(lua);
@@ -364,13 +368,29 @@ void scriptingInit(void) {
     lua_setglobal(lua,"math");
 
     /* Create the (non connected) client that we use to execute Redis commands
-     * inside the Lua interpreter */
-    server.lua_client = createClient(-1);
-    server.lua_client->flags |= REDIS_LUA_CLIENT;
+     * inside the Lua interpreter.
+     * Note: there is no need to create it again when this function is called
+     * by scriptingReset(). */
+    if (server.lua_client == NULL) {
+        server.lua_client = createClient(-1);
+        server.lua_client->flags |= REDIS_LUA_CLIENT;
+    }
 
     server.lua = lua;
 }
 
+/* Release resources related to Lua scripting.
+ * This function is used in order to reset the scripting environment. */
+void scriptingRelease(void) {
+    dictRelease(server.lua_scripts);
+    lua_close(server.lua);
+}
+
+void scriptingReset(void) {
+    scriptingRelease();
+    scriptingInit();
+}
+
 /* Hash the scripit into a SHA1 digest. We use this as Lua function name.
  * Digest should point to a 41 bytes buffer: 40 for SHA1 converted into an
  * hexadecimal number, plus 1 byte for null term. */
@@ -669,3 +689,27 @@ int redis_math_randomseed (lua_State *L) {
   redisSrand48(luaL_checkint(L, 1));
   return 0;
 }
+
+/* ---------------------------------------------------------------------------
+ * SCRIPT command for script environment introspection and control
+ * ------------------------------------------------------------------------- */
+
+void scriptCommand(redisClient *c) {
+    if (c->argc == 2 && !strcasecmp(c->argv[1]->ptr,"flush")) {
+        scriptingReset();
+        addReply(c,shared.ok);
+        server.dirty++; /* Replicating this command is a good idea. */
+    } else if (c->argc >= 2 && !strcasecmp(c->argv[1]->ptr,"exists")) {
+        int j;
+
+        addReplyMultiBulkLen(c, c->argc-2);
+        for (j = 2; j < c->argc; j++) {
+            if (dictFind(server.lua_scripts,c->argv[j]->ptr))
+                addReply(c,shared.cone);
+            else
+                addReply(c,shared.czero);
+        }
+    } else {
+        addReplyError(c, "Unknown SCRIPT subcommand or wrong # of args.");
+    }
+}