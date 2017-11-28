 #endif
     static void logReplyStatus(int tries, const Http::StatusCode status);
     void doneWithRetries();
     void completed();
     void retryOrBail();
     ErrorState *makeConnectingError(const err_type type) const;
+#if USE_OPENSSL
+    void connectedToPeer(Ssl::PeerConnectorAnswer &answer);
+#endif
     static void RegisterWithCacheManager(void);
 
+    /// stops monitoring server connection for closure and updates pconn stats
+    void closeServerConnection(const char *reason);
+
+    void syncWithServerConn(const char *host);
+
 public:
     StoreEntry *entry;
     HttpRequest *request;
     AccessLogEntryPointer al; ///< info for the future access.log entry
 
     static void abort(void*);
