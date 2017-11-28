    bool handleIdleClientPinnedTlsRead();
#endif

    /// parse input buffer prefix into a single transfer protocol request
    /// return NULL to request more header bytes (after checking any limits)
    /// use abortRequestParsing() to handle parsing errors w/o creating request
    virtual ClientSocketContext *parseOneRequest(Http::ProtocolVersion &ver) = 0;

    /// start processing a freshly parsed request
    virtual void processParsedRequest(ClientSocketContext *context, const Http::ProtocolVersion &ver) = 0;

    /// returning N allows a pipeline of 1+N requests (see pipeline_prefetch)
    virtual int pipelinePrefetchMax() const;

    /// timeout to use when waiting for the next request
    virtual time_t idleTimeout() const = 0;

    BodyPipe::Pointer bodyPipe; ///< set when we are reading request body

private:
    int connFinishedWithConn(int size);
    void clientAfterReadingRequests();
    bool concurrentRequestQueueFilled() const;

    void pinConnection(const Comm::ConnectionPointer &pinServerConn, const HttpRequest::Pointer &request);

    /* PROXY protocol functionality */
    bool proxyProtocolValidateClient();
    bool parseProxyProtocolHeader();
    bool parseProxy1p0();
    bool parseProxy2p0();
