@@ -50,6 +50,7 @@ void ldbDisable(client *c);
 void ldbEnable(client *c);
 void evalGenericCommandWithDebugging(client *c, int evalsha);
 void luaLdbLineHook(lua_State *lua, lua_Debug *ar);
+void ldbLog(sds entry);
 
 /* Debugger shared state is stored inside this global structure. */
 #define LDB_BREAKPOINTS_MAX 64
@@ -64,6 +65,7 @@ struct ldbState {
     int step;   /* Stop at next line ragardless of breakpoints. */
     sds *src;   /* Lua script source code split by line. */
     int lines;  /* Number of lines in 'src'. */
+    int currentline;    /* Current line number. */
     sds cbuf;   /* Debugger client command buffer. */
 } ldb;
 
@@ -211,6 +213,12 @@ char *redisProtocolToLuaType_MultiBulk(lua_State *lua, char *reply) {
 void luaPushError(lua_State *lua, char *error) {
     lua_Debug dbg;
 
+    /* If debugging is active and in step mode, log errors resulting from
+     * Redis commands. */
+    if (ldb.active && ldb.step) {
+        ldbLog(sdscatprintf(sdsempty(),"<error> %s",error));
+    }
+
     lua_newtable(lua);
     lua_pushstring(lua,"err");
 
@@ -433,6 +441,21 @@ int luaRedisGenericCommand(lua_State *lua, int raise_error) {
     c->argv = argv;
     c->argc = argc;
 
+    /* Log the command if debugging is active. */
+    if (ldb.active && ldb.step) {
+        sds cmdlog = sdsnew("<redis>");
+        for (j = 0; j < c->argc; j++) {
+            if (j == 10) {
+                cmdlog = sdscatprintf(cmdlog," ... (%d more)",
+                    c->argc-j-1);
+            } else {
+                cmdlog = sdscatlen(cmdlog," ",1);
+                cmdlog = sdscatsds(cmdlog,c->argv[j]->ptr);
+            }
+        }
+        ldbLog(cmdlog);
+    }
+
     /* Command lookup */
     cmd = lookupCommand(argv[0]->ptr);
     if (!cmd || ((cmd->arity > 0 && cmd->arity != argc) ||
@@ -554,6 +577,15 @@ int luaRedisGenericCommand(lua_State *lua, int raise_error) {
     }
     if (raise_error && reply[0] != '-') raise_error = 0;
     redisProtocolToLuaType(lua,reply);
+
+    /* If the debugger is active, log the reply from Redis. */
+    if (ldb.active && ldb.step) {
+        sds replycopy = sdsnew("<reply> ");
+        replycopy = sdscat(replycopy,reply); /* It's always null terminated. */
+        if (sdslen(replycopy) > 70) sdsrange(replycopy,0,69);
+        ldbLog(replycopy);
+    }
+
     /* Sort the output array if needed, assuming it is a non-null multi bulk
      * reply as expected. */
     if ((cmd->flags & CMD_SORT_FOR_SCRIPT) &&
@@ -1511,10 +1543,19 @@ int ldbStartSession(client *c) {
     anetBlock(NULL,ldb.fd);
     anetSendTimeout(NULL,ldb.fd,5000);
     ldb.active = 1;
+
     /* First argument of EVAL is the script itself. We split it into different
      * lines since this is the way the debugger accesses the source code. */
-    sds srcstring = c->argv[1]->ptr;
+    sds srcstring = sdsdup(c->argv[1]->ptr);
+    size_t srclen = sdslen(srcstring);
+    while(srclen && (srcstring[srclen-1] == '\n' ||
+                     srcstring[srclen-1] == '\r'))
+    {
+        srcstring[--srclen] = '\0';
+    }
+    sdssetlen(srcstring,srclen);
     ldb.src = sdssplitlen(srcstring,sdslen(srcstring),"\n",1,&ldb.lines);
+    sdsfree(srcstring);
     return 1;
 }
 
@@ -1558,7 +1599,7 @@ void evalGenericCommandWithDebugging(client *c, int evalsha) {
 char *ldbGetSourceLine(int line) {
     int idx = line-1;
     if (idx < 0 || idx >= ldb.lines) return "<out of range source code line>";
-    return ldb.src[line];
+    return ldb.src[idx];
 }
 
 /* Expect a valid multi-bulk command in the debugging client query buffer.
@@ -1610,6 +1651,27 @@ sds *ldbReplParseCommand(int *argcp) {
     return NULL;
 }
 
+/* Implement the "list" command of the Lua debugger. If around is 0
+ * the whole file is listed, otherwise only a small portion of the file
+ * around the specified line is shown. When a line number is specified
+ * the amonut of context (lines before/after) is specified via the
+ * 'context' argument. */
+void ldbList(int around, int context) {
+    int j;
+
+    for (j = 1; j <= ldb.lines; j++) {
+        if (around != 0 && abs(around-j) > context) continue;
+        char *line = ldbGetSourceLine(j);
+        int mark;
+        if (ldbIsBreakpoint(j))
+            mark = '#';
+        else
+            mark = (ldb.currentline == j) ? '*' : ':';
+        sds thisline = sdscatprintf(sdsempty(),"%d%c %s", j, mark, line);
+        ldbLog(thisline);
+    }
+}
+
 /* Read debugging commands from client. */
 void ldbRepl(void) {
     sds *argv;
@@ -1637,15 +1699,25 @@ void ldbRepl(void) {
 
         /* Execute the command. */
         if (!strcasecmp(argv[0],"help")) {
-            ldbLog(sdsnew("Redis Lua debugger help:"));
-            ldbLog(sdsnew("[s]tep     : run current line and stop again."));
-            ldbLog(sdsnew("[c]continue: run till next breakpoint."));
+ldbLog(sdsnew("Redis Lua debugger help:"));
+ldbLog(sdsnew("[s]tep          run current line and stop again."));
+ldbLog(sdsnew("[n]ext          alias for step."));
+ldbLog(sdsnew("[c]continue     run till next breakpoint."));
+ldbLog(sdsnew("[l]list [line]  list source code, around [line] if specified"));
+ldbLog(sdsnew("                you can use another arg for context size."));
             ldbSendLogs();
-        } else if (!strcasecmp(argv[0],"s") || !strcasecmp(argv[0],"step")) {
+        } else if (!strcasecmp(argv[0],"s") || !strcasecmp(argv[0],"step") ||
+                   !strcasecmp(argv[0],"n") || !strcasecmp(argv[0],"next")) {
             ldb.step = 1;
             break;
         } else if (!strcasecmp(argv[0],"c") || !strcasecmp(argv[0],"continue")){
             break;
+        } else if (!strcasecmp(argv[0],"l") || !strcasecmp(argv[0],"list")){
+            int around = 0, ctx = 5;
+            if (argc > 1) around = atoi(argv[1]);
+            if (argc > 2) ctx = atoi(argv[2]);
+            ldbList(around,ctx);
+            ldbSendLogs();
         } else {
             ldbLog(sdsnew("Unknown Redis Lua debugger command."));
             ldbSendLogs();
@@ -1667,9 +1739,10 @@ void luaLdbLineHook(lua_State *lua, lua_Debug *ar) {
     if(strstr(ar->short_src,"user_script") == NULL) return;
 
     if (ldb.step) {
+        ldb.currentline = ar->currentline;
         ldb.step = 0;
         ldbLog(sdscatprintf(sdsempty(),"%d: %s", (int)ar->currentline,
-            ldbGetSourceLine(ar->currentline-1)));
+            ldbGetSourceLine(ar->currentline)));
         ldbSendLogs();
         ldbRepl();
     }