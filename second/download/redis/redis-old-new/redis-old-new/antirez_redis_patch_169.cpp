@@ -997,7 +997,7 @@ int rdbSaveBackground(char *filename) {
     pid_t childpid;
     long long start;
 
-    if (server.rdb_child_pid != -1) return C_ERR;
+    if (server.aof_child_pid != -1 || server.rdb_child_pid != -1) return C_ERR;
 
     server.dirty_before_bgsave = server.dirty;
     server.lastbgsave_try = time(NULL);
@@ -1687,7 +1687,7 @@ int rdbSaveToSlavesSockets(void) {
     long long start;
     int pipefds[2];
 
-    if (server.rdb_child_pid != -1) return C_ERR;
+    if (server.aof_child_pid != -1 || server.rdb_child_pid != -1) return C_ERR;
 
     /* Before to fork, create a pipe that will be used in order to
      * send back to the parent the IDs of the slaves that successfully
@@ -1842,11 +1842,33 @@ void saveCommand(client *c) {
     }
 }
 
+/* BGSAVE [SCHEDULE] */
 void bgsaveCommand(client *c) {
+    int schedule = 0;
+
+    /* The SCHEDULE option changes the behavior of BGSAVE when an AOF rewrite
+     * is in progress. Instead of returning an error a BGSAVE gets scheduled. */
+    if (c->argc > 1) {
+        if (c->argc == 2 && !strcasecmp(c->argv[1]->ptr,"schedule")) {
+            schedule = 1;
+        } else {
+            addReply(c,shared.syntaxerr);
+            return;
+        }
+    }
+
     if (server.rdb_child_pid != -1) {
         addReplyError(c,"Background save already in progress");
     } else if (server.aof_child_pid != -1) {
-        addReplyError(c,"Can't BGSAVE while AOF log rewriting is in progress");
+        if (schedule) {
+            server.rdb_bgsave_scheduled = 1;
+            addReplyStatus(c,"Background saving scheduled");
+        } else {
+            addReplyError(c,
+                "An AOF log rewriting in progress: can't BGSAVE right now. "
+                "Use BGSAVE SCHEDULE in order to schedule a BGSAVE whenver "
+                "possible.");
+        }
     } else if (rdbSaveBackground(server.rdb_filename) == C_OK) {
         addReplyStatus(c,"Background saving started");
     } else {