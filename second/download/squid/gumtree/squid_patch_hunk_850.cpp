     assert(!comm_has_incomplete_write(conn->fd));
 
     LOCAL_ARRAY(char, desc, FD_DESC_SZ);
     snprintf(desc, FD_DESC_SZ, "Idle server: %s", aKey);
     fd_note(conn->fd, desc);
     debugs(48, 3, HERE << "pushed " << conn << " for " << aKey);
+
+    // successful push notifications resume multi-connection opening sequence
+    notifyManager("push");
 }
 
 Comm::ConnectionPointer
-PconnPool::pop(const Comm::ConnectionPointer &destLink, const char *domain, bool isRetriable)
+PconnPool::pop(const Comm::ConnectionPointer &dest, const char *domain, bool keepOpen)
 {
-    const char * aKey = key(destLink, domain);
+
+    const char * aKey = key(dest, domain);
 
     IdleConnList *list = (IdleConnList *)hash_lookup(table, aKey);
     if (list == NULL) {
         debugs(48, 3, HERE << "lookup for key {" << aKey << "} failed.");
+        // failure notifications resume standby conn creation after fdUsageHigh
+        notifyManager("pop failure");
         return Comm::ConnectionPointer();
     } else {
-        debugs(48, 3, HERE << "found " << hashKeyStr(&list->hash) << (isRetriable?"(to use)":"(to kill)") );
+        debugs(48, 3, HERE << "found " << hashKeyStr(&list->hash) <<
+               (keepOpen ? " to use" : " to kill"));
     }
 
     /* may delete list */
-    Comm::ConnectionPointer temp = list->findUseable(destLink);
-    if (!isRetriable && Comm::IsConnOpen(temp))
-        temp->close();
+    Comm::ConnectionPointer popped = list->findUseable(dest);
+    if (!keepOpen && Comm::IsConnOpen(popped))
+        popped->close();
 
-    return temp;
+    // successful pop notifications replenish standby connections pool
+    notifyManager("pop");
+    return popped;
 }
 
 void
-PconnPool::closeN(int n, const Comm::ConnectionPointer &destLink, const char *domain)
+PconnPool::notifyManager(const char *reason)
 {
-    // TODO: optimize: we can probably do hash_lookup just once
-    for (int i = 0; i < n; ++i)
-        pop(destLink, domain, false); // may fail!
+    if (mgr.valid())
+        PeerPoolMgr::Checkpoint(mgr, reason);
+}
+
+void
+PconnPool::closeN(int n)
+{
+    hash_table *hid = table;
+    hash_first(hid);
+
+    // close N connections, one per list, to treat all lists "fairly"
+    for (int i = 0; i < n && count(); ++i) {
+
+        hash_link *current = hash_next(hid);
+        if (!current) {
+            hash_first(hid);
+            current = hash_next(hid);
+            Must(current); // must have one because the count() was positive
+        }
+
+        // may delete current
+        reinterpret_cast<IdleConnList*>(current)->closeN(1);
+    }
 }
 
 void
 PconnPool::unlinkList(IdleConnList *list)
 {
     theCount -= list->count();
