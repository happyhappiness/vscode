     return instance;
 }
 
 void
 PconnModule::registerWithCacheManager(void)
 {
-    CacheManager::GetInstance()->
-    registerAction("pconn",
-                   "Persistent Connection Utilization Histograms",
-                   DumpWrapper, 0, 1);
+    Mgr::RegisterAction("pconn",
+                        "Persistent Connection Utilization Histograms",
+                        DumpWrapper, 0, 1);
 }
 
 void
-
-PconnModule::add
-(PconnPool *aPool)
+PconnModule::add(PconnPool *aPool)
 {
     assert(poolCount < MAX_NUM_PCONN_POOLS);
     *(pools+poolCount) = aPool;
-    poolCount++;
+    ++poolCount;
 }
 
 void
 PconnModule::dump(StoreEntry *e)
 {
     int i;
 
-    for (i = 0; i < poolCount; i++) {
+    for (i = 0; i < poolCount; ++i) {
         storeAppendPrintf(e, "\n Pool %d Stats\n", i);
         (*(pools+i))->dumpHist(e);
         storeAppendPrintf(e, "\n Pool %d Hash Table\n",i);
         (*(pools+i))->dumpHash(e);
     }
 }
