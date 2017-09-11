@@ -39,14 +39,14 @@
 #include <assert.h>
 #include <stddef.h>
 
-#if defined(USE_JEMALLOC) && defined(MALLOCX_TCACHE_NONE)
+#ifdef HAVE_DEFRAG
 
 /* this method was added to jemalloc in order to help us understand which
  * pointers are worthwhile moving and which aren't */
 int je_get_defrag_hint(void* ptr, int *bin_util, int *run_util);
 
 /* Defrag helper for generic allocations.
- * 
+ *
  * returns NULL in case the allocatoin wasn't moved.
  * when it returns a non-null value, the old pointer was already released
  * and should NOT be accessed. */
@@ -58,13 +58,13 @@ void* activeDefragAlloc(void *ptr) {
         server.stat_active_defrag_misses++;
         return NULL;
     }
-    /* if this run is more utilized than the average utilization in this bin (or it is full), skip it. 
+    /* if this run is more utilized than the average utilization in this bin (or it is full), skip it.
      * this will eventually move all the allocations from relatively empty runs into relatively full runs. */
     if (run_util > bin_util || run_util == 1<<16) {
         server.stat_active_defrag_misses++;
         return NULL;
     }
-    /* move this allocation to a new allocation. 
+    /* move this allocation to a new allocation.
      * make sure not to use the thread cache. so that we don't get back the same pointers we try to free */
     size = zmalloc_size(ptr);
     newptr = zmalloc_no_tcache(size);
@@ -74,7 +74,7 @@ void* activeDefragAlloc(void *ptr) {
 }
 
 /*Defrag helper for sds strings
- * 
+ *
  * returns NULL in case the allocatoin wasn't moved.
  * when it returns a non-null value, the old pointer was already released
  * and should NOT be accessed. */
@@ -90,7 +90,7 @@ sds activeDefragSds(sds sdsptr) {
 }
 
 /* Defrag helper for robj and/or string objects
- * 
+ *
  * returns NULL in case the allocatoin wasn't moved.
  * when it returns a non-null value, the old pointer was already released
  * and should NOT be accessed. */
@@ -221,7 +221,7 @@ double *zslDefrag(zskiplist *zsl, double score, sds oldele, sds newele) {
             x = x->level[i].forward;
         update[i] = x;
     }
-    
+
     /* update the robj pointer inside the skip list record. */
     x = x->level[0].forward;
     serverAssert(x && score == x->score && x->ele==oldele);
@@ -243,7 +243,7 @@ double *zslDefrag(zskiplist *zsl, double score, sds oldele, sds newele) {
  * newkey may be null if the key pointer wasn't moved.
  * return value is the the dictEntry if found, or NULL if not found.
  * NOTE: this is very ugly code, but it let's us avoid the complication of doing a scan on another dict. */
-dictEntry* replaceSateliteDictKeyPtrAndOrDifragDictEntry(dict *d, sds oldkey, sds newkey, unsigned int hash, int *defragged) {
+dictEntry* replaceSateliteDictKeyPtrAndOrDefragDictEntry(dict *d, sds oldkey, sds newkey, unsigned int hash, int *defragged) {
     dictEntry **deref = dictFindEntryRefByPtrAndHash(d, oldkey, hash);
     if (deref) {
         dictEntry *de = *deref;
@@ -269,7 +269,7 @@ int defargKey(redisDb *db, dictEntry *de) {
     dictIterator *di;
     int defragged = 0;
     sds newsds;
-    
+
     /* try to defrag the key name */
     newsds = activeDefragSds(keysds);
     if (newsds)
@@ -279,7 +279,7 @@ int defargKey(redisDb *db, dictEntry *de) {
           * i can't search in db->expires for that key after i already released the pointer it holds
           * it won't be able to do the string compare */
         unsigned int hash = dictGetHash(db->dict, de->key);
-        replaceSateliteDictKeyPtrAndOrDifragDictEntry(db->expires, keysds, newsds, hash, &defragged);
+        replaceSateliteDictKeyPtrAndOrDefragDictEntry(db->expires, keysds, newsds, hash, &defragged);
     }
 
     /* try to defrag robj and / or string value */
@@ -334,7 +334,7 @@ int defargKey(redisDb *db, dictEntry *de) {
         } else if (ob->encoding == OBJ_ENCODING_INTSET) {
             intset *is = ob->ptr;
             intset *newis = activeDefragAlloc(is);
-            if (newis) 
+            if (newis)
                 defragged++, ob->ptr = newis;
         } else {
             serverPanic("Unknown set encoding");
@@ -407,7 +407,7 @@ void defragScanCallback(void *privdata, const dictEntry *de) {
     if(defragged)
         server.stat_active_defrag_key_hits++;
     else
-        server.stat_active_defrag_key_misses++;    
+        server.stat_active_defrag_key_misses++;
 }
 
 /* defrag scan callback for for each hash table bicket,
@@ -439,8 +439,8 @@ float getAllocatorFragmentation(size_t *out_frag_bytes) {
     size_t rss_bytes = resident - allocated;
     if(out_frag_bytes)
         *out_frag_bytes = frag_bytes;
-    serverLog(LL_DEBUG, 
-        "allocated=%zu, active=%zu, resident=%zu, frag=%.0f%% (%.0f%% rss), frag_bytes=%zu (%zu%% rss)", 
+    serverLog(LL_DEBUG,
+        "allocated=%zu, active=%zu, resident=%zu, frag=%.0f%% (%.0f%% rss), frag_bytes=%zu (%zu%% rss)",
         allocated, active, resident, frag_pct, rss_pct, frag_bytes, rss_bytes);
     return frag_pct;
 }
@@ -459,10 +459,10 @@ void activeDefragCycle(void) {
     unsigned int iterations = 0;
     unsigned long long defragged = server.stat_active_defrag_hits;
     long long start, timelimit;
-    
+
     if (server.aof_child_pid!=-1 || server.rdb_child_pid!=-1)
         return; /* defragging memory while there's a fork will just do damage. */
-    
+
     /* once a second, check if we the fragmentation justfies starting a scan or making it more aggressive */
     run_with_period(1000) {
         size_t frag_bytes;
@@ -472,16 +472,16 @@ void activeDefragCycle(void) {
             if(frag_pct < server.active_defrag_threshold_lower || frag_bytes < server.active_defrag_ignore_bytes)
                 return;
         }
-        
+
         /* calculate the adaptive aggressiveness of the defrag */
-        int cpu_pct = INTERPOLATE(frag_pct, server.active_defrag_threshold_lower, server.active_defrag_threshold_upper, 
+        int cpu_pct = INTERPOLATE(frag_pct, server.active_defrag_threshold_lower, server.active_defrag_threshold_upper,
                                   server.active_defrag_cycle_min, server.active_defrag_cycle_max);
         cpu_pct = LIMIT(cpu_pct, server.active_defrag_cycle_min, server.active_defrag_cycle_max);
          /* we allow increasing the aggressiveness during a scan, but don't reduce it */
         if (!server.active_defrag_running || cpu_pct > server.active_defrag_running) {
             server.active_defrag_running = cpu_pct;
-            serverLog(LL_VERBOSE, 
-                "Starting active defrag, frag=%.0f%%, frag_bytes=%zu, cpu=%d%%", 
+            serverLog(LL_VERBOSE,
+                "Starting active defrag, frag=%.0f%%, frag_bytes=%zu, cpu=%d%%",
                 frag_pct, frag_bytes, cpu_pct);
         }
     }
@@ -500,7 +500,7 @@ void activeDefragCycle(void) {
                 long long now = ustime();
                 size_t frag_bytes;
                 float frag_pct = getAllocatorFragmentation(&frag_bytes);
-                serverLog(LL_VERBOSE, 
+                serverLog(LL_VERBOSE,
                     "Active defrag done in %dms, reallocated=%d, frag=%.0f%%, frag_bytes=%zu",
                     (int)((now - start_scan)/1000), (int)(server.stat_active_defrag_hits - start_stat), frag_pct, frag_bytes);
 
@@ -536,7 +536,7 @@ void activeDefragCycle(void) {
     } while(1);
 }
 
-#else /* USE_JEMALLOC */
+#else /* HAVE_DEFRAG */
 
 void activeDefragCycle(void) {
     /* not implemented yet*/