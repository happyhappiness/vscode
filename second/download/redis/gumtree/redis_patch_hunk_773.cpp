         return PSYNC_WAIT_REPLY;
     }
 
     aeDeleteFileEvent(server.el,fd,AE_READABLE);
 
     if (!strncmp(reply,"+FULLRESYNC",11)) {
-        char *runid = NULL, *offset = NULL;
+        char *replid = NULL, *offset = NULL;
 
         /* FULL RESYNC, parse the reply in order to extract the run id
          * and the replication offset. */
-        runid = strchr(reply,' ');
-        if (runid) {
-            runid++;
-            offset = strchr(runid,' ');
+        replid = strchr(reply,' ');
+        if (replid) {
+            replid++;
+            offset = strchr(replid,' ');
             if (offset) offset++;
         }
-        if (!runid || !offset || (offset-runid-1) != CONFIG_RUN_ID_SIZE) {
+        if (!replid || !offset || (offset-replid-1) != CONFIG_RUN_ID_SIZE) {
             serverLog(LL_WARNING,
                 "Master replied with wrong +FULLRESYNC syntax.");
             /* This is an unexpected condition, actually the +FULLRESYNC
              * reply means that the master supports PSYNC, but the reply
              * format seems wrong. To stay safe we blank the master
-             * runid to make sure next PSYNCs will fail. */
-            memset(server.repl_master_runid,0,CONFIG_RUN_ID_SIZE+1);
+             * replid to make sure next PSYNCs will fail. */
+            memset(server.master_replid,0,CONFIG_RUN_ID_SIZE+1);
         } else {
-            memcpy(server.repl_master_runid, runid, offset-runid-1);
-            server.repl_master_runid[CONFIG_RUN_ID_SIZE] = '\0';
-            server.repl_master_initial_offset = strtoll(offset,NULL,10);
+            memcpy(server.master_replid, replid, offset-replid-1);
+            server.master_replid[CONFIG_RUN_ID_SIZE] = '\0';
+            server.master_initial_offset = strtoll(offset,NULL,10);
             serverLog(LL_NOTICE,"Full resync from master: %s:%lld",
-                server.repl_master_runid,
-                server.repl_master_initial_offset);
+                server.master_replid,
+                server.master_initial_offset);
         }
         /* We are going to full resync, discard the cached master structure. */
         replicationDiscardCachedMaster();
         sdsfree(reply);
         return PSYNC_FULLRESYNC;
     }
 
     if (!strncmp(reply,"+CONTINUE",9)) {
-        /* Partial resync was accepted, set the replication state accordingly */
+        /* Partial resync was accepted. */
         serverLog(LL_NOTICE,
             "Successful partial resynchronization with master.");
+
+        /* Check the new replication ID advertised by the master. If it
+         * changed, we need to set the new ID as primary ID, and set or
+         * secondary ID as the old master ID up to the current offset, so
+         * that our sub-slaves will be able to PSYNC with us after a
+         * disconnection. */
+        char *start = reply+10;
+        char *end = reply+9;
+        while(end[0] != '\r' && end[0] != '\n' && end[0] != '\0') end++;
+        if (end-start == CONFIG_RUN_ID_SIZE) {
+            char new[CONFIG_RUN_ID_SIZE+1];
+            memcpy(new,start,CONFIG_RUN_ID_SIZE);
+            new[CONFIG_RUN_ID_SIZE] = '\0';
+
+            if (strcmp(new,server.cached_master->replid)) {
+                /* Master ID changed. */
+                serverLog(LL_WARNING,"Master replication ID changed to %s",new);
+
+                /* Set the old ID as our ID2, up to the current offset+1. */
+                memcpy(server.replid2,server.cached_master->replid,
+                    sizeof(server.replid2));
+                server.second_replid_offset = server.master_repl_offset+1;
+
+                /* Update the cached master ID and our own primary ID to the
+                 * new one. */
+                memcpy(server.replid,new,sizeof(server.replid));
+                memcpy(server.cached_master->replid,new,sizeof(server.replid));
+
+                /* Disconnect all the sub-slaves: they need to be notified. */
+                disconnectSlaves();
+            }
+        }
+
+        /* Setup the replication to continue. */
         sdsfree(reply);
         replicationResurrectCachedMaster(fd);
         return PSYNC_CONTINUE;
     }
 
-    /* If we reach this point we received either an error since the master does
-     * not understand PSYNC, or an unexpected reply from the master.
-     * Return PSYNC_NOT_SUPPORTED to the caller in both cases. */
+    /* If we reach this point we received either an error (since the master does
+     * not understand PSYNC or because it is in a special state and cannot
+     * serve our request), or an unexpected reply from the master.
+     *
+     * Return PSYNC_NOT_SUPPORTED on errors we don't understand, otherwise
+     * return PSYNC_TRY_LATER if we believe this is a transient error. */
+
+    if (!strncmp(reply,"-NOMASTERLINK",13) ||
+        !strncmp(reply,"-LOADING",8))
+    {
+        serverLog(LL_NOTICE,
+            "Master is currently unable to PSYNC "
+            "but should be in the future: %s", reply);
+        sdsfree(reply);
+        return PSYNC_TRY_LATER;
+    }
 
     if (strncmp(reply,"-ERR",4)) {
         /* If it's not an error, log the unexpected event. */
         serverLog(LL_WARNING,
             "Unexpected reply to PSYNC from master: %s", reply);
     } else {
