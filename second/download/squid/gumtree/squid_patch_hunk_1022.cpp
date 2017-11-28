     /// and create the key for storing/retrieve the certificate to/from the cache
     void buildSslCertGenerationParams(Ssl::CertificateProperties &certProperties);
     /// Called when the client sends the first request on a bumped connection.
     /// Returns false if no [delayed] error should be written to the client.
     /// Otherwise, writes the error to the client and returns true. Also checks
     /// for SQUID_X509_V_ERR_DOMAIN_MISMATCH on bumped requests.
-    bool serveDelayedError(ClientSocketContext *context);
+    bool serveDelayedError(Http::Stream *);
 
     Ssl::BumpMode sslBumpMode; ///< ssl_bump decision (Ssl::bumpEnd if n/a).
 
+    /// Tls parser to use for client HELLO messages parsing on bumped
+    /// connections.
+    Security::HandshakeParser tlsParser;
 #else
     bool switchedToHttps() const { return false; }
 #endif
 
     /* clt_conn_tag=tag annotation access */
     const SBuf &connectionTag() const { return connectionTag_; }
     void connectionTag(const char *aTag) { connectionTag_ = aTag; }
 
     /// handle a control message received by context from a peer and call back
-    virtual bool writeControlMsgAndCall(ClientSocketContext *context, HttpReply *rep, AsyncCall::Pointer &call) = 0;
+    virtual bool writeControlMsgAndCall(HttpReply *rep, AsyncCall::Pointer &call) = 0;
 
     /// ClientStream calls this to supply response header (once) and data
-    /// for the current ClientSocketContext.
+    /// for the current Http::Stream.
     virtual void handleReply(HttpReply *header, StoreIOBuffer receivedData) = 0;
 
     /// remove no longer needed leading bytes from the input buffer
     void consumeInput(const size_t byteCount);
 
     /* TODO: Make the methods below (at least) non-public when possible. */
 
     /// stop parsing the request and create context for relaying error info
-    ClientSocketContext *abortRequestParsing(const char *const errUri);
+    Http::Stream *abortRequestParsing(const char *const errUri);
 
     /// generate a fake CONNECT request with the given payload
     /// at the beginning of the client I/O buffer
-    void fakeAConnectRequest(const char *reason, const SBuf &payload);
+    bool fakeAConnectRequest(const char *reason, const SBuf &payload);
+
+    /// generates and sends to tunnel.cc a fake request with a given payload
+    bool initiateTunneledRequest(HttpRequest::Pointer const &cause, Http::MethodType const method, const char *reason, const SBuf &payload);
+
+    /// whether tunneling of unsupported protocol is allowed for this connection
+    bool mayTunnelUnsupportedProto();
+
+    /// build a fake http request
+    ClientHttpRequest *buildFakeRequest(Http::MethodType const method, SBuf &useHost, unsigned short usePort, const SBuf &payload);
+
+    /// client data which may need to forward as-is to server after an
+    /// on_unsupported_protocol tunnel decision.
+    SBuf preservedClientData;
 
     /* Registered Runner API */
     virtual void startShutdown();
     virtual void endingShutdown();
 
 protected:
     void startDechunkingRequest();
     void finishDechunkingRequest(bool withSuccess);
     void abortChunkedRequestBody(const err_type error);
-    err_type handleChunkedRequestBody(size_t &putSize);
+    err_type handleChunkedRequestBody();
 
     void startPinnedConnectionMonitoring();
     void clientPinnedConnectionRead(const CommIoCbParams &io);
 #if USE_OPENSSL
     /// Handles a ready-for-reading TLS squid-to-server connection that
     /// we thought was idle.
