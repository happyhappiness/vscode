  * (the configured masters) but also in order to retain the state of
  * Sentinel across restarts: config epoch of masters, associated slaves
  * and sentinel instances, and so forth. */
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
         master_addr = sentinelGetCurrentMasterAddress(master);
         line = sdscatprintf(sdsempty(),"sentinel monitor %s %s %d %d",
             master->name, master_addr->ip, master_addr->port,
