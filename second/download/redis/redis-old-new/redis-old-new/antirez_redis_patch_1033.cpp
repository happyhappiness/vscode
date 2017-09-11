@@ -1417,7 +1417,7 @@ void rewriteConfigSentinelOption(struct rewriteConfigState *state) {
 
         /* sentinel known-slave */
         di2 = dictGetIterator(master->slaves);
-        while((de = dictNext(di)) != NULL) {
+        while((de = dictNext(di2)) != NULL) {
             sentinelAddr *slave_addr;
 
             ri = dictGetVal(de);
@@ -1439,7 +1439,7 @@ void rewriteConfigSentinelOption(struct rewriteConfigState *state) {
 
         /* sentinel known-sentinel */
         di2 = dictGetIterator(master->sentinels);
-        while((de = dictNext(di)) != NULL) {
+        while((de = dictNext(di2)) != NULL) {
             ri = dictGetVal(de);
             line = sdscatprintf(sdsempty(),
                 "sentinel known-sentinel %s %s %d",