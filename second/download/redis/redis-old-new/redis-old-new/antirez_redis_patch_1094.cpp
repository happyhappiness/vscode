@@ -1741,9 +1741,13 @@ void sentinelReceiveHelloMessages(redisAsyncContext *c, void *reply, void *privd
 
     {
         int numtokens, port, removed, canfailover;
+        /* Separator changed from ":" to "," in recent versions in order to
+         * play well with IPv6 addresses. For now we make sure to parse both
+         * correctly detecting if there is "," inside the string. */
+        char *sep = strchr(r->element[2]->str,',') ? "," : ":";
         char **token = sdssplitlen(r->element[2]->str,
                                    r->element[2]->len,
-                                   ":",1,&numtokens);
+                                   sep,1,&numtokens);
         sentinelRedisInstance *sentinel;
 
         if (numtokens == 4) {
@@ -1841,8 +1845,7 @@ void sentinelPingInstance(sentinelRedisInstance *ri) {
         if (anetSockName(ri->cc->c.fd,ip,sizeof(ip),NULL) != -1) {
             char myaddr[REDIS_IP_STR_LEN+128];
 
-            // FIXME: IPv6 will break this due to nested : characters -geoffgarside
-            snprintf(myaddr,sizeof(myaddr),"%s:%d:%s:%d",
+            snprintf(myaddr,sizeof(myaddr),"%s,%d,%s,%d",
                 ip, server.port, server.runid,
                 (ri->flags & SRI_CAN_FAILOVER) != 0);
             retval = redisAsyncCommand(ri->cc,