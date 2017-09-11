@@ -1832,7 +1832,6 @@ int freeMemoryIfNeeded(void) {
 
     /* Compute how much memory we need to free. */
     mem_tofree = mem_used - server.maxmemory;
-    printf("USED: %zu, TOFREE: %zu\n", mem_used, mem_tofree);
     mem_freed = 0;
     while (mem_freed < mem_tofree) {
         int j, k, keys_freed = 0;
@@ -1923,7 +1922,6 @@ int freeMemoryIfNeeded(void) {
                 delta = (long long) zmalloc_used_memory();
                 dbDelete(db,keyobj);
                 delta -= (long long) zmalloc_used_memory();
-                // printf("%lld\n",delta);
                 mem_freed += delta;
                 server.stat_evictedkeys++;
                 decrRefCount(keyobj);
@@ -1933,27 +1931,7 @@ int freeMemoryIfNeeded(void) {
                  * start spending so much time here that is impossible to
                  * deliver data to the slaves fast enough, so we force the
                  * transmission here inside the loop. */
-                if (slaves) {
-                    listIter li;
-                    listNode *ln;
-
-                    listRewind(server.slaves,&li);
-                    while((ln = listNext(&li))) {
-                        redisClient *slave = listNodeValue(ln);
-                        int events;
-
-                        events = aeGetFileEvents(server.el,slave->fd);
-                        printf("EVENTS: %d\n", events);
-                        if (events & AE_WRITABLE &&
-                            slave->replstate == REDIS_REPL_ONLINE &&
-                            listLength(slave->reply))
-                        {
-                            printf("SLAVE %d -> %d\n",
-                                slave->fd, (int) listLength(slave->reply));
-                            sendReplyToClient(server.el,slave->fd,slave,0);
-                        }
-                    }
-                }
+                if (slaves) flushSlavesOutputBuffers();
             }
         }
         if (!keys_freed) return REDIS_ERR; /* nothing to free... */