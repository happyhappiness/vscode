@@ -1344,13 +1344,26 @@ char *sentinelHandleConfiguration(char **argv, int argc) {
         ri = sentinelGetMasterByName(argv[1]);
         if (!ri) return "No such master with specified name.";
         ri->auth_pass = sdsnew(argv[2]);
+    } else if (!strcasecmp(argv[0],"current-epoch") && argc == 2) {
+        /* current-epoch <epoch> */
+        unsigned long long current_epoch = strtoull(argv[2],NULL,10);
+        if (current_epoch > sentinel.current_epoch)
+            sentinel.current_epoch = current_epoch;
     } else if (!strcasecmp(argv[0],"config-epoch") && argc == 3) {
         /* config-epoch <name> <epoch> */
         ri = sentinelGetMasterByName(argv[1]);
         if (!ri) return "No such master with specified name.";
         ri->config_epoch = strtoull(argv[2],NULL,10);
+        /* The following update of current_epoch is not really useful as
+         * now the current epoch is persisted on the config file, but
+         * we leave this check here for redundancy. */
         if (ri->config_epoch > sentinel.current_epoch)
             sentinel.current_epoch = ri->config_epoch;
+    } else if (!strcasecmp(argv[0],"leader-epoch") && argc == 3) {
+        /* leader-epoch <name> <epoch> */
+        ri = sentinelGetMasterByName(argv[1]);
+        if (!ri) return "No such master with specified name.";
+        ri->leader_epoch = strtoull(argv[2],NULL,10);
     } else if (!strcasecmp(argv[0],"known-slave") && argc == 4) {
         sentinelRedisInstance *slave;
 
@@ -1389,13 +1402,13 @@ char *sentinelHandleConfiguration(char **argv, int argc) {
 void rewriteConfigSentinelOption(struct rewriteConfigState *state) {
     dictIterator *di, *di2;
     dictEntry *de;
+    sds line;
 
     /* For every master emit a "sentinel monitor" config entry. */
     di = dictGetIterator(sentinel.masters);
     while((de = dictNext(di)) != NULL) {
         sentinelRedisInstance *master, *ri;
         sentinelAddr *master_addr;
-        sds line;
 
         /* sentinel monitor */
         master = dictGetVal(de);
@@ -1459,6 +1472,12 @@ void rewriteConfigSentinelOption(struct rewriteConfigState *state) {
             master->name, (unsigned long long) master->config_epoch);
         rewriteConfigRewriteLine(state,"sentinel",line,1);
 
+        /* sentinel leader-epoch */
+        line = sdscatprintf(sdsempty(),
+            "sentinel leader-epoch %s %llu",
+            master->name, (unsigned long long) master->leader_epoch);
+        rewriteConfigRewriteLine(state,"sentinel",line,1);
+
         /* sentinel known-slave */
         di2 = dictGetIterator(master->slaves);
         while((de = dictNext(di2)) != NULL) {
@@ -1494,6 +1513,12 @@ void rewriteConfigSentinelOption(struct rewriteConfigState *state) {
         }
         dictReleaseIterator(di2);
     }
+
+    /* sentinel current-epoch is a global state valid for all the masters. */
+    line = sdscatprintf(sdsempty(),
+        "sentinel current-epoch %llu", (unsigned long long) sentinel.current_epoch);
+    rewriteConfigRewriteLine(state,"sentinel",line,1);
+
     dictReleaseIterator(di);
 }
 
@@ -2035,6 +2060,7 @@ void sentinelProcessHelloMessage(char *hello, int hello_len) {
         /* Update local current_epoch if received current_epoch is greater.*/
         if (current_epoch > sentinel.current_epoch) {
             sentinel.current_epoch = current_epoch;
+            sentinelFlushConfig();
             sentinelEvent(REDIS_WARNING,"+new-epoch",master,"%llu",
                 (unsigned long long) sentinel.current_epoch);
         }
@@ -2952,6 +2978,7 @@ void sentinelAskMasterStateToOtherSentinels(sentinelRedisInstance *master, int f
 char *sentinelVoteLeader(sentinelRedisInstance *master, uint64_t req_epoch, char *req_runid, uint64_t *leader_epoch) {
     if (req_epoch > sentinel.current_epoch) {
         sentinel.current_epoch = req_epoch;
+        sentinelFlushConfig();
         sentinelEvent(REDIS_WARNING,"+new-epoch",master,"%llu",
             (unsigned long long) sentinel.current_epoch);
     }
@@ -2961,6 +2988,7 @@ char *sentinelVoteLeader(sentinelRedisInstance *master, uint64_t req_epoch, char
         sdsfree(master->leader);
         master->leader = sdsnew(req_runid);
         master->leader_epoch = sentinel.current_epoch;
+        sentinelFlushConfig();
         sentinelEvent(REDIS_WARNING,"+vote-for-leader",master,"%s %llu",
             master->leader, (unsigned long long) master->leader_epoch);
         /* If we did not voted for ourselves, set the master failover start