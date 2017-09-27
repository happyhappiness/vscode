     /* Perform the iteration inside the mutex to avoid corruption or invalid
      * pointer arithmetic. The rest of our logic uses read-only header data so
      * doesn't need the lock. */
     /* Iterate over the subcaches */
     for (loop = 0; loop < header->subcache_num && rv == APR_SUCCESS; loop++) {
         SHMCBSubcache *subcache = SHMCB_SUBCACHE(header, loop);
-        rv = shmcb_subcache_iterate(instance, s, header, subcache, iterator,
-                                    &buf, &buflen, pool, now);
+        rv = shmcb_subcache_iterate(instance, s, userctx, header, subcache,
+                                    iterator, &buf, &buflen, pool, now);
     }
     return rv;
 }
 
 /*
  * Subcache-level cache operations 
  */
 
 static void shmcb_subcache_expire(server_rec *s, SHMCBHeader *header,
                                   SHMCBSubcache *subcache, apr_time_t now)
 {
-    unsigned int loop = 0;
+    unsigned int loop = 0, freed = 0, expired = 0;
     unsigned int new_idx_pos = subcache->idx_pos;
     SHMCBIndex *idx = NULL;
 
     while (loop < subcache->idx_used) {
         idx = SHMCB_INDEX(subcache, new_idx_pos);
-        if (idx->expires > now)
-            /* it hasn't expired yet, we're done iterating */
+        if (idx->removed)
+            freed++;
+        else if (idx->expires <= now)
+            expired++;
+        else
+            /* not removed and not expired yet, we're done iterating */
             break;
         loop++;
         new_idx_pos = SHMCB_CYCLIC_INCREMENT(new_idx_pos, 1, header->index_num);
     }
     if (!loop)
         /* Nothing to do */
         return;
     ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
-                 "will be expiring %u socache entries", loop);
+                 "expiring %u and reclaiming %u removed socache entries",
+                 expired, freed);
     if (loop == subcache->idx_used) {
         /* We're expiring everything, piece of cake */
         subcache->idx_used = 0;
         subcache->data_used = 0;
     } else {
         /* There remain other indexes, so we can use idx to adjust 'data' */
