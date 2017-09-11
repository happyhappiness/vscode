@@ -456,19 +456,19 @@ void sentinelIsRunning(void) {
  *  EINVAL: Invalid port number.
  */
 sentinelAddr *createSentinelAddr(char *hostname, int port) {
-    char buf[REDIS_IP_STR_LEN];
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
@@ -2690,7 +2690,7 @@ void sentinelCommand(redisClient *c) {
         /* SENTINEL MONITOR <name> <ip> <port> <quorum> */
         sentinelRedisInstance *ri;
         long quorum, port;
-        char buf[REDIS_IP_STR_LEN];
+        char ip[REDIS_IP_STR_LEN];
 
         if (c->argc != 6) goto numargserr;
         if (getLongFromObjectOrReply(c,c->argv[5],&quorum,"Invalid quorum")
@@ -2700,7 +2700,7 @@ void sentinelCommand(redisClient *c) {
         /* Make sure the IP field is actually a valid IP before passing it
          * to createSentinelRedisInstance(), otherwise we may trigger a
          * DNS lookup at runtime. */
-        if (anetResolveIP(NULL,c->argv[3]->ptr,buf,sizeof(buf)) == ANET_ERR) {
+        if (anetResolveIP(NULL,c->argv[3]->ptr,ip,sizeof(ip)) == ANET_ERR) {
             addReplyError(c,"Invalid IP address specified");
             return;
         }