     Ssl::BumpMode sslBumpMode; ///< ssl_bump decision (Ssl::bumpEnd if n/a).
 
 #else
     bool switchedToHttps() const { return false; }
 #endif
 
+    /* clt_conn_tag=tag annotation access */
+    const SBuf &connectionTag() const { return connectionTag_; }
+    void connectionTag(const char *aTag) { connectionTag_ = aTag; }
+
+    /// handle a control message received by context from a peer and call back
+    virtual bool writeControlMsgAndCall(ClientSocketContext *context, HttpReply *rep, AsyncCall::Pointer &call) = 0;
+
+    /// ClientStream calls this to supply response header (once) and data
+    /// for the current ClientSocketContext.
+    virtual void handleReply(HttpReply *header, StoreIOBuffer receivedData) = 0;
+
+    /// remove no longer needed leading bytes from the input buffer
+    void consumeInput(const size_t byteCount);
+
+    /* TODO: Make the methods below (at least) non-public when possible. */
+
+    /// stop parsing the request and create context for relaying error info
+    ClientSocketContext *abortRequestParsing(const char *const errUri);
+
+    /// generate a fake CONNECT request with the given payload
+    /// at the beginning of the client I/O buffer
+    void fakeAConnectRequest(const char *reason, const SBuf &payload);
+
+    /* Registered Runner API */
+    virtual void startShutdown();
+    virtual void endingShutdown();
+
 protected:
     void startDechunkingRequest();
     void finishDechunkingRequest(bool withSuccess);
     void abortChunkedRequestBody(const err_type error);
     err_type handleChunkedRequestBody(size_t &putSize);
 
     void startPinnedConnectionMonitoring();
     void clientPinnedConnectionRead(const CommIoCbParams &io);
+#if USE_OPENSSL
+    /// Handles a ready-for-reading TLS squid-to-server connection that
+    /// we thought was idle.
+    /// \return false if and only if the connection should be closed.
+    bool handleIdleClientPinnedTlsRead();
+#endif
+
+    /// parse input buffer prefix into a single transfer protocol request
+    /// return NULL to request more header bytes (after checking any limits)
+    /// use abortRequestParsing() to handle parsing errors w/o creating request
+    virtual ClientSocketContext *parseOneRequest(Http::ProtocolVersion &ver) = 0;
+
+    /// start processing a freshly parsed request
+    virtual void processParsedRequest(ClientSocketContext *context, const Http::ProtocolVersion &ver) = 0;
+
+    /// returning N allows a pipeline of 1+N requests (see pipeline_prefetch)
+    virtual int pipelinePrefetchMax() const;
+
+    /// timeout to use when waiting for the next request
+    virtual time_t idleTimeout() const = 0;
+
+    BodyPipe::Pointer bodyPipe; ///< set when we are reading request body
 
 private:
-    int connReadWasError(comm_err_t flag, int size, int xerrno);
     int connFinishedWithConn(int size);
     void clientAfterReadingRequests();
     bool concurrentRequestQueueFilled() const;
 
+    void pinNewConnection(const Comm::ConnectionPointer &pinServer, HttpRequest *request, CachePeer *aPeer, bool auth);
+
+    /* PROXY protocol functionality */
+    bool proxyProtocolValidateClient();
+    bool parseProxyProtocolHeader();
+    bool parseProxy1p0();
+    bool parseProxy2p0();
+    bool proxyProtocolError(const char *reason);
+
+    /// whether PROXY protocol header is still expected
+    bool needProxyProtocolHeader_;
+
 #if USE_AUTH
     /// some user details that can be used to perform authentication on this connection
     Auth::UserRequest::Pointer auth_;
 #endif
 
-    HttpParser parser_;
-
-    // XXX: CBDATA plays with public/private and leaves the following 'private' fields all public... :(
-
-#if USE_SSL
+#if USE_OPENSSL
     bool switchedToHttps_;
     /// The SSL server host name appears in CONNECT request or the server ip address for the intercepted requests
     String sslConnectHostOrIp; ///< The SSL server host name as passed in the CONNECT request
-    String sslCommonName; ///< CN name for SSL certificate generation
+    SBuf sslCommonName_; ///< CN name for SSL certificate generation
     String sslBumpCertKey; ///< Key to use to store/retrieve generated certificate
 
     /// HTTPS server cert. fetching state for bump-ssl-server-first
     Ssl::ServerBump *sslServerBump;
     Ssl::CertSignAlgorithm signAlgorithm; ///< The signing algorithm to use
 #endif
