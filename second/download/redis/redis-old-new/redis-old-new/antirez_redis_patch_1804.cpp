@@ -70,6 +70,7 @@ static struct config {
 
 static void usage();
 char *redisGitSHA1(void);
+char *redisGitDirty(void);
 
 /*------------------------------------------------------------------------------
  * Utility functions
@@ -105,6 +106,20 @@ typedef struct {
 static helpEntry *helpEntries;
 static int helpEntriesLen;
 
+static sds cliVersion() {
+    sds version;
+    version = sdscatprintf(sdsempty(), "%s", REDIS_VERSION);
+
+    /* Add git commit and working tree status when available */
+    if (strtoll(redisGitSHA1(),NULL,16)) {
+        version = sdscatprintf(version, " (git:%s", redisGitSHA1());
+        if (strtoll(redisGitDirty(),NULL,10))
+            version = sdscatprintf(version, "-dirty");
+        version = sdscat(version, ")");
+    }
+    return version;
+}
+
 static void cliInitHelp() {
     int commandslen = sizeof(commandHelp)/sizeof(struct commandHelp);
     int groupslen = sizeof(commandGroups)/sizeof(char*);
@@ -145,14 +160,16 @@ static void cliOutputCommandHelp(struct commandHelp *help, int group) {
 
 /* Print generic help. */
 static void cliOutputGenericHelp() {
+    sds version = cliVersion();
     printf(
         "redis-cli %s\r\n"
         "Type: \"help @<group>\" to get a list of commands in <group>\r\n"
         "      \"help <command>\" for help on <command>\r\n"
         "      \"help <tab>\" to get a list of possible help topics\r\n"
         "      \"quit\" to exit\r\n",
-        REDIS_VERSION
+        version
     );
+    sdsfree(version);
 }
 
 /* Output all command help, filtering by group or command name. */