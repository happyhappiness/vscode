  * idle connections across the collection.
  */
 class PconnPool
 {
 
 public:
-    PconnPool(const char *);
+    PconnPool(const char *aDescription, const CbcPointer<PeerPoolMgr> &aMgr);
     ~PconnPool();
 
     void moduleInit();
     void push(const Comm::ConnectionPointer &serverConn, const char *domain);
 
     /**
-     * Updates destLink to point at an existing open connection if available and retriable.
-     * Otherwise, return false.
+     * Returns either a pointer to a popped connection to dest or nil.
+     * Closes the connection before returning its pointer unless keepOpen.
      *
-     * We close available persistent connection if the caller transaction is not
-     * retriable to avoid having a growing number of open connections when many
-     * transactions create persistent connections but are not retriable.
+     * A caller with a non-retriable transaction should set keepOpen to false
+     * and call pop() anyway, even though the caller does not want a pconn.
+     * This forces us to close an available persistent connection, avoiding
+     * creating a growing number of open connections when many transactions
+     * create (and push) persistent connections but are not retriable and,
+     * hence, do not need to pop a connection.
      */
-    Comm::ConnectionPointer pop(const Comm::ConnectionPointer &destLink, const char *domain, bool retriable);
+    Comm::ConnectionPointer pop(const Comm::ConnectionPointer &dest, const char *domain, bool keepOpen);
     void count(int uses);
     void dumpHist(StoreEntry *e) const;
     void dumpHash(StoreEntry *e) const;
     void unlinkList(IdleConnList *list);
     void noteUses(int uses);
-    void closeN(int n, const Comm::ConnectionPointer &destLink, const char *domain);
+    /// closes any n connections, regardless of their destination
+    void closeN(int n);
     int count() const { return theCount; }
     void noteConnectionAdded() { ++theCount; }
     void noteConnectionRemoved() { assert(theCount > 0); --theCount; }
 
+    // sends an async message to the pool manager, if any
+    void notifyManager(const char *reason);
+
 private:
 
     static const char *key(const Comm::ConnectionPointer &destLink, const char *domain);
 
     int hist[PCONN_HIST_SZ];
     hash_table *table;
     const char *descr;
+    CbcPointer<PeerPoolMgr> mgr; ///< optional pool manager (for notifications)
     int theCount; ///< the number of pooled connections
 };
 
 class StoreEntry;
 class PconnPool;
 
