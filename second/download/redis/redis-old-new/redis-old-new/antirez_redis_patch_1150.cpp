@@ -1241,6 +1241,7 @@ void rewriteConfigBytesOption(struct rewriteConfigState *state, char *option, lo
     rewriteConfigRewriteLine(state,option,line,force);
 }
 
+/* Rewrite a yes/no option. */
 void rewriteConfigYesNoOption(struct rewriteConfigState *state, char *option, int value, int defvalue) {
     int force = value != defvalue;
     sds line = sdscatprintf(sdsempty(),"%s %s",option,
@@ -1249,6 +1250,7 @@ void rewriteConfigYesNoOption(struct rewriteConfigState *state, char *option, in
     rewriteConfigRewriteLine(state,option,line,force);
 }
 
+/* Rewrite a string option. */
 void rewriteConfigStringOption(struct rewriteConfigState *state, char *option, char *value, char *defvalue) {
     int force = 1;
     sds line;
@@ -1267,20 +1269,25 @@ void rewriteConfigStringOption(struct rewriteConfigState *state, char *option, c
     rewriteConfigRewriteLine(state,option,line,force);
 }
 
+/* Rewrite a numerical (long long range) option. */
 void rewriteConfigNumericalOption(struct rewriteConfigState *state, char *option, long long value, long long defvalue) {
     int force = value != defvalue;
     sds line = sdscatprintf(sdsempty(),"%s %lld",option,value);
 
     rewriteConfigRewriteLine(state,option,line,force);
 }
 
+/* Rewrite a octal option. */
 void rewriteConfigOctalOption(struct rewriteConfigState *state, char *option, int value, int defvalue) {
     int force = value != defvalue;
     sds line = sdscatprintf(sdsempty(),"%s %o",option,value);
 
     rewriteConfigRewriteLine(state,option,line,force);
 }
 
+/* Rewrite an enumeration option, after the "value" every enum/value pair
+ * is specified, terminated by NULL. After NULL the default value is
+ * specified. See how the function is used for more information. */
 void rewriteConfigEnumOption(struct rewriteConfigState *state, char *option, int value, ...) {
     va_list ap;
     char *enum_name, *matching_name;
@@ -1304,6 +1311,7 @@ void rewriteConfigEnumOption(struct rewriteConfigState *state, char *option, int
     rewriteConfigRewriteLine(state,option,line,force);
 }
 
+/* Rewrite the syslog-fability option. */
 void rewriteConfigSyslogfacilityOption(struct rewriteConfigState *state) {
     int value = server.syslog_facility, j;
     int force = value != LOG_LOCAL0;
@@ -1320,6 +1328,7 @@ void rewriteConfigSyslogfacilityOption(struct rewriteConfigState *state) {
     rewriteConfigRewriteLine(state,option,line,force);
 }
 
+/* Rewrite the save option. */
 void rewriteConfigSaveOption(struct rewriteConfigState *state) {
     int j;
     sds line;
@@ -1334,13 +1343,15 @@ void rewriteConfigSaveOption(struct rewriteConfigState *state) {
     }
 }
 
+/* Rewrite the dir option, always using absolute paths.*/
 void rewriteConfigDirOption(struct rewriteConfigState *state) {
     char cwd[1024];
 
     if (getcwd(cwd,sizeof(cwd)) == NULL) return; /* no rewrite on error. */
     rewriteConfigStringOption(state,"dir",cwd,NULL);
 }
 
+/* Rewrite the slaveof option. */
 void rewriteConfigSlaveofOption(struct rewriteConfigState *state) {
     char *option = "slaveof";
     sds line;
@@ -1353,6 +1364,7 @@ void rewriteConfigSlaveofOption(struct rewriteConfigState *state) {
     rewriteConfigRewriteLine(state,option,line,1);
 }
 
+/* Rewrite the appendonly option. */
 void rewriteConfigAppendonlyOption(struct rewriteConfigState *state) {
     int force = server.aof_state != REDIS_AOF_OFF;
     char *option = "appendonly";
@@ -1363,6 +1375,7 @@ void rewriteConfigAppendonlyOption(struct rewriteConfigState *state) {
     rewriteConfigRewriteLine(state,option,line,force);
 }
 
+/* Rewrite the notify-keyspace-events option. */
 void rewriteConfigNotifykeyspaceeventsOption(struct rewriteConfigState *state) {
     int force = server.notify_keyspace_events != 0;
     char *option = "notify-keyspace-events";
@@ -1374,6 +1387,7 @@ void rewriteConfigNotifykeyspaceeventsOption(struct rewriteConfigState *state) {
     rewriteConfigRewriteLine(state,option,line,force);
 }
 
+/* Rewrite the client-output-buffer-limit option. */
 void rewriteConfigClientoutputbufferlimitOption(struct rewriteConfigState *state) {
     int j;
     char *option = "client-output-buffer-limit";
@@ -1417,12 +1431,40 @@ sds rewriteConfigGetContentFromState(struct rewriteConfigState *state) {
     return content;
 }
 
+/* Free the configuration rewrite state. */
 void rewriteConfigReleaseState(struct rewriteConfigState *state) {
     sdsfreesplitres(state->lines,state->numlines);
     dictRelease(state->option_to_line);
     zfree(state);
 }
 
+/* At the end of the rewrite process the state contains the remaining
+ * map between "option name" => "lines in the original config file".
+ * Lines used by the rewrite process were removed by the function
+ * rewriteConfigRewriteLine(), all the other lines are "orphaned" and
+ * should be replaced by empty lines.
+ *
+ * This function does just this, iterating all the option names and
+ * blanking all the lines still associated. */
+void rewriteConfigRemoveOrphaned(struct rewriteConfigState *state) {
+    dictIterator *di = dictGetIterator(state->option_to_line);
+    dictEntry *de;
+
+    while((de = dictNext(di)) != NULL) {
+        list *l = dictGetVal(de);
+
+        while(listLength(l)) {
+            listNode *ln = listFirst(l);
+            int linenum = (long) ln->value;
+
+            sdsfree(state->lines[linenum]);
+            state->lines[linenum] = sdsempty();
+            listDelNode(l,ln);
+        }
+    }
+    dictReleaseIterator(di);
+}
+
 /* Rewrite the configuration file at "path".
  * If the configuration file already exists, we try at best to retain comments
  * and overall structure.
@@ -1520,7 +1562,7 @@ int rewriteConfig(char *path) {
     /* Step 3: remove all the orphaned lines in the old file, that is, lines
      * that were used by a config option and are no longer used, like in case
      * of multiple "save" options or duplicated options. */
-//    rewriteConfigRemoveOrphaned(state);
+    rewriteConfigRemoveOrphaned(state);
 
     /* Step 4: generate a new configuration file from the modified state
      * and write it into the original file. */