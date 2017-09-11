@@ -1201,10 +1201,11 @@ int serverCron(struct aeEventLoop *eventLoop, long long id, void *clientData) {
             } else if (pid == server.aof_child_pid) {
                 backgroundRewriteDoneHandler(exitcode,bysignal);
             } else {
-                serverLog(LL_WARNING,
-                    "Warning, detected child with unmatched pid: %ld"
-                    " (EVAL forked debugging session?)",
-                    (long)pid);
+                if (!ldbRemoveChild(pid)) {
+                    serverLog(LL_WARNING,
+                        "Warning, detected child with unmatched pid: %ld",
+                        (long)pid);
+                }
             }
             updateDictResizePolicy();
         }
@@ -2528,6 +2529,9 @@ int prepareForShutdown(int flags) {
 
     serverLog(LL_WARNING,"User requested shutdown...");
 
+    /* Kill all the Lua debugger forked sessions. */
+    ldbKillForkedSessions();
+
     /* Kill the saving child if there is a background saving in progress.
        We want to avoid race conditions, for instance our saving child may
        overwrite the synchronous saving did by SHUTDOWN. */