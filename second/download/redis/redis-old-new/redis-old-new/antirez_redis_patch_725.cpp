@@ -1292,11 +1292,11 @@ void backgroundSaveDoneHandlerSocket(int exitcode, int bysignal) {
     server.rdb_save_time_start = -1;
 
     /* If the child returns an OK exit code, read the set of slave client
-     * IDs that received the full RDB payload, closing all the slaves
-     * which are not among the ones listed.
+     * IDs and the associated status code. We'll terminate all the slaves
+     * in error state.
      *
      * If the process returned an error, consider the list of slaves that
-     * can continue to be emtpy, so that it's just a speical case of the
+     * can continue to be emtpy, so that it's just a special case of the
      * normal code path. */
     ok_slaves = zmalloc(sizeof(uint64_t)); /* Make space for the count. */
     ok_slaves[0] = 0;
@@ -1306,7 +1306,7 @@ void backgroundSaveDoneHandlerSocket(int exitcode, int bysignal) {
         if (read(server.rdb_pipe_read_result_from_child, ok_slaves, readlen) ==
                  readlen)
         {
-            readlen = ok_slaves[0]*sizeof(uint64_t);
+            readlen = ok_slaves[0]*sizeof(uint64_t)*2;
 
             /* Make space for enough elements as specified by the first
              * uint64_t element in the array. */
@@ -1334,14 +1334,23 @@ void backgroundSaveDoneHandlerSocket(int exitcode, int bysignal) {
 
         if (slave->replstate == REDIS_REPL_WAIT_BGSAVE_END) {
             uint64_t j;
+            int errorcode = 0;
 
+            /* Search for the slave ID in the reply. In order for a slave to
+             * continue the replication process, we need to find it in the list,
+             * and it must have an error code set to 0 (which means success). */
             for (j = 0; j < ok_slaves[0]; j++) {
-                if (slave->id == ok_slaves[j+1]) break; /* Found in OK list. */
+                if (slave->id == ok_slaves[2*j+1]) {
+                    errorcode = ok_slaves[2*j+2];
+                    break; /* Found in slaves list. */
+                }
             }
-            if (j == ok_slaves[0]) {
+            if (j == ok_slaves[0] || errorcode != 0) {
                 redisLog(REDIS_WARNING,
-                "Closing slave %llu: child->slave RDB transfer failed.",
-                slave->id);
+                "Closing slave %llu: child->slave RDB transfer failed: %s",
+                    slave->id,
+                    (errorcode == 0) ? "RDB transfer child aborted"
+                                     : strerror(errorcode));
                 freeClient(slave);
             } else {
                 redisLog(REDIS_WARNING,
@@ -1448,29 +1457,34 @@ int rdbSaveToSlavesSockets(void) {
             /* If we are returning OK, at least one slave was served
              * with the RDB file as expected, so we need to send a report
              * to the parent via the pipe. The format of the message is:
-             * just an array of uint64_t integers (to avoid alignment concerns),
-             * where the first element is the number of uint64_t elements
-             * that follows, representing slave client IDs that were
-             * successfully served. */
-            void *msg = zmalloc(sizeof(uint64_t)*(1+numfds));
+             *
+             * <len> <slave[0].id> <slave[0].error> ...
+             *
+             * len, slave IDs, and slave errors, are all uint64_t integers,
+             * so basically the reply is composed of 64 bits for the len field
+             * plus 2 additional 64 bit integers for each entry, for a total
+             * of 'len' entries.
+             *
+             * The 'id' represents the slave's client ID, so that the master
+             * can match the report with a specific slave, and 'error' is
+             * set to 0 if the replication process terminated with a success
+             * or the error code if an error occurred. */
+            void *msg = zmalloc(sizeof(uint64_t)*(1+2*numfds));
             uint64_t *len = msg;
             uint64_t *ids = len+1;
             int j, msglen;
 
-            *len = 0;
+            *len = numfds;
             for (j = 0; j < numfds; j++) {
-                /* No error? Add it. */
-                if (slave_sockets.io.fdset.state[j] == 0) {
-                    ids[*len] = clientids[j];
-                    (*len)++;
-                }
+                *ids++ = clientids[j];
+                *ids++ = slave_sockets.io.fdset.state[j];
             }
 
             /* Write the message to the parent. If we have no good slaves or
              * we are unable to transfer the message to the parent, we exit
              * with an error so that the parent will abort the replication
              * process with all the childre that were waiting. */
-            msglen = sizeof(uint64_t)*(1+(*len));
+            msglen = sizeof(uint64_t)*(1+2*numfds);
             if (*len == 0 ||
                 write(server.rdb_pipe_write_result_to_parent,msg,msglen)
                 != msglen)