@@ -52,6 +52,7 @@ void evalGenericCommandWithDebugging(client *c, int evalsha);
 void luaLdbLineHook(lua_State *lua, lua_Debug *ar);
 void ldbLog(sds entry);
 void ldbLogRedisReply(char *reply, size_t maxlen);
+sds ldbCatStackValue(sds s, lua_State *lua, int idx);
 
 /* Debugger shared state is stored inside this global structure. */
 #define LDB_BREAKPOINTS_MAX 64      /* Max number of breakpoints. */
@@ -718,6 +719,23 @@ int luaRedisBreakpointCommand(lua_State *lua) {
     return 1;
 }
 
+/* redis.debug()
+ *
+ * Log a string message into the output console.
+ * Can take multiple arguments that will be separated by commas.
+ * Nothing is returned to the caller. */
+int luaRedisDebugCommand(lua_State *lua) {
+    if (!ldb.active) return 0;
+    int argc = lua_gettop(lua);
+    sds log = sdscatprintf(sdsempty(),"<debug> line %d: ", ldb.currentline);
+    while(argc--) {
+        log = ldbCatStackValue(log,lua,-1 - argc);
+        if (argc != 0) log = sdscatlen(log,", ",2);
+    }
+    ldbLog(log);
+    return 0;
+}
+
 /* redis.set_repl()
  *
  * Set the propagation of write commands executed in the context of the
@@ -965,6 +983,11 @@ void scriptingInit(int setup) {
     lua_pushcfunction(lua,luaRedisBreakpointCommand);
     lua_settable(lua,-3);
 
+    /* redis.debug */
+    lua_pushstring(lua,"debug");
+    lua_pushcfunction(lua,luaRedisDebugCommand);
+    lua_settable(lua,-3);
+
     /* Finally set the table as 'redis' global var. */
     lua_setglobal(lua,"redis");
 
@@ -2066,19 +2089,24 @@ void ldbRepl(lua_State *lua) {
         /* Execute the command. */
         if (!strcasecmp(argv[0],"h") || !strcasecmp(argv[0],"help")) {
 ldbLog(sdsnew("Redis Lua debugger help:"));
-ldbLog(sdsnew("[h]elp          Show this help."));
-ldbLog(sdsnew("[s]tep          Run current line and stop again."));
-ldbLog(sdsnew("[n]ext          Alias for step."));
-ldbLog(sdsnew("[c]continue     Run till next breakpoint."));
-ldbLog(sdsnew("[l]list [line]  List source code, around [line] if specified"));
-ldbLog(sdsnew("                you can use another arg for context size."));
-ldbLog(sdsnew("[p]rint <var>   Show the value of the specified variable."));
-ldbLog(sdsnew("[b]eark         Show all breakpoints."));
-ldbLog(sdsnew("[b]eark <line>  Add a breakpoint to the specified line."));
-ldbLog(sdsnew("[b]eark -<line> Remove breakpoint from the specified line."));
-ldbLog(sdsnew("[b]eark 0       Remove all breakpoints."));
-ldbLog(sdsnew("[e]eval <code>  Execute some Lua code (in a different callframe)."));
-ldbLog(sdsnew("[r]edis <cmd>   Execute a Redis command."));
+ldbLog(sdsnew("[h]elp               Show this help."));
+ldbLog(sdsnew("[s]tep               Run current line and stop again."));
+ldbLog(sdsnew("[n]ext               Alias for step."));
+ldbLog(sdsnew("[c]continue          Run till next breakpoint."));
+ldbLog(sdsnew("[l]list [line]       List source code, around [line] if specified"));
+ldbLog(sdsnew("                     you can use another arg for context size."));
+ldbLog(sdsnew("[p]rint <var>        Show the value of the specified variable."));
+ldbLog(sdsnew("[b]eark              Show all breakpoints."));
+ldbLog(sdsnew("[b]eark <line>       Add a breakpoint to the specified line."));
+ldbLog(sdsnew("[b]eark -<line>      Remove breakpoint from the specified line."));
+ldbLog(sdsnew("[b]eark 0            Remove all breakpoints."));
+ldbLog(sdsnew("[e]eval <code>       Execute some Lua code (in a different callframe)."));
+ldbLog(sdsnew("[r]edis <cmd>        Execute a Redis command."));
+ldbLog(sdsnew(""));
+ldbLog(sdsnew("Debugger functions you can call from Lua scripts:"));
+ldbLog(sdsnew("redis.debug()        Produce logs in the debugger console."));
+ldbLog(sdsnew("redis.breakpoint()   Stop execution like if there was a breakpoing."));
+ldbLog(sdsnew("                     in the next line of code."));
             ldbSendLogs();
         } else if (!strcasecmp(argv[0],"s") || !strcasecmp(argv[0],"step") ||
                    !strcasecmp(argv[0],"n") || !strcasecmp(argv[0],"next")) {
@@ -2128,12 +2156,12 @@ void luaLdbLineHook(lua_State *lua, lua_Debug *ar) {
     lua_getinfo(lua,"Sl",ar);
     if(strstr(ar->short_src,"user_script") == NULL) return;
 
-    int bp = ldbIsBreakpoint(ar->currentline) || ldb.luabp;
+    ldb.currentline = ar->currentline;
+    int bp = ldbIsBreakpoint(ldb.currentline) || ldb.luabp;
     if (ldb.step || bp) {
         char *reason = "step over";
         if (bp) reason = ldb.luabp ? "redis.breakpoint() called" :
                                      "break point";
-        ldb.currentline = ar->currentline;
         ldb.step = 0;
         ldb.luabp = 0;
         ldbLog(sdscatprintf(sdsempty(),