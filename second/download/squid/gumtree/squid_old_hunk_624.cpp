    /// Whether the client sent a CONNECT request to us.
    bool clientExpectsConnectResponse() const {
        return !(request != NULL &&
                 (request->flags.interceptTproxy || request->flags.intercepted));
    }

    class Connection
    {

    public:
        Connection() : len (0), buf ((char *)xmalloc(SQUID_TCP_SO_RCVBUF)), size_ptr(NULL) {}

