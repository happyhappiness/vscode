@@ -85,8 +85,8 @@ int clusterBumpConfigEpochWithoutConsensus(void);
  *
  * If the file does not exist or is zero-length (this may happen because
  * when we lock the nodes.conf file, we create a zero-length one for the
- * sake of locking if it does not already exist), REDIS_ERR is returned.
- * If the configuration was loaded from the file, REDIS_OK is returned. */
+ * sake of locking if it does not already exist), C_ERR is returned.
+ * If the configuration was loaded from the file, C_OK is returned. */
 int clusterLoadConfig(char *filename) {
     FILE *fp = fopen(filename,"r");
     struct stat sb;
@@ -95,7 +95,7 @@ int clusterLoadConfig(char *filename) {
 
     if (fp == NULL) {
         if (errno == ENOENT) {
-            return REDIS_ERR;
+            return C_ERR;
         } else {
             serverLog(REDIS_WARNING,
                 "Loading the cluster node config from %s: %s",
@@ -104,11 +104,11 @@ int clusterLoadConfig(char *filename) {
         }
     }
 
-    /* Check if the file is zero-length: if so return REDIS_ERR to signal
+    /* Check if the file is zero-length: if so return C_ERR to signal
      * we have to write the config. */
     if (fstat(fileno(fp),&sb) != -1 && sb.st_size == 0) {
         fclose(fp);
-        return REDIS_ERR;
+        return C_ERR;
     }
 
     /* Parse the file. Note that single lines of the cluster config file can
@@ -272,7 +272,7 @@ int clusterLoadConfig(char *filename) {
     if (clusterGetMaxEpoch() > server.cluster->currentEpoch) {
         server.cluster->currentEpoch = clusterGetMaxEpoch();
     }
-    return REDIS_OK;
+    return C_OK;
 
 fmterr:
     serverLog(REDIS_WARNING,
@@ -355,8 +355,8 @@ void clusterSaveConfigOrDie(int do_fsync) {
  * in-place, reopening the file, and writing to it in place (later adjusting
  * the length with ftruncate()).
  *
- * On success REDIS_OK is returned, otherwise an error is logged and
- * the function returns REDIS_ERR to signal a lock was not acquired. */
+ * On success C_OK is returned, otherwise an error is logged and
+ * the function returns C_ERR to signal a lock was not acquired. */
 int clusterLockConfig(char *filename) {
 /* flock() does not exist on Solaris
  * and a fcntl-based solution won't help, as we constantly re-open that file,
@@ -371,7 +371,7 @@ int clusterLockConfig(char *filename) {
         serverLog(REDIS_WARNING,
             "Can't open %s in order to acquire a lock: %s",
             filename, strerror(errno));
-        return REDIS_ERR;
+        return C_ERR;
     }
 
     if (flock(fd,LOCK_EX|LOCK_NB) == -1) {
@@ -386,13 +386,13 @@ int clusterLockConfig(char *filename) {
                 "Impossible to lock %s: %s", filename, strerror(errno));
         }
         close(fd);
-        return REDIS_ERR;
+        return C_ERR;
     }
     /* Lock acquired: leak the 'fd' by not closing it, so that we'll retain the
      * lock to the file as long as the process exists. */
 #endif /* __sun */
 
-    return REDIS_OK;
+    return C_OK;
 }
 
 void clusterInit(void) {
@@ -420,11 +420,11 @@ void clusterInit(void) {
 
     /* Lock the cluster config file to make sure every node uses
      * its own nodes.conf. */
-    if (clusterLockConfig(server.cluster_configfile) == REDIS_ERR)
+    if (clusterLockConfig(server.cluster_configfile) == C_ERR)
         exit(1);
 
     /* Load or create a new nodes configuration. */
-    if (clusterLoadConfig(server.cluster_configfile) == REDIS_ERR) {
+    if (clusterLoadConfig(server.cluster_configfile) == C_ERR) {
         /* No configuration found. We will just use the random name provided
          * by the createClusterNode() function. */
         myself = server.cluster->myself =
@@ -452,7 +452,7 @@ void clusterInit(void) {
     }
 
     if (listenToPort(server.port+REDIS_CLUSTER_PORT_INCR,
-        server.cfd,&server.cfd_count) == REDIS_ERR)
+        server.cfd,&server.cfd_count) == C_ERR)
     {
         exit(1);
     } else {
@@ -783,23 +783,23 @@ int clusterNodeRemoveSlave(clusterNode *master, clusterNode *slave) {
                         (sizeof(*master->slaves) * remaining_slaves));
             }
             master->numslaves--;
-            return REDIS_OK;
+            return C_OK;
         }
     }
-    return REDIS_ERR;
+    return C_ERR;
 }
 
 int clusterNodeAddSlave(clusterNode *master, clusterNode *slave) {
     int j;
 
     /* If it's already a slave, don't add it again. */
     for (j = 0; j < master->numslaves; j++)
-        if (master->slaves[j] == slave) return REDIS_ERR;
+        if (master->slaves[j] == slave) return C_ERR;
     master->slaves = zrealloc(master->slaves,
         sizeof(clusterNode*)*(master->numslaves+1));
     master->slaves[master->numslaves] = slave;
     master->numslaves++;
-    return REDIS_OK;
+    return C_OK;
 }
 
 void clusterNodeResetSlaves(clusterNode *n) {
@@ -849,7 +849,7 @@ int clusterAddNode(clusterNode *node) {
 
     retval = dictAdd(server.cluster->nodes,
             sdsnewlen(node->name,REDIS_CLUSTER_NAMELEN), node);
-    return (retval == DICT_OK) ? REDIS_OK : REDIS_ERR;
+    return (retval == DICT_OK) ? C_OK : C_ERR;
 }
 
 /* Remove a node from the cluster. The functio performs the high level
@@ -949,8 +949,8 @@ uint64_t clusterGetMaxEpoch(void) {
  * 3) Persist the configuration on disk before sending packets with the
  *    new configuration.
  *
- * If the new config epoch is generated and assigend, REDIS_OK is returned,
- * otherwise REDIS_ERR is returned (since the node has already the greatest
+ * If the new config epoch is generated and assigend, C_OK is returned,
+ * otherwise C_ERR is returned (since the node has already the greatest
  * configuration around) and no operation is performed.
  *
  * Important note: this function violates the principle that config epochs
@@ -983,9 +983,9 @@ int clusterBumpConfigEpochWithoutConsensus(void) {
         serverLog(REDIS_WARNING,
             "New configEpoch set to %llu",
             (unsigned long long) myself->configEpoch);
-        return REDIS_OK;
+        return C_OK;
     } else {
-        return REDIS_ERR;
+        return C_ERR;
     }
 }
 
@@ -3343,26 +3343,26 @@ int clusterNodeGetSlotBit(clusterNode *n, int slot) {
 }
 
 /* Add the specified slot to the list of slots that node 'n' will
- * serve. Return REDIS_OK if the operation ended with success.
+ * serve. Return C_OK if the operation ended with success.
  * If the slot is already assigned to another instance this is considered
- * an error and REDIS_ERR is returned. */
+ * an error and C_ERR is returned. */
 int clusterAddSlot(clusterNode *n, int slot) {
-    if (server.cluster->slots[slot]) return REDIS_ERR;
+    if (server.cluster->slots[slot]) return C_ERR;
     clusterNodeSetSlotBit(n,slot);
     server.cluster->slots[slot] = n;
-    return REDIS_OK;
+    return C_OK;
 }
 
 /* Delete the specified slot marking it as unassigned.
- * Returns REDIS_OK if the slot was assigned, otherwise if the slot was
- * already unassigned REDIS_ERR is returned. */
+ * Returns C_OK if the slot was assigned, otherwise if the slot was
+ * already unassigned C_ERR is returned. */
 int clusterDelSlot(int slot) {
     clusterNode *n = server.cluster->slots[slot];
 
-    if (!n) return REDIS_ERR;
+    if (!n) return C_ERR;
     serverAssert(clusterNodeClearSlotBit(n,slot) == 1);
     server.cluster->slots[slot] = NULL;
-    return REDIS_OK;
+    return C_OK;
 }
 
 /* Delete all the slots associated with the specified node.
@@ -3505,13 +3505,13 @@ void clusterUpdateState(void) {
  *       this lots, we set the slots as IMPORTING from our point of view
  *       in order to justify we have those slots, and in order to make
  *       redis-trib aware of the issue, so that it can try to fix it.
- * 2) If we find data in a DB different than DB0 we return REDIS_ERR to
+ * 2) If we find data in a DB different than DB0 we return C_ERR to
  *    signal the caller it should quit the server with an error message
  *    or take other actions.
  *
- * The function always returns REDIS_OK even if it will try to correct
+ * The function always returns C_OK even if it will try to correct
  * the error described in "1". However if data is found in DB different
- * from DB0, REDIS_ERR is returned.
+ * from DB0, C_ERR is returned.
  *
  * The function also uses the logging facility in order to warn the user
  * about desynchronizations between the data we have in memory and the
@@ -3522,11 +3522,11 @@ int verifyClusterConfigWithData(void) {
 
     /* If this node is a slave, don't perform the check at all as we
      * completely depend on the replication stream. */
-    if (nodeIsSlave(myself)) return REDIS_OK;
+    if (nodeIsSlave(myself)) return C_OK;
 
     /* Make sure we only have keys in DB0. */
     for (j = 1; j < server.dbnum; j++) {
-        if (dictSize(server.db[j].dict)) return REDIS_ERR;
+        if (dictSize(server.db[j].dict)) return C_ERR;
     }
 
     /* Check that all the slots we see populated memory have a corresponding
@@ -3557,7 +3557,7 @@ int verifyClusterConfigWithData(void) {
         }
     }
     if (update_config) clusterSaveConfigOrDie(1);
-    return REDIS_OK;
+    return C_OK;
 }
 
 /* -----------------------------------------------------------------------------
@@ -3725,7 +3725,7 @@ sds clusterGenNodesDescription(int filter) {
 int getSlotOrReply(client *c, robj *o) {
     long long slot;
 
-    if (getLongLongFromObject(o,&slot) != REDIS_OK ||
+    if (getLongLongFromObject(o,&slot) != C_OK ||
         slot < 0 || slot >= REDIS_CLUSTER_SLOTS)
     {
         addReplyError(c,"Invalid or out of range slot");
@@ -3813,7 +3813,7 @@ void clusterCommand(client *c) {
     if (!strcasecmp(c->argv[1]->ptr,"meet") && c->argc == 4) {
         long long port;
 
-        if (getLongLongFromObject(c->argv[3], &port) != REDIS_OK) {
+        if (getLongLongFromObject(c->argv[3], &port) != C_OK) {
             addReplyErrorFormat(c,"Invalid TCP port specified: %s",
                                 (char*)c->argv[3]->ptr);
             return;
@@ -3894,7 +3894,7 @@ void clusterCommand(client *c) {
 
                 retval = del ? clusterDelSlot(j) :
                                clusterAddSlot(myself,j);
-                serverAssertWithInfo(c,NULL,retval == REDIS_OK);
+                serverAssertWithInfo(c,NULL,retval == C_OK);
             }
         }
         zfree(slots);
@@ -3977,7 +3977,7 @@ void clusterCommand(client *c) {
                  * failover happens at the same time we close the slot, the
                  * configEpoch collision resolution will fix it assigning
                  * a different epoch to each node. */
-                if (clusterBumpConfigEpochWithoutConsensus() == REDIS_OK) {
+                if (clusterBumpConfigEpochWithoutConsensus() == C_OK) {
                     serverLog(REDIS_WARNING,
                         "configEpoch updated after importing slot %d", slot);
                 }
@@ -4061,7 +4061,7 @@ void clusterCommand(client *c) {
         /* CLUSTER COUNTKEYSINSLOT <slot> */
         long long slot;
 
-        if (getLongLongFromObjectOrReply(c,c->argv[2],&slot,NULL) != REDIS_OK)
+        if (getLongLongFromObjectOrReply(c,c->argv[2],&slot,NULL) != C_OK)
             return;
         if (slot < 0 || slot >= REDIS_CLUSTER_SLOTS) {
             addReplyError(c,"Invalid slot");
@@ -4074,10 +4074,10 @@ void clusterCommand(client *c) {
         unsigned int numkeys, j;
         robj **keys;
 
-        if (getLongLongFromObjectOrReply(c,c->argv[2],&slot,NULL) != REDIS_OK)
+        if (getLongLongFromObjectOrReply(c,c->argv[2],&slot,NULL) != C_OK)
             return;
         if (getLongLongFromObjectOrReply(c,c->argv[3],&maxkeys,NULL)
-            != REDIS_OK)
+            != C_OK)
             return;
         if (slot < 0 || slot >= REDIS_CLUSTER_SLOTS || maxkeys < 0) {
             addReplyError(c,"Invalid slot or number of keys");
@@ -4245,7 +4245,7 @@ void clusterCommand(client *c) {
          * resolution system which is too slow when a big cluster is created. */
         long long epoch;
 
-        if (getLongLongFromObjectOrReply(c,c->argv[2],&epoch,NULL) != REDIS_OK)
+        if (getLongLongFromObjectOrReply(c,c->argv[2],&epoch,NULL) != C_OK)
             return;
 
         if (epoch < 0) {
@@ -4339,25 +4339,25 @@ void createDumpPayload(rio *payload, robj *o) {
 
 /* Verify that the RDB version of the dump payload matches the one of this Redis
  * instance and that the checksum is ok.
- * If the DUMP payload looks valid REDIS_OK is returned, otherwise REDIS_ERR
+ * If the DUMP payload looks valid C_OK is returned, otherwise C_ERR
  * is returned. */
 int verifyDumpPayload(unsigned char *p, size_t len) {
     unsigned char *footer;
     uint16_t rdbver;
     uint64_t crc;
 
     /* At least 2 bytes of RDB version and 8 of CRC64 should be present. */
-    if (len < 10) return REDIS_ERR;
+    if (len < 10) return C_ERR;
     footer = p+(len-10);
 
     /* Verify RDB version */
     rdbver = (footer[1] << 8) | footer[0];
-    if (rdbver != REDIS_RDB_VERSION) return REDIS_ERR;
+    if (rdbver != REDIS_RDB_VERSION) return C_ERR;
 
     /* Verify CRC64 */
     crc = crc64(0,p,len-8);
     memrev64ifbe(&crc);
-    return (memcmp(&crc,footer+2,8) == 0) ? REDIS_OK : REDIS_ERR;
+    return (memcmp(&crc,footer+2,8) == 0) ? C_OK : C_ERR;
 }
 
 /* DUMP keyname
@@ -4407,15 +4407,15 @@ void restoreCommand(client *c) {
     }
 
     /* Check if the TTL value makes sense */
-    if (getLongLongFromObjectOrReply(c,c->argv[2],&ttl,NULL) != REDIS_OK) {
+    if (getLongLongFromObjectOrReply(c,c->argv[2],&ttl,NULL) != C_OK) {
         return;
     } else if (ttl < 0) {
         addReplyError(c,"Invalid TTL value, must be >= 0");
         return;
     }
 
     /* Verify RDB version and data checksum. */
-    if (verifyDumpPayload(c->argv[3]->ptr,sdslen(c->argv[3]->ptr)) == REDIS_ERR)
+    if (verifyDumpPayload(c->argv[3]->ptr,sdslen(c->argv[3]->ptr)) == C_ERR)
     {
         addReplyError(c,"DUMP payload version or checksum are wrong");
         return;
@@ -4587,9 +4587,9 @@ void migrateCommand(client *c) {
     }
 
     /* Sanity check */
-    if (getLongFromObjectOrReply(c,c->argv[5],&timeout,NULL) != REDIS_OK)
+    if (getLongFromObjectOrReply(c,c->argv[5],&timeout,NULL) != C_OK)
         return;
-    if (getLongFromObjectOrReply(c,c->argv[4],&dbid,NULL) != REDIS_OK)
+    if (getLongFromObjectOrReply(c,c->argv[4],&dbid,NULL) != C_OK)
         return;
     if (timeout <= 0) timeout = 1000;
 