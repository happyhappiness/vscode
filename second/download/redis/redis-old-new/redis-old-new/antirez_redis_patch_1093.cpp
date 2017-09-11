@@ -835,7 +835,9 @@ sentinelRedisInstance *createSentinelRedisInstance(char *name, int flags, char *
 
     /* For slaves and sentinel we use ip:port as name. */
     if (flags & (SRI_SLAVE|SRI_SENTINEL)) {
-        snprintf(slavename,sizeof(slavename),"%s:%d",hostname,port);
+        snprintf(slavename,sizeof(slavename),
+            strchr(hostname,':') ? "[%s]:%d" : "%s:%d",
+            hostname,port);
         name = slavename;
     }
 
@@ -943,7 +945,9 @@ sentinelRedisInstance *sentinelRedisInstanceLookupSlave(
     sentinelRedisInstance *slave;
   
     redisAssert(ri->flags & SRI_MASTER);
-    key = sdscatprintf(sdsempty(),"%s:%d",ip,port);
+    key = sdscatprintf(sdsempty(),
+        strchr(ip,':') ? "[%s]:%d" : "%s:%d",
+        ip,port);
     slave = dictFetchValue(ri->slaves,key);
     sdsfree(key);
     return slave;