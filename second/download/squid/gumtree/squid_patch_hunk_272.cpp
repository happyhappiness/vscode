            std::hex << std::uppercase << std::setfill('0') << std::setw(8) << e->swap_filen);
 
     dynamic_cast<SwapDir *>(INDEXSD(e->swap_dirn))->logEntry(*e, op);
 }
 
 void
-StoreController::updateSize(int64_t size, int sign)
+StoreController::getStats(StoreInfoStats &stats) const
 {
-    fatal("StoreController has no independent size\n");
-}
+    if (memStore)
+        memStore->getStats(stats);
+    else {
+        // move this code to a non-shared memory cache class when we have it
+        stats.mem.shared = false;
+        stats.mem.capacity = Config.memMaxSize;
+        stats.mem.size = mem_node::StoreMemSize();
+        stats.mem.count = hot_obj_count;
+    }
 
-void
-SwapDir::updateSize(int64_t size, int sign)
-{
-    int64_t blks = (size + fs.blksize - 1) / fs.blksize;
-    int64_t k = ((blks * fs.blksize) >> 10) * sign;
-    cur_size += k;
-    store_swap_size += k;
+    swapDir->getStats(stats);
 
-    if (sign > 0)
-        n_disk_objects++;
-    else if (sign < 0)
-        n_disk_objects--;
+    // low-level info not specific to memory or disk cache
+    stats.store_entry_count = StoreEntry::inUseCount();
+    stats.mem_object_count = MemObject::inUseCount();
 }
 
 void
 StoreController::stat(StoreEntry &output) const
 {
     storeAppendPrintf(&output, "Store Directory Statistics:\n");
     storeAppendPrintf(&output, "Store Entries          : %lu\n",
                       (unsigned long int)StoreEntry::inUseCount());
     storeAppendPrintf(&output, "Maximum Swap Size      : %" PRIu64 " KB\n",
-                      maxSize());
-    storeAppendPrintf(&output, "Current Store Swap Size: %8lu KB\n",
-                      store_swap_size);
-    storeAppendPrintf(&output, "Current Capacity       : %" PRId64 "%% used, %" PRId64 "%% free\n",
-                      Math::int64Percent(store_swap_size, maxSize()),
-                      Math::int64Percent((maxSize() - store_swap_size), maxSize()));
-    /* FIXME Here we should output memory statistics */
+                      maxSize() >> 10);
+    storeAppendPrintf(&output, "Current Store Swap Size: %.2f KB\n",
+                      currentSize() / 1024.0);
+    storeAppendPrintf(&output, "Current Capacity       : %.2f%% used, %.2f%% free\n",
+                      Math::doublePercent(currentSize(), maxSize()),
+                      Math::doublePercent((maxSize() - currentSize()), maxSize()));
+
+    if (memStore)
+        memStore->stat(output);
 
     /* now the swapDir */
     swapDir->stat(output);
 }
 
 /* if needed, this could be taught to cache the result */
