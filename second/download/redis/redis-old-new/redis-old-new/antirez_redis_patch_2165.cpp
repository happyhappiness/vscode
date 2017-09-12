@@ -6484,9 +6484,6 @@ static sds genRedisInfoString(void) {
     int j;
     char hmem[64];
 
-    server.hash_max_zipmap_entries = REDIS_HASH_MAX_ZIPMAP_ENTRIES;
-    server.hash_max_zipmap_value = REDIS_HASH_MAX_ZIPMAP_VALUE;
-  
     bytesToHuman(hmem,zmalloc_used_memory());
     info = sdscatprintf(sdsempty(),
         "redis_version:%s\r\n"