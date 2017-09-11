@@ -689,6 +689,7 @@ void activeExpireCycle(void) {
 
                     propagateExpire(db,keyobj);
                     dbDelete(db,keyobj);
+                    notifyKeyspaceEvent("expired",keyobj,db->id);
                     decrRefCount(keyobj);
                     expired++;
                     server.stat_expiredkeys++;
@@ -2431,6 +2432,7 @@ int freeMemoryIfNeeded(void) {
                 delta -= (long long) zmalloc_used_memory();
                 mem_freed += delta;
                 server.stat_evictedkeys++;
+                notifyKeyspaceEvent("evicted",keyobj,db->id);
                 decrRefCount(keyobj);
                 keys_freed++;
 