@@ -45,6 +45,25 @@ char *redisProtocolToLuaType_Error(lua_State *lua, char *reply);
 char *redisProtocolToLuaType_MultiBulk(lua_State *lua, char *reply);
 int redis_math_random (lua_State *L);
 int redis_math_randomseed (lua_State *L);
+void ldbInit(void);
+void ldbDisable(client *c);
+void ldbEnable(client *c);
+void evalGenericCommandWithDebugging(client *c, int evalsha);
+void luaLdbLineHook(lua_State *lua, lua_Debug *ar);
+
+/* Debugger shared state is stored inside this global structure. */
+#define LDB_BREAKPOINTS_MAX 64
+struct ldbState {
+    int fd;     /* Socket of the debugging client. */
+    int active; /* Are we debugging EVAL right now? */
+    int forked; /* Is this a fork()ed debugging session? */
+    list *logs; /* List of messages to send to the client. */
+    list *traces; /* Messages about Redis commands executed since last stop.*/
+    int bp[LDB_BREAKPOINTS_MAX]; /* An array of breakpoints line numbers. */
+    int bpcount; /* Number of valid entries inside bp. */
+    int step;   /* Stop at next line ragardless of breakpoints. */
+    robj *src;  /* Lua script source code. */
+} ldb;
 
 /* ---------------------------------------------------------------------------
  * Utility functions.
@@ -821,6 +840,7 @@ void scriptingInit(int setup) {
         server.lua_timedout = 0;
         server.lua_always_replicate_commands = 0; /* Only DEBUG can change it.*/
         server.lua_time_limit = LUA_SCRIPT_TIME_LIMIT;
+        ldbInit();
     }
 
     luaLoadLibraries(lua);
@@ -1039,15 +1059,6 @@ int redis_math_randomseed (lua_State *L) {
 }
 
 /* ---------------------------------------------------------------------------
- * LDB: Redis Lua debugging facilities
- * ------------------------------------------------------------------------- */
-
-/* Enable debug mode of Lua scripts for this client. */
-void ldbEnable(client *c) {
-    c->flags |= CLIENT_LUA_DEBUG;
-}
-
-/* ---------------------------------------------------------------------------
  * EVAL and SCRIPT commands implementation
  * ------------------------------------------------------------------------- */
 
@@ -1214,13 +1225,21 @@ void evalGenericCommand(client *c, int evalsha) {
     /* Set a hook in order to be able to stop the script execution if it
      * is running for too much time.
      * We set the hook only if the time limit is enabled as the hook will
-     * make the Lua script execution slower. */
+     * make the Lua script execution slower.
+     *
+     * If we are debugging, we set instead a "line" hook so that the
+     * debugger is call-back at every line executed by the script. */
     server.lua_caller = c;
     server.lua_time_start = mstime();
     server.lua_kill = 0;
-    if (server.lua_time_limit > 0 && server.masterhost == NULL) {
+    if (server.lua_time_limit > 0 && server.masterhost == NULL &&
+        ldb.active == 0)
+    {
         lua_sethook(lua,luaMaskCountHook,LUA_MASKCOUNT,100000);
         delhook = 1;
+    } else if (ldb.active) {
+        lua_sethook(server.lua,luaLdbLineHook,LUA_MASKLINE,0);
+        delhook = 1;
     }
 
     /* At this point whether this script was never seen before or if it was
@@ -1229,7 +1248,7 @@ void evalGenericCommand(client *c, int evalsha) {
     err = lua_pcall(lua,0,1,-2);
 
     /* Perform some cleanup that we need to do both on error and success. */
-    if (delhook) lua_sethook(lua,luaMaskCountHook,0,0); /* Disable hook */
+    if (delhook) lua_sethook(lua,NULL,0,0); /* Disable hook */
     if (server.lua_timedout) {
         server.lua_timedout = 0;
         /* Restore the readable handler that was unregistered when the
@@ -1308,7 +1327,10 @@ void evalGenericCommand(client *c, int evalsha) {
 }
 
 void evalCommand(client *c) {
-    evalGenericCommand(c,0);
+    if (!(c->flags & CLIENT_LUA_DEBUG))
+        evalGenericCommand(c,0);
+    else
+        evalGenericCommandWithDebugging(c,0);
 }
 
 void evalShaCommand(client *c) {
@@ -1320,7 +1342,12 @@ void evalShaCommand(client *c) {
         addReply(c, shared.noscripterr);
         return;
     }
-    evalGenericCommand(c,1);
+    if (!(c->flags & CLIENT_LUA_DEBUG))
+        evalGenericCommand(c,1);
+    else {
+        addReplyError(c,"Please use EVAL instead of EVALSHA for debugging");
+        return;
+    }
 }
 
 void scriptCommand(client *c) {
@@ -1366,12 +1393,149 @@ void scriptCommand(client *c) {
             server.lua_kill = 1;
             addReply(c,shared.ok);
         }
-    } else if (c->argc == 2 && !strcasecmp(c->argv[1]->ptr,"debug")) {
-        ldbEnable(c);
-        addReply(c,shared.ok);
+    } else if (c->argc == 3 && !strcasecmp(c->argv[1]->ptr,"debug")) {
+        if (clientHasPendingReplies(c)) {
+            addReplyError(c,"SCRIPT DEBUG must be called outside a pipeline");
+            return;
+        }
+        if (!strcasecmp(c->argv[2]->ptr,"no")) {
+            ldbDisable(c);
+        } else if (!strcasecmp(c->argv[2]->ptr,"yes")) {
+            ldbEnable(c);
+            addReply(c,shared.ok);
+        } else if (!strcasecmp(c->argv[2]->ptr,"sync")) {
+            ldbEnable(c);
+            addReply(c,shared.ok);
+            c->flags |= CLIENT_LUA_DEBUG_SYNC;
+        } else {
+            addReplyError(c,"Use SCRIPT DEBUG yes/async/no");
+        }
     } else {
         addReplyError(c, "Unknown SCRIPT subcommand or wrong # of args.");
     }
 }
 
+/* ---------------------------------------------------------------------------
+ * LDB: Redis Lua debugging facilities
+ * ------------------------------------------------------------------------- */
+
+/* Initialize Lua debugger data structures. */
+void ldbInit(void) {
+    ldb.fd = -1;
+    ldb.active = 0;
+    ldb.logs = listCreate();
+    ldb.traces = listCreate();
+    listSetFreeMethod(ldb.logs,(void (*)(void*))sdsfree);
+    listSetFreeMethod(ldb.traces, (void (*)(void*))sdsfree);
+    ldb.src = NULL;
+}
+
+/* Remove all the pending messages in the specified list. */
+void ldbFlushLog(list *log) {
+    listNode *ln;
+
+    while((ln = listFirst(log)) != NULL)
+        listDelNode(log,ln);
+}
+
+/* Enable debug mode of Lua scripts for this client. */
+void ldbEnable(client *c) {
+    c->flags |= CLIENT_LUA_DEBUG;
+    ldbFlushLog(ldb.logs);
+    ldbFlushLog(ldb.traces);
+    ldb.fd = c->fd;
+    ldb.step = 0;
+    ldb.bpcount = 0;
+}
+
+void ldbDisable(client *c) {
+    c->flags &= ~(CLIENT_LUA_DEBUG|CLIENT_LUA_DEBUG_SYNC);
+}
+
+/* Append a log entry to the specified LDB log. */
+void ldbLog(list *log, sds entry) {
+    listAddNodeTail(log,entry);
+}
+
+/* Send ldb.logs and ldb.traces to the debugging client as a multi-bulk
+ * reply consisting of simple strings. Log entries which include newlines
+ * have them replaced with spaces. The entries sent are also consumed. */
+void ldbWriteLogs(void) {
+}
+
+/* Start a debugging session before calling EVAL implementation.
+ * The techique we use is to capture the client socket file descriptor,
+ * in order to perform direct I/O with it from within Lua hooks. This
+ * way we don't have to re-enter Redis in order to handle I/O.
+ *
+ * The function returns 1 if the caller should proceed to call EVAL,
+ * and 0 if instead the caller should abort the operation (this happens
+ * for the parent in a forked session, since it's up to the children
+ * to continue, or when fork returned an error).
+ *
+ * The caller should call ldbEndSession() only if ldbStartSession()
+ * returned 1. */
+int ldbStartSession(client *c) {
+    ldb.forked = (c->flags & CLIENT_LUA_DEBUG_SYNC) == 0;
+    if (ldb.forked) {
+        pid_t cp = fork();
+        if (cp == -1) {
+            addReplyError(c,"Fork() failed: can't run EVAL in debugging mode.");
+            return 0;
+        } else if (cp == 0) {
+            /* Child */
+            serverLog(LL_WARNING,"Redis forked for debugging eval");
+            closeListeningSockets(0);
+        } else {
+            /* Parent */
+            freeClientAsync(c); /* Close the client in the parent side. */
+            return 0;
+        }
+    }
+
+    /* Setup our debugging session. */
+    anetBlock(NULL,ldb.fd);
+    ldb.active = 1;
+    ldb.src = c->argv[1]; /* First argument of EVAL is the script itself. */
+    incrRefCount(ldb.src);
+    return 1;
+}
+
+/* End a debugging session after the EVAL call with debugging enabled
+ * returned. */
+void ldbEndSession(client *c) {
+    /* If it's a fork()ed session, we just exit. */
+    if (ldb.forked) {
+        writeToClient(c->fd, c, 0);
+        serverLog(LL_WARNING,"Lua debugging session child exiting");
+        exitFromChild(0);
+    }
+
+    /* Otherwise let's restore client's state. */
+    anetNonBlock(NULL,ldb.fd);
+    ldb.active = 0;
+    decrRefCount(ldb.src);
+}
+
+/* Wrapper for EVAL / EVALSHA that enables debugging, and makes sure
+ * that when EVAL returns, whatever happened, the session is ended. */
+void evalGenericCommandWithDebugging(client *c, int evalsha) {
+    if (ldbStartSession(c)) {
+        evalGenericCommand(c,evalsha);
+        ldbEndSession(c);
+    } else {
+        ldbDisable(c);
+    }
+}
+
+/* This is the core of our Lua debugger, called each time Lua is about
+ * to start executing a new line. */
+void luaLdbLineHook(lua_State *lua, lua_Debug *ar) {
+    lua_getstack(lua,0,ar);
+    lua_getinfo(lua,"Sl",ar);
+    if(strstr(ar->short_src,"user_script") != NULL)
+        printf("%s %d\n", ar->short_src, (int) ar->currentline);
+}
+
+
 