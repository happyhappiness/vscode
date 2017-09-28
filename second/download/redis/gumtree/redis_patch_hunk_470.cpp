          * totally fresh: no config epoch, no other known node, and so forth.
          * This happens at cluster creation time to start with a cluster where
          * every node has a different node ID, without to rely on the conflicts
          * resolution system which is too slow when a big cluster is created. */
         long long epoch;
 
-        if (getLongLongFromObjectOrReply(c,c->argv[2],&epoch,NULL) != REDIS_OK)
+        if (getLongLongFromObjectOrReply(c,c->argv[2],&epoch,NULL) != C_OK)
             return;
 
         if (epoch < 0) {
             addReplyErrorFormat(c,"Invalid config epoch specified: %lld",epoch);
         } else if (dictSize(server.cluster->nodes) > 1) {
             addReplyError(c,"The user can assign a config epoch only when the "
                             "node does not know any other node.");
         } else if (myself->configEpoch != 0) {
             addReplyError(c,"Node config epoch is already non-zero");
         } else {
             myself->configEpoch = epoch;
-            redisLog(REDIS_WARNING,
+            serverLog(LL_WARNING,
                 "configEpoch set to %llu via CLUSTER SET-CONFIG-EPOCH",
                 (unsigned long long) myself->configEpoch);
 
             if (server.cluster->currentEpoch < (uint64_t)epoch)
                 server.cluster->currentEpoch = epoch;
             /* No need to fsync the config here since in the unlucky event
