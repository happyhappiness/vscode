@@ -544,6 +544,8 @@ void syncCommand(client *c) {
 
     /* Here we need to check if there is a background saving operation
      * in progress, or if it is required to start one */
+
+    /* CASE 1: BGSAVE is in progress and replication target is disk. */
     if (server.rdb_child_pid != -1 &&
         server.rdb_child_type == RDB_CHILD_TYPE_DISK)
     {
@@ -572,6 +574,8 @@ void syncCommand(client *c) {
             c->replstate = SLAVE_STATE_WAIT_BGSAVE_START;
             serverLog(LL_NOTICE,"Waiting for next BGSAVE for SYNC");
         }
+
+    /* CASE 2: BGSAVE is in progress and replication target is socket. */
     } else if (server.rdb_child_pid != -1 &&
                server.rdb_child_type == RDB_CHILD_TYPE_SOCKET)
     {
@@ -580,6 +584,8 @@ void syncCommand(client *c) {
          * in order to synchronize. */
         c->replstate = SLAVE_STATE_WAIT_BGSAVE_START;
         serverLog(LL_NOTICE,"Waiting for next BGSAVE for SYNC");
+
+    /* CASE 3: There is no BGSAVE is progress. */
     } else {
         if (server.repl_diskless_sync) {
             /* Diskless replication RDB child is created inside
@@ -589,7 +595,8 @@ void syncCommand(client *c) {
             if (server.repl_diskless_sync_delay)
                 serverLog(LL_NOTICE,"Delay next BGSAVE for SYNC");
         } else {
-            /* Ok we don't have a BGSAVE in progress, let's start one. */
+            /* Target is disk and we don't have a BGSAVE in progress,
+             * let's start one. */
             if (startBgsaveForReplication() != C_OK) {
                 serverLog(LL_NOTICE,"Replication failed, can't BGSAVE");
                 addReplyError(c,"Unable to perform background save");