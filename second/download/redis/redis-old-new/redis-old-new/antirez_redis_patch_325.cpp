@@ -1198,7 +1198,13 @@ int serverCron(struct aeEventLoop *eventLoop, long long id, void *clientData) {
 
             if (WIFSIGNALED(statloc)) bysignal = WTERMSIG(statloc);
 
-            if (pid == server.rdb_child_pid) {
+            if (pid == -1) {
+                serverLog(LL_WARNING,"wait3() returned an error: %s. "
+                    "rdb_child_pid = %d, aof_child_pid = %d",
+                    strerror(errno),
+                    (int) server.rdb_child_pid,
+                    (int) server.aof_child_pid);
+            } else if (pid == server.rdb_child_pid) {
                 backgroundSaveDoneHandler(exitcode,bysignal);
             } else if (pid == server.aof_child_pid) {
                 backgroundRewriteDoneHandler(exitcode,bysignal);