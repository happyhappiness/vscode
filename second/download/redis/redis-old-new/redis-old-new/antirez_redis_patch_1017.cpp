@@ -1169,17 +1169,27 @@ void dictListDestructor(void *privdata, void *val);
 void rewriteConfigSentinelOption(struct rewriteConfigState *state);
 
 dictType optionToLineDictType = {
-    dictSdsHash,                /* hash function */
+    dictSdsCaseHash,            /* hash function */
     NULL,                       /* key dup */
     NULL,                       /* val dup */
-    dictSdsKeyCompare,          /* key compare */
+    dictSdsKeyCaseCompare,      /* key compare */
     dictSdsDestructor,          /* key destructor */
     dictListDestructor          /* val destructor */
 };
 
+dictType optionSetDictType = {
+    dictSdsCaseHash,            /* hash function */
+    NULL,                       /* key dup */
+    NULL,                       /* val dup */
+    dictSdsKeyCaseCompare,      /* key compare */
+    dictSdsDestructor,          /* key destructor */
+    NULL                        /* val destructor */
+};
+
 /* The config rewrite state. */
 struct rewriteConfigState {
     dict *option_to_line; /* Option -> list of config file lines map */
+    dict *rewritten;      /* Dictionary of already processed options */
     int numlines;         /* Number of lines in current config */
     sds *lines;           /* Current lines as an array of sds strings */
     int has_tail;         /* True if we already added directives that were
@@ -1203,6 +1213,16 @@ void rewriteConfigAddLineNumberToOption(struct rewriteConfigState *state, sds op
     listAddNodeTail(l,(void*)(long)linenum);
 }
 
+/* Add the specified option to the set of processed options.
+ * This is useful as only unused lines of processed options will be blanked
+ * in the config file, while options the rewrite process does not understand
+ * remain untouched. */
+void rewriteConfigMarkAsProcessed(struct rewriteConfigState *state, char *option) {
+    sds opt = sdsnew(option);
+
+    if (dictAdd(state->rewritten,opt) != DICT_OK) sdsfree(opt);
+}
+
 /* Read the old file, split it into lines to populate a newly created
  * config rewrite state, and return it to the caller.
  *
@@ -1217,6 +1237,7 @@ struct rewriteConfigState *rewriteConfigReadOldFile(char *path) {
     if (fp == NULL && errno != ENOENT) return NULL;
 
     state->option_to_line = dictCreate(&optionToLineDictType,NULL);
+    state->rewritten = dictCreate(&optionSetDictType,NULL);
     state->numlines = 0;
     state->lines = NULL;
     state->has_tail = 0;
@@ -1284,6 +1305,8 @@ void rewriteConfigRewriteLine(struct rewriteConfigState *state, char *option, sd
     sds o = sdsnew(option);
     list *l = dictFetchValue(state->option_to_line,o);
 
+    rewriteConfigMarkAsProcessed(state,option);
+
     if (!l && !force) {
         /* Option not used previously, and we are not forced to use it. */
         sdsfree(line);
@@ -1340,7 +1363,6 @@ void rewriteConfigBytesOption(struct rewriteConfigState *state, char *option, lo
     rewriteConfigFormatMemory(buf,sizeof(buf),value);
     line = sdscatprintf(sdsempty(),"%s %s",option,buf);
     rewriteConfigRewriteLine(state,option,line,force);
-
 }
 
 /* Rewrite a yes/no option. */
@@ -1359,7 +1381,10 @@ void rewriteConfigStringOption(struct rewriteConfigState *state, char *option, c
 
     /* String options set to NULL need to be not present at all in the
      * configuration file to be set to NULL again at the next reboot. */
-    if (value == NULL) return;
+    if (value == NULL) {
+        rewriteConfigMarkAsProcessed(state,option);
+        return;
+    }
 
     /* Compare the strings as sds strings to have a binary safe comparison. */
     if (defvalue && strcmp(value,defvalue) == 0) force = 0;
@@ -1449,7 +1474,10 @@ void rewriteConfigSaveOption(struct rewriteConfigState *state) {
 void rewriteConfigDirOption(struct rewriteConfigState *state) {
     char cwd[1024];
 
-    if (getcwd(cwd,sizeof(cwd)) == NULL) return; /* no rewrite on error. */
+    if (getcwd(cwd,sizeof(cwd)) == NULL) {
+        rewriteConfigMarkAsProcessed(state,"dir");
+        return; /* no rewrite on error. */
+    }
     rewriteConfigStringOption(state,"dir",cwd,NULL);
 }
 
@@ -1460,7 +1488,10 @@ void rewriteConfigSlaveofOption(struct rewriteConfigState *state) {
 
     /* If this is a master, we want all the slaveof config options
      * in the file to be removed. */
-    if (server.masterhost == NULL) return;
+    if (server.masterhost == NULL) {
+        rewriteConfigMarkAsProcessed(state,"slaveof");
+        return;
+    }
     line = sdscatprintf(sdsempty(),"%s %s %d", option,
         server.masterhost, server.masterport);
     rewriteConfigRewriteLine(state,option,line,1);
@@ -1525,7 +1556,10 @@ void rewriteConfigBindOption(struct rewriteConfigState *state) {
     char *option = "bind";
 
     /* Nothing to rewrite if we don't have bind addresses. */
-    if (server.bindaddr_count == 0) return;
+    if (server.bindaddr_count == 0) {
+        rewriteConfigMarkAsProcessed(state,option);
+        return;
+    }
 
     /* Rewrite as bind <addr1> <addr2> ... <addrN> */
     addresses = sdsjoin(server.bindaddr,server.bindaddr_count," ");
@@ -1561,6 +1595,7 @@ sds rewriteConfigGetContentFromState(struct rewriteConfigState *state) {
 void rewriteConfigReleaseState(struct rewriteConfigState *state) {
     sdsfreesplitres(state->lines,state->numlines);
     dictRelease(state->option_to_line);
+    dictRelease(state->rewritten);
     zfree(state);
 }
 
@@ -1578,6 +1613,14 @@ void rewriteConfigRemoveOrphaned(struct rewriteConfigState *state) {
 
     while((de = dictNext(di)) != NULL) {
         list *l = dictGetVal(de);
+        sds option = dictGetKey(de);
+
+        /* Don't blank lines about options the rewrite process
+         * don't understand. */
+        if (dictFetch(state->rewritten,option) == NULL) {
+            redisLog(REDIS_DEBUG,"Not rewritten option: %s", option);
+            continue;
+        }
 
         while(listLength(l)) {
             listNode *ln = listFirst(l);
@@ -1667,8 +1710,6 @@ int rewriteConfig(char *path) {
     /* Step 2: rewrite every single option, replacing or appending it inside
      * the rewrite state. */
 
-    /* TODO: Turn every default into a define, use it also in
-     * initServerConfig(). */
     rewriteConfigYesNoOption(state,"daemonize",server.daemonize,0);
     rewriteConfigStringOption(state,"pidfile",server.pidfile,REDIS_DEFAULT_PID_FILE);
     rewriteConfigNumericalOption(state,"port",server.port,REDIS_SERVERPORT);