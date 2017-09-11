@@ -62,7 +62,9 @@ struct ldbState {
     int bp[LDB_BREAKPOINTS_MAX]; /* An array of breakpoints line numbers. */
     int bpcount; /* Number of valid entries inside bp. */
     int step;   /* Stop at next line ragardless of breakpoints. */
-    robj *src;  /* Lua script source code. */
+    sds *src;   /* Lua script source code split by line. */
+    int lines;  /* Number of lines in 'src'. */
+    sds cbuf;   /* Debugger client command buffer. */
 } ldb;
 
 /* ---------------------------------------------------------------------------
@@ -1424,10 +1426,10 @@ void ldbInit(void) {
     ldb.fd = -1;
     ldb.active = 0;
     ldb.logs = listCreate();
-    ldb.traces = listCreate();
     listSetFreeMethod(ldb.logs,(void (*)(void*))sdsfree);
-    listSetFreeMethod(ldb.traces, (void (*)(void*))sdsfree);
     ldb.src = NULL;
+    ldb.lines = 0;
+    ldb.cbuf = sdsempty();
 }
 
 /* Remove all the pending messages in the specified list. */
@@ -1442,25 +1444,37 @@ void ldbFlushLog(list *log) {
 void ldbEnable(client *c) {
     c->flags |= CLIENT_LUA_DEBUG;
     ldbFlushLog(ldb.logs);
-    ldbFlushLog(ldb.traces);
     ldb.fd = c->fd;
-    ldb.step = 0;
+    ldb.step = 1;
     ldb.bpcount = 0;
+    sdsfree(ldb.cbuf);
+    ldb.cbuf = sdsempty();
 }
 
 void ldbDisable(client *c) {
     c->flags &= ~(CLIENT_LUA_DEBUG|CLIENT_LUA_DEBUG_SYNC);
 }
 
 /* Append a log entry to the specified LDB log. */
-void ldbLog(list *log, sds entry) {
-    listAddNodeTail(log,entry);
+void ldbLog(sds entry) {
+    listAddNodeTail(ldb.logs,entry);
 }
 
-/* Send ldb.logs and ldb.traces to the debugging client as a multi-bulk
- * reply consisting of simple strings. Log entries which include newlines
- * have them replaced with spaces. The entries sent are also consumed. */
-void ldbWriteLogs(void) {
+/* Send ldb.logs to the debugging client as a multi-bulk reply
+ * consisting of simple strings. Log entries which include newlines have them
+ * replaced with spaces. The entries sent are also consumed. */
+void ldbSendLogs(void) {
+    sds proto = sdsempty();
+    proto = sdscatfmt(proto,"*%i\r\n", (int)listLength(ldb.logs));
+    while(listLength(ldb.logs)) {
+        listNode *ln = listFirst(ldb.logs);
+        proto = sdscatlen(proto,"+",1);
+        sdsmapchars(ln->value,"\r\n","  ",2);
+        proto = sdscatsds(proto,ln->value);
+        proto = sdscatlen(proto,"\r\n",2);
+        listDelNode(ldb.logs,ln);
+    }
+    write(ldb.fd,proto,sdslen(proto));
 }
 
 /* Start a debugging session before calling EVAL implementation.
@@ -1495,9 +1509,12 @@ int ldbStartSession(client *c) {
 
     /* Setup our debugging session. */
     anetBlock(NULL,ldb.fd);
+    anetSendTimeout(NULL,ldb.fd,5000);
     ldb.active = 1;
-    ldb.src = c->argv[1]; /* First argument of EVAL is the script itself. */
-    incrRefCount(ldb.src);
+    /* First argument of EVAL is the script itself. We split it into different
+     * lines since this is the way the debugger accesses the source code. */
+    sds srcstring = c->argv[1]->ptr;
+    ldb.src = sdssplitlen(srcstring,sdslen(srcstring),"\n",1,&ldb.lines);
     return 1;
 }
 
@@ -1513,8 +1530,16 @@ void ldbEndSession(client *c) {
 
     /* Otherwise let's restore client's state. */
     anetNonBlock(NULL,ldb.fd);
+    anetSendTimeout(NULL,ldb.fd,0);
+
+    /* Close the client connectin after sending the final EVAL reply
+     * in order to signal the end of the debugging session. */
+    c->flags |= CLIENT_CLOSE_AFTER_REPLY;
+
+    /* Cleanup. */
+    sdsfreesplitres(ldb.src,ldb.lines);
+    ldb.lines = 0;
     ldb.active = 0;
-    decrRefCount(ldb.src);
 }
 
 /* Wrapper for EVAL / EVALSHA that enables debugging, and makes sure
@@ -1528,14 +1553,125 @@ void evalGenericCommandWithDebugging(client *c, int evalsha) {
     }
 }
 
+/* Return a pointer to ldb.src source code line, considering line to be
+ * one-based, and returning a special string for out of range lines. */
+char *ldbGetSourceLine(int line) {
+    int idx = line-1;
+    if (idx < 0 || idx >= ldb.lines) return "<out of range source code line>";
+    return ldb.src[line];
+}
+
+/* Expect a valid multi-bulk command in the debugging client query buffer.
+ * On success the command is parsed and returned as an array of SDS strings,
+ * otherwise NULL is returned and there is to read more buffer. */
+sds *ldbReplParseCommand(int *argcp) {
+    sds *argv = NULL;
+    int argc = 0;
+    if (sdslen(ldb.cbuf) == 0) return NULL;
+
+    /* Working on a copy is simpler in this case. We can modify it freely
+     * for the sake of simpler parsing. */
+    sds copy = sdsdup(ldb.cbuf);
+    char *p = copy;
+
+    /* This Redis protocol parser is a joke... just the simplest thing that
+     * works in this context. It is also very forgiving regarding broken
+     * protocol. */
+
+    /* Seek and parse *<count>\r\n. */
+    p = strchr(p,'*'); if (!p) goto protoerr;
+    char *plen = p+1; /* Multi bulk len pointer. */
+    p = strstr(p,"\r\n"); if (!p) goto protoerr;
+    *p = '\0'; p += 2;
+    *argcp = atoi(plen);
+    if (*argcp <= 0 || *argcp > 1024) goto protoerr;
+
+    /* Parse each argument. */
+    argv = zmalloc(sizeof(sds)*(*argcp));
+    argc = 0;
+    while(argc < *argcp) {
+        if (*p != '$') goto protoerr;
+        plen = p+1; /* Bulk string len pointer. */
+        p = strstr(p,"\r\n"); if (!p) goto protoerr;
+        *p = '\0'; p += 2;
+        int slen = atoi(plen); /* Length of this arg. */
+        if (slen <= 0 || slen > 1024) goto protoerr;
+        argv[argc++] = sdsnewlen(p,slen);
+        p += slen; /* Skip the already parsed argument. */
+        if (p[0] != '\r' || p[1] != '\n') goto protoerr;
+        p += 2; /* Skip \r\n. */
+    }
+    sdsfree(copy);
+    return argv;
+
+protoerr:
+    sdsfreesplitres(argv,argc);
+    sdsfree(copy);
+    return NULL;
+}
+
+/* Read debugging commands from client. */
+void ldbRepl(void) {
+    sds *argv;
+    int argc;
+
+    /* We continue processing commands until a command that should return
+     * to the Lua interpreter is found. */
+    while(1) {
+        while((argv = ldbReplParseCommand(&argc)) == NULL) {
+            char buf[1024];
+            int nread = read(ldb.fd,buf,sizeof(buf));
+            if (nread <= 0) {
+                /* Make sure the script runs without user input since the
+                 * client is no longer connected. */
+                ldb.step = 0;
+                ldb.bpcount = 0;
+                return;
+            }
+            ldb.cbuf = sdscatlen(ldb.cbuf,buf,nread);
+        }
+
+        /* Flush the old buffer. */
+        sdsfree(ldb.cbuf);
+        ldb.cbuf = sdsempty();
+
+        /* Execute the command. */
+        if (!strcasecmp(argv[0],"help")) {
+            ldbLog(sdsnew("Redis Lua debugger help:"));
+            ldbLog(sdsnew("[s]tep     : run current line and stop again."));
+            ldbLog(sdsnew("[c]continue: run till next breakpoint."));
+            ldbSendLogs();
+        } else if (!strcasecmp(argv[0],"s") || !strcasecmp(argv[0],"step")) {
+            ldb.step = 1;
+            break;
+        } else if (!strcasecmp(argv[0],"c") || !strcasecmp(argv[0],"continue")){
+            break;
+        } else {
+            ldbLog(sdsnew("Unknown Redis Lua debugger command."));
+            ldbSendLogs();
+        }
+
+        /* Free the command vector. */
+        sdsfreesplitres(argv,argc);
+    }
+
+    /* Free the current command argv if we break inside the while loop. */
+    sdsfreesplitres(argv,argc);
+}
+
 /* This is the core of our Lua debugger, called each time Lua is about
  * to start executing a new line. */
 void luaLdbLineHook(lua_State *lua, lua_Debug *ar) {
     lua_getstack(lua,0,ar);
     lua_getinfo(lua,"Sl",ar);
-    if(strstr(ar->short_src,"user_script") != NULL)
-        printf("%s %d\n", ar->short_src, (int) ar->currentline);
+    if(strstr(ar->short_src,"user_script") == NULL) return;
+
+    if (ldb.step) {
+        ldb.step = 0;
+        ldbLog(sdscatprintf(sdsempty(),"%d: %s", (int)ar->currentline,
+            ldbGetSourceLine(ar->currentline-1)));
+        ldbSendLogs();
+        ldbRepl();
+    }
 }
 
-
-