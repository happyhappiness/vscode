#endif
    static void logReplyStatus(int tries, const Http::StatusCode status);
    void doneWithRetries();
    void completed();
    void retryOrBail();
    ErrorState *makeConnectingError(const err_type type) const;
    void connectedToPeer(Security::EncryptorAnswer &answer);
    static void RegisterWithCacheManager(void);

    /// stops monitoring server connection for closure and updates pconn stats
    void closeServerConnection(const char *reason);

    void syncWithServerConn(const char *host);
    void syncHierNote(const Comm::ConnectionPointer &server, const char *host);

public:
    StoreEntry *entry;
    HttpRequest *request;
    AccessLogEntryPointer al; ///< info for the future access.log entry

