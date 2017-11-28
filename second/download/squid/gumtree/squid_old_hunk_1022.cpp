    /// and create the key for storing/retrieve the certificate to/from the cache
    void buildSslCertGenerationParams(Ssl::CertificateProperties &certProperties);
    /// Called when the client sends the first request on a bumped connection.
    /// Returns false if no [delayed] error should be written to the client.
    /// Otherwise, writes the error to the client and returns true. Also checks
    /// for SQUID_X509_V_ERR_DOMAIN_MISMATCH on bumped requests.
    bool serveDelayedError(ClientSocketContext *context);

    Ssl::BumpMode sslBumpMode; ///< ssl_bump decision (Ssl::bumpEnd if n/a).

#else
    bool switchedToHttps() const { return false; }
#endif

    /* clt_conn_tag=tag annotation access */
    const SBuf &connectionTag() const { return connectionTag_; }
    void connectionTag(const char *aTag) { connectionTag_ = aTag; }

    /// handle a control message received by context from a peer and call back
    virtual bool writeControlMsgAndCall(ClientSocketContext *context, HttpReply *rep, AsyncCall::Pointer &call) = 0;

    /// ClientStream calls this to supply response header (once) and data
    /// for the current ClientSocketContext.
    virtual void handleReply(HttpReply *header, StoreIOBuffer receivedData) = 0;

    /// remove no longer needed leading bytes from the input buffer
    void consumeInput(const size_t byteCount);

    /* TODO: Make the methods below (at least) non-public when possible. */

    /// stop parsing the request and create context for relaying error info
    ClientSocketContext *abortRequestParsing(const char *const errUri);

    /// generate a fake CONNECT request with the given payload
    /// at the beginning of the client I/O buffer
    void fakeAConnectRequest(const char *reason, const SBuf &payload);

    /* Registered Runner API */
    virtual void startShutdown();
    virtual void endingShutdown();

protected:
    void startDechunkingRequest();
    void finishDechunkingRequest(bool withSuccess);
    void abortChunkedRequestBody(const err_type error);
    err_type handleChunkedRequestBody(size_t &putSize);

    void startPinnedConnectionMonitoring();
    void clientPinnedConnectionRead(const CommIoCbParams &io);
#if USE_OPENSSL
    /// Handles a ready-for-reading TLS squid-to-server connection that
    /// we thought was idle.
