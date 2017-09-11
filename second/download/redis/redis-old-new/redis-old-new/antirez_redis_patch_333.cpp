@@ -1992,7 +1992,7 @@ void ldbLogRedisReply(char *reply, size_t maxlen) {
     ldbLog(log);
 }
 
-/* Implements the "print" command of the Lua debugger. It scans for Lua
+/* Implements the "print <var>" command of the Lua debugger. It scans for Lua
  * var "varname" starting from the current stack frame up to the top stack
  * frame. The first matching variable is printed. */
 void ldbPrint(lua_State *lua, char *varname) {
@@ -2025,6 +2025,32 @@ void ldbPrint(lua_State *lua, char *varname) {
     }
 }
 
+/* Implements the "print" command (without arguments) of the Lua debugger.
+ * Prints all the variables in the current stack frame. */
+void ldbPrintAll(lua_State *lua) {
+    lua_Debug ar;
+    int vars = 0;
+
+    if (lua_getstack(lua,0,&ar) != 0) {
+        const char *name;
+        int i = 1; /* Variable index. */
+        while((name = lua_getlocal(lua,&ar,i)) != NULL) {
+            i++;
+            if (!strstr(name,"(*temporary)")) {
+                sds prefix = sdscatprintf(sdsempty(),"<value> %s = ",name);
+                ldbLogStackValue(lua,prefix);
+                sdsfree(prefix);
+                vars++;
+            }
+            lua_pop(lua,1);
+        }
+    }
+
+    if (vars == 0) {
+        ldbLog(sdsnew("No local variables in the current context."));
+    }
+}
+
 /* Implements the break command to list, add and remove breakpoints. */
 void ldbBreak(sds *argv, int argc) {
     if (argc == 1) {
@@ -2157,7 +2183,9 @@ ldbLog(sdsnew("                     line = 0 means: current position."));
 ldbLog(sdsnew("[l]list [line] [ctx] In this form [ctx] specifies how many lines"));
 ldbLog(sdsnew("                     to show before/after [line]."));
 ldbLog(sdsnew("[w]hole              List all source code. Alias for 'list 1 1000000'."));
+ldbLog(sdsnew("[p]rint              Show all the local variables."));
 ldbLog(sdsnew("[p]rint <var>        Show the value of the specified variable."));
+ldbLog(sdsnew("                     Can also show global vars KEYS and ARGV."));
 ldbLog(sdsnew("[b]reak              Show all breakpoints."));
 ldbLog(sdsnew("[b]reak <line>       Add a breakpoint to the specified line."));
 ldbLog(sdsnew("[b]reak -<line>      Remove breakpoint from the specified line."));
@@ -2191,10 +2219,11 @@ ldbLog(sdsnew("                     in the next line of code."));
                    (!strcasecmp(argv[0],"r") || !strcasecmp(argv[0],"redis"))) {
             ldbRedis(lua,argv,argc);
             ldbSendLogs();
-        } else if (argc == 2 &&
-                   (!strcasecmp(argv[0],"p") || !strcasecmp(argv[0],"print")))
-        {
-            ldbPrint(lua,argv[1]);
+        } else if ((!strcasecmp(argv[0],"p") || !strcasecmp(argv[0],"print"))) {
+            if (argc == 2)
+                ldbPrint(lua,argv[1]);
+            else
+                ldbPrintAll(lua);
             ldbSendLogs();
         } else if (!strcasecmp(argv[0],"l") || !strcasecmp(argv[0],"list")){
             int around = ldb.currentline, ctx = 5;