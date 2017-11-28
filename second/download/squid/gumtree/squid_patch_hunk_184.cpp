 
 private:
     CBDATA_CLASS(FtpStateData);
 
 public:
     // these should all be private
-    void start();
+    virtual void start();
     void loginParser(const char *, int escaped);
     int restartable();
     void appendSuccessHeader();
     void hackShortcut(FTPSM * nextState);
     void failed(err_type, int xerrno);
     void failedErrorMessage(err_type, int xerrno);
     void unhack();
-    void listingStart();
-    void listingFinish();
     void scheduleReadControlReply(int);
     void handleControlReply();
     void readStor();
-    char *htmlifyListEntry(const char *line);
     void parseListing();
+    MemBuf *htmlifyListEntry(const char *line);
+    void completedListing(void);
     void dataComplete();
     void dataRead(const CommIoCbParams &io);
+
+    /// ignore timeout on CTRL channel. set read timeout on DATA channel.
+    void switchTimeoutToDataChannel();
+    /// create a data channel acceptor and start listening.
+    void listenForDataChannel(const Comm::ConnectionPointer &conn, const char *note);
+
     int checkAuth(const HttpHeader * req_hdr);
     void checkUrlpath();
     void buildTitleUrl();
     void writeReplyBody(const char *, size_t len);
     void printfReplyBody(const char *fmt, ...);
-    virtual int dataDescriptor() const;
+    virtual const Comm::ConnectionPointer & dataConnection() const;
     virtual void maybeReadVirginBody();
     virtual void closeServer();
     virtual void completeForwarding();
     virtual void abortTransaction(const char *reason);
     void processHeadResponse();
     void processReplyBody();
