    void stopReceiving(const char *error);
    /// note response sending error and close as soon as we read the request
    void stopSending(const char *error);

    void expectNoForwarding(); ///< cleans up virgin request [body] forwarding state

    BodyPipe::Pointer expectRequestBody(int64_t size);
    virtual void noteMoreBodySpaceAvailable(BodyPipe::Pointer);
    virtual void noteBodyConsumerAborted(BodyPipe::Pointer);

    bool handleReadData(char *buf, size_t size);
    bool handleRequestBodyData();

    /**
     * Correlate the current ConnStateData object with the pinning_fd socket descriptor.
     */
    void pinConnection(const Comm::ConnectionPointer &pinServerConn, HttpRequest *request, CachePeer *peer, bool auth);
    /**
     * Decorrelate the ConnStateData object from its pinned CachePeer
     */
    void unpinConnection();
    /**
     * Checks if there is pinning info if it is valid. It can close the server side connection
     * if pinned info is not valid.
     \param request   if it is not NULL also checks if the pinning info refers to the request client side HttpRequest
     \param CachePeer      if it is not NULL also check if the CachePeer is the pinning CachePeer
     \return          The details of the server side connection (may be closed if failures were present).
