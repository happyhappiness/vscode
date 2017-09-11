@@ -689,7 +689,8 @@ void activeExpireCycle(void) {
 
                     propagateExpire(db,keyobj);
                     dbDelete(db,keyobj);
-                    notifyKeyspaceEvent("expired",keyobj,db->id);
+                    notifyKeyspaceEvent(REDIS_NOTIFY_EXPIRED,
+                        "expired",keyobj,db->id);
                     decrRefCount(keyobj);
                     expired++;
                     server.stat_expiredkeys++;
@@ -2432,7 +2433,8 @@ int freeMemoryIfNeeded(void) {
                 delta -= (long long) zmalloc_used_memory();
                 mem_freed += delta;
                 server.stat_evictedkeys++;
-                notifyKeyspaceEvent("evicted",keyobj,db->id);
+                notifyKeyspaceEvent(REDIS_NOTIFY_EVICTED, "evicted",
+                    keyobj, db->id);
                 decrRefCount(keyobj);
                 keys_freed++;
 