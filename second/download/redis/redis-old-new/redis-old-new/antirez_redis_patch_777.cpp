@@ -159,7 +159,7 @@ typedef struct sentinelRedisInstance {
     /* Master specific. */
     dict *sentinels;    /* Other sentinels monitoring the same master. */
     dict *slaves;       /* Slaves for this master instance. */
-    int quorum;         /* Number of sentinels that need to agree on failure. */
+    unsigned int quorum;/* Number of sentinels that need to agree on failure. */
     int parallel_syncs; /* How many slaves to reconfigure at same time. */
     char *auth_pass;    /* Password to use for AUTH against master & slaves. */
 
@@ -345,6 +345,7 @@ int dictSdsKeyCompare(void *privdata, const void *key1, const void *key2);
 void releaseSentinelRedisInstance(sentinelRedisInstance *ri);
 
 void dictInstancesValDestructor (void *privdata, void *obj) {
+    REDIS_NOTUSED(privdata);
     releaseSentinelRedisInstance(obj);
 }
 
@@ -403,7 +404,7 @@ void initSentinelConfig(void) {
 
 /* Perform the Sentinel mode initialization. */
 void initSentinel(void) {
-    int j;
+    unsigned int j;
 
     /* Remove usual Redis commands from the command table, then just add
      * the SENTINEL command. */
@@ -455,19 +456,19 @@ void sentinelIsRunning(void) {
  *  EINVAL: Invalid port number.
  */
 sentinelAddr *createSentinelAddr(char *hostname, int port) {
-    char buf[32];
+    char ip[REDIS_IP_STR_LEN];
     sentinelAddr *sa;
 
     if (port <= 0 || port > 65535) {
         errno = EINVAL;
         return NULL;
     }
-    if (anetResolve(NULL,hostname,buf,sizeof(buf)) == ANET_ERR) {
+    if (anetResolve(NULL,hostname,ip,sizeof(ip)) == ANET_ERR) {
         errno = ENOENT;
         return NULL;
     }
     sa = zmalloc(sizeof(*sa));
-    sa->ip = sdsnew(buf);
+    sa->ip = sdsnew(ip);
     sa->port = port;
     return sa;
 }
@@ -1634,6 +1635,7 @@ void sentinelLinkEstablishedCallback(const redisAsyncContext *c, int status) {
 }
 
 void sentinelDisconnectCallback(const redisAsyncContext *c, int status) {
+    REDIS_NOTUSED(status);
     sentinelDisconnectInstanceFromContext(c);
 }
 
@@ -1998,6 +2000,7 @@ void sentinelRefreshInstanceInfo(sentinelRedisInstance *ri, const char *info) {
 void sentinelInfoReplyCallback(redisAsyncContext *c, void *reply, void *privdata) {
     sentinelRedisInstance *ri = c->data;
     redisReply *r;
+    REDIS_NOTUSED(privdata);
 
     if (ri) ri->pending_commands--;
     if (!reply || !ri) return;
@@ -2012,13 +2015,16 @@ void sentinelInfoReplyCallback(redisAsyncContext *c, void *reply, void *privdata
  * value of the command but its effects directly. */
 void sentinelDiscardReplyCallback(redisAsyncContext *c, void *reply, void *privdata) {
     sentinelRedisInstance *ri = c->data;
+    REDIS_NOTUSED(reply);
+    REDIS_NOTUSED(privdata);
 
     if (ri) ri->pending_commands--;
 }
 
 void sentinelPingReplyCallback(redisAsyncContext *c, void *reply, void *privdata) {
     sentinelRedisInstance *ri = c->data;
     redisReply *r;
+    REDIS_NOTUSED(privdata);
 
     if (ri) ri->pending_commands--;
     if (!reply || !ri) return;
@@ -2057,6 +2063,7 @@ void sentinelPingReplyCallback(redisAsyncContext *c, void *reply, void *privdata
 void sentinelPublishReplyCallback(redisAsyncContext *c, void *reply, void *privdata) {
     sentinelRedisInstance *ri = c->data;
     redisReply *r;
+    REDIS_NOTUSED(privdata);
 
     if (ri) ri->pending_commands--;
     if (!reply || !ri) return;
@@ -2166,6 +2173,7 @@ void sentinelProcessHelloMessage(char *hello, int hello_len) {
 void sentinelReceiveHelloMessages(redisAsyncContext *c, void *reply, void *privdata) {
     sentinelRedisInstance *ri = c->data;
     redisReply *r;
+    REDIS_NOTUSED(privdata);
 
     if (!reply || !ri) return;
     r = reply;
@@ -2559,7 +2567,7 @@ sentinelRedisInstance *sentinelGetMasterByNameOrReplyError(redisClient *c,
 {
     sentinelRedisInstance *ri;
 
-    ri = dictFetchValue(sentinel.masters,c->argv[2]->ptr);
+    ri = dictFetchValue(sentinel.masters,name->ptr);
     if (!ri) {
         addReplyError(c,"No such master with that name");
         return NULL;
@@ -2682,7 +2690,7 @@ void sentinelCommand(redisClient *c) {
         /* SENTINEL MONITOR <name> <ip> <port> <quorum> */
         sentinelRedisInstance *ri;
         long quorum, port;
-        char buf[32];
+        char ip[REDIS_IP_STR_LEN];
 
         if (c->argc != 6) goto numargserr;
         if (getLongFromObjectOrReply(c,c->argv[5],&quorum,"Invalid quorum")
@@ -2692,7 +2700,7 @@ void sentinelCommand(redisClient *c) {
         /* Make sure the IP field is actually a valid IP before passing it
          * to createSentinelRedisInstance(), otherwise we may trigger a
          * DNS lookup at runtime. */
-        if (anetResolveIP(NULL,c->argv[3]->ptr,buf,sizeof(buf)) == ANET_ERR) {
+        if (anetResolveIP(NULL,c->argv[3]->ptr,ip,sizeof(ip)) == ANET_ERR) {
             addReplyError(c,"Invalid IP address specified");
             return;
         }
@@ -2997,7 +3005,7 @@ void sentinelCheckSubjectivelyDown(sentinelRedisInstance *ri) {
 void sentinelCheckObjectivelyDown(sentinelRedisInstance *master) {
     dictIterator *di;
     dictEntry *de;
-    int quorum = 0, odown = 0;
+    unsigned int quorum = 0, odown = 0;
 
     if (master->flags & SRI_S_DOWN) {
         /* Is down for enough sentinels? */
@@ -3034,6 +3042,7 @@ void sentinelCheckObjectivelyDown(sentinelRedisInstance *master) {
 void sentinelReceiveIsMasterDownReply(redisAsyncContext *c, void *reply, void *privdata) {
     sentinelRedisInstance *ri = c->data;
     redisReply *r;
+    REDIS_NOTUSED(privdata);
 
     if (ri) ri->pending_commands--;
     if (!reply || !ri) return;
@@ -3057,7 +3066,7 @@ void sentinelReceiveIsMasterDownReply(redisAsyncContext *c, void *reply, void *p
             /* If the runid in the reply is not "*" the Sentinel actually
              * replied with a vote. */
             sdsfree(ri->leader);
-            if (ri->leader_epoch != r->element[2]->integer)
+            if ((long long)ri->leader_epoch != r->element[2]->integer)
                 redisLog(REDIS_WARNING,
                     "%s voted for %s %llu", ri->name,
                     r->element[1]->str,