  * i.e. e->referenced()
  * so that the entry can notify the creating Store
  */
 void
 StoreController::reference(StoreEntry &e)
 {
+    // special entries do not belong to any specific Store, but are IN_MEMORY
+    if (EBIT_TEST(e.flags, ENTRY_SPECIAL))
+        return;
+
     /* Notify the fs that we're referencing this object again */
 
     if (e.swap_dirn > -1)
-        e.store()->reference(e);
+        swapDir->reference(e);
 
-    /* Notify the memory cache that we're referencing this object again */
+    // Notify the memory cache that we're referencing this object again
+    if (memStore && e.mem_status == IN_MEMORY)
+        memStore->reference(e);
+
+    // TODO: move this code to a non-shared memory cache class when we have it
     if (e.mem_obj) {
         if (mem_policy->Referenced)
             mem_policy->Referenced(mem_policy, &e, &e.mem_obj->repl);
     }
 }
 
-void
-StoreController::dereference(StoreEntry & e)
+bool
+StoreController::dereference(StoreEntry &e, bool wantsLocalMemory)
 {
+    // special entries do not belong to any specific Store, but are IN_MEMORY
+    if (EBIT_TEST(e.flags, ENTRY_SPECIAL))
+        return true;
+
+    bool keepInStoreTable = false; // keep only if somebody needs it there
+
     /* Notify the fs that we're not referencing this object any more */
 
     if (e.swap_filen > -1)
-        e.store()->dereference(e);
+        keepInStoreTable = swapDir->dereference(e, wantsLocalMemory) || keepInStoreTable;
+
+    // Notify the memory cache that we're not referencing this object any more
+    if (memStore && e.mem_status == IN_MEMORY)
+        keepInStoreTable = memStore->dereference(e, wantsLocalMemory) || keepInStoreTable;
 
-    /* Notify the memory cache that we're not referencing this object any more */
+    // TODO: move this code to a non-shared memory cache class when we have it
     if (e.mem_obj) {
         if (mem_policy->Dereferenced)
             mem_policy->Dereferenced(mem_policy, &e, &e.mem_obj->repl);
+        // non-shared memory cache relies on store_table
+        if (!memStore)
+            keepInStoreTable = wantsLocalMemory || keepInStoreTable;
     }
+
+    return keepInStoreTable;
 }
 
 StoreEntry *
+StoreController::get(const cache_key *key)
+{
+    if (StoreEntry *e = swapDir->get(key)) {
+        // TODO: ignore and maybe handleIdleEntry() unlocked intransit entries
+        // because their backing store slot may be gone already.
+        debugs(20, 3, HERE << "got in-transit entry: " << *e);
+        return e;
+    }
 
-StoreController::get
-(const cache_key *key)
+    if (memStore) {
+        if (StoreEntry *e = memStore->get(key)) {
+            debugs(20, 3, HERE << "got mem-cached entry: " << *e);
+            return e;
+        }
+    }
+
+    // TODO: this disk iteration is misplaced; move to StoreHashIndex when
+    // the global store_table is no longer used for in-transit objects.
+    if (const int cacheDirs = Config.cacheSwap.n_configured) {
+        // ask each cache_dir until the entry is found; use static starting
+        // point to avoid asking the same subset of disks more often
+        // TODO: coordinate with put() to be able to guess the right disk often
+        static int idx = 0;
+        for (int n = 0; n < cacheDirs; ++n) {
+            idx = (idx + 1) % cacheDirs;
+            SwapDir *sd = dynamic_cast<SwapDir*>(INDEXSD(idx));
+            if (!sd->active())
+                continue;
+
+            if (StoreEntry *e = sd->get(key)) {
+                debugs(20, 3, HERE << "cache_dir " << idx <<
+                       " got cached entry: " << *e);
+                return e;
+            }
+        }
+    }
+
+    debugs(20, 4, HERE << "none of " << Config.cacheSwap.n_configured <<
+           " cache_dirs have " << storeKeyText(key));
+    return NULL;
+}
+
+void
+StoreController::get(String const key, STOREGETCLIENT aCallback, void *aCallbackData)
 {
+    fatal("not implemented");
+}
 
-    return swapDir->get
-           (key);
+// move this into [non-shared] memory cache class when we have one
+/// whether e should be kept in local RAM for possible future caching
+bool
+StoreController::keepForLocalMemoryCache(const StoreEntry &e) const
+{
+    if (!e.memoryCachable())
+        return false;
+
+    // does the current and expected size obey memory caching limits?
+    assert(e.mem_obj);
+    const int64_t loadedSize = e.mem_obj->endOffset();
+    const int64_t expectedSize = e.mem_obj->expectedReplySize(); // may be < 0
+    const int64_t ramSize = max(loadedSize, expectedSize);
+    const int64_t ramLimit = min(
+                                 static_cast<int64_t>(Config.memMaxSize),
+                                 static_cast<int64_t>(Config.Store.maxInMemObjSize));
+    return ramSize <= ramLimit;
 }
 
 void
+StoreController::maybeTrimMemory(StoreEntry &e, const bool preserveSwappable)
+{
+    bool keepInLocalMemory = false;
+    if (memStore)
+        keepInLocalMemory = memStore->keepInLocalMemory(e);
+    else
+        keepInLocalMemory = keepForLocalMemoryCache(e);
 
-StoreController::get
-(String const key, STOREGETCLIENT aCallback, void *aCallbackData)
+    debugs(20, 7, HERE << "keepInLocalMemory: " << keepInLocalMemory);
+
+    if (!keepInLocalMemory)
+        e.trimMemory(preserveSwappable);
+}
+
+void
+StoreController::handleIdleEntry(StoreEntry &e)
 {
-    fatal("not implemented");
+    bool keepInLocalMemory = false;
+
+    if (EBIT_TEST(e.flags, ENTRY_SPECIAL)) {
+        // Icons (and cache digests?) should stay in store_table until we
+        // have a dedicated storage for them (that would not purge them).
+        // They are not managed [well] by any specific Store handled below.
+        keepInLocalMemory = true;
+    } else if (memStore) {
+        memStore->considerKeeping(e);
+        // leave keepInLocalMemory false; memStore maintains its own cache
+    } else {
+        keepInLocalMemory = keepForLocalMemoryCache(e) && // in good shape and
+                            // the local memory cache is not overflowing
+                            (mem_node::InUseCount() <= store_pages_max);
+    }
+
+    // An idle, unlocked entry that only belongs to a SwapDir which controls
+    // its own index, should not stay in the global store_table.
+    if (!dereference(e, keepInLocalMemory)) {
+        debugs(20, 5, HERE << "destroying unlocked entry: " << &e << ' ' << e);
+        destroyStoreEntry(static_cast<hash_link*>(&e));
+        return;
+    }
+
+    debugs(20, 5, HERE << "keepInLocalMemory: " << keepInLocalMemory);
+
+    // TODO: move this into [non-shared] memory cache class when we have one
+    if (keepInLocalMemory) {
+        e.setMemStatus(IN_MEMORY);
+        e.mem_obj->unlinkRequest();
+    } else {
+        e.purgeMem(); // may free e
+    }
 }
 
 StoreHashIndex::StoreHashIndex()
 {
     if (store_table)
         abort();
