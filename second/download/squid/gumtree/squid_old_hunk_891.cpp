    bool waitingForConnectResponse() const { return connectRespBuf; }
    /// Whether we are waiting for the CONNECT request/response exchange with the peer.
    bool waitingForConnectExchange() const { return waitingForConnectRequest() || waitingForConnectResponse(); }

    /// Whether the client sent a CONNECT request to us.
    bool clientExpectsConnectResponse() const {
        return !(request != NULL &&
                 (request->flags.interceptTproxy || request->flags.intercepted));
    }

    /// Sends "502 Bad Gateway" error response to the client,
    /// if it is waiting for Squid CONNECT response, closing connections.
    void informUserOfPeerError(const char *errMsg);

    class Connection
    {

    public:
        Connection() : len (0), buf ((char *)xmalloc(SQUID_TCP_SO_RCVBUF)), size_ptr(NULL) {}

        ~Connection();

        int bytesWanted(int lower=0, int upper = INT_MAX) const;
        void bytesIn(int const &);
#if USE_DELAY_POOLS
