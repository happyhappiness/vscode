@@ -790,12 +790,26 @@ void scriptingEnableGlobalsProtection(lua_State *lua) {
 }
 
 /* Initialize the scripting environment.
- * It is possible to call this function to reset the scripting environment
- * assuming that we call scriptingRelease() before.
- * See scriptingReset() for more information. */
-void scriptingInit(void) {
+ *
+ * This function is called the first time at server startup with
+ * the 'setup' argument set to 1.
+ *
+ * It can be called again multiple times during the lifetime of the Redis
+ * process, with 'setup' set to 0, and following a scriptingRelease() call,
+ * in order to reset the Lua scripting environment.
+ *
+ * However it is simpler to just call scriptingReset() that does just that. */
+void scriptingInit(int setup) {
     lua_State *lua = lua_open();
 
+    if (setup) {
+        server.lua_client = NULL;
+        server.lua_caller = NULL;
+        server.lua_timedout = 0;
+        server.lua_always_replicate_commands = 0; /* Only DEBUG can change it.*/
+        server.lua_time_limit = LUA_SCRIPT_TIME_LIMIT;
+    }
+
     luaLoadLibraries(lua);
     luaRemoveUnsupportedFunctions(lua);
 
@@ -952,7 +966,7 @@ void scriptingRelease(void) {
 
 void scriptingReset(void) {
     scriptingRelease();
-    scriptingInit();
+    scriptingInit(0);
 }
 
 /* Set an array of Redis String Objects as a Lua array (table) stored into a
@@ -1012,6 +1026,15 @@ int redis_math_randomseed (lua_State *L) {
 }
 
 /* ---------------------------------------------------------------------------
+ * LDB: Redis Lua debugging facilities
+ * ------------------------------------------------------------------------- */
+
+/* Enable debug mode of Lua scripts for this client. */
+void ldbEnable(client *c) {
+    c->flags |= CLIENT_LUA_DEBUG;
+}
+
+/* ---------------------------------------------------------------------------
  * EVAL and SCRIPT commands implementation
  * ------------------------------------------------------------------------- */
 
@@ -1331,6 +1354,9 @@ void scriptCommand(client *c) {
             server.lua_kill = 1;
             addReply(c,shared.ok);
         }
+    } else if (c->argc == 2 && !strcasecmp(c->argv[1]->ptr,"debug")) {
+        ldbEnable(c);
+        addReply(c,shared.ok);
     } else {
         addReplyError(c, "Unknown SCRIPT subcommand or wrong # of args.");
     }