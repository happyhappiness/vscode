@@ -50,8 +50,11 @@ struct evictionPoolEntry {
     unsigned long long idle;    /* Object idle time. */
     sds key;                    /* Key name. */
     sds cached;                 /* Cached SDS object for key name. */
+    int dbid;                   /* Key DB number. */
 };
 
+static struct evictionPoolEntry *EvictionPoolLRU;
+
 /* ----------------------------------------------------------------------------
  * Implementation of eviction, aging and LRU
  * --------------------------------------------------------------------------*/
@@ -114,7 +117,7 @@ unsigned long long estimateObjectIdleTime(robj *o) {
  * evicted in the whole database. */
 
 /* Create a new eviction pool. */
-struct evictionPoolEntry *evictionPoolAlloc(void) {
+void evictionPoolAlloc(void) {
     struct evictionPoolEntry *ep;
     int j;
 
@@ -123,8 +126,9 @@ struct evictionPoolEntry *evictionPoolAlloc(void) {
         ep[j].idle = 0;
         ep[j].key = NULL;
         ep[j].cached = sdsnewlen(NULL,EVPOOL_CACHED_SDS_SIZE);
+        ep[j].dbid = 0;
     }
-    return ep;
+    EvictionPoolLRU = ep;
 }
 
 /* This is an helper function for freeMemoryIfNeeded(), it is used in order
@@ -136,8 +140,7 @@ struct evictionPoolEntry *evictionPoolAlloc(void) {
  * idle time are on the left, and keys with the higher idle time on the
  * right. */
 
-#define EVICTION_SAMPLES_ARRAY_SIZE 16
-void evictionPoolPopulate(dict *sampledict, dict *keydict, struct evictionPoolEntry *pool) {
+void evictionPoolPopulate(int dbid, dict *sampledict, dict *keydict, struct evictionPoolEntry *pool) {
     int j, k, count;
     dictEntry *samples[server.maxmemory_samples];
 
@@ -176,15 +179,21 @@ void evictionPoolPopulate(dict *sampledict, dict *keydict, struct evictionPoolEn
             if (pool[EVPOOL_SIZE-1].key == NULL) {
                 /* Free space on the right? Insert at k shifting
                  * all the elements from k to end to the right. */
+
+                /* Save SDS before overwriting. */
+                sds cached = pool[EVPOOL_SIZE-1].cached;
                 memmove(pool+k+1,pool+k,
                     sizeof(pool[0])*(EVPOOL_SIZE-k-1));
+                pool[k].cached = cached;
             } else {
                 /* No free space on right? Insert at k-1 */
                 k--;
                 /* Shift all elements on the left of k (included) to the
                  * left, so we discard the element with smaller idle time. */
+                sds cached = pool[0].cached; /* Save SDS before overwriting. */
                 if (pool[0].key != pool[0].cached) sdsfree(pool[0].key);
                 memmove(pool,pool+1,sizeof(pool[0])*k);
+                pool[k].cached = cached;
             }
         }
 
@@ -201,6 +210,7 @@ void evictionPoolPopulate(dict *sampledict, dict *keydict, struct evictionPoolEn
             pool[k].key = pool[k].cached;
         }
         pool[k].idle = idle;
+        pool[k].dbid = dbid;
     }
 }
 
@@ -249,119 +259,161 @@ int freeMemoryIfNeeded(void) {
 
     latencyStartMonitor(latency);
     while (mem_freed < mem_tofree) {
-        int j, k, keys_freed = 0;
-
-        for (j = 0; j < server.dbnum; j++) {
-            long bestval = 0; /* just to prevent warning */
-            sds bestkey = NULL;
-            dictEntry *de;
-            redisDb *db = server.db+j;
-            dict *dict;
-
-            if (server.maxmemory_policy == MAXMEMORY_ALLKEYS_LRU ||
-                server.maxmemory_policy == MAXMEMORY_ALLKEYS_RANDOM)
-            {
-                dict = server.db[j].dict;
-            } else {
-                dict = server.db[j].expires;
-            }
-            if (dictSize(dict) == 0) continue;
-
-            /* volatile-random and allkeys-random policy */
-            if (server.maxmemory_policy == MAXMEMORY_ALLKEYS_RANDOM ||
-                server.maxmemory_policy == MAXMEMORY_VOLATILE_RANDOM)
-            {
-                de = dictGetRandomKey(dict);
-                bestkey = dictGetKey(de);
-            }
+        int j, k, i, keys_freed = 0;
+        static int next_db = 0;
+        sds bestkey = NULL;
+        int bestdbid;
+        redisDb *db;
+        dict *dict;
+        dictEntry *de;
 
-            /* volatile-lru and allkeys-lru policy */
-            else if (server.maxmemory_policy == MAXMEMORY_ALLKEYS_LRU ||
-                server.maxmemory_policy == MAXMEMORY_VOLATILE_LRU)
-            {
-                struct evictionPoolEntry *pool = db->eviction_pool;
-
-                while(bestkey == NULL) {
-                    evictionPoolPopulate(dict, db->dict, db->eviction_pool);
-                    /* Go backward from best to worst element to evict. */
-                    for (k = EVPOOL_SIZE-1; k >= 0; k--) {
-                        if (pool[k].key == NULL) continue;
-                        de = dictFind(dict,pool[k].key);
-
-                        /* Remove the entry from the pool. */
-                        if (pool[k].key != pool[k].cached)
-                            sdsfree(pool[k].key);
-                        pool[k].key = NULL;
-                        pool[k].idle = 0;
-
-                        /* If the key exists, is our pick. Otherwise it is
-                         * a ghost and we need to try the next element. */
-                        if (de) {
-                            bestkey = dictGetKey(de);
-                            break;
-                        } else {
-                            /* Ghost... */
-                            continue;
-                        }
+        if (server.maxmemory_policy == MAXMEMORY_ALLKEYS_LRU ||
+            server.maxmemory_policy == MAXMEMORY_VOLATILE_LRU)
+        {
+            struct evictionPoolEntry *pool = EvictionPoolLRU;
+
+            while(bestkey == NULL) {
+                unsigned long total_keys = 0, keys;
+
+                /* We don't want to make local-db choices when expiring keys,
+                 * so to start populate the eviction pool sampling keys from
+                 * every DB. */
+                for (i = 0; i < server.dbnum; i++) {
+                    db = server.db+i;
+                    dict = (server.maxmemory_policy == MAXMEMORY_ALLKEYS_LRU) ?
+                            db->dict : db->expires;
+                    if ((keys = dictSize(dict)) != 0) {
+                        evictionPoolPopulate(i, dict, db->dict, pool);
+                        total_keys += keys;
                     }
                 }
-            }
+                if (!total_keys) break; /* No keys to evict. */
+
+                /* Go backward from best to worst element to evict. */
+                for (k = EVPOOL_SIZE-1; k >= 0; k--) {
+                    if (pool[k].key == NULL) continue;
+                    bestdbid = pool[k].dbid;
+
+                    if (server.maxmemory_policy == MAXMEMORY_ALLKEYS_LRU) {
+                        de = dictFind(server.db[pool[k].dbid].dict,
+                            pool[k].key);
+                    } else {
+                        de = dictFind(server.db[pool[k].dbid].expires,
+                            pool[k].key);
+                    }
 
-            /* volatile-ttl */
-            else if (server.maxmemory_policy == MAXMEMORY_VOLATILE_TTL) {
-                for (k = 0; k < server.maxmemory_samples; k++) {
-                    sds thiskey;
-                    long thisval;
+                    /* Remove the entry from the pool. */
+                    if (pool[k].key != pool[k].cached)
+                        sdsfree(pool[k].key);
+                    pool[k].key = NULL;
+                    pool[k].idle = 0;
+
+                    /* If the key exists, is our pick. Otherwise it is
+                     * a ghost and we need to try the next element. */
+                    if (de) {
+                        bestkey = dictGetKey(de);
+                        break;
+                    } else {
+                        /* Ghost... Iterate again. */
+                    }
+                }
+            }
+        }
 
+        /* volatile-random and allkeys-random policy */
+        else if (server.maxmemory_policy == MAXMEMORY_ALLKEYS_RANDOM ||
+                 server.maxmemory_policy == MAXMEMORY_VOLATILE_RANDOM)
+        {
+            /* When evicting a random key, we try to evict a key for
+             * each DB, so we use the static 'next_db' variable to
+             * incrementally visit all DBs. */
+            for (i = 0; i < server.dbnum; i++) {
+                j = (++next_db) % server.dbnum;
+                db = server.db+j;
+                dict = (server.maxmemory_policy == MAXMEMORY_ALLKEYS_RANDOM) ?
+                        db->dict : db->expires;
+                if (dictSize(dict) != 0) {
                     de = dictGetRandomKey(dict);
-                    thiskey = dictGetKey(de);
-                    thisval = (long) dictGetVal(de);
-
-                    /* Expire sooner (minor expire unix timestamp) is better
-                     * candidate for deletion */
-                    if (bestkey == NULL || thisval < bestval) {
-                        bestkey = thiskey;
-                        bestval = thisval;
-                    }
+                    bestkey = dictGetKey(de);
+                    bestdbid = j;
+                    break;
                 }
             }
+        }
 
-            /* Finally remove the selected key. */
-            if (bestkey) {
-                robj *keyobj = createStringObject(bestkey,sdslen(bestkey));
-                propagateExpire(db,keyobj,server.lazyfree_lazy_eviction);
-                /* We compute the amount of memory freed by db*Delete() alone.
-                 * It is possible that actually the memory needed to propagate
-                 * the DEL in AOF and replication link is greater than the one
-                 * we are freeing removing the key, but we can't account for
-                 * that otherwise we would never exit the loop.
-                 *
-                 * AOF and Output buffer memory will be freed eventually so
-                 * we only care about memory used by the key space. */
-                delta = (long long) zmalloc_used_memory();
-                latencyStartMonitor(eviction_latency);
-                if (server.lazyfree_lazy_eviction)
-                    dbAsyncDelete(db,keyobj);
-                else
-                    dbSyncDelete(db,keyobj);
-                latencyEndMonitor(eviction_latency);
-                latencyAddSampleIfNeeded("eviction-del",eviction_latency);
-                latencyRemoveNestedEvent(latency,eviction_latency);
-                delta -= (long long) zmalloc_used_memory();
-                mem_freed += delta;
-                server.stat_evictedkeys++;
-                notifyKeyspaceEvent(NOTIFY_EVICTED, "evicted",
-                    keyobj, db->id);
-                decrRefCount(keyobj);
-                keys_freed++;
-
-                /* When the memory to free starts to be big enough, we may
-                 * start spending so much time here that is impossible to
-                 * deliver data to the slaves fast enough, so we force the
-                 * transmission here inside the loop. */
-                if (slaves) flushSlavesOutputBuffers();
+        /* volatile-ttl */
+        else if (server.maxmemory_policy == MAXMEMORY_VOLATILE_TTL) {
+            long bestttl = 0; /* Initialized to avoid warning. */
+
+            /* In this policy we scan a single DB per iteration (visiting
+             * a different DB per call), expiring the key with the smallest
+             * TTL among the few sampled.
+             *
+             * Note that this algorithm makes local-DB choices, and should
+             * use a pool and code more similr to the one used in the
+             * LRU eviction policies in the future. */
+            for (i = 0; i < server.dbnum; i++) {
+                j = (++next_db) % server.dbnum;
+                db = server.db+j;
+                dict = db->expires;
+                if (dictSize(dict) != 0) {
+                    for (k = 0; k < server.maxmemory_samples; k++) {
+                        sds thiskey;
+                        long thisttl;
+
+                        de = dictGetRandomKey(dict);
+                        thiskey = dictGetKey(de);
+                        thisttl = (long) dictGetVal(de);
+
+                        /* Keys expiring sooner (smaller unix timestamp) are
+                         * better candidates for deletion */
+                        if (bestkey == NULL || thisttl < bestttl) {
+                            bestkey = thiskey;
+                            bestttl = thisttl;
+                            bestdbid = j;
+                        }
+                    }
+                }
             }
         }
+
+        /* Finally remove the selected key. */
+        if (bestkey) {
+            db = server.db+bestdbid;
+            robj *keyobj = createStringObject(bestkey,sdslen(bestkey));
+            propagateExpire(db,keyobj,server.lazyfree_lazy_eviction);
+            /* We compute the amount of memory freed by db*Delete() alone.
+             * It is possible that actually the memory needed to propagate
+             * the DEL in AOF and replication link is greater than the one
+             * we are freeing removing the key, but we can't account for
+             * that otherwise we would never exit the loop.
+             *
+             * AOF and Output buffer memory will be freed eventually so
+             * we only care about memory used by the key space. */
+            delta = (long long) zmalloc_used_memory();
+            latencyStartMonitor(eviction_latency);
+            if (server.lazyfree_lazy_eviction)
+                dbAsyncDelete(db,keyobj);
+            else
+                dbSyncDelete(db,keyobj);
+            latencyEndMonitor(eviction_latency);
+            latencyAddSampleIfNeeded("eviction-del",eviction_latency);
+            latencyRemoveNestedEvent(latency,eviction_latency);
+            delta -= (long long) zmalloc_used_memory();
+            mem_freed += delta;
+            server.stat_evictedkeys++;
+            notifyKeyspaceEvent(NOTIFY_EVICTED, "evicted",
+                keyobj, db->id);
+            decrRefCount(keyobj);
+            keys_freed++;
+
+            /* When the memory to free starts to be big enough, we may
+             * start spending so much time here that is impossible to
+             * deliver data to the slaves fast enough, so we force the
+             * transmission here inside the loop. */
+            if (slaves) flushSlavesOutputBuffers();
+        }
+
         if (!keys_freed) {
             latencyEndMonitor(latency);
             latencyAddSampleIfNeeded("eviction-cycle",latency);