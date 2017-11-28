 void
 PconnPool::dumpHist(StoreEntry * e) const
 {
     storeAppendPrintf(e,
                       "%s persistent connection counts:\n"
                       "\n"
-                      "\treq/\n"
-                      "\tconn      count\n"
-                      "\t----  ---------\n",
+                      "\t Requests\t Connection Count\n"
+                      "\t --------\t ----------------\n",
                       descr);
 
     for (int i = 0; i < PCONN_HIST_SZ; ++i) {
         if (hist[i] == 0)
             continue;
 
-        storeAppendPrintf(e, "\t%4d  %9d\n", i, hist[i]);
+        storeAppendPrintf(e, "\t%d\t%d\n", i, hist[i]);
     }
 }
 
 void
 PconnPool::dumpHash(StoreEntry *e) const
 {
     hash_table *hid = table;
     hash_first(hid);
 
     int i = 0;
-    for (hash_link *walker = hid->next; walker; walker = hash_next(hid)) {
-        storeAppendPrintf(e, "\t item %5d: %s\n", i, (char *)(walker->key));
+    for (hash_link *walker = hash_next(hid); walker; walker = hash_next(hid)) {
+        storeAppendPrintf(e, "\t item %d:\t%s\n", i, (char *)(walker->key));
         ++i;
     }
 }
 
 /* ========== PconnPool PUBLIC FUNCTIONS ============================================ */
 
-PconnPool::PconnPool(const char *aDescr) : table(NULL), descr(aDescr),
-        theCount(0)
+PconnPool::PconnPool(const char *aDescr, const CbcPointer<PeerPoolMgr> &aMgr):
+    table(NULL), descr(aDescr),
+    mgr(aMgr),
+    theCount(0)
 {
     int i;
     table = hash_create((HASHCMP *) strcmp, 229, hash_string);
 
     for (i = 0; i < PCONN_HIST_SZ; ++i)
         hist[i] = 0;
 
     PconnModule::GetInstance()->add(this);
 }
 
+static void
+DeleteIdleConnList(void *hashItem)
+{
+    delete reinterpret_cast<IdleConnList*>(hashItem);
+}
+
 PconnPool::~PconnPool()
 {
-    descr = NULL;
+    PconnModule::GetInstance()->remove(this);
+    hashFreeItems(table, &DeleteIdleConnList);
     hashFreeMemory(table);
+    descr = NULL;
 }
 
 void
 PconnPool::push(const Comm::ConnectionPointer &conn, const char *domain)
 {
     if (fdUsageHigh()) {
