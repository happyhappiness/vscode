@@ -416,11 +416,11 @@ dictType leaderVotesDictType = {
 
 /* =========================== Initialization =============================== */
 
-void sentinelCommand(redisClient *c);
-void sentinelInfoCommand(redisClient *c);
-void sentinelSetCommand(redisClient *c);
-void sentinelPublishCommand(redisClient *c);
-void sentinelRoleCommand(redisClient *c);
+void sentinelCommand(client *c);
+void sentinelInfoCommand(client *c);
+void sentinelSetCommand(client *c);
+void sentinelPublishCommand(client *c);
+void sentinelRoleCommand(client *c);
 
 struct redisCommand sentinelcmds[] = {
     {"ping",pingCommand,1,"",0,NULL,0,0,0,0,0},
@@ -859,7 +859,7 @@ void sentinelKillTimedoutScripts(void) {
 }
 
 /* Implements SENTINEL PENDING-SCRIPTS command. */
-void sentinelPendingScriptsCommand(redisClient *c) {
+void sentinelPendingScriptsCommand(client *c) {
     listNode *ln;
     listIter li;
 
@@ -2604,7 +2604,7 @@ const char *sentinelFailoverStateStr(int state) {
 }
 
 /* Redis instance to Redis protocol representation. */
-void addReplySentinelRedisInstance(redisClient *c, sentinelRedisInstance *ri) {
+void addReplySentinelRedisInstance(client *c, sentinelRedisInstance *ri) {
     char *flags = sdsempty();
     void *mbl;
     int fields = 0;
@@ -2795,7 +2795,7 @@ void addReplySentinelRedisInstance(redisClient *c, sentinelRedisInstance *ri) {
 
 /* Output a number of instances contained inside a dictionary as
  * Redis protocol. */
-void addReplyDictOfRedisInstances(redisClient *c, dict *instances) {
+void addReplyDictOfRedisInstances(client *c, dict *instances) {
     dictIterator *di;
     dictEntry *de;
 
@@ -2812,7 +2812,7 @@ void addReplyDictOfRedisInstances(redisClient *c, dict *instances) {
 /* Lookup the named master into sentinel.masters.
  * If the master is not found reply to the client with an error and returns
  * NULL. */
-sentinelRedisInstance *sentinelGetMasterByNameOrReplyError(redisClient *c,
+sentinelRedisInstance *sentinelGetMasterByNameOrReplyError(client *c,
                         robj *name)
 {
     sentinelRedisInstance *ri;
@@ -2850,7 +2850,7 @@ int sentinelIsQuorumReachable(sentinelRedisInstance *master, int *usableptr) {
     return result;
 }
 
-void sentinelCommand(redisClient *c) {
+void sentinelCommand(client *c) {
     if (!strcasecmp(c->argv[1]->ptr,"masters")) {
         /* SENTINEL MASTERS */
         if (c->argc != 2) goto numargserr;
@@ -3166,7 +3166,7 @@ void sentinelCommand(redisClient *c) {
 }
 
 /* SENTINEL INFO [section] */
-void sentinelInfoCommand(redisClient *c) {
+void sentinelInfoCommand(client *c) {
     if (c->argc > 2) {
         addReply(c,shared.syntaxerr);
         return;
@@ -3232,7 +3232,7 @@ void sentinelInfoCommand(redisClient *c) {
 
 /* Implements Sentinel verison of the ROLE command. The output is
  * "sentinel" and the list of currently monitored master names. */
-void sentinelRoleCommand(redisClient *c) {
+void sentinelRoleCommand(client *c) {
     dictIterator *di;
     dictEntry *de;
 
@@ -3250,7 +3250,7 @@ void sentinelRoleCommand(redisClient *c) {
 }
 
 /* SENTINEL SET <mastername> [<option> <value> ...] */
-void sentinelSetCommand(redisClient *c) {
+void sentinelSetCommand(client *c) {
     sentinelRedisInstance *ri;
     int j, changes = 0;
     char *option, *value;
@@ -3343,7 +3343,7 @@ void sentinelSetCommand(redisClient *c) {
  *
  * Because we have a Sentinel PUBLISH, the code to send hello messages is the same
  * for all the three kind of instances: masters, slaves, sentinels. */
-void sentinelPublishCommand(redisClient *c) {
+void sentinelPublishCommand(client *c) {
     if (strcmp(c->argv[1]->ptr,SENTINEL_HELLO_CHANNEL)) {
         addReplyError(c, "Only HELLO messages are accepted by Sentinel instances.");
         return;