     void stopReceiving(const char *error);
     /// note response sending error and close as soon as we read the request
     void stopSending(const char *error);
 
     void expectNoForwarding(); ///< cleans up virgin request [body] forwarding state
 
+    /* BodyPipe API */
     BodyPipe::Pointer expectRequestBody(int64_t size);
-    virtual void noteMoreBodySpaceAvailable(BodyPipe::Pointer);
-    virtual void noteBodyConsumerAborted(BodyPipe::Pointer);
+    virtual void noteMoreBodySpaceAvailable(BodyPipe::Pointer) = 0;
+    virtual void noteBodyConsumerAborted(BodyPipe::Pointer) = 0;
 
-    bool handleReadData(char *buf, size_t size);
+    bool handleReadData();
     bool handleRequestBodyData();
 
-    /**
-     * Correlate the current ConnStateData object with the pinning_fd socket descriptor.
-     */
-    void pinConnection(const Comm::ConnectionPointer &pinServerConn, HttpRequest *request, CachePeer *peer, bool auth);
-    /**
-     * Decorrelate the ConnStateData object from its pinned CachePeer
-     */
-    void unpinConnection();
+    /// Forward future client requests using the given server connection.
+    /// Optionally, monitor pinned server connection for remote-end closures.
+    void pinConnection(const Comm::ConnectionPointer &pinServerConn, HttpRequest *request, CachePeer *peer, bool auth, bool monitor = true);
+    /// Undo pinConnection() and, optionally, close the pinned connection.
+    void unpinConnection(const bool andClose);
+    /// Returns validated pinnned server connection (and stops its monitoring).
+    Comm::ConnectionPointer borrowPinnedConnection(HttpRequest *request, const CachePeer *aPeer);
     /**
      * Checks if there is pinning info if it is valid. It can close the server side connection
      * if pinned info is not valid.
      \param request   if it is not NULL also checks if the pinning info refers to the request client side HttpRequest
      \param CachePeer      if it is not NULL also check if the CachePeer is the pinning CachePeer
      \return          The details of the server side connection (may be closed if failures were present).
