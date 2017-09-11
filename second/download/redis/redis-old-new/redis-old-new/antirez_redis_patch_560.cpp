@@ -1031,7 +1031,6 @@ int sentinelTryConnectionSharing(sentinelRedisInstance *ri) {
         releaseInstanceLink(ri->link,NULL);
         ri->link = match->link;
         match->link->refcount++;
-        printf("SHARED!\n");
         return REDIS_OK;
     }
     dictReleaseIterator(di);