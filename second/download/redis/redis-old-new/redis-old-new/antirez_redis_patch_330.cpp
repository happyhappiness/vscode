@@ -51,12 +51,12 @@ void ldbEnable(client *c);
 void evalGenericCommandWithDebugging(client *c, int evalsha);
 void luaLdbLineHook(lua_State *lua, lua_Debug *ar);
 void ldbLog(sds entry);
-void ldbLogRedisReply(char *reply, size_t maxlen);
+void ldbLogRedisReply(char *reply);
 sds ldbCatStackValue(sds s, lua_State *lua, int idx);
 
 /* Debugger shared state is stored inside this global structure. */
-#define LDB_BREAKPOINTS_MAX 64      /* Max number of breakpoints. */
-#define LDB_REPLY_MAX_LOG_LEN 60    /* Max chars when logging a reply. */
+#define LDB_BREAKPOINTS_MAX 64  /* Max number of breakpoints. */
+#define LDB_MAX_LEN_DEFAULT 256 /* Default len limit for replies / var dumps. */
 struct ldbState {
     int fd;     /* Socket of the debugging client. */
     int active; /* Are we debugging EVAL right now? */
@@ -72,6 +72,8 @@ struct ldbState {
     int lines;  /* Number of lines in 'src'. */
     int currentline;    /* Current line number. */
     sds cbuf;   /* Debugger client command buffer. */
+    size_t maxlen;  /* Max var dump / reply length. */
+    int maxlen_hint_sent; /* Did we already hint about "set maxlen"? */
 } ldb;
 
 /* ---------------------------------------------------------------------------
@@ -573,7 +575,7 @@ int luaRedisGenericCommand(lua_State *lua, int raise_error) {
 
     /* If the debugger is active, log the reply from Redis. */
     if (ldb.active && ldb.step)
-        ldbLogRedisReply(reply,LDB_REPLY_MAX_LOG_LEN);
+        ldbLogRedisReply(reply);
 
     /* Sort the output array if needed, assuming it is a non-null multi bulk
      * reply as expected. */
@@ -1515,8 +1517,13 @@ void ldbEnable(client *c) {
     ldb.luabp = 0;
     sdsfree(ldb.cbuf);
     ldb.cbuf = sdsempty();
+    ldb.maxlen = LDB_MAX_LEN_DEFAULT;
+    ldb.maxlen_hint_sent = 0;
 }
 
+/* Exit debugging mode from the POV of client. This function is not enough
+ * to properly shut down a client debugging session, see ldbEndSession()
+ * for more information. */
 void ldbDisable(client *c) {
     c->flags &= ~(CLIENT_LUA_DEBUG|CLIENT_LUA_DEBUG_SYNC);
 }
@@ -1526,6 +1533,25 @@ void ldbLog(sds entry) {
     listAddNodeTail(ldb.logs,entry);
 }
 
+/* A version of ldbLog() which prevents producing logs greater than
+ * ldb.maxlen. The first time the limit is reached an hint is generated
+ * to inform the user that reply trimming can be disabled using the
+ * debugger "maxlen" command. */
+void ldbLogWithMaxLen(sds entry) {
+    int trimmed = 0;
+    if (ldb.maxlen && sdslen(entry) > ldb.maxlen) {
+        sdsrange(entry,0,ldb.maxlen-1);
+        entry = sdscatlen(entry," ...",4);
+        trimmed = 1;
+    }
+    ldbLog(entry);
+    if (trimmed && ldb.maxlen_hint_sent == 0) {
+        ldb.maxlen_hint_sent = 1;
+        ldbLog(sdsnew(
+        "<hint> The above reply was trimmed. Use 'maxlen 0' to disable trimming."));
+    }
+}
+
 /* Send ldb.logs to the debugging client as a multi-bulk reply
  * consisting of simple strings. Log entries which include newlines have them
  * replaced with spaces. The entries sent are also consumed. */
@@ -1901,7 +1927,7 @@ sds ldbCatStackValue(sds s, lua_State *lua, int idx) {
 void ldbLogStackValue(lua_State *lua, char *prefix) {
     sds s = sdsnew(prefix);
     s = ldbCatStackValue(s,lua,-1);
-    ldbLog(s);
+    ldbLogWithMaxLen(s);
 }
 
 char *ldbRedisProtocolToHuman_Int(sds *o, char *reply);
@@ -1979,17 +2005,10 @@ char *ldbRedisProtocolToHuman_MultiBulk(sds *o, char *reply) {
 /* Log a Redis reply as debugger output, in an human readable format.
  * If the resulting string is longer than 'len' plus a few more chars
  * used as prefix, it gets truncated. */
-void ldbLogRedisReply(char *reply, size_t maxlen) {
+void ldbLogRedisReply(char *reply) {
     sds log = sdsnew("<reply> ");
-    maxlen += sdslen(log);
     ldbRedisProtocolToHuman(&log,reply);
-    /* Trip and add ... if the length was reached, to hint the user it's not
-     * the whole reply. */
-    if (sdslen(log) > maxlen) {
-        sdsrange(log,0,maxlen-1);
-        log = sdscatlen(log," ...",4);
-    }
-    ldbLog(log);
+    ldbLogWithMaxLen(log);
 }
 
 /* Implements the "print <var>" command of the Lua debugger. It scans for Lua
@@ -2165,6 +2184,22 @@ void ldbTrace(lua_State *lua) {
     }
 }
 
+/* Impleemnts the debugger "maxlen" command. It just queries or sets the
+ * ldb.maxlen variable. */
+void ldbMaxlen(sds *argv, int argc) {
+    if (argc == 2) {
+        int newval = atoi(argv[1]);
+        ldb.maxlen_hint_sent = 1; /* User knows about this command. */
+        if (newval != 0 && newval <= 60) newval = 60;
+        ldb.maxlen = newval;
+    }
+    if (ldb.maxlen) {
+        ldbLog(sdscatprintf(sdsempty(),"<value> replies are truncated at %d bytes.",(int)ldb.maxlen));
+    } else {
+        ldbLog(sdscatprintf(sdsempty(),"<value> replies are unlimited."));
+    }
+}
+
 /* Read debugging commands from client. */
 void ldbRepl(lua_State *lua) {
     sds *argv;
@@ -2213,6 +2248,8 @@ ldbLog(sdsnew("[b]reak 0            Remove all breakpoints."));
 ldbLog(sdsnew("[t]race              Show a backtrace."));
 ldbLog(sdsnew("[e]eval <code>       Execute some Lua code (in a different callframe)."));
 ldbLog(sdsnew("[r]edis <cmd>        Execute a Redis command."));
+ldbLog(sdsnew("[m]axlen [len]       Trim logged Redis replies and Lua var dumps to len."));
+ldbLog(sdsnew("                     Specifying zero as <len> means unlimited."));
 ldbLog(sdsnew("[a]abort             Stop the execution of the script. In sync"));
 ldbLog(sdsnew("                     mode dataset changes will be retained."));
 ldbLog(sdsnew(""));
@@ -2230,6 +2267,9 @@ ldbLog(sdsnew("                     in the next line of code."));
         } else if (!strcasecmp(argv[0],"t") || !strcasecmp(argv[0],"trace")) {
             ldbTrace(lua);
             ldbSendLogs();
+        } else if (!strcasecmp(argv[0],"m") || !strcasecmp(argv[0],"maxlen")) {
+            ldbMaxlen(argv,argc);
+            ldbSendLogs();
         } else if (!strcasecmp(argv[0],"b") || !strcasecmp(argv[0],"break")) {
             ldbBreak(argv,argc);
             ldbSendLogs();