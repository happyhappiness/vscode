@@ -1602,8 +1602,39 @@ char *ldbGetSourceLine(int line) {
     return ldb.src[idx];
 }
 
+/* Return true if there is a breakpoint in the specified line. */
 int ldbIsBreakpoint(int line) {
-    /* TODO: fixme. */
+    int j;
+
+    for (j = 0; j < ldb.bpcount; j++)
+        if (ldb.bp[j] == line) return 1;
+    return 0;
+}
+
+/* Add the specified breakpoint. Ignore it if we already reached the max.
+ * Returns 1 if the breakpoint was added (or was already set). 0 if there is
+ * no space for the breakpoint or if the line is invalid. */
+int ldbAddBreakpoint(int line) {
+    if (line <= 0 || line > ldb.lines) return 0;
+    if (!ldbIsBreakpoint(line) && ldb.bpcount != LDB_BREAKPOINTS_MAX) {
+        ldb.bp[ldb.bpcount++] = line;
+        return 1;
+    }
+    return 0;
+}
+
+/* Remove the specified breakpoint, returning 1 if the operation was
+ * performed or 0 if there was no such breakpoint. */
+int ldbDelBreakpoint(int line) {
+    int j;
+
+    for (j = 0; j < ldb.bpcount; j++) {
+        if (ldb.bp[j] == line) {
+            ldb.bpcount--;
+            memmove(ldb.bp+j,ldb.bp+j+1,ldb.bpcount-j);
+            return 1;
+        }
+    }
     return 0;
 }
 
@@ -1668,10 +1699,10 @@ void ldbList(int around, int context) {
         if (around != 0 && abs(around-j) > context) continue;
         char *line = ldbGetSourceLine(j);
         int mark;
-        if (ldbIsBreakpoint(j))
-            mark = '#';
+        if (ldb.currentline == j)
+            mark = '*';
         else
-            mark = (ldb.currentline == j) ? '*' : ':';
+            mark = ldbIsBreakpoint(j) ? '#' : ':';
         sds thisline = sdscatprintf(sdsempty(),"%d%c %s", j, mark, line);
         ldbLog(thisline);
     }
@@ -1723,8 +1754,9 @@ void ldbLogStackValue(lua_State *lua) {
 /* Implements the "print" command of the Lua debugger. It scans for Lua
  * var "varname" starting from the current stack frame up to the top stack
  * frame. The first matching variable is printed. */
-void ldbPrint(lua_State *lua, lua_Debug *orig_ar, char *varname) {
+void ldbPrint(lua_State *lua, char *varname) {
     lua_Debug ar;
+
     int l = 0; /* Stack level. */
     while (lua_getstack(lua,l,&ar) != 0) {
         l++;
@@ -1743,8 +1775,52 @@ void ldbPrint(lua_State *lua, lua_Debug *orig_ar, char *varname) {
     ldbLog(sdsnew("No such variable."));
 }
 
+/* Implements the break command to list, add and remove breakpoints. */
+void ldbBreak(sds *argv, int argc) {
+    if (argc == 1) {
+        if (ldb.bpcount == 0) {
+            ldbLog(sdsnew("No breakpoints set. Use 'b <line>' to add one."));
+            return;
+        } else {
+            ldbLog(sdscatfmt(sdsempty(),"%i breakpoints set:",ldb.bpcount));
+            int j;
+            for (j = 0; j < ldb.bpcount; j++) {
+                ldbLog(sdscatfmt(sdsempty(),"%i# %s", ldb.bp[j],
+                    ldbGetSourceLine(ldb.bp[j])));
+            }
+        }
+    } else {
+        int j;
+        for (j = 1; j < argc; j++) {
+            char *arg = argv[j];
+            long line;
+            if (!string2l(arg,sdslen(arg),&line)) {
+                ldbLog(sdscatfmt(sdsempty(),"Invalid argument:'%s'",arg));
+            } else {
+                if (line == 0) {
+                    ldb.bpcount = 0;
+                    ldbLog(sdsnew("All breakpoints removed."));
+                } else if (line > 0) {
+                    if (ldb.bpcount == LDB_BREAKPOINTS_MAX) {
+                        ldbLog(sdsnew("Too many breakpoints set."));
+                    } else if (ldbAddBreakpoint(line)) {
+                        ldbList(line,1);
+                    } else {
+                        ldbLog(sdsnew("Wrong line number."));
+                    }
+                } else if (line < 0) {
+                    if (ldbDelBreakpoint(line))
+                        ldbLog(sdsnew("Breakpoint removed."));
+                    else
+                        ldbLog(sdsnew("No breakpoint in the specified line."));
+                }
+            }
+        }
+    }
+}
+
 /* Read debugging commands from client. */
-void ldbRepl(lua_State *lua, lua_Debug *ar) {
+void ldbRepl(lua_State *lua) {
     sds *argv;
     int argc;
 
@@ -1777,17 +1853,24 @@ ldbLog(sdsnew("[c]continue     Run till next breakpoint."));
 ldbLog(sdsnew("[l]list [line]  List source code, around [line] if specified"));
 ldbLog(sdsnew("                you can use another arg for context size."));
 ldbLog(sdsnew("[p]rint <var>   Show the value of the specified local variable."));
+ldbLog(sdsnew("[b]eark         Show all breakpoints."));
+ldbLog(sdsnew("[b]eark <line>  Add a breakpoint to the specified line."));
+ldbLog(sdsnew("[b]eark -<line> Remove breakpoint from the specified line."));
+ldbLog(sdsnew("[b]eark 0       Remove all breakpoints."));
             ldbSendLogs();
         } else if (!strcasecmp(argv[0],"s") || !strcasecmp(argv[0],"step") ||
                    !strcasecmp(argv[0],"n") || !strcasecmp(argv[0],"next")) {
             ldb.step = 1;
             break;
         } else if (!strcasecmp(argv[0],"c") || !strcasecmp(argv[0],"continue")){
             break;
+        } else if (!strcasecmp(argv[0],"b") || !strcasecmp(argv[0],"break")){
+            ldbBreak(argv,argc);
+            ldbSendLogs();
         } else if (argc == 2 &&
                    (!strcasecmp(argv[0],"p") || !strcasecmp(argv[0],"print")))
         {
-            ldbPrint(lua,ar,argv[1]);
+            ldbPrint(lua,argv[1]);
             ldbSendLogs();
         } else if (!strcasecmp(argv[0],"l") || !strcasecmp(argv[0],"list")){
             int around = 0, ctx = 5;
@@ -1816,13 +1899,14 @@ void luaLdbLineHook(lua_State *lua, lua_Debug *ar) {
     lua_getinfo(lua,"Sl",ar);
     if(strstr(ar->short_src,"user_script") == NULL) return;
 
-    if (ldb.step) {
+    if (ldb.step || ldbIsBreakpoint(ar->currentline)) {
         ldb.currentline = ar->currentline;
         ldb.step = 0;
-        ldbLog(sdscatprintf(sdsempty(),"%d: %s", (int)ar->currentline,
-            ldbGetSourceLine(ar->currentline)));
+        int mark = ldbIsBreakpoint(ldb.currentline) ? '#' : '*';
+        ldbLog(sdscatprintf(sdsempty(),"%d%c %s", (int)ar->currentline,
+            mark, ldbGetSourceLine(ar->currentline)));
         ldbSendLogs();
-        ldbRepl(lua,ar);
+        ldbRepl(lua);
     }
 }
 