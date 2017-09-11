@@ -65,6 +65,7 @@ struct ldbState {
     int bp[LDB_BREAKPOINTS_MAX]; /* An array of breakpoints line numbers. */
     int bpcount; /* Number of valid entries inside bp. */
     int step;   /* Stop at next line ragardless of breakpoints. */
+    int luabp;  /* Stop at next line because redis.breakpoint() was called. */
     sds *src;   /* Lua script source code split by line. */
     int lines;  /* Number of lines in 'src'. */
     int currentline;    /* Current line number. */
@@ -702,6 +703,21 @@ int luaRedisReplicateCommandsCommand(lua_State *lua) {
     return 1;
 }
 
+/* redis.breakpoint()
+ *
+ * Allows to stop execution during a debuggign session from within
+ * the Lua code implementation, like if a breakpoint was set in the code
+ * immediately after the function. */
+int luaRedisBreakpointCommand(lua_State *lua) {
+    if (ldb.active) {
+        ldb.luabp = 1;
+        lua_pushboolean(lua,1);
+    } else {
+        lua_pushboolean(lua,0);
+    }
+    return 1;
+}
+
 /* redis.set_repl()
  *
  * Set the propagation of write commands executed in the context of the
@@ -944,6 +960,11 @@ void scriptingInit(int setup) {
     lua_pushnumber(lua,PROPAGATE_AOF|PROPAGATE_REPL);
     lua_settable(lua,-3);
 
+    /* redis.breakpoint */
+    lua_pushstring(lua,"breakpoint");
+    lua_pushcfunction(lua,luaRedisBreakpointCommand);
+    lua_settable(lua,-3);
+
     /* Finally set the table as 'redis' global var. */
     lua_setglobal(lua,"redis");
 
@@ -1465,6 +1486,7 @@ void ldbEnable(client *c) {
     ldb.fd = c->fd;
     ldb.step = 1;
     ldb.bpcount = 0;
+    ldb.luabp = 0;
     sdsfree(ldb.cbuf);
     ldb.cbuf = sdsempty();
 }
@@ -2008,11 +2030,14 @@ void luaLdbLineHook(lua_State *lua, lua_Debug *ar) {
     lua_getinfo(lua,"Sl",ar);
     if(strstr(ar->short_src,"user_script") == NULL) return;
 
-    int bp = ldbIsBreakpoint(ar->currentline);
+    int bp = ldbIsBreakpoint(ar->currentline) || ldb.luabp;
     if (ldb.step || bp) {
-        char *reason = bp ? "break point" : "step over";
+        char *reason = "step over";
+        if (bp) reason = ldb.luabp ? "redis.breakpoint() called" :
+                                     "break point";
         ldb.currentline = ar->currentline;
         ldb.step = 0;
+        ldb.luabp = 0;
         ldbLog(sdscatprintf(sdsempty(),
             "* Stopped at %d, stop reason = %s",
             ldb.currentline, reason));