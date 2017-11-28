
private:
    CBDATA_CLASS(FtpStateData);

public:
    // these should all be private
    void start();
    void loginParser(const char *, int escaped);
    int restartable();
    void appendSuccessHeader();
    void hackShortcut(FTPSM * nextState);
    void failed(err_type, int xerrno);
    void failedErrorMessage(err_type, int xerrno);
    void unhack();
    void listingStart();
    void listingFinish();
    void scheduleReadControlReply(int);
    void handleControlReply();
    void readStor();
    char *htmlifyListEntry(const char *line);
    void parseListing();
    void dataComplete();
    void dataRead(const CommIoCbParams &io);
    int checkAuth(const HttpHeader * req_hdr);
    void checkUrlpath();
    void buildTitleUrl();
    void writeReplyBody(const char *, size_t len);
    void printfReplyBody(const char *fmt, ...);
    virtual int dataDescriptor() const;
    virtual void maybeReadVirginBody();
    virtual void closeServer();
    virtual void completeForwarding();
    virtual void abortTransaction(const char *reason);
    void processHeadResponse();
    void processReplyBody();
