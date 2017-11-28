    clientStream_status_t socketState();
    void sendBody(HttpReply * rep, StoreIOBuffer bodyData);
    void sendStartOfMessage(HttpReply * rep, StoreIOBuffer bodyData);
    size_t lengthToSend(Range<int64_t> const &available);
    void noteSentBodyBytes(size_t);
    void buildRangeHeader(HttpReply * rep);
    int fd() const;
    clientStreamNode * getTail() const;
    clientStreamNode * getClientReplyContext() const;
    void connIsFinished();
    void removeFromConnectionList(ConnStateData * conn);
    void deferRecipientForLater(clientStreamNode * node, HttpReply * rep, StoreIOBuffer receivedData);
    bool multipartRangeRequest() const;
    void registerWithConn();

private:
    CBDATA_CLASS(ClientSocketContext);
    void prepareReply(HttpReply * rep);
    void packRange(StoreIOBuffer const &, MemBuf * mb);
    void deRegisterWithConn();
    void doClose();
    void initiateClose(const char *reason);
    bool mayUseConnection_; /* This request may use the connection. Don't read anymore requests for now */
    bool connRegistered_;
};

/** A connection to a socket */
class ConnStateData : public BodyProducer/*, public RefCountable*/
{

public:

    ConnStateData();
    ~ConnStateData();

    void readSomeData();
    int getAvailableBufferLength() const;
    bool areAllContextsForThisConnection() const;
    void freeAllContexts();
    void readNextRequest();
    bool maybeMakeSpaceAvailable();
    ClientSocketContext::Pointer getCurrentContext() const;
    void addContextToQueue(ClientSocketContext * context);
    int getConcurrentRequestCount() const;
    bool isOpen() const;

    int fd;

    /// chunk buffering and parsing algorithm state
    typedef enum { chunkUnknown, chunkNone, chunkParsing, chunkReady, chunkError } DechunkingState;

    struct In {
        In();
        ~In();
        char *addressToReadInto() const;

        ChunkedCodingParser *bodyParser; ///< parses chunked request body
        MemBuf chunked; ///< contains unparsed raw (chunked) body data
        MemBuf dechunked; ///< accumulates parsed (dechunked) content
        char *buf;
        size_t notYetUsed;
        size_t allocatedSize;
        size_t chunkedSeen; ///< size of processed or ignored raw read data
        DechunkingState dechunkingState; ///< request dechunking state
    } in;

    int64_t bodySizeLeft();

    /**
     * Is this connection based authentication? if so what type it
     * is.
     */
    auth_type_t auth_type;

    /**
     * note this is ONLY connection based because NTLM is against HTTP spec.
     * the user details for connection based authentication
     */
    AuthUserRequest *auth_user_request;

    /**
     * used by the owner of the connection, opaque otherwise
     * TODO: generalise the connection owner concept.
     */
    ClientSocketContext::Pointer currentobject;

    IpAddress peer;

    IpAddress me;

    IpAddress log_addr;
    char rfc931[USER_IDENT_SZ];
    int nrequests;

    struct {
        bool readMoreRequests;
        bool swanSang; // XXX: temporary flag to check proper cleanup
    } flags;
    struct {
        int fd;                 /* pinned server side connection */
        char *host;             /* host name of pinned connection */
        int port;               /* port of pinned connection */
        bool pinned;             /* this connection was pinned */
        bool auth;               /* pinned for www authentication */
        struct peer *peer;             /* peer the connection goes via */
        AsyncCall::Pointer closeHandler; /*The close handler for pinned server side connection*/
    } pinning;

    http_port_list *port;

    bool transparent() const;
    void transparent(bool const);
    bool reading() const;
    void stopReading(); ///< cancels comm_read if it is scheduled

    /// true if we stopped receiving the request
    const char *stoppedReceiving() const { return stoppedReceiving_; }
    /// true if we stopped sending the response
