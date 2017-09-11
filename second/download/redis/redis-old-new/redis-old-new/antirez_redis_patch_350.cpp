@@ -1602,6 +1602,11 @@ char *ldbGetSourceLine(int line) {
     return ldb.src[idx];
 }
 
+int ldbIsBreakpoint(int line) {
+    /* TODO: fixme. */
+    return 0;
+}
+
 /* Expect a valid multi-bulk command in the debugging client query buffer.
  * On success the command is parsed and returned as an array of SDS strings,
  * otherwise NULL is returned and there is to read more buffer. */
@@ -1672,8 +1677,74 @@ void ldbList(int around, int context) {
     }
 }
 
+/* Produce a debugger log entry representing the value of the Lua object
+ * currently on the top of the stack. */
+void ldbLogStackValue(lua_State *lua) {
+    int t = lua_type(lua,-1);
+    sds s = sdsnew("<value> ");
+
+    switch(t) {
+    case LUA_TSTRING:
+        s = sdscat(s,lua_tostring(lua,-1));
+        break;
+    case LUA_TBOOLEAN:
+        s = sdscat(s,lua_toboolean(lua,-1) ? "true" : "false");
+        break;
+    case LUA_TNUMBER:
+        s = sdscatprintf(s,"%g",(double)lua_tonumber(lua,-1));
+        break;
+    case LUA_TNIL:
+        s = sdscat(s,"nil");
+        break;
+    case LUA_TTABLE:
+    case LUA_TFUNCTION:
+    case LUA_TUSERDATA:
+    case LUA_TTHREAD:
+    case LUA_TLIGHTUSERDATA:
+        {
+        const void *p = lua_topointer(lua,-1);
+        char *typename = "unknown";
+        if (t == LUA_TTABLE) typename = "table";
+        else if (t == LUA_TFUNCTION) typename = "function";
+        else if (t == LUA_TUSERDATA) typename = "userdata";
+        else if (t == LUA_TTHREAD) typename = "thread";
+        else if (t == LUA_TLIGHTUSERDATA) typename = "light-userdata";
+        s = sdscatprintf(s,"%s at %p",typename,p);
+        }
+        break;
+    default:
+        s = sdscat(s,"?");
+        break;
+    }
+    ldbLog(s);
+    lua_pop(lua,1);
+}
+
+/* Implements the "print" command of the Lua debugger. It scans for Lua
+ * var "varname" starting from the current stack frame up to the top stack
+ * frame. The first matching variable is printed. */
+void ldbPrint(lua_State *lua, lua_Debug *orig_ar, char *varname) {
+    lua_Debug ar;
+    int l = 0; /* Stack level. */
+    while (lua_getstack(lua,l,&ar) != 0) {
+        l++;
+        const char *name;
+        int i = 1; /* Variable index. */
+        while((name = lua_getlocal(lua,&ar,i)) != NULL) {
+            i++;
+            if (strcmp(varname,name) == 0) {
+                ldbLogStackValue(lua);
+                return;
+            } else {
+                lua_pop(lua,1); /* Discard the var name on the stack. */
+            }
+        }
+    }
+    ldbLog(sdsnew("No such variable."));
+}
+
 /* Read debugging commands from client. */
-void ldbRepl(void) {
+void ldbRepl(lua_State *lua, lua_Debug *ar) {
     sds *argv;
     int argc;
 
@@ -1700,26 +1771,33 @@ void ldbRepl(void) {
         /* Execute the command. */
         if (!strcasecmp(argv[0],"help")) {
 ldbLog(sdsnew("Redis Lua debugger help:"));
-ldbLog(sdsnew("[s]tep          run current line and stop again."));
-ldbLog(sdsnew("[n]ext          alias for step."));
-ldbLog(sdsnew("[c]continue     run till next breakpoint."));
-ldbLog(sdsnew("[l]list [line]  list source code, around [line] if specified"));
+ldbLog(sdsnew("[s]tep          Run current line and stop again."));
+ldbLog(sdsnew("[n]ext          Alias for step."));
+ldbLog(sdsnew("[c]continue     Run till next breakpoint."));
+ldbLog(sdsnew("[l]list [line]  List source code, around [line] if specified"));
 ldbLog(sdsnew("                you can use another arg for context size."));
+ldbLog(sdsnew("[p]rint <var>   Show the value of the specified local variable."));
             ldbSendLogs();
         } else if (!strcasecmp(argv[0],"s") || !strcasecmp(argv[0],"step") ||
                    !strcasecmp(argv[0],"n") || !strcasecmp(argv[0],"next")) {
             ldb.step = 1;
             break;
         } else if (!strcasecmp(argv[0],"c") || !strcasecmp(argv[0],"continue")){
             break;
+        } else if (argc == 2 &&
+                   (!strcasecmp(argv[0],"p") || !strcasecmp(argv[0],"print")))
+        {
+            ldbPrint(lua,ar,argv[1]);
+            ldbSendLogs();
         } else if (!strcasecmp(argv[0],"l") || !strcasecmp(argv[0],"list")){
             int around = 0, ctx = 5;
             if (argc > 1) around = atoi(argv[1]);
             if (argc > 2) ctx = atoi(argv[2]);
             ldbList(around,ctx);
             ldbSendLogs();
         } else {
-            ldbLog(sdsnew("Unknown Redis Lua debugger command."));
+            ldbLog(sdsnew("Unknown Redis Lua debugger command or "
+                          "wrong number of arguments."));
             ldbSendLogs();
         }
 
@@ -1744,7 +1822,7 @@ void luaLdbLineHook(lua_State *lua, lua_Debug *ar) {
         ldbLog(sdscatprintf(sdsempty(),"%d: %s", (int)ar->currentline,
             ldbGetSourceLine(ar->currentline)));
         ldbSendLogs();
-        ldbRepl();
+        ldbRepl(lua,ar);
     }
 }
 