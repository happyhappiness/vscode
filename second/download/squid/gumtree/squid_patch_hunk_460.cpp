         fatal("'store_avg_object_size' should be larger than 0.");
 
     /* Calculate size of hash table (maximum currently 64k buckets).  */
     /* this is very bogus, its specific to the any Store maintaining an
      * in-core index, not global */
     size_t buckets = (Store::Root().maxSize() + Config.memMaxSize) / Config.Store.avgObjectSize;
-    debugs(20, 1, "Swap maxSize " << (Store::Root().maxSize() >> 10) <<
+    debugs(20, DBG_IMPORTANT, "Swap maxSize " << (Store::Root().maxSize() >> 10) <<
            " + " << ( Config.memMaxSize >> 10) << " KB, estimated " << buckets << " objects");
     buckets /= Config.Store.objectsPerBucket;
-    debugs(20, 1, "Target number of buckets: " << buckets);
+    debugs(20, DBG_IMPORTANT, "Target number of buckets: " << buckets);
     /* ideally the full scan period should be configurable, for the
      * moment it remains at approximately 24 hours.  */
     store_hash_buckets = storeKeyHashBuckets(buckets);
-    debugs(20, 1, "Using " << store_hash_buckets << " Store buckets");
-    debugs(20, 1, "Max Mem  size: " << ( Config.memMaxSize >> 10) << " KB" <<
+    debugs(20, DBG_IMPORTANT, "Using " << store_hash_buckets << " Store buckets");
+    debugs(20, DBG_IMPORTANT, "Max Mem  size: " << ( Config.memMaxSize >> 10) << " KB" <<
            (Config.memShared ? " [shared]" : ""));
-    debugs(20, 1, "Max Swap size: " << (Store::Root().maxSize() >> 10) << " KB");
+    debugs(20, DBG_IMPORTANT, "Max Swap size: " << (Store::Root().maxSize() >> 10) << " KB");
 
     store_table = hash_create(storeKeyHashCmp,
                               store_hash_buckets, storeKeyHashHash);
 
     for (int i = 0; i < Config.cacheSwap.n_configured; ++i) {
         /* this starts a search of the store dirs, loading their
