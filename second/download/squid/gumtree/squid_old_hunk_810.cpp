#endif
    static void logReplyStatus(int tries, const Http::StatusCode status);
    void doneWithRetries();
    void completed();
    void retryOrBail();
    ErrorState *makeConnectingError(const err_type type) const;
    static void RegisterWithCacheManager(void);

public:
    StoreEntry *entry;
    HttpRequest *request;
    AccessLogEntryPointer al; ///< info for the future access.log entry

    static void abort(void*);
