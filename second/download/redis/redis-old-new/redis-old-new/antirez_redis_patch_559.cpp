@@ -980,7 +980,6 @@ instanceLink *releaseInstanceLink(instanceLink *link, sentinelRedisInstance *ri)
             cb = callbacks->head;
             while(cb) {
                 if (cb->privdata == ri) {
-                    printf("HERE\n");
                     cb->fn = sentinelDiscardReplyCallback;
                     cb->privdata = NULL; /* Not strictly needed. */
                 }