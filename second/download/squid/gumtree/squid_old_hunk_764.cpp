    Ssl::BumpMode sslBumpMode; ///< ssl_bump decision (Ssl::bumpEnd if n/a).

#else
    bool switchedToHttps() const { return false; }
#endif

protected:
    void startDechunkingRequest();
    void finishDechunkingRequest(bool withSuccess);
    void abortChunkedRequestBody(const err_type error);
    err_type handleChunkedRequestBody(size_t &putSize);

    void startPinnedConnectionMonitoring();
    void clientPinnedConnectionRead(const CommIoCbParams &io);

private:
    int connReadWasError(comm_err_t flag, int size, int xerrno);
    int connFinishedWithConn(int size);
    void clientAfterReadingRequests();
    bool concurrentRequestQueueFilled() const;

#if USE_AUTH
    /// some user details that can be used to perform authentication on this connection
    Auth::UserRequest::Pointer auth_;
#endif

    HttpParser parser_;

    // XXX: CBDATA plays with public/private and leaves the following 'private' fields all public... :(

#if USE_SSL
    bool switchedToHttps_;
    /// The SSL server host name appears in CONNECT request or the server ip address for the intercepted requests
    String sslConnectHostOrIp; ///< The SSL server host name as passed in the CONNECT request
    String sslCommonName; ///< CN name for SSL certificate generation
    String sslBumpCertKey; ///< Key to use to store/retrieve generated certificate

    /// HTTPS server cert. fetching state for bump-ssl-server-first
    Ssl::ServerBump *sslServerBump;
    Ssl::CertSignAlgorithm signAlgorithm; ///< The signing algorithm to use
#endif
