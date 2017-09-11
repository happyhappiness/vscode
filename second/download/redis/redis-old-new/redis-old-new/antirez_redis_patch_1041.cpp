@@ -1043,24 +1043,6 @@ sentinelRedisInstance *sentinelGetMasterByName(char *name) {
     return ri;
 }
 
-/* Senitnel lookup by runid */
-sentinelRedisInstance *sentinelGetSentinelByRunid(sentinelRedisInstance *master, char *runid) {
-    sentinelRedisInstance *retval = NULL;
-    dictIterator *di;
-    dictEntry *de;
-
-    di = dictGetIterator(master->sentinels);
-    while((de = dictNext(di)) != NULL) {
-        sentinelRedisInstance *ri = dictGetVal(de);
-        if (!strcmp(ri->runid,runid)) {
-            retval = ri;
-            break;
-        }
-    }
-    dictReleaseIterator(di);
-    return retval;
-}
-
 /* Add the specified flags to all the instances in the specified dictionary. */
 void sentinelAddFlagsToDictOfRedisInstances(dict *instances, int flags) {
     dictIterator *di;
@@ -2417,17 +2399,15 @@ int compareRunID(const void *a, const void *b) {
  * If a vote is not available returns NULL, otherwise return the Sentinel
  * runid and populate the leader_epoch with the epoch of the last vote. */
 char *sentinelVoteLeader(sentinelRedisInstance *master, uint64_t req_epoch, char *req_runid, uint64_t *leader_epoch) {
-    sentinelRedisInstance *si = sentinelGetSentinelByRunid(master,req_runid);
-
     if (req_epoch > sentinel.current_epoch)
         sentinel.current_epoch = req_epoch;
 
-    if (si && master->leader_epoch < req_epoch &&
-              sentinel.current_epoch <= req_epoch)
-    {
+    if (master->leader_epoch < req_epoch && sentinel.current_epoch <= req_epoch) {
         sdsfree(master->leader);
         master->leader = sdsnew(req_runid);
         master->leader_epoch = sentinel.current_epoch;
+        printf("Selected leader %s for epoch %llu\n", master->leader,
+            (unsigned long long) master->leader_epoch);
     }
 
     *leader_epoch = master->leader_epoch;