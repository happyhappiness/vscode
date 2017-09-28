             }
         }
     }
     if (startbgsave) startBgsaveForReplication(mincapa);
 }
 
+/* Change the current instance replication ID with a new, random one.
+ * This will prevent successful PSYNCs between this master and other
+ * slaves, so the command should be called when something happens that
+ * alters the current story of the dataset. */
+void changeReplicationId(void) {
+    getRandomHexChars(server.replid,CONFIG_RUN_ID_SIZE);
+    server.replid[CONFIG_RUN_ID_SIZE] = '\0';
+}
+
+/* Clear (invalidate) the secondary replication ID. This happens, for
+ * example, after a full resynchronization, when we start a new replication
+ * history. */
+void clearReplicationId2(void) {
+    memset(server.replid2,'0',sizeof(server.replid));
+    server.replid2[CONFIG_RUN_ID_SIZE] = '\0';
+    server.second_replid_offset = -1;
+}
+
+/* Use the current replication ID / offset as secondary replication
+ * ID, and change the current one in order to start a new history.
+ * This should be used when an instance is switched from slave to master
+ * so that it can serve PSYNC requests performed using the master
+ * replication ID. */
+void shiftReplicationId(void) {
+    memcpy(server.replid2,server.replid,sizeof(server.replid));
+    /* We set the second replid offset to the master offset + 1, since
+     * the slave will ask for the first byte it has not yet received, so
+     * we need to add one to the offset: for example if, as a slave, we are
+     * sure we have the same history as the master for 50 bytes, after we
+     * are turned into a master, we can accept a PSYNC request with offset
+     * 51, since the slave asking has the same history up to the 50th
+     * byte, and is asking for the new bytes starting at offset 51. */
+    server.second_replid_offset = server.master_repl_offset+1;
+    changeReplicationId();
+    serverLog(LL_WARNING,"Setting secondary replication ID to %s, valid up to offset: %lld. New replication ID is %s", server.replid2, server.second_replid_offset, server.replid);
+}
+
 /* ----------------------------------- SLAVE -------------------------------- */
 
 /* Returns 1 if the given replication state is a handshake state,
  * 0 otherwise. */
 int slaveIsInHandshakeState(void) {
     return server.repl_state >= REPL_STATE_RECEIVE_PONG &&
