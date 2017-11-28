     bool handleIdleClientPinnedTlsRead();
 #endif
 
     /// parse input buffer prefix into a single transfer protocol request
     /// return NULL to request more header bytes (after checking any limits)
     /// use abortRequestParsing() to handle parsing errors w/o creating request
-    virtual ClientSocketContext *parseOneRequest(Http::ProtocolVersion &ver) = 0;
+    virtual Http::Stream *parseOneRequest() = 0;
 
     /// start processing a freshly parsed request
-    virtual void processParsedRequest(ClientSocketContext *context, const Http::ProtocolVersion &ver) = 0;
+    virtual void processParsedRequest(Http::StreamPointer &) = 0;
 
     /// returning N allows a pipeline of 1+N requests (see pipeline_prefetch)
     virtual int pipelinePrefetchMax() const;
 
     /// timeout to use when waiting for the next request
     virtual time_t idleTimeout() const = 0;
 
+    /// Perform client data lookups that depend on client src-IP.
+    /// The PROXY protocol may require some data input first.
+    void whenClientIpKnown();
+
     BodyPipe::Pointer bodyPipe; ///< set when we are reading request body
 
 private:
-    int connFinishedWithConn(int size);
+    /* ::Server API */
+    virtual bool connFinishedWithConn(int size);
+    virtual void checkLogging();
+
     void clientAfterReadingRequests();
     bool concurrentRequestQueueFilled() const;
 
-    void pinConnection(const Comm::ConnectionPointer &pinServerConn, const HttpRequest::Pointer &request);
+    void pinNewConnection(const Comm::ConnectionPointer &pinServer, HttpRequest *request, CachePeer *aPeer, bool auth);
 
     /* PROXY protocol functionality */
     bool proxyProtocolValidateClient();
     bool parseProxyProtocolHeader();
     bool parseProxy1p0();
     bool parseProxy2p0();
