 /* Lookup a slave in a master Redis instance, by ip and port. */
 sentinelRedisInstance *sentinelRedisInstanceLookupSlave(
                 sentinelRedisInstance *ri, char *ip, int port)
 {
     sds key;
     sentinelRedisInstance *slave;
+    char buf[NET_PEER_ID_LEN];
 
-    redisAssert(ri->flags & SRI_MASTER);
-    key = sdscatprintf(sdsempty(),
-        strchr(ip,':') ? "[%s]:%d" : "%s:%d",
-        ip,port);
+    serverAssert(ri->flags & SRI_MASTER);
+    anetFormatAddr(buf,sizeof(buf),ip,port);
+    key = sdsnew(buf);
     slave = dictFetchValue(ri->slaves,key);
     sdsfree(key);
     return slave;
 }
 
 /* Return the name of the type of the instance as a string. */
