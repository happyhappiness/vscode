     }
 
     /// Sends "502 Bad Gateway" error response to the client,
     /// if it is waiting for Squid CONNECT response, closing connections.
     void informUserOfPeerError(const char *errMsg, size_t);
 
+    /// starts connecting to the next hop, either for the first time or while
+    /// recovering from the previous connect failure
+    void startConnecting();
+
     class Connection
     {
 
     public:
         Connection() : len (0), buf ((char *)xmalloc(SQUID_TCP_SO_RCVBUF)), size_ptr(NULL), delayedLoops(0),
             readPending(NULL), readPendingFunc(NULL) {}
