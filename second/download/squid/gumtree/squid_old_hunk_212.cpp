    void keepaliveAccounting(HttpReply *);
    void checkDateSkew(HttpReply *);

    bool continueAfterParsingHeader();
    void truncateVirginBody();

    virtual void haveParsedReplyHeaders();
    virtual void closeServer(); // end communication with the server
    virtual bool doneWithServer() const; // did we end communication?
    virtual void abortTransaction(const char *reason); // abnormal termination

    // consuming request body
    virtual void handleMoreRequestBodyAvailable();
    virtual void handleRequestBodyProducerAborted();

    void writeReplyBody();
    bool decodeAndWriteReplyBody();
    void doneSendingRequestBody();
    void requestBodyHandler(MemBuf &);
    virtual void sentRequestBody(const CommIoCbParams &io);
    void sendComplete(const CommIoCbParams &io);
    void httpStateConnClosed(const CommCloseCbParams &params);
    void httpTimeout(const CommTimeoutCbParams &params);

    mb_size_t buildRequestPrefix(HttpRequest * request,
                                 HttpRequest * orig_request,
                                 StoreEntry * entry,
                                 MemBuf * mb);
    static bool decideIfWeDoRanges (HttpRequest * orig_request);
    bool peerSupportsConnectionPinning() const;

    ChunkedCodingParser *httpChunkDecoder;
private:
    CBDATA_CLASS2(HttpStateData);
