@@ -897,7 +897,7 @@ sentinelRedisInstance *createSentinelRedisInstance(char *name, int flags, char *
     sentinelRedisInstance *ri;
     sentinelAddr *addr;
     dict *table = NULL;
-    char slavename[128], *sdsname;
+    char slavename[REDIS_PEER_ID_LEN], *sdsname;
 
     redisAssert(flags & (SRI_MASTER|SRI_SLAVE|SRI_SENTINEL));
     redisAssert((flags & SRI_MASTER) || master != NULL);
@@ -908,9 +908,7 @@ sentinelRedisInstance *createSentinelRedisInstance(char *name, int flags, char *
 
     /* For slaves and sentinel we use ip:port as name. */
     if (flags & (SRI_SLAVE|SRI_SENTINEL)) {
-        snprintf(slavename,sizeof(slavename),
-            strchr(hostname,':') ? "[%s]:%d" : "%s:%d",
-            hostname,port);
+        anetFormatIP(slavename, sizeof(slavename), hostname, port);
         name = slavename;
     }
 
@@ -1035,9 +1033,7 @@ sentinelRedisInstance *sentinelRedisInstanceLookupSlave(
     sentinelRedisInstance *slave;
 
     redisAssert(ri->flags & SRI_MASTER);
-    key = sdscatprintf(sdsempty(),
-        strchr(ip,':') ? "[%s]:%d" : "%s:%d",
-        ip,port);
+    key = sdsformatip(ip, port);
     slave = dictFetchValue(ri->slaves,key);
     sdsfree(key);
     return slave;