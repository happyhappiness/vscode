@@ -63,6 +63,7 @@ struct ldbState {
     int forked; /* Is this a fork()ed debugging session? */
     list *logs; /* List of messages to send to the client. */
     list *traces; /* Messages about Redis commands executed since last stop.*/
+    list *children; /* All forked debugging sessions pids. */
     int bp[LDB_BREAKPOINTS_MAX]; /* An array of breakpoints line numbers. */
     int bpcount; /* Number of valid entries inside bp. */
     int step;   /* Stop at next line ragardless of breakpoints. */
@@ -1489,6 +1490,7 @@ void ldbInit(void) {
     ldb.active = 0;
     ldb.logs = listCreate();
     listSetFreeMethod(ldb.logs,(void (*)(void*))sdsfree);
+    ldb.children = listCreate();
     ldb.src = NULL;
     ldb.lines = 0;
     ldb.cbuf = sdsempty();
@@ -1560,11 +1562,22 @@ int ldbStartSession(client *c) {
             addReplyError(c,"Fork() failed: can't run EVAL in debugging mode.");
             return 0;
         } else if (cp == 0) {
-            /* Child */
+            /* Child. Let's ignore important signals handled by the parent. */
+            struct sigaction act;
+            sigemptyset(&act.sa_mask);
+            act.sa_flags = 0;
+            act.sa_handler = SIG_IGN;
+            sigaction(SIGTERM, &act, NULL);
+            sigaction(SIGINT, &act, NULL);
+
+            /* Log the creation of the child and close the listening
+             * socket to make sure if the parent crashes a reset is sent
+             * to the clients. */
             serverLog(LL_WARNING,"Redis forked for debugging eval");
             closeListeningSockets(0);
         } else {
             /* Parent */
+            listAddNodeTail(ldb.children,(void*)(unsigned long)cp);
             freeClientAsync(c); /* Close the client in the parent side. */
             return 0;
         }
@@ -1618,6 +1631,33 @@ void ldbEndSession(client *c) {
     ldb.active = 0;
 }
 
+/* If the specified pid is among the list of children spawned for
+ * forked debugging sessions, it is removed from the children list.
+ * If the pid was found non-zero is returned. */
+int ldbRemoveChild(pid_t pid) {
+    listNode *ln = listSearchKey(ldb.children,(void*)(unsigned long)pid);
+    if (ln) {
+        listDelNode(ldb.children,ln);
+        return 1;
+    }
+    return 0;
+}
+
+/* Kill all the forked sessions. */
+void ldbKillForkedSessions(void) {
+    listIter li;
+    listNode *ln;
+
+    listRewind(ldb.children,&li);
+    while((ln = listNext(&li))) {
+        pid_t pid = (unsigned long) ln->value;
+        serverLog(LL_WARNING,"Killing debugging session %ld",(long)pid);
+        kill(pid,SIGKILL);
+    }
+    listRelease(ldb.children);
+    ldb.children = listCreate();
+}
+
 /* Wrapper for EVAL / EVALSHA that enables debugging, and makes sure
  * that when EVAL returns, whatever happened, the session is ended. */
 void evalGenericCommandWithDebugging(client *c, int evalsha) {