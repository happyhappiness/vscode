                 sentinelRedisInstance *ri, char *ip, int port)
 {
     sds key;
     sentinelRedisInstance *slave;
   
     redisAssert(ri->flags & SRI_MASTER);
-    key = sdscatprintf(sdsempty(),"%s:%d",ip,port);
+    key = sdscatprintf(sdsempty(),
+        strchr(ip,':') ? "[%s]:%d" : "%s:%d",
+        ip,port);
     slave = dictFetchValue(ri->slaves,key);
     sdsfree(key);
     return slave;
 }
 
 /* Return the name of the type of the instance as a string. */
