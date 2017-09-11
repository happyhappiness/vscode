@@ -58,14 +58,16 @@ void* activeDefragAlloc(void *ptr) {
         server.stat_active_defrag_misses++;
         return NULL;
     }
-    /* if this run is more utilized than the average utilization in this bin (or it is full), skip it.
-     * this will eventually move all the allocations from relatively empty runs into relatively full runs. */
+    /* if this run is more utilized than the average utilization in this bin
+     * (or it is full), skip it. This will eventually move all the allocations
+     * from relatively empty runs into relatively full runs. */
     if (run_util > bin_util || run_util == 1<<16) {
         server.stat_active_defrag_misses++;
         return NULL;
     }
     /* move this allocation to a new allocation.
-     * make sure not to use the thread cache. so that we don't get back the same pointers we try to free */
+     * make sure not to use the thread cache. so that we don't get back the same
+     * pointers we try to free */
     size = zmalloc_size(ptr);
     newptr = zmalloc_no_tcache(size);
     memcpy(newptr, ptr, size);
@@ -99,7 +101,7 @@ robj *activeDefragStringOb(robj* ob, int *defragged) {
     if (ob->refcount!=1)
         return NULL;
 
-    /* try to defrag robj (only if not an EMBSTR type (handled below) */
+    /* try to defrag robj (only if not an EMBSTR type (handled below). */
     if (ob->type!=OBJ_STRING || ob->encoding!=OBJ_ENCODING_EMBSTR) {
         if ((ret = activeDefragAlloc(ob))) {
             ob = ret;
@@ -116,7 +118,8 @@ robj *activeDefragStringOb(robj* ob, int *defragged) {
                 (*defragged)++;
             }
         } else if (ob->encoding==OBJ_ENCODING_EMBSTR) {
-            /* the sds is embedded in the object allocation, calculate the offset and update the pointer in the new allocation */
+            /* The sds is embedded in the object allocation, calculate the
+             * offset and update the pointer in the new allocation. */
             long ofs = (intptr_t)ob->ptr - (intptr_t)ob;
             if ((ret = activeDefragAlloc(ob))) {
                 ret->ptr = (void*)((intptr_t)ret + ofs);
@@ -129,14 +132,16 @@ robj *activeDefragStringOb(robj* ob, int *defragged) {
     return ret;
 }
 
-/* Defrag helper for dictEntries to be used during dict iteration (called on each step).
- * returns a stat of how many pointers were moved. */
+/* Defrag helper for dictEntries to be used during dict iteration (called on
+ * each step). Teturns a stat of how many pointers were moved. */
 int dictIterDefragEntry(dictIterator *iter) {
-    /* This function is a little bit dirty since it messes with the internals of the dict and it's iterator,
-     * but the benefit is that it is very easy to use, and require no other chagnes in the dict. */
+    /* This function is a little bit dirty since it messes with the internals
+     * of the dict and it's iterator, but the benefit is that it is very easy
+     * to use, and require no other chagnes in the dict. */
     int defragged = 0;
     dictht *ht;
-    /* handle the next entry (if there is one), and update the pointer in the current entry. */
+    /* Handle the next entry (if there is one), and update the pointer in the
+     * current entry. */
     if (iter->nextEntry) {
         dictEntry *newde = activeDefragAlloc(iter->nextEntry);
         if (newde) {
@@ -159,8 +164,8 @@ int dictIterDefragEntry(dictIterator *iter) {
 }
 
 /* Defrag helper for dict main allocations (dict struct, and hash tables).
- * receives a pointer to the dict* and implicitly updates it when the dict struct itself was moved.
- * returns a stat of how many pointers were moved. */
+ * receives a pointer to the dict* and implicitly updates it when the dict
+ * struct itself was moved. Returns a stat of how many pointers were moved. */
 int dictDefragTables(dict** dictRef) {
     dict *d = *dictRef;
     dictEntry **newtable;
@@ -200,10 +205,12 @@ void zslUpdateNode(zskiplist *zsl, zskiplistNode *oldnode, zskiplistNode *newnod
 }
 
 /* Defrag helper for sorted set.
- * Update the robj pointer, defrag the skiplist struct and return the new score reference.
- * we may not access oldele pointer (not even the pointer stored in the skiplist), as it was already freed.
- * newele may be null, in which case we only need to defrag the skiplist, but not update the obj pointer.
- * when return value is non-NULL, it is the score reference that must be updated in the dict record. */
+ * Update the robj pointer, defrag the skiplist struct and return the new score
+ * reference. We may not access oldele pointer (not even the pointer stored in
+ * the skiplist), as it was already freed. Newele may be null, in which case we
+ * only need to defrag the skiplist, but not update the obj pointer.
+ * When return value is non-NULL, it is the score reference that must be updated
+ * in the dict record. */
 double *zslDefrag(zskiplist *zsl, double score, sds oldele, sds newele) {
     zskiplistNode *update[ZSKIPLIST_MAXLEVEL], *x, *newx;
     int i;
@@ -214,7 +221,9 @@ double *zslDefrag(zskiplist *zsl, double score, sds oldele, sds newele) {
     x = zsl->header;
     for (i = zsl->level-1; i >= 0; i--) {
         while (x->level[i].forward &&
-            x->level[i].forward->ele != oldele && /* make sure not to access the ->obj pointer if it matches oldele */
+            x->level[i].forward->ele != oldele && /* make sure not to access the
+                                                     ->obj pointer if it matches
+                                                     oldele */
             (x->level[i].forward->score < score ||
                 (x->level[i].forward->score == score &&
                 sdscmp(x->level[i].forward->ele,ele) < 0)))
@@ -237,12 +246,13 @@ double *zslDefrag(zskiplist *zsl, double score, sds oldele, sds newele) {
     return NULL;
 }
 
-/* Utility function that replaces an old key pointer in the dictionary with a new pointer.
- * Additionally, we try to defrag the dictEntry in that dict.
- * oldkey mey be a dead pointer and should not be accessed (we get a pre-calculated hash value).
- * newkey may be null if the key pointer wasn't moved.
- * return value is the the dictEntry if found, or NULL if not found.
- * NOTE: this is very ugly code, but it let's us avoid the complication of doing a scan on another dict. */
+/* Utility function that replaces an old key pointer in the dictionary with a
+ * new pointer. Additionally, we try to defrag the dictEntry in that dict.
+ * Oldkey mey be a dead pointer and should not be accessed (we get a
+ * pre-calculated hash value). Newkey may be null if the key pointer wasn't
+ * moved. Return value is the the dictEntry if found, or NULL if not found.
+ * NOTE: this is very ugly code, but it let's us avoid the complication of
+ * doing a scan on another dict. */
 dictEntry* replaceSateliteDictKeyPtrAndOrDefragDictEntry(dict *d, sds oldkey, sds newkey, unsigned int hash, int *defragged) {
     dictEntry **deref = dictFindEntryRefByPtrAndHash(d, oldkey, hash);
     if (deref) {
@@ -259,8 +269,9 @@ dictEntry* replaceSateliteDictKeyPtrAndOrDefragDictEntry(dict *d, sds oldkey, sd
     return NULL;
 }
 
-/* for each key we scan in the main dict, this function will attempt to defrag all the various pointers it has.
- * returns a stat of how many pointers were moved. */
+/* for each key we scan in the main dict, this function will attempt to defrag
+ * all the various pointers it has. Returns a stat of how many pointers were
+ * moved. */
 int defargKey(redisDb *db, dictEntry *de) {
     sds keysds = dictGetKey(de);
     robj *newob, *ob;
@@ -270,27 +281,27 @@ int defargKey(redisDb *db, dictEntry *de) {
     int defragged = 0;
     sds newsds;
 
-    /* try to defrag the key name */
+    /* Try to defrag the key name. */
     newsds = activeDefragSds(keysds);
     if (newsds)
         defragged++, de->key = newsds;
     if (dictSize(db->expires)) {
          /* Dirty code:
-          * i can't search in db->expires for that key after i already released the pointer it holds
-          * it won't be able to do the string compare */
+          * I can't search in db->expires for that key after i already released
+          * the pointer it holds it won't be able to do the string compare */
         unsigned int hash = dictGetHash(db->dict, de->key);
         replaceSateliteDictKeyPtrAndOrDefragDictEntry(db->expires, keysds, newsds, hash, &defragged);
     }
 
-    /* try to defrag robj and / or string value */
+    /* Try to defrag robj and / or string value. */
     ob = dictGetVal(de);
     if ((newob = activeDefragStringOb(ob, &defragged))) {
         de->v.val = newob;
         ob = newob;
     }
 
     if (ob->type == OBJ_STRING) {
-        /* already handled in activeDefragStringOb */
+        /* Already handled in activeDefragStringOb. */
     } else if (ob->type == OBJ_LIST) {
         if (ob->encoding == OBJ_ENCODING_QUICKLIST) {
             quicklist *ql = ob->ptr, *newql;
@@ -400,7 +411,7 @@ int defargKey(redisDb *db, dictEntry *de) {
     return defragged;
 }
 
-/* defrag scan callback for the main db dictionary */
+/* Defrag scan callback for the main db dictionary. */
 void defragScanCallback(void *privdata, const dictEntry *de) {
     int defragged = defargKey((redisDb*)privdata, (dictEntry*)de);
     server.stat_active_defrag_hits += defragged;
@@ -410,8 +421,8 @@ void defragScanCallback(void *privdata, const dictEntry *de) {
         server.stat_active_defrag_key_misses++;
 }
 
-/* defrag scan callback for for each hash table bicket,
- * used in order to defrag the dictEntry allocations */
+/* Defrag scan callback for for each hash table bicket,
+ * used in order to defrag the dictEntry allocations. */
 void defragDictBucketCallback(void *privdata, dictEntry **bucketref) {
     UNUSED(privdata);
     while(*bucketref) {
@@ -424,15 +435,24 @@ void defragDictBucketCallback(void *privdata, dictEntry **bucketref) {
 }
 
 /* Utility function to get the fragmentation ratio from jemalloc.
- * it is critical to do that by comparing only heap maps that belown to jemalloc, and skip ones the jemalloc keeps as spare.
- * since we use this fragmentation ratio in order to decide if a defrag action should be taken or not,
- * a false detection can cause the defragmenter to waste a lot of CPU without the possibility of getting any results. */
+ * It is critical to do that by comparing only heap maps that belown to
+ * jemalloc, and skip ones the jemalloc keeps as spare. Since we use this
+ * fragmentation ratio in order to decide if a defrag action should be taken
+ * or not, a false detection can cause the defragmenter to waste a lot of CPU
+ * without the possibility of getting any results. */
 float getAllocatorFragmentation(size_t *out_frag_bytes) {
     size_t epoch = 1, allocated = 0, resident = 0, active = 0, sz = sizeof(size_t);
-    je_mallctl("epoch", &epoch, &sz, &epoch, sz); /* Update the statistics cached by mallctl. */
-    je_mallctl("stats.resident", &resident, &sz, NULL, 0); /* unlike RSS, this does not include RSS from shared libraries and other non heap mappings */
-    je_mallctl("stats.active", &active, &sz, NULL, 0); /* unlike resident, this doesn't not include the pages jemalloc reserves for re-use (purge will clean that) */
-    je_mallctl("stats.allocated", &allocated, &sz, NULL, 0); /* unlike zmalloc_used_memory, this matches the stats.resident by taking into account all allocations done by this process (not only zmalloc) */
+    /* Update the statistics cached by mallctl. */
+    je_mallctl("epoch", &epoch, &sz, &epoch, sz);
+    /* Unlike RSS, this does not include RSS from shared libraries and other non
+     * heap mappings. */
+    je_mallctl("stats.resident", &resident, &sz, NULL, 0);
+    /* Unlike resident, this doesn't not include the pages jemalloc reserves
+     * for re-use (purge will clean that). */
+    je_mallctl("stats.active", &active, &sz, NULL, 0);
+    /* Unlike zmalloc_used_memory, this matches the stats.resident by taking
+     * into account all allocations done by this process (not only zmalloc). */
+    je_mallctl("stats.allocated", &allocated, &sz, NULL, 0);
     float frag_pct = ((float)active / allocated)*100 - 100;
     size_t frag_bytes = active - allocated;
     float rss_pct = ((float)resident / allocated)*100 - 100;
@@ -461,24 +481,33 @@ void activeDefragCycle(void) {
     long long start, timelimit;
 
     if (server.aof_child_pid!=-1 || server.rdb_child_pid!=-1)
-        return; /* defragging memory while there's a fork will just do damage. */
+        return; /* Defragging memory while there's a fork will just do damage. */
 
-    /* once a second, check if we the fragmentation justfies starting a scan or making it more aggressive */
+    /* Once a second, check if we the fragmentation justfies starting a scan
+     * or making it more aggressive. */
     run_with_period(1000) {
         size_t frag_bytes;
         float frag_pct = getAllocatorFragmentation(&frag_bytes);
-        /* if we're not already running, and below the threshold, exit. */
+        /* If we're not already running, and below the threshold, exit. */
         if (!server.active_defrag_running) {
             if(frag_pct < server.active_defrag_threshold_lower || frag_bytes < server.active_defrag_ignore_bytes)
                 return;
         }
 
-        /* calculate the adaptive aggressiveness of the defrag */
-        int cpu_pct = INTERPOLATE(frag_pct, server.active_defrag_threshold_lower, server.active_defrag_threshold_upper,
-                                  server.active_defrag_cycle_min, server.active_defrag_cycle_max);
-        cpu_pct = LIMIT(cpu_pct, server.active_defrag_cycle_min, server.active_defrag_cycle_max);
-         /* we allow increasing the aggressiveness during a scan, but don't reduce it */
-        if (!server.active_defrag_running || cpu_pct > server.active_defrag_running) {
+        /* Calculate the adaptive aggressiveness of the defrag */
+        int cpu_pct = INTERPOLATE(frag_pct,
+                server.active_defrag_threshold_lower,
+                server.active_defrag_threshold_upper,
+                server.active_defrag_cycle_min,
+                server.active_defrag_cycle_max);
+        cpu_pct = LIMIT(cpu_pct,
+                server.active_defrag_cycle_min,
+                server.active_defrag_cycle_max);
+         /* We allow increasing the aggressiveness during a scan, but don't
+          * reduce it. */
+        if (!server.active_defrag_running ||
+            cpu_pct > server.active_defrag_running)
+        {
             server.active_defrag_running = cpu_pct;
             serverLog(LL_VERBOSE,
                 "Starting active defrag, frag=%.0f%%, frag_bytes=%zu, cpu=%d%%",
@@ -495,7 +524,7 @@ void activeDefragCycle(void) {
 
     do {
         if (!cursor) {
-            /* Move on to next database, and stop if we reached the last one */
+            /* Move on to next database, and stop if we reached the last one. */
             if (++current_db >= server.dbnum) {
                 long long now = ustime();
                 size_t frag_bytes;
@@ -512,7 +541,7 @@ void activeDefragCycle(void) {
                 return;
             }
             else if (current_db==0) {
-                /* start a scan from the first database */
+                /* Start a scan from the first database. */
                 start_scan = ustime();
                 start_stat = server.stat_active_defrag_hits;
             }
@@ -523,8 +552,9 @@ void activeDefragCycle(void) {
 
         do {
             cursor = dictScan(db->dict, cursor, defragScanCallback, defragDictBucketCallback, db);
-            /* once in 16 scan iterations, or 1000 pointer reallocations (if we have a lot of pointers in one hash bucket),
-             * check if we reached the tiem limit */
+            /* Once in 16 scan iterations, or 1000 pointer reallocations
+             * (if we have a lot of pointers in one hash bucket), check if we
+             * reached the tiem limit. */
             if (cursor && (++iterations > 16 || server.stat_active_defrag_hits - defragged > 1000)) {
                 if ((ustime() - start) > timelimit) {
                     return;
@@ -539,7 +569,7 @@ void activeDefragCycle(void) {
 #else /* HAVE_DEFRAG */
 
 void activeDefragCycle(void) {
-    /* not implemented yet*/
+    /* Not implemented yet. */
 }
 
 #endif