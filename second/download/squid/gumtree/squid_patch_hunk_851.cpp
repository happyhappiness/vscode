                         DumpWrapper, 0, 1);
 }
 
 void
 PconnModule::add(PconnPool *aPool)
 {
-    assert(poolCount < MAX_NUM_PCONN_POOLS);
-    *(pools+poolCount) = aPool;
-    ++poolCount;
+    pools.insert(aPool);
 }
 
 void
-PconnModule::dump(StoreEntry *e)
+PconnModule::remove(PconnPool *aPool)
 {
-    int i;
+    pools.erase(aPool);
+}
 
-    for (i = 0; i < poolCount; ++i) {
+void
+PconnModule::dump(StoreEntry *e)
+{
+    typedef Pools::const_iterator PCI;
+    int i = 0; // TODO: Why number pools if they all have names?
+    for (PCI p = pools.begin(); p != pools.end(); ++p, ++i) {
+        // TODO: Let each pool dump itself the way it wants to.
         storeAppendPrintf(e, "\n Pool %d Stats\n", i);
-        (*(pools+i))->dumpHist(e);
+        (*p)->dumpHist(e);
         storeAppendPrintf(e, "\n Pool %d Hash Table\n",i);
-        (*(pools+i))->dumpHash(e);
+        (*p)->dumpHash(e);
     }
 }
 
 void
 PconnModule::DumpWrapper(StoreEntry *e)
 {
