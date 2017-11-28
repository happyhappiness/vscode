 #endif
 
 static void
 cbdataDump(StoreEntry * sentry)
 {
     storeAppendPrintf(sentry, "%d cbdata entries\n", cbdataCount);
-#if CBDATA_DEBUG
+#if USE_CBDATA_DEBUG
 
     storeAppendPrintf(sentry, "Pointer\tType\tLocks\tAllocated by\n");
     CBDataDumper dumper(sentry);
     for_each (cbdataEntries, dumper);
     storeAppendPrintf(sentry, "\n");
     storeAppendPrintf(sentry, "types\tsize\tallocated\ttotal\n");
 
-    for (int i = 1; i < cbdata_types; i++) {
+    for (int i = 1; i < cbdata_types; ++i) {
         MemAllocator *pool = cbdata_index[i].pool;
 
         if (pool) {
 #if HASHED_CBDATA
             int obj_size = pool->objectSize();
 #else
