     clientStream_status_t socketState();
     void sendBody(HttpReply * rep, StoreIOBuffer bodyData);
     void sendStartOfMessage(HttpReply * rep, StoreIOBuffer bodyData);
     size_t lengthToSend(Range<int64_t> const &available);
     void noteSentBodyBytes(size_t);
     void buildRangeHeader(HttpReply * rep);
-    int fd() const;
     clientStreamNode * getTail() const;
     clientStreamNode * getClientReplyContext() const;
     void connIsFinished();
     void removeFromConnectionList(ConnStateData * conn);
     void deferRecipientForLater(clientStreamNode * node, HttpReply * rep, StoreIOBuffer receivedData);
     bool multipartRangeRequest() const;
     void registerWithConn();
+    void noteIoError(const int xerrno); ///< update state to reflect I/O error
+
+    /// starts writing 1xx control message to the client
+    void writeControlMsg(HttpControlMsg &msg);
+
+protected:
+    static IOCB WroteControlMsg;
+    void wroteControlMsg(const Comm::ConnectionPointer &conn, char *bufnotused, size_t size, comm_err_t errflag, int xerrno);
 
 private:
     CBDATA_CLASS(ClientSocketContext);
     void prepareReply(HttpReply * rep);
+    void packChunk(const StoreIOBuffer &bodyData, MemBuf &mb);
     void packRange(StoreIOBuffer const &, MemBuf * mb);
     void deRegisterWithConn();
     void doClose();
     void initiateClose(const char *reason);
+
+    AsyncCall::Pointer cbControlMsgSent; ///< notifies HttpControlMsg Source
+
     bool mayUseConnection_; /* This request may use the connection. Don't read anymore requests for now */
     bool connRegistered_;
 };
 
-/** A connection to a socket */
-class ConnStateData : public BodyProducer/*, public RefCountable*/
+
+class ConnectionDetail;
+
+/**
+ * Manages a connection to a client.
+ *
+ * Multiple requests (up to 2) can be pipelined. This object is responsible for managing
+ * which one is currently being fulfilled and what happens to the queue if the current one
+ * causes the client connection to be closed early.
+ *
+ * Act as a manager for the connection and passes data in buffer to the current parser.
+ * the parser has ambiguous scope at present due to being made from global functions
+ * I believe this object uses the parser to identify boundaries and kick off the
+ * actual HTTP request handling objects (ClientSocketContext, ClientHttpRequest, HttpRequest)
+ *
+ * If the above can be confirmed accurate we can call this object PipelineManager or similar
+ */
+class ConnStateData : public BodyProducer, public HttpControlMsgSink
 {
 
 public:
 
     ConnStateData();
     ~ConnStateData();
 
     void readSomeData();
     int getAvailableBufferLength() const;
     bool areAllContextsForThisConnection() const;
     void freeAllContexts();
+    void notifyAllContexts(const int xerrno); ///< tell everybody about the err
+    /// Traffic parsing
+    bool clientParseRequests();
     void readNextRequest();
     bool maybeMakeSpaceAvailable();
     ClientSocketContext::Pointer getCurrentContext() const;
     void addContextToQueue(ClientSocketContext * context);
     int getConcurrentRequestCount() const;
     bool isOpen() const;
+    void checkHeaderLimits();
 
-    int fd;
+    // HttpControlMsgSink API
+    virtual void sendControlMsg(HttpControlMsg msg);
 
-    /// chunk buffering and parsing algorithm state
-    typedef enum { chunkUnknown, chunkNone, chunkParsing, chunkReady, chunkError } DechunkingState;
+    // Client TCP connection details from comm layer.
+    Comm::ConnectionPointer clientConnection;
 
     struct In {
         In();
         ~In();
         char *addressToReadInto() const;
 
         ChunkedCodingParser *bodyParser; ///< parses chunked request body
-        MemBuf chunked; ///< contains unparsed raw (chunked) body data
-        MemBuf dechunked; ///< accumulates parsed (dechunked) content
         char *buf;
         size_t notYetUsed;
         size_t allocatedSize;
-        size_t chunkedSeen; ///< size of processed or ignored raw read data
-        DechunkingState dechunkingState; ///< request dechunking state
     } in;
 
-    int64_t bodySizeLeft();
-
-    /**
-     * Is this connection based authentication? if so what type it
-     * is.
+    /** number of body bytes we need to comm_read for the "current" request
+     *
+     * \retval 0         We do not need to read any [more] body bytes
+     * \retval negative  May need more but do not know how many; could be zero!
+     * \retval positive  Need to read exactly that many more body bytes
      */
-    auth_type_t auth_type;
+    int64_t mayNeedToReadMoreBody() const;
 
+#if USE_AUTH
     /**
-     * note this is ONLY connection based because NTLM is against HTTP spec.
+     * note this is ONLY connection based because NTLM and Negotiate is against HTTP spec.
      * the user details for connection based authentication
      */
-    AuthUserRequest *auth_user_request;
+    Auth::UserRequest::Pointer auth_user_request;
+#endif
 
     /**
      * used by the owner of the connection, opaque otherwise
      * TODO: generalise the connection owner concept.
      */
     ClientSocketContext::Pointer currentobject;
 
-    IpAddress peer;
-
-    IpAddress me;
-
-    IpAddress log_addr;
-    char rfc931[USER_IDENT_SZ];
+    Ip::Address log_addr;
     int nrequests;
 
     struct {
-        bool readMoreRequests;
+        bool readMore; ///< needs comm_read (for this request or new requests)
         bool swanSang; // XXX: temporary flag to check proper cleanup
     } flags;
     struct {
-        int fd;                 /* pinned server side connection */
+        Comm::ConnectionPointer serverConnection; /* pinned server side connection */
         char *host;             /* host name of pinned connection */
         int port;               /* port of pinned connection */
         bool pinned;             /* this connection was pinned */
         bool auth;               /* pinned for www authentication */
         struct peer *peer;             /* peer the connection goes via */
         AsyncCall::Pointer closeHandler; /*The close handler for pinned server side connection*/
     } pinning;
 
-    http_port_list *port;
+    AnyP::PortCfg *port;
 
     bool transparent() const;
-    void transparent(bool const);
     bool reading() const;
     void stopReading(); ///< cancels comm_read if it is scheduled
 
     /// true if we stopped receiving the request
     const char *stoppedReceiving() const { return stoppedReceiving_; }
     /// true if we stopped sending the response
