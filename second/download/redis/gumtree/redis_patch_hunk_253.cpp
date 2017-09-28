 /* Rewrite the slaveof option. */
 void rewriteConfigSlaveofOption(struct rewriteConfigState *state) {
     char *option = "slaveof";
     sds line;
 
     /* If this is a master, we want all the slaveof config options
-     * in the file to be removed. */
-    if (server.masterhost == NULL) {
+     * in the file to be removed. Note that if this is a cluster instance
+     * we don't want a slaveof directive inside redis.conf. */
+    if (server.cluster_enabled || server.masterhost == NULL) {
         rewriteConfigMarkAsProcessed(state,"slaveof");
         return;
     }
     line = sdscatprintf(sdsempty(),"%s %s %d", option,
         server.masterhost, server.masterport);
     rewriteConfigRewriteLine(state,option,line,1);
