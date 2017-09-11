@@ -1329,9 +1329,21 @@ void rewriteConfigSaveOption(struct rewriteConfigState *state) {
 }
 
 void rewriteConfigDirOption(struct rewriteConfigState *state) {
+    char cwd[1024];
+
+    if (getcwd(cwd,sizeof(cwd)) == NULL) return; /* no rewrite on error. */
+    rewriteConfigStringOption(state,"dir",cwd,NULL);
 }
 
 void rewriteConfigSlaveofOption(struct rewriteConfigState *state) {
+    sds line;
+
+    /* If this is a master, we want all the slaveof config options
+     * in the file to be removed. */
+    if (server.masterhost == NULL) return;
+    line = sdscatprintf(sdsempty(),"slaveof %s %d",
+        server.masterhost, server.masterport);
+    rewriteConfigRewriteLine(state,"slaveof",line,1);
 }
 
 void rewriteConfigAppendonlyOption(struct rewriteConfigState *state) {